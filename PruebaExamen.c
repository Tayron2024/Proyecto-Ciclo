#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h> // Para utilizar system()

#define LONGEST -75
#define PI 3.1416
#define vtre -23.44
#define GpH 15

struct Coordenadas {
    double longitud, latitud;
};

struct Angulo {
    double azimuth, aOrientacion;
};

void ingresarCoordenadas(struct Coordenadas *coordenadas);
double Ds(struct tm *FechaAc);
double DeclinacionSolar(struct tm *FechaAc);
double EcuacionDelTiempo(double B);
double HoraLocal(struct tm *FechaAc);
double TiempoSolarVerdadero(struct Coordenadas coordenadas, double HoraLocal, double Eot);
double AlturaSolar(double TSV);
double OrientacionSolar(struct Angulo *angulo, struct Coordenadas coordenadas, double ds,  double H);
double Azimuth(struct Angulo *angulo, struct Coordenadas coordenadas, double ds);
void PresentarAngulos(struct Angulo angulo);

int main() {
    printf("\033[H\033[J"); // Limpiar pantalla en Unix/Linux utilizando escape sequences
    struct Coordenadas coordenadas;
    struct Angulo angulo;
    struct tm *FechaActual;
    time_t seconds;

    seconds = time(NULL);
    FechaActual = localtime(&seconds);

    ingresarCoordenadas(&coordenadas);

    double ds = Ds(FechaActual);
    double B = DeclinacionSolar(FechaActual);
    double EoT = EcuacionDelTiempo(B);
    double horaLocal = HoraLocal(FechaActual);
    double TSV = TiempoSolarVerdadero(coordenadas, horaLocal, EoT);
    double H = AlturaSolar(TSV); 

    angulo.aOrientacion = OrientacionSolar(&angulo, coordenadas, ds, H);
    angulo.azimuth = Azimuth(&angulo, coordenadas, ds);

    PresentarAngulos(angulo);

    return 0;
}

void ingresarCoordenadas(struct Coordenadas *coordenadas) {
    printf("Ingrese la longitud: ");
    scanf("%lf", &coordenadas->longitud);
    printf("Ingrese la latitud: ");
    scanf("%lf", &coordenadas->latitud);
}

double Ds(struct tm *FechaAc) {
    double ds = vtre * (cos((2 * PI / 365) * (FechaAc->tm_yday + 10)));
    return ds;
}

double DeclinacionSolar(struct tm *FechaAc) {
    double B = (2 * PI / 365) * (FechaAc->tm_yday - 81);
    return B;
}

double EcuacionDelTiempo(double B) {
    double Eot = (9.87 * sin(2 * B)) - (7.53 * cos(B)) - (1.5 * sin(B));
    return Eot;
}

double HoraLocal(struct tm *FechaAc) {
    double Horalocal = FechaAc->tm_hour + (FechaAc->tm_min / 60.0);
    return Horalocal;
}

double TiempoSolarVerdadero(struct Coordenadas coordenadas, double HoraLocal, double Eot) {
    double TSV = HoraLocal + ((4 * (coordenadas.longitud - LONGEST) + Eot) / 60.0);
    return TSV;
}

double AlturaSolar(double TSV) {
    double H = GpH * (TSV - 12);
    return H;
}

double OrientacionSolar(struct Angulo *angulo, struct Coordenadas coordenadas, double ds, double H) {
    angulo->aOrientacion = asin((sin(ds) * sin(coordenadas.latitud * PI / 180.0)) + (cos(ds) * cos(coordenadas.latitud * PI / 180.0) * cos(H)));
    return angulo->aOrientacion;
}

double Azimuth(struct Angulo *angulo, struct Coordenadas coordenadas, double ds) {
    angulo->azimuth = acos(((sin(ds) - sin(angulo->aOrientacion)) * sin(coordenadas.latitud * PI / 180.0)) / (cos(angulo->aOrientacion) * cos(coordenadas.latitud * PI / 180.0)));
    return angulo->azimuth;
}

void PresentarAngulos(struct Angulo angulo) {
    printf("El azimuth es: %lf\n", angulo.azimuth);
    printf("El angulo de Orientacion es: %lf\n", angulo.aOrientacion);
}