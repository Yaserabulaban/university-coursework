"""
Definition of models.
"""

from django.db import models
from django.utils.timezone import now
from django.contrib.auth.models import User
from decimal import Decimal

#sharing entity

class Item(models.Model):
    item_id = models.CharField(primary_key = True, max_length = 10)
    item_name = models.TextField()
    item_description = models.TextField(null = True, default = None, blank = True)
    def __str__(self):
        return str(self.item_id)

# Customer Model
class Customer(models.Model):
    customer_id = models.AutoField(primary_key=True)
    user = models.OneToOneField(User, on_delete=models.CASCADE)  # Links to Django's User model
    customer_name = models.CharField(max_length=100)
    customer_email = models.EmailField(unique=True)
    customer_phone = models.CharField(max_length=15)
    customer_address = models.TextField()

    def save(self, *args, **kwargs):
        super().save(*args, **kwargs)

    def __str__(self):
        return self.customer_name

# Vendor Model
class Vendor(models.Model):
    vendor_id = models.AutoField(primary_key=True)
    user = models.OneToOneField(User, on_delete=models.CASCADE)  # Links to Django's User model
    vendor_name = models.CharField(max_length=100)
    vendor_email = models.EmailField(unique=True)
    vendor_phone = models.CharField(max_length=15)
    vendor_location = models.TextField()

    def save(self, *args, **kwargs):
        super().save(*args, **kwargs)

    def __str__(self):
        return self.vendor_name

# Driver Model
class Driver(models.Model):
    driver_id = models.AutoField(primary_key=True)
    user = models.OneToOneField(User, on_delete=models.CASCADE)  # Links to Django's User model
    driver_name = models.CharField(max_length=100)
    driver_email = models.EmailField(unique=True)
    driver_phone = models.CharField(max_length=15)
    availability_status = models.BooleanField(default=True)  # True = Available, False = Not Available
    accepted_orders = models.IntegerField(default=0)  # Track accepted orders
    completed_orders = models.IntegerField(default=0)  # Track completed orders

    def save(self, *args, **kwargs):
        super().save(*args, **kwargs)

    def completed_orders_count(self):
        """Returns the number of completed orders for this driver"""
        return self.orders.filter(order_status="Completed.").count()

    def total_earnings(self):
        """Calculates total earnings as 5% of completed orders' total amount"""
        completed_orders = self.orders.filter(order_status="Completed.")
        return sum(order.total_amount * Decimal(0.05) for order in completed_orders)

    def __str__(self):
        return self.driver_name


class Order(models.Model):
    order_id = models.AutoField(primary_key=True)  # Auto-increment order ID
    customer = models.ForeignKey(Customer, on_delete=models.CASCADE)  # Link to user model
    vendor = models.ForeignKey(Vendor, on_delete=models.CASCADE, related_name='orders', null=True, blank=True)  # Allow null values
    driver = models.ForeignKey(Driver, on_delete=models.CASCADE, related_name='orders', null=True, blank=True)  # Allow null values
    petrol_type = models.CharField(max_length=10, choices=[
        ('RON95', 'RON 95'),
        ('RON97', 'RON 97'),
        ('RON100', 'RON 100'),
        ('Diesel', 'Diesel'),
    ])
    quantity = models.DecimalField(max_digits=10, decimal_places=2)
    order_date = models.DateField(default=now)  # Auto-set to current date
    order_status = models.TextField(default="Waiting for vendor response.")  # Default status
    total_amount = models.DecimalField(max_digits=10, decimal_places=2, blank=True, null=True)
    delivery_address = models.CharField(max_length=200)

    def save(self, *args, **kwargs):
        super().save(*args, **kwargs)  # Call the parent save() method

    def __str__(self):
        return f"Order {self.order_id} - {self.customer.username}"
    

class Stock(models.Model):
    PETROL_TYPES = [
        ('RON95', 'RON 95'),
        ('RON97', 'RON 97'),
        ('RON100', 'RON 100'),
        ('Diesel', 'Diesel'),
    ]
    
    stock_id = models.AutoField(primary_key=True)
    vendor = models.ForeignKey(Vendor, on_delete=models.CASCADE, related_name="stock")  # Many stocks belong to one vendor
    petrol_type = models.CharField(max_length=50, choices=PETROL_TYPES)  # Defines fuel type (e.g., Petrol, Diesel)
    quantity = models.DecimalField(max_digits=10, decimal_places=2)  # Fuel quantity in liters
    price_per_liter = models.DecimalField(max_digits=6, decimal_places=2)  # Price per liter

    def __str__(self):
        return f"{self.petrol_type} - {self.vendor.vendor_name}"

    class Meta:
        unique_together = ('vendor', 'petrol_type')  # Prevent duplicate fuel types for a vendor

class Report(models.Model):
    report_id = models.AutoField(primary_key=True)
    vendor = models.ForeignKey(Vendor, on_delete=models.CASCADE, related_name="reports")  # Foreign key to Vendor
    report_date = models.DateField()  # Date when the report was generated
    total_orders = models.IntegerField()  # Total number of orders in the period
    total_revenue = models.DecimalField(max_digits=10, decimal_places=2)  # Total revenue

    def __str__(self):
        return f"Report {self.report_id} for {self.vendor.vendor_name} - {self.report_date}"
    
class Payment(models.Model):
    payment_id = models.AutoField(primary_key=True)  # Auto-incrementing primary key
    order_id = models.ForeignKey(Order, on_delete=models.CASCADE)  # Foreign Key to Order
    customer_id = models.ForeignKey(Customer, on_delete=models.CASCADE)  # Foreign Key to Customer
    payment_date = models.DateField()  # Date of the payment
    total_amount = models.DecimalField(max_digits=10, decimal_places=2)  # Total paid amount
    payment_method_choices = [
        ('Credit', 'Credit'),
        ('Cash', 'Cash'),
        ('Ewallet', 'Ewallet'),
    ]
    payment_method = models.CharField(max_length=255, choices=payment_method_choices)  # Payment method
    payment_status_choices = [
        ('Completed', 'Completed'),
        ('Pending', 'Pending'),
    ]
    payment_status = models.CharField(max_length=255, choices=payment_status_choices)  # Payment status

    def __str__(self):
        return f"Payment {self.payment_id} for Order {self.order_id}"