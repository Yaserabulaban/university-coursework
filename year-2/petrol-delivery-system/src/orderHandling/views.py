from django.contrib.auth.decorators import login_required
from .controllers import OrderController, AccountController, StockController, ReportController
from django.shortcuts import render, get_object_or_404
from app.models import Stock, Vendor
from django.http import JsonResponse

@login_required
def createorderform(request):
    return OrderController.create_order(request)

@login_required
def createorderconfirmation(request, order_id):
    return OrderController.create_order_confirmation(request, order_id)

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
def acceptdeclineorderdriver(request):
    return OrderController.accept_decline_order_driver(request)

@login_required
def acceptdeclineordervendor(request):
    return OrderController.accept_decline_order_vendor(request)

@login_required
def updateorderstatusdriver(request, order_id, action):
    return OrderController.update_order_status_driver(request, order_id, action)

@login_required
def updateorderstatusvendor(request, order_id, action):
    return OrderController.update_order_status_vendor(request, order_id, action)

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

@login_required
def viewordersvendor(request):
    return OrderController.view_orders_vendor(request)

@login_required
def submitavailabilitystatus(request):
    return StockController.submit_availability_status(request)

@login_required
def generatereport(request):
    return ReportController.generate_report(request)

@login_required
def paymentpage(request, order_id, total_amount):
    return OrderController.payment_page(request, order_id, total_amount)

@login_required
def processpayment(request):
    return OrderController.process_payment(request)