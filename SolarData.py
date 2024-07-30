import os
import django
import math
import time
import requests
import json
import keyboard  # Necesitas instalar esta biblioteca con 'pip install keyboard'
from datetime import datetime, timedelta


# Configura Django para usar los modelos
os.environ.setdefault('DJANGO_SETTINGS_MODULE', 'sol.settings')
django.setup()

from myapp.models import SolarData

# Constantes
PI = math.pi
GpH = 15.0  # Grados por hora
LONGEST = -75.0  # Longitud estándar para referencia

class CoordenadasNum:
    def __init__(self):
        self.longitud = 0.0
        self.latitud = 0.0

class Geolocalizador:
    def __init__(self, api_key):
        self.api_key = api_key

    def geolocate(self):
        url = f"https://www.googleapis.com/geolocation/v1/geolocate?key={self.api_key}"
        headers = {'Content-Type': 'application/json'}
        response = requests.post(url, headers=headers)
        
        if response.status_code == 200:
            data = response.json()
            location = data.get("location", {})
            lat = location.get("lat")
            lng = location.get("lng")
            if lat is not None and lng is not None:
                return lat, lng
            else:
                print("Latitude or Longitude not found in the response.")
                return None, None
        else:
            print(f"Request failed with status code {response.status_code}")
            return None, None

class CalculadorSolar:
    @staticmethod
    def obtenerHoraLocal():
        return datetime.now()

    @staticmethod
    def calcularDeclinacion(fechaHora):
        diaDelAnio = fechaHora.timetuple().tm_yday
        B = (2 * PI * (diaDelAnio - 81)) / 365.0
        return 23.45 * math.sin(B)

    @staticmethod
    def calcularEcuacionDelTiempo(fechaHora):
        diaDelAnio = fechaHora.timetuple().tm_yday
        B = (2 * PI * (diaDelAnio - 81)) / 365.0
        return 9.87 * math.sin(2 * B) - 7.53 * math.cos(B) - 1.5 * math.sin(B)

    @staticmethod
    def calcularHoraLocal(fechaHora):
        return fechaHora.hour + fechaHora.minute / 60.0 + fechaHora.second / 3600.0

    @staticmethod
    def calcularTiempoSolarVerdadero(coord, horaLocal, ecuacionTiempo):
        return horaLocal + (4 * (LONGEST - coord.longitud) + ecuacionTiempo) / 60.0

    @staticmethod
    def calcularAlturaSolar(declinacion, latitud, tiempoSolarVerdadero):
        latitud_rad = math.radians(latitud)
        declinacion_rad = math.radians(declinacion)
        angulo_horario = math.radians((tiempoSolarVerdadero - 12) * GpH)
        alturaSolar = math.asin(
            math.sin(latitud_rad) * math.sin(declinacion_rad) +
            math.cos(latitud_rad) * math.cos(declinacion_rad) * math.cos(angulo_horario)
        )
        return math.degrees(alturaSolar)

class CalculadorAzimuth:
    @staticmethod
    def calcularAzimuth(declinacion, latitud, alturaSolar, tiempoSolarVerdadero):
        declinacion_rad = math.radians(declinacion)
        latitud_rad = math.radians(latitud)
        alturaSolar_rad = math.radians(alturaSolar)
        angulo_horario = math.radians((tiempoSolarVerdadero - 12) * GpH)
        
        cosAzimuth = (
            (math.sin(alturaSolar_rad) - math.sin(latitud_rad) * math.sin(declinacion_rad)) /
            (math.cos(latitud_rad) * math.cos(declinacion_rad))
        )
        cosAzimuth = max(-1.0, min(1.0, cosAzimuth))  # Clamping value to [-1, 1] range
        azimuth_rad = math.acos(cosAzimuth)
        
        if angulo_horario > 0:
            azimuth_rad = 2 * PI - azimuth_rad
            
        azimuth = math.degrees(azimuth_rad)
        return azimuth

def enviar_datos_a_arduino(ser, azimuth, alturaSolar):
    ser.write(f"{azimuth:.2f},{alturaSolar:.2f}\n".encode())

def guardar_datos_db(fechaHora, azimuth, alturaSolar):
    fecha = fechaHora.date()
    hora = fechaHora.time()
    solar_data = SolarData(fecha=fecha, hora=hora, azimuth=azimuth, altura=alturaSolar)
    solar_data.save()

def main(api_key):
    geolocalizador = Geolocalizador(api_key)
    calculador = CalculadorSolar()
    calculadorAzimuth = CalculadorAzimuth()

    latitud, longitud = geolocalizador.geolocate()
    
    if latitud is None or longitud is None:
        print("No se pudo obtener la latitud y longitud.")
        return

    coordNum = CoordenadasNum()
    coordNum.latitud = latitud
    coordNum.longitud = longitud

    

    while True:
        
        fechaHora = calculador.obtenerHoraLocal()  # Actualiza la hora actual en cada iteración
        declinacion = calculador.calcularDeclinacion(fechaHora)
        ecuacionTiempo = calculador.calcularEcuacionDelTiempo(fechaHora)
        horaLocal = calculador.calcularHoraLocal(fechaHora)
        tiempoSolarVerdadero = calculador.calcularTiempoSolarVerdadero(coordNum, horaLocal, ecuacionTiempo)
        alturaSolar = calculador.calcularAlturaSolar(declinacion, coordNum.latitud, tiempoSolarVerdadero)
        azimuth = calculadorAzimuth.calcularAzimuth(declinacion, coordNum.latitud, alturaSolar, tiempoSolarVerdadero)

        guardar_datos_db(fechaHora, azimuth, alturaSolar)
        
        time.sleep(300)  # Espera 5 minutos antes de la próxima actualización

    ser.close()

if __name__ == "__main__":
    api_key = "AIzaSyAIMJFf-a4KxIIpRuv5vvPO5Mz-qnske2A"
    main(api_key)


