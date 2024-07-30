from django.shortcuts import render
from django.http import JsonResponse
from .models import SolarData
import json
from django.views.decorators.csrf import csrf_exempt


def mostrar_datos_solares(request):
    # Obtener los últimos datos de la base de datos
    datos = SolarData.objects.last()

    # Pasar los datos al template
    context = {
        'datos': datos,
        'api_key': 'AIzaSyAIMJFf-a4KxIIpRuv5vvPO5Mz-qnske2A'
    }
    return render(request, 'myapp/mostrar_datos.html', context)


@csrf_exempt
def guardar_datos(request):
    if request.method == 'POST':
        data = json.loads(request.body)
        longitud = data.get('longitud')
        latitud = data.get('latitud')
        azimuth = data.get('azimuth')
        inclinacion = data.get('inclinacion')
        
        # Guardar datos en la base de datos
        SolarData.objects.create(
            longitud=longitud,
            latitud=latitud,
            azimuth=azimuth,
            altura=inclinacion
        )
        
        return JsonResponse({'status': 'success'})
    return JsonResponse({'status': 'failed'}, status=400)
