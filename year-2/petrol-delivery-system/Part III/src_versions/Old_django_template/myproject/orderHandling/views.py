from django.contrib.auth.decorators import login_required
from .controllers import OrderController, AccountController
from django.shortcuts import render, get_object_or_404
from app.models import Driver

@login_required
def createorderform(request):
    return OrderController.create_order(request)

@login_required
def createorderconfirmation(request):
    return OrderController.create_order_confirmation(request)

@login_required
def listorders(request):
    return (OrderController.list_orders(request))

@login_required
def editorder(request, order_id):
    return OrderController.edit_order(request, order_id)

@login_required
def vieworders(request):
    return OrderController.view_orders(request)

@login_required
def acceptdeclineorder(request):
    return OrderController.accept_decline_order(request)

@login_required
def updateorderstatus(request, order_id, action):
    return OrderController.update_order_status(request, order_id, action)

@login_required
def viewordersdriver(request):
    return OrderController.view_orders_driver(request)

@login_required
def completeorcancelorder(request):
    return OrderController.complete_or_cancel_order(request)

@login_required
def editaccountdetails(request):
    return AccountController.edit_account_details(request)

@login_required
def driverperformance(request):
    return AccountController.driver_performance(request)