from django.shortcuts import render, redirect

# Create your views here.
from django.http import HttpRequest
from django.template import RequestContext
from datetime import datetime
from app.forms import UserForm, CustomerForm, VendorForm, DriverForm
from django.contrib.auth.decorators import login_required
from django.contrib.auth.models import User
from django.contrib.auth import login
from app.models import Customer, Vendor, Driver
from django.contrib.auth.models import Group

def home(request):
    """Renders the home page."""
    assert isinstance(request, HttpRequest)
    if request.user.is_authenticated:
        return(redirect('/menu'))
    else:
        return render(
            request,
            'app/index.html',
            {
                'title':'Home Page',
                'year': datetime.now().year,
            }
        )

def contact(request):
    """Renders the contact page."""
    assert isinstance(request, HttpRequest)
    return render(
        request,
        'app/contact.html',
        {
            'title':'Contact',
            'message':'Dr. Yeoh.',
            'year':datetime.now().year,
        }
    )

def about(request):
    """Renders the about page."""
    assert isinstance(request, HttpRequest)
    return render(
        request,
        'app/about.html',
        {
            'title':'ABC System',
            'message':'This application processes ...',
            'year':datetime.now().year,
        }
    )

@login_required
def menu(request):
    check_customer = request.user.groups.filter(name='customer').exists()
    check_driver = request.user.groups.filter(name='driver').exists()
    check_vendor = request.user.groups.filter(name='vendor').exists()

    context = {
            'title':'Main Menu',
            'is_customer': check_customer,
            'is_driver' : check_driver,
            'is_vendor' : check_vendor,
            'year':datetime.now().year,
        }
    context['user'] = request.user

    return render(request,'app/menu.html',context)

def choose_role(request):
    return render(request, 'app/choose_role.html')

# Create Customer
def create_customer(request):
    # Initialize the forms in the beginning to ensure they are always available
    user_form = UserForm()
    customer_form = CustomerForm()

    if request.method == "POST":
        # Create user
        user_form = UserForm(request.POST)
        if user_form.is_valid():
            user = user_form.save(commit=False)
            user.set_password(user_form.cleaned_data['password'])
            user.save()

            # Assign the user to the 'customer' group
            customer_group = Group.objects.get(name='customer')
            user.groups.add(customer_group)

            # Create customer
            customer_form = CustomerForm(request.POST)
            if customer_form.is_valid():
                customer = customer_form.save(commit=False)
                customer.user = user
                customer.save()

            login(request, user)  # Log the user in after registration
            return redirect('home')  # Redirect to home or wherever you want

    return render(request, 'app/create_customer.html', {
        'user_form': user_form,
        'customer_form': customer_form,  # Ensure the form is always passed to the template
    })

# Create Vendor
def create_vendor(request):
    # Initialize the forms in the beginning to ensure they are always available
    user_form = UserForm()
    vendor_form = VendorForm()

    if request.method == "POST":
        # Create user
        user_form = UserForm(request.POST)
        if user_form.is_valid():
            user = user_form.save(commit=False)
            user.set_password(user_form.cleaned_data['password'])
            user.save()

            # Assign the user to the 'vendor' group
            vendor_group = Group.objects.get(name='vendor')
            user.groups.add(vendor_group)

            # Create Vendor
            vendor_form = VendorForm(request.POST)
            if vendor_form.is_valid():
                vendor = vendor_form.save(commit=False)
                vendor.user = user
                vendor.save()

            login(request, user)  # Log the user in after registration
            return redirect('home')  # Redirect to home or wherever you want

    return render(request, 'app/create_vendor.html', {
        'user_form': user_form,
        'vendor_form': vendor_form,  # Ensure the form is always passed to the template
    })

# Create Driver
def create_driver(request):
    # Initialize the forms in the beginning to ensure they are always available
    user_form = UserForm()
    driver_form = DriverForm()

    if request.method == "POST":
        # Create user
        user_form = UserForm(request.POST)
        if user_form.is_valid():
            user = user_form.save(commit=False)
            user.set_password(user_form.cleaned_data['password'])
            user.save()

            # Assign the user to the 'driver' group
            driver_group = Group.objects.get(name='driver')
            user.groups.add(driver_group)

            # Create driver
            driver_form = DriverForm(request.POST)
            if driver_form.is_valid():
                driver = driver_form.save(commit=False)
                driver.user = user
                driver.save()

            login(request, user)  # Log the user in after registration
            return redirect('home')  # Redirect to home or wherever you want

    return render(request, 'app/create_driver.html', {
        'user_form': user_form,
        'driver_form': driver_form,  # Ensure the form is always passed to the template
    })

