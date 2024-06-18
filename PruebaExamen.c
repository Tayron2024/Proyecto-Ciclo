/**
 * @file SF.c
 * @author Mathías Medina - Tayron Morales - Victor Macas (  )
 * @brief 
 * @version 0.1
 * @date 2024-06-17
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <windows.h>

#define PI 3.14159265
#define GpH 15.0
#define LONGEST -75.0
#define vtre -23.44

struct CoordenadasChar{
    char longitud[265];
    char latitud[265];
};
struct CoordenadasNum{
    double longitud;
    double latitud;
};


void obtenerHoraLocal(struct tm *fechaHora);


void ingresarCoordenadas(struct CoordenadasChar *coord, struct CoordenadasNum coordNum);
void validar(char num[]);

double calcularDeclinacion(struct tm fechaHora);

double calcularEcuacionDelTiempo(struct tm fechaHora);

double calcularHoraLocal(struct tm fechaHora);

double calcularTiempoSolarVerdadero(struct CoordenadasNum coord, double horaLocal, double ecuacionTiempo);

double calcularAlturaSolar(double tiempoSolarVerdadero);

double calcularAnguloOrientacion(double alturaSolar, double declinacion, double latitud);

double calcularAzimuth(double declinacion, double latitud, double alturaSolar);
void PresentarDatos(struct tm fechaHora ,double azimuth, double anguloOrientacion);

int main() {
    struct CoordenadasChar CoordenadasChar;
    struct CoordenadasNum CoordenadasNum;

    struct tm fechaHora;
    
        ingresarCoordenadas(&CoordenadasChar,CoordenadasNum);
        obtenerHoraLocal(&fechaHora);

    
        double declinacion = calcularDeclinacion(fechaHora);

        double ecuacionTiempo = calcularEcuacionDelTiempo(fechaHora);

        double horaLocal = calcularHoraLocal(fechaHora);

        double tiempoSolarVerdadero = calcularTiempoSolarVerdadero(CoordenadasNum, horaLocal, ecuacionTiempo);

        double alturaSolar = calcularAlturaSolar(tiempoSolarVerdadero);

        double anguloOrientacion = calcularAnguloOrientacion(alturaSolar, declinacion, CoordenadasNum.latitud);

        double azimuth = calcularAzimuth(declinacion, CoordenadasNum.latitud, alturaSolar);

        PresentarDatos(fechaHora,azimuth, anguloOrientacion);
        
    return 0;
}

void obtenerHoraLocal(struct tm *fechaHora){
    struct tm fechaActual;
    time_t t = time(NULL);
    *fechaHora = *localtime(&t);
    
    fechaActual.tm_year = fechaHora->tm_year +1900;
    fechaActual.tm_hour = fechaHora->tm_hour;
    fechaActual.tm_min= fechaHora->tm_min;
    fechaActual.tm_yday= fechaHora->tm_yday+1; 
}

void ingresarCoordenadas(struct CoordenadasChar *coordChar, struct CoordenadasNum coordNum){
    printf("Ingrese la longitud (en grados): ");
    scanf("%s", &coordChar->longitud);
    validar(coordChar->longitud);
    coordNum.longitud = atof(coordChar->longitud);
    printf("Ingrese la latitud (en grados): ");
    scanf("%s", &coordChar->latitud);
    validar(coordChar->latitud);
    coordNum.latitud = atof(coordChar->latitud);

}

void validar(char num[]) {
    for (int i = 0; i < strlen(num); i++) {
        if (!isdigit(num[i]) && num[i] != '-' && num[i] != '.') {
            printf("Ingrese un numero valido: ");
            scanf("%s", num); // Permite al usuario ingresar un nuevo valor
            validar(num); // Llama a la función de validación nuevamente
            return;
        }
    }
}

double calcularDeclinacion(struct tm fechaHora){
    int diaDelAnio = fechaHora.tm_yday;
    return vtre * cos(2 * PI * (diaDelAnio + 10) / 365.0);
}

double calcularEcuacionDelTiempo(struct tm fechaHora){
    int diaDelAnio = fechaHora.tm_yday + 1;
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

void PresentarDatos(struct tm fechaHora ,double azimuth, double anguloOrientacion){
    for (fechaHora.tm_hour; fechaHora.tm_hour <24; fechaHora.tm_hour++){
        for ( fechaHora.tm_min; fechaHora.tm_min< 60; fechaHora.tm_min++){
            for (fechaHora.tm_sec; fechaHora.tm_sec< 60; fechaHora.tm_sec++){
                system("@cls||clear");
                printf("Fecha de ejecucion: \t %d/%d/%d", fechaHora.tm_mday, fechaHora.tm_mon, fechaHora.tm_year);
                printf("\nHora de ejecucion:\t %d: %d:%d\n",fechaHora.tm_hour, fechaHora.tm_min,fechaHora.tm_sec); 
                printf("Orientacion optima de los paneles solares:\n");
                printf("Azimuth solar: %lf grados\n", azimuth);
                printf("Angulo de elevacion solar: %.2f grados\n\n", anguloOrientacion);
                Sleep(1000);
            }   
        }   
    }
}
