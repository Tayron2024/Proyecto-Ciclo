#include <stdio.h>
#include <math.h>
#include <time.h>

#define PI 3.14159265
//GpH (Grados por Hora)
#define GpH 15.0
//LONGEST (Longitud Estándar)
#define LONGEST -75.0
//vtre (Valor de la Tilt de la Tierra)
#define vtre -23.44

// Estructura para almacenar las coordenadas geográficas
struct Coordenadas {
    double longitud;
    double latitud;
};

// Función para obtener la fecha y hora local del sistema
void obtenerHoraLocal(struct tm *fechaHora) {
    time_t t = time(NULL);
    *fechaHora = *localtime(&t);
}

// Función para que el usuario ingrese las coordenadas geográficas
void ingresarCoordenadas(struct Coordenadas *coord) {
    printf("Ingrese la longitud (en grados): ");
    scanf("%lf", &coord->longitud);
    printf("Ingrese la latitud (en grados): ");
    scanf("%lf", &coord->latitud);
}

// Función para calcular la declinación solar
// Utiliza la fórmula de declinación solar en función del día del año
double calcularDeclinacion(struct tm fechaHora) {
    int diaDelAnio = fechaHora.tm_yday + 1;
    return vtre * cos(2 * PI * (diaDelAnio + 10) / 365.0);
}

// Función para calcular la ecuación del tiempo
// Utiliza la fórmula de la ecuación del tiempo basada en el día del año
double calcularEcuacionDelTiempo(struct tm fechaHora) {
    int diaDelAnio = fechaHora.tm_yday + 1;
    double B = (2 * PI * (diaDelAnio - 81)) / 365.0;
    return 9.87 * sin(2 * B) - 7.53 * cos(B) - 1.5 * sin(B);
}

// Función para calcular la hora local del sistema
// Convierte la hora, minutos y segundos a fracción de horas
double calcularHoraLocal(struct tm fechaHora) {
    return fechaHora.tm_hour + fechaHora.tm_min / 60.0 + fechaHora.tm_sec / 3600.0;
}

// Función para calcular el tiempo solar verdadero
// Ajusta la hora local por la longitud geográfica y la ecuación del tiempo
double calcularTiempoSolarVerdadero(struct Coordenadas coord, double horaLocal, double ecuacionTiempo) {
    return horaLocal + (4 * (coord.longitud - LONGEST) + ecuacionTiempo) / 60.0;
}

// Función para calcular la altura solar
// Determina el ángulo de elevación del Sol sobre el horizonte en función del tiempo solar verdadero
double calcularAlturaSolar(double tiempoSolarVerdadero) {
    return GpH * (tiempoSolarVerdadero - 12.0);
}

// Función para calcular el ángulo de orientación de los paneles solares
// Utiliza la fórmula del ángulo de elevación solar y la declinación solar para determinar el ángulo óptimo
double calcularAnguloOrientacion(double alturaSolar, double declinacion, double latitud) {
    double anguloRad = asin(sin(declinacion * PI / 180.0) * sin(latitud * PI / 180.0) +
                            cos(declinacion * PI / 180.0) * cos(latitud * PI / 180.0) * cos(alturaSolar * PI / 180.0));
    return anguloRad * 180.0 / PI;
}

// Función para calcular el azimuth solar
// Determina la dirección del Sol medida desde el norte en sentido horario
double calcularAzimuth(double declinacion, double latitud, double alturaSolar) {
    double azimuthRad = acos((sin(declinacion * PI / 180.0) - sin(alturaSolar * PI / 180.0) * sin(latitud * PI / 180.0)) /
                             (cos(alturaSolar * PI / 180.0) * cos(latitud * PI / 180.0)));
    return azimuthRad * 180.0 / PI;
}

int main() {
    struct Coordenadas coordenadas;
    struct tm fechaHora;

    // Obtener la fecha y hora local del sistema
    obtenerHoraLocal(&fechaHora);

    // Solicitar al usuario que ingrese las coordenadas geográficas
    ingresarCoordenadas(&coordenadas);

    // Calcular la declinación solar en función de la fecha y hora obtenidas
    double declinacion = calcularDeclinacion(fechaHora);

    // Calcular la ecuación del tiempo basada en la fecha y hora
    double ecuacionTiempo = calcularEcuacionDelTiempo(fechaHora);

    // Calcular la hora local ajustada por la longitud geográfica
    double horaLocal = calcularHoraLocal(fechaHora);

    // Calcular el tiempo solar verdadero ajustado por la ecuación del tiempo y la longitud
    double tiempoSolarVerdadero = calcularTiempoSolarVerdadero(coordenadas, horaLocal, ecuacionTiempo);

    // Calcular la altura solar en función del tiempo solar verdadero
    double alturaSolar = calcularAlturaSolar(tiempoSolarVerdadero);

    // Calcular el ángulo de orientación de los paneles solares
    double anguloOrientacion = calcularAnguloOrientacion(alturaSolar, declinacion, coordenadas.latitud);

    // Calcular el azimuth solar
    double azimuth = calcularAzimuth(declinacion, coordenadas.latitud, alturaSolar);

    // Mostrar los resultados de la orientación óptima de los paneles solares
    printf("\nOrientación óptima de los paneles solares:\n");
    printf("Azimuth solar: %.2f grados\n", azimuth);
    printf("Ángulo de elevación solar: %.2f grados\n", anguloOrientacion);

    return 0;
}
