from django.urls import path
from . import views

urlpatterns = [
    path('datos_solares/', views.mostrar_datos_solares, name='mostrar_datos_solares'),
    path('api/guardar_datos/', views.guardar_datos, name='guardar_datos'),
]
