from django.db import models

class SolarData(models.Model):
    fecha = models.DateField(auto_now_add=True)
    hora = models.TimeField(auto_now_add=True)
    azimuth = models.FloatField()
    altura = models.FloatField()
    latitud = models.FloatField(default=0.0)
    longitud = models.FloatField(default=0.0)

    def __str__(self):
        return f"{self.fecha} {self.hora} - Azimuth: {self.azimuth}, Altura: {self.altura}"
