#include <stdio.h>
#include <math.h>
#include <time.h>

#define PI 3.14159265
#define GpH 15.0
#define LONGEST -75.0
#define vtre -23.44

struct Coordenadas {
    double longitud;
    double latitud;
};

void obtenerHoraLocal(struct tm *fechaHora) {
    time_t t = time(NULL);
    *fechaHora = *localtime(&t);
}

void ingresarCoordenadas(struct Coordenadas *coord) {
    printf("Ingrese la longitud (en grados): ");
    scanf("%lf", &coord->longitud);
    printf("Ingrese la latitud (en grados): ");
    scanf("%lf", &coord->latitud);
}

double calcularDeclinacion(struct tm fechaHora) {
    int diaDelAnio = fechaHora.tm_yday + 1;
    return vtre * cos(2 * PI * (diaDelAnio + 10) / 365.0);
}

double calcularEcuacionDelTiempo(struct tm fechaHora) {
    int diaDelAnio = fechaHora.tm_yday + 1;
    double B = (2 * PI * (diaDelAnio - 81)) / 365.0;
    return 9.87 * sin(2 * B) - 7.53 * cos(B) - 1.5 * sin(B);
}

double calcularHoraLocal(struct tm fechaHora) {
    return fechaHora.tm_hour + fechaHora.tm_min / 60.0 + fechaHora.tm_sec / 3600.0;
}

double calcularTiempoSolarVerdadero(struct Coordenadas coord, double horaLocal, double ecuacionTiempo) {
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

int main() {
    struct Coordenadas coordenadas;
    struct tm fechaHora;

    obtenerHoraLocal(&fechaHora);

    ingresarCoordenadas(&coordenadas);

    double declinacion = calcularDeclinacion(fechaHora);

    double ecuacionTiempo = calcularEcuacionDelTiempo(fechaHora);

    double horaLocal = calcularHoraLocal(fechaHora);

    double tiempoSolarVerdadero = calcularTiempoSolarVerdadero(coordenadas, horaLocal, ecuacionTiempo);

    double alturaSolar = calcularAlturaSolar(tiempoSolarVerdadero);

    double anguloOrientacion = calcularAnguloOrientacion(alturaSolar, declinacion, coordenadas.latitud);

    double azimuth = calcularAzimuth(declinacion, coordenadas.latitud, alturaSolar);

    printf("\nOrientación óptima de los paneles solares:\n");
    printf("Azimuth solar: %.2f grados\n", azimuth);
    printf("Ángulo de elevación solar: %.2f grados\n", anguloOrientacion);

    return 0;
}
