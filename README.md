**Universidad Nacional de Loja**


**Algoritmo para Optimización de Orientación de Paneles Solares**

**Presentado por:** Tayron Morales, Mathias ......, Victor.

**Fecha:** 16/06/2024

**Resumen de la Problematica**

En el contexto de la creciente necesidad de utilizar fuentes de energía renovable, los paneles solares juegan un papel crucial al convertir la radiación solar en electricidad. Para maximizar la eficiencia de estos sistemas, es fundamental optimizar la orientación de los paneles solares de manera dinámica, considerando la posición cambiante del Sol a lo largo del día y del año. Este trabajo presenta un algoritmo diseñado para calcular automáticamente los ángulos de azimuth y elevación del Sol, asegurando así que los paneles solares capturen la máxima radiación solar disponible en todo momento.


**Descripción del Problema y Objetivo del Algoritmo**

El problema abordado es determinar la orientación óptima de paneles solares en tiempo real para maximizar la captación de luz solar. Esto implica calcular dinámicamente los ángulos de azimuth y elevación del sol en función de la ubicación geográfica y la hora del día, asegurando así que los paneles solares estén orientados de manera que capturen la máxima radiación solar posible en todo momento.


**El objetivo del algoritmo es proporcionar una herramienta computacional que permita:**

1.	Obtener automáticamente la fecha y hora del sistema.
  
2.	Permitir al usuario ingresar manualmente las coordenadas geográficas donde se instalarán los paneles solares.
   
3.	Calcular la orientación óptima de los paneles solares en términos de azimuth y ángulo de elevación.
   
4.	Mostrar estos valores para que los instaladores puedan ajustar físicamente la posición de los paneles solares.

   
**Análisis Detallado de las Variables Involucradas**

**Objetivos de Optimización**

El objetivo principal del algoritmo es maximizar la eficiencia energética de los paneles solares, ajustando continuamente su orientación para seguir la trayectoria del sol a lo largo del día y del año. Esto implica:

•	Obtener automáticamente la fecha y hora del sistema para calcular la posición solar actual.
•	Permitir al usuario ingresar manualmente las coordenadas geográficas para personalizar el cálculo según la ubicación del sistema de paneles solares.
•	Calcular dinámicamente los ángulos de azimuth y elevación del sol.
•	Presentar estos ángulos de manera clara para que los instaladores puedan ajustar físicamente la orientación de los paneles solares.


**Análisis de Variables**

**1.Fecha y Hora:**

-struct tm: Representa la fecha y hora del sistema, incluyendo detalles como hora, minutos, segundos, día del mes, mes, año, etc.
-Variables:
1.	int tm_sec: Segundos.
2.	int tm_min: Minutos.
3.	int tm_hour: Horas.
4.	int tm_mday: Día del mes.
5.	int tm_mon: Mes (enero = 0, diciembre = 11).
6.	int tm_year: Año desde 1900.
7.	int tm_wday: Día de la semana (domingo = 0).
8.	int tm_yday: Día del año (0-365).
9.	int tm_isdst: Horario de verano (1 si está en horario de verano, 0 si no lo está, -1 si es desconocido).
-Impacto: Permite calcular la posición del Sol en cualquier momento del año, crucial para determinar la orientación óptima de los paneles solares.

**2.Coordenadas Geográficas:**

struct Coordenadas: Almacena la longitud y latitud del lugar donde se instalan los paneles solares
Variables:
-	double longitud: Longitud geográfica del lugar en grados.
-	double latitud: Latitud geográfica del lugar en grados.
-	Impacto: Determina la posición relativa del lugar respecto al Sol, afectando directamente los cálculos de azimuth y elevación solar.

  
  **3.Parámetros Solares:**
-Declinación Solar (declinacion): Determina la inclinación del eje de la Tierra con respecto al plano orbital, afectando la altura máxima del Sol en el cielo. 
-double declinacion: Declinación solar, que determina la inclinación del eje de la Tierra con respecto al plano orbital.
-Ecuación del Tiempo (ecuacionTiempo): Corrige la diferencia entre la hora solar verdadera y la hora civil local.
-double ecuacionTiempo: Corrección de la diferencia entre la hora solar verdadera y la hora civil local.


**Hora Local (horaLocal): Tiempo local ajustado por la longitud geográfica.**

-double horaLocal: Hora local ajustada por la longitud geográfica.
-Tiempo Solar Verdadero (tiempoSolarVerdadero): Momento del día en el cual el Sol está en su punto más alto en el cielo
-double tiempoSolarVerdadero: Momento del día en el cual el Sol está en su punto más alto en el cielo.
-Altura Solar (alturaSolar): Ángulo de elevación del Sol sobre el horizonte.
-double alturaSolar: Ángulo de elevación del Sol sobre el horizonte.
-Azimuth (azimuth): Dirección del Sol medida desde el norte en sentido horario.
-double azimuth: Dirección del Sol medida desde el norte en sentido horario.


**Influencia de las Variables**

•	Fecha y Hora: Determinan la posición del Sol en el cielo, variando a lo largo del día y del año.
•	Coordenadas Geográficas: Definen la ubicación específica del sistema de paneles solares, afectando directamente la trayectoria solar observada.
•	Parámetros Solares: Calculados dinámicamente para ajustar la orientación de los paneles solares de manera óptima según la posición del Sol.


**Explicación de las Estructuras de Datos y Funciones Utilizadas**
•	Estructura struct Coordenadas:
-Almacena la longitud y latitud ingresadas manualmente por el usuario para calcular la orientación solar.
•	Funciones Utilizadas:
-obtenerHoraLocal(struct tm *fechaHora): Obtiene la fecha y hora del sistema actual.
-ingresarCoordenadas(struct Coordenadas *coord): Permite al usuario ingresar las coordenadas geográficas.
-Funciones para calcular la declinación solar, la ecuación del tiempo, la hora local, el tiempo solar verdadero, la altura solar, el ángulo de orientación solar y el azimuth solar.



**Un pseudocódigo y diagramas de flujo del algoritmo original comparados con la implementación en C.**

Inicio del Programa

    Definir Constantes:
        PI = 3.14159265
        GpH = 15.0
        LONGEST = -75.0
        vtre = -23.44

    Definir Estructura Coordenadas:
        longitud: Real
        latitud: Real

    Función obtenerHoraLocal(fechaHora: estructura tm)
        Obtener la fecha y hora del sistema y almacenarla en fechaHora usando la función localtime()

    Función ingresarCoordenadas(coord: estructura Coordenadas)
        Mostrar mensaje "Ingrese la longitud (en grados): "
        Leer y almacenar la longitud en coord.longitud
        Mostrar mensaje "Ingrese la latitud (en grados): "
        Leer y almacenar la latitud en coord.latitud

    Función calcularDeclinacion(fechaHora: estructura tm) -> Real
        Calcular el día del año (tm_yday + 1)
        Calcular la declinación solar utilizando la fórmula:
            declinacion = vtre * cos(2 * PI * (diaDelAnio + 10) / 365.0)
        Retornar declinacion

    Función calcularEcuacionDelTiempo(fechaHora: estructura tm) -> Real
        Calcular el día del año (tm_yday + 1)
        Calcular B usando la fórmula:
            B = (2 * PI * (diaDelAnio - 81)) / 365.0
        Calcular la ecuación del tiempo utilizando la fórmula:
            ecuacionTiempo = 9.87 * sin(2 * B) - 7.53 * cos(B) - 1.5 * sin(B)
        Retornar ecuacionTiempo

    Función calcularHoraLocal(fechaHora: estructura tm) -> Real
        Calcular la hora local utilizando la fórmula:
            horaLocal = tm_hour + tm_min / 60.0 + tm_sec / 3600.0
        Retornar horaLocal

    Función calcularTiempoSolarVerdadero(coord: estructura Coordenadas, horaLocal: Real, ecuacionTiempo: Real) -> Real
        Calcular el tiempo solar verdadero utilizando la fórmula:
            tiempoSolarVerdadero = horaLocal + (4 * (coord.longitud - LONGEST) + ecuacionTiempo) / 60.0
        Retornar tiempoSolarVerdadero

    Función calcularAlturaSolar(tiempoSolarVerdadero: Real) -> Real
        Calcular la altura solar utilizando la fórmula:
            alturaSolar = GpH * (tiempoSolarVerdadero - 12.0)
        Retornar alturaSolar

    Función calcularAnguloOrientacion(alturaSolar: Real, declinacion: Real, latitud: Real) -> Real
        Calcular el ángulo de orientación utilizando la fórmula:
            anguloRad = asin(sin(declinacion * PI / 180.0) * sin(latitud * PI / 180.0) +
                            cos(declinacion * PI / 180.0) * cos(latitud * PI / 180.0) * cos(alturaSolar * PI / 180.0))
            anguloOrientacion = anguloRad * 180.0 / PI
        Retornar anguloOrientacion

    Función calcularAzimuth(declinacion: Real, latitud: Real, alturaSolar: Real) -> Real
        Calcular el azimuth utilizando la fórmula:
            azimuthRad = acos((sin(declinacion * PI / 180.0) - sin(alturaSolar * PI / 180.0) * sin(latitud * PI / 180.0)) /
                             (cos(alturaSolar * PI / 180.0) * cos(latitud * PI / 180.0)))
            azimuth = azimuthRad * 180.0 / PI
        Retornar azimuth

    Procedimiento principal()
        Definir coordenadas: estructura Coordenadas
        Definir fechaHora: estructura tm
        obtenerHoraLocal(fechaHora)
        ingresarCoordenadas(coordenadas)

        declinacion = calcularDeclinacion(fechaHora)
        ecuacionTiempo = calcularEcuacionDelTiempo(fechaHora)
        horaLocal = calcularHoraLocal(fechaHora)
        tiempoSolarVerdadero = calcularTiempoSolarVerdadero(coordenadas, horaLocal, ecuacionTiempo)
        alturaSolar = calcularAlturaSolar(tiempoSolarVerdadero)
        anguloOrientacion = calcularAnguloOrientacion(alturaSolar, declinacion, coordenadas.latitud)
        azimuth = calcularAzimuth(declinacion, coordenadas.latitud, alturaSolar)

        Mostrar "Orientación óptima de los paneles solares:"
        Mostrar "Azimuth solar: " + azimuth + " grados"
        Mostrar "Ángulo de elevación solar: " + anguloOrientacion + " grados"

    Fin del Programa

**Codigo**
https://github.com/Tayron2024/Prueba/blob/bcebf81f5c154aabe3eb27fdbf9cc63bc7908079/PruebaExamen.c


**Implementación en un Sistema Real de Paneles Solares y Mejoras Futuras**

Implementación en un Sistema Real:

•	Interfaz de Usuario: El código puede integrarse en una aplicación con una interfaz gráfica para facilitar la entrada de coordenadas y mostrar los ángulos de orientación de manera más visual.

•	Sensores y Actuadores: En sistemas de paneles solares automatizados, el cálculo de orientación puede controlarse mediante sensores que detecten la posición del Sol y actuadores que ajusten automáticamente la inclinación y orientación de los paneles.

•	Integración con Predicciones Meteorológicas: Podría integrarse con datos meteorológicos en tiempo real para anticipar cambios en la radiación solar y ajustar la orientación de los paneles en consecuencia.

•	Optimización de Algoritmos: Implementar algoritmos más precisos y eficientes para el cálculo de la posición del Sol, considerando factores atmosféricos y variaciones climáticas.

•	Simulaciones y Modelos Predictivos: Desarrollar modelos predictivos que consideren el cambio estacional y la variabilidad climática para optimizar aún más la orientación de los paneles solares.

•	Soporte para Múltiples Paneles: Extender el código para manejar configuraciones con múltiples paneles solares, cada uno con su orientación óptima calculada dinámicamente.

•	Monitorización y Mantenimiento Remoto: Integrar funcionalidades de monitorización remota para supervisar el rendimiento de los paneles y realizar ajustes de orientación cuando sea necesario.

