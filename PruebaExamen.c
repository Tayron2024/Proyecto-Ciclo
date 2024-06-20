/**
 * @file SF.c
 * @author  Mathías Medina - Tayron Morales - Victor Mac
 * @brief 
 * @version 0.1
 * @date 2024-06-20
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <windows.h>

#define PI 3.14159265
// Grados por hora
#define GpH 15.0
// Longitud estándar para referencia
#define LONGEST -75.0
// Declinación solar promedio
#define D_ISol -23.44

/**CoordenadasChar
  Estructura para almacenar coordenadas en formato de cadena.*/

struct CoordenadasChar {
    // Longitud en grados (cadena)
    char longitud[265];
    // Latitud en grados (cadena)
    char latitud[265];
};

/**struct CoordenadasNum
 * Estructura para almacenar coordenadas en formato numérico.*/

struct CoordenadasNum {
    // Longitud en grados (numérico)
    double longitud;
    // Latitud en grados (numérico)
    double latitud;
};

/**Función para obtener la hora local del sistema.
  fechaHora Puntero a la estructura tm donde se almacenará la fecha y hora local.*/

void obtenerHoraLocal(struct tm *fechaHora);

/**Función para ingresar coordenadas de longitud y latitud.
  coordChar Puntero a la estructura CoordenadasChar para ingresar coordenadas como cadena.
  coordNum Puntero a la estructura CoordenadasNum para almacenar coordenadas como números.*/

void ingresarCoordenadas(struct CoordenadasChar *coordChar, struct CoordenadasNum *coordNum);

/**Función para validar que una cadena de caracteres sea un número válido.
  num Cadena que se desea validar.*/

void validar(char num[]);

/**Función para calcular la declinación solar.
  fechaHora Estructura tm que contiene la fecha y hora actual.
  double Valor de la declinación solar en grados.*/

double calcularDeclinacion(struct tm fechaHora);

/**Función para calcular la ecuación del tiempo.
  fechaHora Estructura tm que contiene la fecha y hora actual.
  double Valor de la ecuación del tiempo en minutos.*/

double calcularEcuacionDelTiempo(struct tm fechaHora);

/**Función para calcular la hora local.
  fechaHora Estructura tm que contiene la fecha y hora actual.
  double Valor de la hora local en horas decimales.*/

double calcularHoraLocal(struct tm fechaHora);

/**Función para calcular el tiempo solar verdadero.
  coord Estructura CoordenadasNum que contiene la longitud y latitud.
  horaLocal Hora local en horas decimales.
  ecuacionTiempo Valor de la ecuación del tiempo en minutos.
  double Valor del tiempo solar verdadero en horas decimales.
  */
double calcularTiempoSolarVerdadero(struct CoordenadasNum coord, double horaLocal, double ecuacionTiempo);

/**
  Función para calcular la altura solar.
  tiempoSolarVerdadero Tiempo solar verdadero en horas decimales.
  double Altura solar en grados.
 */

double calcularAlturaSolar(double tiempoSolarVerdadero);

/**
 Función para calcular el ángulo de orientación de los paneles solares.
  Altura solar en grados.
  Declinación solar en grados.
  Latitud en grados.
  double Ángulo de orientación de los paneles solares en grados.
 */

double calcularAnguloOrientacion(double alturaSolar, double declinacion, double latitud);

/**
  Función para calcular el azimuth solar.
  Declinación solar en grados.
  Latitud en grados.
  Altura solar en grados.
  double Azimuth solar en grados.
 */

double calcularAzimuth(double declinacion, double latitud, double alturaSolar);

/**
  Función para presentar los datos calculados.
  fechaHora Estructura tm que contiene la fecha y hora actual.
  Azimuth solar en grados.
  anguloOrientacion Ángulo de elevación solar en grados.
 */

void PresentarDatos(struct tm fechaHora ,double azimuth, double anguloOrientacion);

/**
   Funcion Principal del Programa int main();
 */

int main() {
    struct CoordenadasChar coordenadasChar;
    struct CoordenadasNum coordenadasNum;

    struct tm fechaHora;
    
    ingresarCoordenadas(&coordenadasChar, &coordenadasNum);
    obtenerHoraLocal(&fechaHora);

    double declinacion = calcularDeclinacion(fechaHora);
    double ecuacionTiempo = calcularEcuacionDelTiempo(fechaHora);
    double horaLocal = calcularHoraLocal(fechaHora);
    double tiempoSolarVerdadero = calcularTiempoSolarVerdadero(coordenadasNum, horaLocal, ecuacionTiempo);
    double alturaSolar = calcularAlturaSolar(tiempoSolarVerdadero);
    double anguloOrientacion = calcularAnguloOrientacion(alturaSolar, declinacion, coordenadasNum.latitud);
    double azimuth = calcularAzimuth(declinacion, coordenadasNum.latitud, alturaSolar);

    PresentarDatos(fechaHora, azimuth, anguloOrientacion);
    
    return 0;
}

void obtenerHoraLocal(struct tm *fechaHora) {
    time_t t = time(NULL);
    *fechaHora = *localtime(&t);
}

void ingresarCoordenadas(struct CoordenadasChar *coordChar, struct CoordenadasNum *coordNum) {
    printf("Ingrese la longitud dentro de -180 a 180 (en grados): ");
    scanf("%s", coordChar->longitud);
    validar(coordChar->longitud);
    coordNum->longitud = atof(coordChar->longitud);
    while (coordNum->longitud > 180 || coordNum->longitud < -180) {
        printf("Ingrese la longitud dentro de -180 a 180 (en grados): ");
        scanf("%s", coordChar->longitud);
        validar(coordChar->longitud);
        coordNum->longitud = atof(coordChar->longitud);
    }
    
    printf("Ingrese la latitud dentro de -90 a 90 (en grados): ");
    scanf("%s", coordChar->latitud);
    validar(coordChar->latitud);
    coordNum->latitud = atof(coordChar->latitud);
    while (coordNum->latitud > 90 || coordNum->latitud < -90) {
        printf("Ingrese la latitud dentro de -90 a 90 (en grados): ");
        scanf("%s", coordChar->latitud);
        validar(coordChar->latitud);
        coordNum->latitud = atof(coordChar->latitud);
    }
}

void validar(char num[]) {
    for (int i = 0; i < strlen(num); i++) {
        if (!isdigit(num[i]) && num[i] != '-' && num[i] != '.') {
            printf("Ingrese un numero valido: ");
            scanf("%s", num); 
            validar(num); 
            return;
        }
    }
}

double calcularDeclinacion(struct tm fechaHora) {
    int diaDelAnio = fechaHora.tm_yday + 1; // Añadir 1 ya que tm_yday inicia desde 0
    return D_ISol * cos(2 * PI * (diaDelAnio + 10) / 365.0);
}

double calcularEcuacionDelTiempo(struct tm fechaHora) {
    int diaDelAnio = fechaHora.tm_yday + 1; // Añadir 1 ya que tm_yday inicia desde 0
    double B = (2 * PI * (diaDelAnio - 81)) / 365.0;
    return 9.87 * sin(2 * B) - 7.53 * cos(B) - 1.5 * sin(B);
}

double calcularHoraLocal(struct tm fechaHora) {
    return fechaHora.tm_hour + fechaHora.tm_min / 60.0 + fechaHora.tm_sec / 3600.0;
}

double calcularTiempoSolarVerdadero(struct CoordenadasNum coord, double horaLocal, double ecuacionTiempo) {
    return horaLocal + (4 * (coord.longitud - LONGEST) + ecuacionTiempo) / 60.0;
}

double calcularAlturaSolar(double tiempoSolarVerdadero) {
    return GpH * (tiempoSolarVerdadero - 12.0);
}

double calcularAnguloOrientacion(double alturaSolar, double declinacion, double latitud) {
    double anguloRad = asin(sin(declinacion * PI / 180.0) * sin(latitud * PI / 180.0) +
                            cos(declinacion * PI / 180.0) * cos(latitud * PI / 180.0) * cos(alturaSolar * PI / 180.0));
    return anguloRad * 180.0 / PI;
}

double calcularAzimuth(double declinacion, double latitud, double alturaSolar) {
    double azimuthRad = acos((sin(declinacion * PI / 180.0) - sin(alturaSolar * PI / 180.0) * sin(latitud * PI / 180.0)) /
                             (cos(alturaSolar * PI / 180.0) * cos(latitud * PI / 180.0)));
    return azimuthRad * 180.0 / PI;
}

void PresentarDatos(struct tm fechaHora, double azimuth, double anguloOrientacion) {
    for (int hora = fechaHora.tm_hour; hora < 24; hora++) {
        for (int minuto = fechaHora.tm_min; minuto < 60; minuto++) {
            for (int segundo = fechaHora.tm_sec; segundo < 60; segundo++) {
                system("@cls||clear");
                printf("Fecha de ejecucion: \t %d/%d/%d", fechaHora.tm_mday, fechaHora.tm_mon + 1, fechaHora.tm_year + 1900);
                printf("\n\rHora de ejecucion: %02d: %02d:%02d\n", hora, minuto, segundo);
                printf("\nOrientacion optima de los paneles solares:\n");
                printf("Azimuth solar: %.2lf grados\n", azimuth);
                printf("Angulo de elevacion solar: %.2lf grados\n\n", anguloOrientacion);
                Sleep(1000);
            }
        }
    }
}
