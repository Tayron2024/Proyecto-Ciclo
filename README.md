**Codigo**


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


**Implementación en un Sistema Real de Paneles Solares y Mejoras Futuras**

Implementación en un Sistema Real:

•	Interfaz de Usuario: El código puede integrarse en una aplicación con una interfaz gráfica para facilitar la entrada de coordenadas y mostrar los ángulos de orientación de manera más visual.

•	Sensores y Actuadores: En sistemas de paneles solares automatizados, el cálculo de orientación puede controlarse mediante sensores que detecten la posición del Sol y actuadores que ajusten automáticamente la inclinación y orientación de los paneles.

•	Integración con Predicciones Meteorológicas: Podría integrarse con datos meteorológicos en tiempo real para anticipar cambios en la radiación solar y ajustar la orientación de los paneles en consecuencia.

•	Optimización de Algoritmos: Implementar algoritmos más precisos y eficientes para el cálculo de la posición del Sol, considerando factores atmosféricos y variaciones climáticas.

•	Simulaciones y Modelos Predictivos: Desarrollar modelos predictivos que consideren el cambio estacional y la variabilidad climática para optimizar aún más la orientación de los paneles solares.

•	Soporte para Múltiples Paneles: Extender el código para manejar configuraciones con múltiples paneles solares, cada uno con su orientación óptima calculada dinámicamente.

•	Monitorización y Mantenimiento Remoto: Integrar funcionalidades de monitorización remota para supervisar el rendimiento de los paneles y realizar ajustes de orientación cuando sea necesario.

