"""myproject URL Configuration

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/4.1/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  path('', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  path('', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.urls import include, path
    2. Add a URL to urlpatterns:  path('blog/', include('blog.urls'))
"""
from django.contrib import admin
from django.urls import path, re_path
from app import views as main_views, forms
from orderHandling import views as orderHandling_views
import django.contrib.auth.views
from django.contrib.auth.views import LoginView, LogoutView
from datetime import datetime
admin.autodiscover()

urlpatterns = [
    path('admin/', admin.site.urls),
    re_path(r'^$', main_views.home, name='home'),
    re_path(r'^contact$', main_views.contact, name='contact'),
    re_path(r'^about$', main_views.about, name='about'),
    re_path(r'^choose_role/$', main_views.choose_role, name='choose_role'),  # Page to choose the role
    re_path(r'^create_customer/$', main_views.create_customer, name='create_customer'),
    re_path(r'^create_vendor/$', main_views.create_vendor, name='create_vendor'),
    re_path(r'^create_driver/$', main_views.create_driver, name='create_driver'),
    re_path(r'^login/$',
        LoginView.as_view(template_name = 'app/login.html'),
        name='login'),
    re_path(r'^logout$',
        LogoutView.as_view(template_name = 'app/index.html'),
        name='logout'),
    re_path(r'^menu$', main_views.menu, name='menu'),
    re_path(r'^createorderform$', orderHandling_views.createorderform, name='createorderform'),
    re_path(r'^createorderconfirmation/(?P<order_id>\d+)/$', orderHandling_views.createorderconfirmation, name='createorderconfirmation'),
    re_path(r'^listorders/$', orderHandling_views.listorders , name='listorders'),
    re_path(r'^editorder/(?P<order_id>\d+)/$', orderHandling_views.editorder, name='editorder'),
    re_path(r'^vieworders/$', orderHandling_views.vieworders , name='vieworders'),
    re_path(r'^acceptdeclineorderdriver/$', orderHandling_views.acceptdeclineorderdriver, name='acceptdeclineorderdriver'),
    re_path(r'^completeorcancelorder/$', orderHandling_views.completeorcancelorder, name='completeorcancelorder'),
    re_path(r'^updateorderstatusdriver/(?P<order_id>\d+)/(?P<action>\w+)/$', orderHandling_views.updateorderstatusdriver, name='updateorderstatusdriver'),
    re_path(r'^viewordersdriver/$', orderHandling_views.viewordersdriver , name='viewordersdriver'),
    re_path(r'^editaccountdetails/$', orderHandling_views.editaccountdetails , name='editaccountdetails'),
    re_path(r'^driverperformance/$', orderHandling_views.driverperformance , name='driverperformance'),
    re_path(r'^viewordersvendor/$', orderHandling_views.viewordersvendor , name='viewordersvendor'),
    re_path(r'^submitavailabilitystatus/', orderHandling_views.submitavailabilitystatus, name='submitavailabilitystatus'),
    re_path(r'^acceptdeclineordervendor/$', orderHandling_views.acceptdeclineordervendor, name='acceptdeclineordervendor'),
    re_path(r'^updateorderstatusvendor/(?P<order_id>\d+)/(?P<action>\w+)/$', orderHandling_views.updateorderstatusvendor, name='updateorderstatusvendor'),
    re_path(r'^generatereport/', orderHandling_views.generatereport, name='generatereport'),
    re_path(r'^paymentpage/(?P<order_id>\d+)/(?P<total_amount>\d+\.\d{2})/$', orderHandling_views.paymentpage, name='paymentpage'),
    re_path(r'^processpayment$', orderHandling_views.processpayment, name='processpayment'),
]
