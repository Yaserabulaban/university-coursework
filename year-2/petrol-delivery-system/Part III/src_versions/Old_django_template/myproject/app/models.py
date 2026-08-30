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
    customer = models.ForeignKey(User, on_delete=models.CASCADE)  # Link to user model
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
        # Price per liter based on petrol type
        base_price = 2.50  # Example base price
        price_per_liter = {
            'RON95': Decimal(base_price),
            'RON97': Decimal(base_price + 0.25),
            'RON100': Decimal(base_price + 0.50),
            'Diesel': Decimal(base_price - 0.25),
        }
        self.total_amount = self.quantity * price_per_liter.get(self.petrol_type, base_price)
        super().save(*args, **kwargs)  # Call the parent save() method

    def __str__(self):
        return f"Order {self.order_id} - {self.customer.username}"