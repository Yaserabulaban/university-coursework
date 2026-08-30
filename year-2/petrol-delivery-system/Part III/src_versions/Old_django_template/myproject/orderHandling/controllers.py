from django.shortcuts import render, get_object_or_404, redirect
from django.utils.timezone import now
from django.contrib.auth.models import User
from decimal import Decimal
from app.models import Order, Customer, Driver
from app.forms import OrderForm
from django.contrib.auth import get_user_model

class OrderController:

    @staticmethod
    def create_order(request):
        if request.method == "POST":
            newvendor_id = request.POST['vendor_id']
            newpetrol_type = request.POST['petrol_type']
            newquantity = Decimal(request.POST['quantity'])
            newdelivery_address = request.POST['delivery_address']

            neworder = Order(
                customer=request.user,
                vendor_id=newvendor_id,
                driver_id=None,
                petrol_type=newpetrol_type,
                quantity=newquantity,
                delivery_address=newdelivery_address
            )
            neworder.save()

            return redirect('createorderconfirmation')

        return render(request, 'createOrder/createorderform.html')

    @staticmethod
    def create_order_confirmation(request):
        if request.method == "POST":
            newvendor_id = request.POST['vendor_id']
            newpetrol_type = request.POST['petrol_type']
            newquantity = Decimal(request.POST['quantity'])
            newdelivery_address = request.POST['delivery_address']

            price_per_liter = {
                'RON95': Decimal(2.50),
                'RON97': Decimal(2.75),
                'RON100': Decimal(3.00),
                'Diesel': Decimal(2.25),
            }

            total_amount = newquantity * price_per_liter.get(newpetrol_type, 2.50)

            neworder = Order(
                customer=request.user,
                vendor_id=newvendor_id,
                driver_id=None,
                petrol_type=newpetrol_type,
                quantity=newquantity,
                order_date=now().date(),
                order_status="Waiting for vendor response.",
                total_amount=total_amount,
                delivery_address=newdelivery_address
            )
            neworder.save()

            context = {
                'order_id': neworder.order_id,
                'customer_id': request.user.id,
                'vendor_id': newvendor_id,
                'driver_id': None,
                'petrol_type': newpetrol_type,
                'quantity': newquantity,
                'order_date': neworder.order_date,
                'order_status': neworder.order_status,
                'total_amount': neworder.total_amount,
                'delivery_address': newdelivery_address,
            }
            return render(request, 'createOrder/createorderconfirmation.html', context)

        return render(request, 'createOrder/createorderform.html')

    @staticmethod
    def list_orders(request):
        try:
            user = request.user  # Lazy object
            user_id = user.pk  # Extract user ID explicitly

            # Fetch Customer using user_id
            customer = Customer.objects.filter(user_id=user_id).first()

            if not customer:
                return render(request, 'editOrder/listorders.html', {'orders': []})

            # Fetch Orders using Customer ID
            editable_orders = Order.objects.filter(
                customer_id=customer.user_id,  # Compare Customer ID, not object
                order_status__in=["Waiting for vendor response.","Waiting for driver response."]
            )

            return render(request, 'editOrder/listorders.html', {'orders': editable_orders})

        except Exception as e:
            print(f"DEBUG ERROR: {e}")
            return render(request, 'editOrder/listorders.html', {'orders': []})

    @staticmethod
    def edit_order(request, order_id):
        order = get_object_or_404(Order, order_id=order_id)

        if order.order_status in ["Out for delivery", "Completed"]:
            return render(request, 'editOrder/noteditable.html', {'order': order})

        if request.method == "POST":
            form = OrderForm(request.POST, instance=order)
            if form.is_valid():
                form.save()
                return redirect('listorders')

        else:
            form = OrderForm(instance=order)

        return render(request, 'editOrder/editorder.html', {'form': form, 'order': order})

    @staticmethod
    def view_orders(request):
        
        try:
            user = request.user  # Lazy object
            user_id = user.pk  # Extract user ID explicitly

            # Fetch Customer using user_id
            customer = Customer.objects.filter(user_id=user_id).first()

            if not customer:
                return render(request, 'viewOrder/vieworders.html', {'orders': []})

            # Fetch Orders using Customer ID
            editable_orders = Order.objects.filter(
                customer_id=customer.user_id,  # Compare Customer ID, not object
            )

            return render(request, 'viewOrder/vieworders.html', {'orders': editable_orders})

        except Exception as e:
            print(f"DEBUG ERROR: {e}")
            return render(request, 'viewOrder/vieworders.html', {'orders': []})

    @staticmethod
    def accept_decline_order(request):
        orders = Order.objects.filter(driver_id=None)
        return render(request, 'acceptDeclineOrder/acceptdeclineorder.html', {'orders': orders})

    @staticmethod
    def update_order_status(request, order_id, action):
        order = get_object_or_404(Order, order_id=order_id)

        try:
            # Get the driver associated with the logged-in user
            driver = Driver.objects.get(user_id=request.user.id)
        except Driver.DoesNotExist:
            # Handle case where the user is not a driver
            return redirect('acceptdeclineorder')  # or render an error message

        if action == "accept":
            order.driver_id = driver.driver_id  # Assign the driver's ID to the order
            order.order_status = "Waiting for pickup."
            driver.accepted_orders += 1  # Increase accepted orders count

        elif action == "decline":
            order.order_status = "Finding driver."  # No change in driver order count

        elif action == "complete":
            order.order_status = "Completed."
            driver.completed_orders += 1  # Increase completed orders count
            driver.accepted_orders -= 1  # Remove from accepted orders

        elif action == "cancelled":
            order.order_status = "Cancelled."
            driver.accepted_orders -= 1  # Decrease accepted orders count if canceled

        order.save()  # Save the order with the updated status
        driver.save()  # Save the driver with the updated order counts

        if action in ["accept", "decline"]:
            return redirect('acceptdeclineorder')
        else:
            return redirect("completeorcancelorder")
    
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
                order_status__in=["Waiting for pickup."])  # Compare using driver.id

            return render(request, 'updateOrderStatus/updateorderstatus.html', {'orders': editable_orders, 'driver': driver})

        except Exception as e:
            print(f"DEBUG ERROR: {e}")
            return render(request, 'updateOrderStatus/updateorderstatus.html', {'orders': [], 'driver': None})

    
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
