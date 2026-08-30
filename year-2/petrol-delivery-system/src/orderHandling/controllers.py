from django.shortcuts import render, get_object_or_404, redirect
from django.utils.timezone import now
from django.contrib.auth.models import User
from decimal import Decimal, ROUND_HALF_UP
from app.models import Order, Customer, Driver, Vendor, Stock, Report, Payment
from app.forms import OrderForm
from django.contrib.auth import get_user_model
from django.utils.dateparse import parse_date
from datetime import date
from django.http import HttpResponse
from django.contrib import messages


class OrderController:
    rejected_orders = {}

    from decimal import Decimal

    @staticmethod
    def create_order(request):
        if request.method == "POST":
            newvendor_id = request.POST.get('vendor_id')
            newpetrol_type = request.POST['petrol_type']
            newquantity = Decimal(request.POST['quantity'])
            newdelivery_address = request.POST['delivery_address']

            # Ensure vendor_id is provided
            print(newvendor_id)
            if not newvendor_id:
                return render(request, 'createOrder/createorderform.html', {
                    'vendors': Vendor.objects.all(),
                    'error_message': "Please select a vendor.",
                })

            # Fetch customer ID from the logged-in user
            customer = Customer.objects.filter(user_id=request.user.id).first()
            if not customer:
                return redirect('error_page')  # Redirect if customer not found

            # Fetch the selected vendor
            vendor = Vendor.objects.get(vendor_id=newvendor_id)

            try:
                # Fetch the selected vendor's stock for the petrol type
                stock = Stock.objects.get(vendor=vendor, petrol_type=newpetrol_type)
            except Stock.DoesNotExist:
                return render(request, 'createOrder/createorderform.html', {
                    'vendors': Vendor.objects.all(),
                    'error_message': "Stock not available for the selected fuel type at this vendor.",
                    'selected_vendor': vendor,
                })

            # Check if the requested quantity is available
            if stock.quantity < newquantity:
                return render(request, 'createOrder/createorderform.html', {
                    'vendors': Vendor.objects.all(),
                    'error_message': "Requested quantity is not available at this vendor.",
                    'selected_vendor': vendor,
                    'selected_stock': stock,
                })

            # Calculate the total amount (quantity * price per liter)
            total_amount = newquantity * stock.price_per_liter

            # Proceed to create the order if stock is sufficient
            neworder = Order.objects.create(
                customer=customer,
                vendor=vendor,
                driver=None,
                petrol_type=newpetrol_type,
                quantity=newquantity,
                order_date=now().date(),
                order_status="Waiting for vendor response.",
                total_amount=total_amount,
                delivery_address=newdelivery_address
            )

            # Redirect to the order confirmation page with the new order_id
            return redirect('paymentpage', order_id=neworder.order_id, total_amount=neworder.total_amount)
        
        # If GET request, show the form
        vendors = Vendor.objects.all()
        return render(request, 'createOrder/createorderform.html', {
            'vendors': vendors
        })

    @staticmethod
    def create_order_confirmation(request, order_id):
        try:
            order = Order.objects.get(order_id=order_id)
        except Order.DoesNotExist:
            return redirect('error_page')  # Handle case where order doesn't exist

        context = {
            'order_id': order.order_id,
            'customer_id': order.customer.customer_id,  
            'vendor_id': order.vendor.vendor_id,
            'driver_id': order.driver.id if order.driver else None,
            'petrol_type': order.petrol_type,
            'quantity': order.quantity,
            'order_date': order.order_date,
            'order_status': order.order_status,
            'total_amount': order.total_amount,
            'delivery_address': order.delivery_address,
        }
        return render(request, 'createOrder/createorderconfirmation.html', context)

    def payment_page(request, order_id, total_amount):
        # Show payment page with the order and amount details
        return render(request, 'paymentPage/paymentpage.html', {
            'order_id': order_id,
            'total_amount': total_amount
        })

    def process_payment(request):
        if request.method == "POST":
            order_id = request.POST.get('order_id')
            payment_method = request.POST.get('payment_method')
            total_amount = request.POST.get('total_amount')
            customer_id = Customer.objects.filter(user_id=request.user.id).first()
            order = Order.objects.filter(order_id=order_id).first()

            # Create the Payment record
            new_payment = Payment(
                order_id=order,
                customer_id=customer_id,
                payment_date=now().date(),
                total_amount=total_amount,
                payment_method=payment_method,
                payment_status="Completed"
            )
            new_payment.save()

            # Redirect to order confirmation page
            return redirect('createorderconfirmation', order_id=order_id)

        return HttpResponse("Invalid request")

    @staticmethod
    def list_orders(request):
        try:
            user = request.user  # Lazy object
            user_id = user.pk  # Extract user ID explicitly

            # Fetch customer ID from the logged-in user
            customer = Customer.objects.filter(user_id = user_id).first()
            print(customer.customer_id)
            if not customer:
                return render(request, 'editOrder/listorders.html', {'orders': []})

            # Fetch Orders using Customer ID
            editable_orders = Order.objects.filter(
                customer_id=customer.customer_id,  # Compare using stored customer_id
                order_status__in=["Waiting for vendor response.", "Finding driver."]
            )

            return render(request, 'editOrder/listorders.html', {'orders': editable_orders})

        except Exception as e:
            print(f"DEBUG ERROR: {e}")
            return render(request, 'editOrder/listorders.html', {'orders': []})

    @staticmethod
    def edit_order(request, order_id):
        # Fetch the order
        order = get_object_or_404(Order, order_id=order_id)

        # Check if the order is in a non-editable state
        if order.order_status in ["Waiting for pickup and delivery.", "Completed"]:
            return render(request, 'editOrder/noteditable.html', {'order': order})

        # When the form is submitted (POST request)
        if request.method == "POST":
            # Get the vendor and petrol type from the form submission
            vendor_id = order.vendor.vendor_id
            petrol_type = request.POST.get('petrol_type')
            quantity = Decimal(request.POST.get('quantity'))  # Assuming it's submitted as a number
            delivery_address = request.POST.get('delivery_address')

            # Get the selected vendor
            vendor = get_object_or_404(Vendor, vendor_id=vendor_id)

            # Get the stock record for the vendor and petrol type
            try:
                stock = Stock.objects.get(vendor=vendor, petrol_type=petrol_type)
            except Stock.DoesNotExist:
                return render(request, 'editOrder/editorder.html', {'error_message': 'Selected vendor does not have the specified fuel type.'})

            # Calculate the total amount (price per liter * quantity)
            total_amount = stock.price_per_liter * quantity

            # Update the order details
            order.petrol_type = petrol_type
            order.quantity = quantity
            order.delivery_address = delivery_address
            order.total_amount = total_amount  # Update the total amount

            order.save()  # Save the updated order

            # Redirect to the order list or confirmation page
            return redirect('listorders')  # or another relevant page like 'orderconfirmation'

        else:
            # If it's a GET request, just display the form to edit the order
            form = OrderForm(instance=order)

        return render(request, 'editOrder/editorder.html', {'form': form, 'order': order})

    @staticmethod
    def view_orders(request):
        try:
            # Fetch customer ID from the logged-in user
            customer = Customer.objects.filter(user_id=request.user.id).first()
            if not customer:
                return render(request, 'viewOrder/vieworders.html', {'orders': []})

            # Fetch Orders using Customer ID
            orders = Order.objects.filter(
                customer_id=customer.customer_id  # Compare using stored customer_id
            )

            return render(request, 'viewOrder/vieworders.html', {'orders': orders})

        except Exception as e:
            print(f"DEBUG ERROR: {e}")
            return render(request, 'viewOrder/vieworders.html', {'orders': []})

    @staticmethod
    def accept_decline_order_vendor(request):
        try:
            user = request.user  # Lazy object
            user_id = user.pk  # Extract user ID explicitly

            # Fetch Customer using user_id
            vendor = Vendor.objects.filter(user_id=user_id).first()

            if not vendor:
                return render(request, 'acceptDeclineOrder/acceptdeclineordervendor.html', {'orders': []})

            # Fetch Orders using vendor ID
            orders = Order.objects.filter(
                vendor_id=vendor.vendor_id,  # Compare vendor ID, not object
                order_status__in=["Waiting for vendor response."],
            )

            return render(request, 'acceptDeclineOrder/acceptdeclineordervendor.html', {'orders': orders})

        except Exception as e:
            print(f"DEBUG ERROR: {e}")
            return render(request, 'acceptDeclineOrder/acceptdeclineordervendor.html', {'orders': []})
    
    @staticmethod
    def accept_decline_order_driver(request):
        try:
            driver = Driver.objects.get(user_id=request.user.id)
        except Driver.DoesNotExist:
            return redirect('home')  # Or render an error message if the user is not a driver

        # Get the list of orders that are available to be accepted
        orders = Order.objects.filter(order_status="Finding driver.")

        # Filter out orders the current driver has rejected
        rejected_order_ids = OrderController.rejected_orders.get(driver.driver_id, set())
        orders = orders.exclude(order_id__in=rejected_order_ids)
        return render(request, 'acceptDeclineOrder/acceptdeclineorderdriver.html', {'orders': orders})

    @staticmethod
    def update_order_status_driver(request, order_id, action):
        order = get_object_or_404(Order, order_id=order_id)

        try:
            # Get the driver associated with the logged-in user
            driver = Driver.objects.get(user_id=request.user.id)
        except Driver.DoesNotExist:
            # Handle case where the user is not a driver
            return redirect('acceptdeclineorderdriver')  # or render an error message

        if action == "accept":
            order.driver_id = driver.driver_id  # Assign the driver's ID to the order
            order.order_status = "Waiting for pickup and delivery."
            driver.accepted_orders += 1  # Increase accepted orders count

        elif action == "decline":
            order.order_status = "Finding driver."  # No change in driver order count
            if driver.driver_id not in OrderController.rejected_orders:
                OrderController.rejected_orders[driver.driver_id] = set()
            OrderController.rejected_orders[driver.driver_id].add(order_id)

        elif action == "complete":
            order.order_status = "Completed."
            driver.completed_orders += 1  # Increase completed orders count
            driver.accepted_orders -= 1  # Remove from accepted orders

        elif action == "cancelled":
            order.order_status = "Finding driver."
            driver.accepted_orders -= 1  # Decrease accepted orders count if canceled
            if driver.driver_id not in OrderController.rejected_orders:
                OrderController.rejected_orders[driver.driver_id] = set()
            OrderController.rejected_orders[driver.driver_id].add(order_id)

        order.save()  # Save the order with the updated status
        driver.save()  # Save the driver with the updated order counts

        if action in ["accept", "decline"]:
            return redirect('acceptdeclineorderdriver')
        else:
            return redirect("completeorcancelorder")
        
    @staticmethod
    def update_order_status_vendor(request, order_id, action):
        order = get_object_or_404(Order, order_id=order_id)

        try:
            # Get the vendor associated with the logged-in user
            vendor = Vendor.objects.get(user_id=request.user.id)
        except Vendor.DoesNotExist:
            return redirect('acceptdeclineordervendor')  # Redirect if user is not a vendor

        if action == "accept":
            try:
                # Fetch the stock for the vendor and petrol type
                stock = Stock.objects.get(vendor=vendor, petrol_type=order.petrol_type)
                
                # Check if enough stock is available
                if stock.quantity >= order.quantity:
                    stock.quantity -= order.quantity  # Deduct the ordered amount
                    stock.save()  # Save the updated stock value
                    order.order_status = "Finding driver."
                else:
                    # If not enough stock, show an error message
                    messages.error(request, "Insufficient stock to accept this order.")
                    return redirect('acceptdeclineordervendor')

            except Stock.DoesNotExist:
                # If stock entry does not exist, return an error
                messages.error(request, "No stock available for this petrol type.")
                return redirect('acceptdeclineordervendor')

        elif action == "decline":
            order.order_status = "Declined by vendor."

        order.save()  # Save the updated order status
        return redirect('acceptdeclineordervendor')

        
    
    @staticmethod
    def view_orders_driver(request):
        try:
            user = request.user  # Lazy object
            user_id = user.pk  # Extract user ID explicitly

            # Fetch Driver using user_id
            driver = Driver.objects.filter(user_id=user_id).first()

            if not driver:
                # If no driver is associated with the user, return an empty list
                return render(request, 'viewOrder/viewordersdriver.html', {'orders': []})
            
            print(f"Driver found: {driver}")  # Debug print to ensure the driver was found

            # Fetch Orders using driver_id (from Driver table)
            editable_orders = Order.objects.filter(driver_id=driver.driver_id)  # Compare using driver.id

            return render(request, 'viewOrder/viewordersdriver.html', {'orders': editable_orders, 'driver': driver})

        except Exception as e:
            print(f"DEBUG ERROR: {e}")
            return render(request, 'viewOrder/viewordersdriver.html', {'orders': [], 'driver': None})


    @staticmethod
    def complete_or_cancel_order(request):
        try:
            user = request.user  # Lazy object
            user_id = user.pk  # Extract user ID explicitly

            # Fetch Driver using user_id
            driver = Driver.objects.filter(user_id=user_id).first()

            if not driver:
                # If no driver is associated with the user, return an empty list
                return render(request, 'updateOrderStatus/updateorderstatus.html', {'orders': []})
            
            print(f"Driver found: {driver}")  # Debug print to ensure the driver was found

            # Fetch Orders using driver_id (from Driver table)
            editable_orders = Order.objects.filter(
                driver_id=driver.driver_id, 
                order_status__in=["Waiting for pickup and delivery."])  # Compare using driver.id

            return render(request, 'updateOrderStatus/updateorderstatus.html', {'orders': editable_orders, 'driver': driver})

        except Exception as e:
            print(f"DEBUG ERROR: {e}")
            return render(request, 'updateOrderStatus/updateorderstatus.html', {'orders': [], 'driver': None})
        
    @staticmethod
    def view_orders_vendor(request):
        try:
            user = request.user  # Lazy object
            user_id = user.pk  # Extract user ID explicitly

            # Fetch Driver using user_id
            vendor = Vendor.objects.filter(user_id=user_id).first()

            if not vendor:
                # If no vendor is associated with the user, return an empty list
                return render(request, 'viewOrder/viewordersvendor.html', {'orders': []})
            
            print(f"Vendor found: {vendor}")  # Debug print to ensure the driver was found

            # Fetch Orders using driver_id (from Driver table)
            editable_orders = Order.objects.filter(vendor_id=vendor.vendor_id)  # Compare using driver.id

            status_filter = request.GET.get('status', '')  # Get filter from request

            if status_filter:  # Apply filter if a status is selected
                editable_orders = editable_orders.filter(order_status=status_filter)

            return render(request, 'viewOrder/viewordersvendor.html', {
                'orders': editable_orders,
                'selected_status': status_filter,
            })
        

            '''return render(request, 'viewOrder/viewordersvendor.html', {'orders': editable_orders, 'vendor': vendor})'''

        except Exception as e:
            print(f"DEBUG ERROR: {e}")
            return render(request, 'viewOrder/viewordersvendor.html', {'orders': [], 'driver': None})

    
class AccountController:

    @staticmethod
    def edit_account_details(request):
        # Ensure user is authenticated
        if not request.user.is_authenticated:
            return redirect('login')  # Redirect to login if user is not authenticated

        # Fetch the customer linked to the current user
        customer = Customer.objects.filter(user=request.user).first()
        if not customer:
            return redirect('home')  # Redirect if no customer profile exists

        if request.method == "POST":
            # Get form data
            new_name = request.POST.get('customer_name')
            new_email = request.POST.get('customer_email')
            new_phone = request.POST.get('customer_phone')
            new_address = request.POST.get('customer_address')

            # Update customer details
            customer.customer_name = new_name
            customer.customer_email = new_email
            customer.customer_phone = new_phone
            customer.customer_address = new_address
            customer.save()

            return redirect('editaccountdetails')  # Redirect to account details page after saving

        return render(request, 'account/editaccount.html', {'customer': customer})
    
    @staticmethod
    def driver_performance(request):
        try:
            print("Debug: Fetching driver performance for user:", request.user)
            driver = get_object_or_404(Driver, user=request.user)
            print("Debug: Driver found:", driver)
            return render(request, "driverPerformance/driverperformance.html", {"driver": driver})
        except Exception as e:
            print("Debug: Error fetching driver performance:", str(e))

class ReportController:
    @staticmethod
    def generate_report(request):
        user = request.user
        vendor = Vendor.objects.filter(user=user).first()

        if not vendor:
            return render(request, 'report/generatereport.html', {'error': "Vendor not found."})

        report = None

        if request.method == "POST":
            start_date = request.POST.get("start_date")
            end_date = request.POST.get("end_date")

            if start_date and end_date:
                start_date = parse_date(start_date)
                end_date = parse_date(end_date)

                # Ensure the end date is not before the start date
                if start_date > end_date:
                    return render(request, 'report/generatereport.html', {'error': "End date must be after start date."})

                # Fetch orders within the selected date range
                orders = Order.objects.filter(vendor=vendor, order_date__range=[start_date, end_date])

                total_orders = orders.count()
                total_revenue = sum(order.total_amount for order in orders) * Decimal(0.95)
                total_revenue = total_revenue.quantize(Decimal('0.01'), rounding=ROUND_HALF_UP)  # 95% of total revenue

                # Save report to the database
                report = Report.objects.create(
                    vendor=vendor,
                    report_date=date.today(),
                    total_orders=total_orders,
                    total_revenue=total_revenue
                )

        return render(request, 'report/generatereport.html', {'vendor': vendor, 'report': report})

class StockController:
    def submit_availability_status(request):
        if request.method == "POST":
            # Get logged-in user's vendor info
            user = request.user  
            vendor = Vendor.objects.filter(user_id=user.pk).first()

            if not vendor:
                return render(request, 'app/submit_availability_status.html', {'error': 'Vendor not found.'})

            petrol_type = request.POST.get("petrol_type")
            quantity = request.POST.get("quantity")
            price_per_liter = request.POST.get("price")

            try:
                quantity = float(quantity)
                price_per_liter = float(price_per_liter)

                if quantity <= 0 or price_per_liter <= 0:
                    return render(request, 'updateOrderStatus/submitavailabilitystatus.html', {'error': 'Invalid quantity or price value.'})

                # Check if stock for this fuel type already exists
                stock, created = Stock.objects.update_or_create(
                    vendor=vendor,
                    petrol_type=petrol_type,
                    defaults={'quantity': quantity, 'price_per_liter': price_per_liter}
                )

                message = "Stock updated successfully." if not created else "Stock added successfully."
                return render(request, 'updateOrderStatus/submitavailabilitystatus.html', {'message': message})

            except ValueError:
                return render(request, 'updateOrderStatus/submitavailabilitystatus.html', {'error': 'Invalid numeric values provided.'})

        return render(request, 'updateOrderStatus/submitavailabilitystatus.html')