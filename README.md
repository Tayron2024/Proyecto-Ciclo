Diapos: https://www.canva.com/design/DAFoeF7Q2z0/Hlvmx4vdAuXlucRIEMYkCw/edit?utm_content=DAFoeF7Q2z0&utm_campaign=designshare&utm_medium=link2&utm_source=sharebutton


# **UNIVERSIDAD NACIONAL DE LOJA**


## **Algoritmo para Optimización de Orientación de Paneles Solares**

**Presentado por: Tayron Morales, Matias Medina, Victor Macas**

**Fecha:** 16/06/2024

![Banner-Blog-Airis](https://github.com/Tayron2024/Prueba/assets/169932075/ccfc80eb-5521-4334-81d7-65837258254f)

### **Descripción del Proyecto**

En el contexto de la creciente necesidad de utilizar fuentes de energía renovable, los paneles solares juegan un papel crucial al convertir la radiación solar en electricidad. 
Para maximizar la eficiencia de estos sistemas, es fundamental optimizar la orientación de los paneles solares de manera dinámica, considerando la posición cambiante del Sol a lo largo del día y del año. 
Este trabajo presenta un algoritmo diseñado para calcular automáticamente los ángulos de azimuth y elevación del Sol, asegurando así que los paneles solares capturen la máxima radiación solar disponible en todo momento.


### **Descripción del Problema y Objetivo del Algoritmo**

El problema abordado es determinar la orientación óptima de paneles solares en tiempo real para maximizar la captación de luz solar. Esto implica calcular dinámicamente los ángulos de azimuth y elevación del sol en función de la ubicación geográfica y la hora del día, asegurando así que los paneles solares estén orientados de manera que capturen la máxima radiación solar posible en todo momento.


### **El objetivo del algoritmo es proporcionar una herramienta computacional que permita:**

-	Obtener automáticamente la fecha y hora del sistema.
-	Permitir al usuario ingresar manualmente las coordenadas geográficas donde se instalarán los paneles solares.
-	Calcular la orientación óptima de los paneles solares en términos de azimuth y ángulo de elevación.
-	Mostrar estos valores para que los instaladores puedan ajustar físicamente la posición de los paneles solares.


### **Análisis de Variables**

**1.Fecha y Hora:**

- Struct tm: Representa la fecha y hora del sistema, incluyendo detalles como hora, minutos, segundos, día del mes, mes, año, etc.
- Variables:
1.	int tm_sec: Segundos.
2.	int tm_min: Minutos.
3.	int tm_hour: Horas.
4.	int tm_mday: Día del mes.
5.	int tm_mon: Mes (enero = 0, diciembre = 11).
6.	int tm_year: Año desde 1900.
7.	int tm_wday: Día de la semana (domingo = 0).
8.	int tm_yday: Día del año (0-365).
9.	int tm_isdst: Horario de verano (1 si está en horario de verano, 0 si no lo está, -1 si es desconocido).
- Impacto: Permite calcular la posición del Sol en cualquier momento del año, crucial para determinar la orientación óptima de los paneles solares.

![word-image-106](https://github.com/Tayron2024/Prueba/assets/169932075/359973ee-6d49-4aed-b7c6-bbec888f470c)

**2.Coordenadas Geográficas:**

Struct Coordenadas: Almacena la longitud y latitud del lugar donde se instalan los paneles solares
Variables:

-	"Double" longitud: Longitud geográfica del lugar en grados.
-	"Double" latitud: Latitud geográfica del lugar en grados.
-	Impacto: Determina la posición relativa del lugar respecto al Sol, afectando directamente los cálculos de azimuth y elevación solar.

  ![las-coordenadas-en-un-mapa-para-primaria](https://github.com/Tayron2024/Prueba/assets/169932075/3667fdac-1527-4faa-80d5-35dfd35ef9f7)

  **3.Parámetros Solares:**
  
- Declinación Solar (declinacion): Determina la inclinación del eje de la Tierra con respecto al plano orbital, afectando la altura máxima del Sol en el cielo. 
- Double declinacion
- Ecuación del Tiempo (ecuacionTiempo): Corrige la diferencia entre la hora solar verdadera y la hora civil local.
- Double ecuacionTiempo: Corrección de la diferencia entre la hora solar verdadera y la hora civil local.

![orientacion-inclinacion-panel](https://github.com/Tayron2024/Prueba/assets/169932075/97c834a5-5c72-4b70-9f4a-cab9297694c0)

**Hora Local (horaLocal): Tiempo local ajustado por la longitud geográfica.**

- "Double" horaLocal: Hora local ajustada por la longitud geográfica.
- Tiempo Solar Verdadero (tiempoSolarVerdadero): Momento del día en el cual el Sol está en su punto más alto en el cielo
- "Double" tiempoSolarVerdadero
- Altura Solar (alturaSolar): Ángulo de elevación del Sol sobre el horizonte.
- "Double" alturaSolar
- Azimuth (azimuth): Dirección del Sol medida desde el norte en sentido horario.
- "Double" azimuth


**Influencia de las Variables**

•	Fecha y Hora: Determinan la posición del Sol en el cielo, variando a lo largo del día y del año

•	Coordenadas Geográficas: Definen la ubicación específica del sistema de paneles solares, afectando directamente la trayectoria solar observada

•	Parámetros Solares: Calculados dinámicamente para ajustar la orientación de los paneles solares de manera óptima según la posición del Sol


### **Explicación de las Estructuras de Datos y Funciones Utilizadas**

•	Estructura struct Coordenadas:

- Almacena la longitud y latitud ingresadas manualmente por el usuario para calcular la orientación solar
  
•	Funciones Utilizadas:

- obtenerHoraLocal(struct tm *fechaHora): Obtiene la fecha y hora del sistema actual.
  
- ingresarCoordenadas(struct Coordenadas *coord): Permite al usuario ingresar las coordenadas geográficas.

- Funciones para calcular la declinación solar, la ecuación del tiempo, la hora local, el tiempo solar verdadero, la altura solar, el ángulo de orientación solar y el azimuth solar.


### **Un pseudocódigo y diagramas de flujo del algoritmo original comparados con la implementación en C.**

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
    
### **Diagrama de Flujo**

- Funcion Main
![WhatsApp Image 2024-06-16 at 20 33 21](https://github.com/Tayron2024/Prueba/assets/169932075/bdf435b5-470b-44da-a4d5-a6b0e2540ea7)
![WhatsApp Image 2024-06-16 at 20 34 43](https://github.com/Tayron2024/Prueba/assets/169932075/2bfe0139-4eae-46d8-a893-9ec5124c95bd)
![WhatsApp Image 2024-06-16 at 20 35 14](https://github.com/Tayron2024/Prueba/assets/169932075/a4164b02-8477-4b32-a36b-92fd760ee52d)
![WhatsApp Image 2024-06-16 at 20 37 43](https://github.com/Tayron2024/Prueba/assets/169932075/213a85d5-f550-45e6-81b7-1f4658b8a61a)
![WhatsApp Image 2024-06-16 at 20 38 01](https://github.com/Tayron2024/Prueba/assets/169932075/8fc25954-c906-4a1c-bf54-75cfb3242dfa)
![WhatsApp Image 2024-06-16 at 20 38 25](https://github.com/Tayron2024/Prueba/assets/169932075/eb1d7412-5fe7-4b73-b3f4-056efa2056b4)
![WhatsApp Image 2024-06-16 at 20 38 48](https://github.com/Tayron2024/Prueba/assets/169932075/095a7a37-b0db-41b8-9191-86509380bc0e)
![WhatsApp Image 2024-06-16 at 20 39 44](https://github.com/Tayron2024/Prueba/assets/169932075/f79498db-ce68-4e5c-970b-2b8bf2e65ee0)
- Struct del Azimuth
![WhatsApp Image 2024-06-16 at 20 40 11](https://github.com/Tayron2024/Prueba/assets/169932075/7ae58325-d400-40d6-90a8-504e91a869a7)



### **Codigo**
https://github.com/Tayron2024/Prueba/blob/99ff764baa2cb27f678a62f825c885cea9467747/PruebaExamen.c

Cálculos Utilizados

![Imagen1](https://github.com/Tayron2024/Prueba/assets/169932075/5a535d61-1b50-482b-b9d4-d33bef203b0a)

![Imagen2](https://github.com/Tayron2024/Prueba/assets/169932075/9718da92-bfe6-4bba-8938-d4f12c56adc7)

![Imagen3](https://github.com/Tayron2024/Prueba/assets/169932075/2a9ee401-edf2-4574-b663-8a5d2e0cf77a)

![Imagen4](https://github.com/Tayron2024/Prueba/assets/169932075/63c643f5-478e-4c86-8f66-5e917959f1d6)

![Imagen5](https://github.com/Tayron2024/Prueba/assets/169932075/aad616c4-6974-44e4-9bd8-6c740193f479)

![Imagen6](https://github.com/Tayron2024/Prueba/assets/169932075/1bc3ff22-89f0-4ca3-9704-09c83055faf8)


Referencias
https://images.app.goo.gl/txU9i8VxaMnANEcr6

https://images.app.goo.gl/2c4oqbHvELzahhqCA

https://images.app.goo.gl/y75bgKa2di76gcsB6	

https://es.planetcalc.com/4270/

https://www.pveducation.org/es/fotovoltaica/2-propiedades-de-la-luz-del-sol/hora-solar

https://concepto.de/coordenadas-geograficas/

https://www.coordenadas-gps.com

https://www.sfe-solar.com/noticias/articulos/parametros-panel-fotovoltaico/


### **Implementación en un Sistema Real de Paneles Solares y Mejoras Futuras**

**Implementación en un Sistema Real:**

•	Interfaz de Usuario: El código puede integrarse en una aplicación con una interfaz gráfica para facilitar la entrada de coordenadas y mostrar los ángulos de orientación de manera más visual.

•	Sensores y Actuadores: En sistemas de paneles solares automatizados, el cálculo de orientación puede controlarse mediante sensores que detecten la posición del Sol y actuadores que ajusten automáticamente la inclinación y orientación de los paneles.

•	Integración con Predicciones Meteorológicas: Podría integrarse con datos meteorológicos en tiempo real para anticipar cambios en la radiación solar y ajustar la orientación de los paneles en consecuencia.

•	Optimización de Algoritmos: Implementar algoritmos más precisos y eficientes para el cálculo de la posición del Sol, considerando factores atmosféricos y variaciones climáticas.

•	Simulaciones y Modelos Predictivos: Desarrollar modelos predictivos que consideren el cambio estacional y la variabilidad climática para optimizar aún más la orientación de los paneles solares.

•	Soporte para Múltiples Paneles: Extender el código para manejar configuraciones con múltiples paneles solares, cada uno con su orientación óptima calculada dinámicamente.

•	Monitorización y Mantenimiento Remoto: Integrar funcionalidades de monitorización remota para supervisar el rendimiento de los paneles y realizar ajustes de orientación cuando sea necesario.

### **Requisitos**

**Requisitos de Hardware**

### **Computadora o Dispositivo Compatible:**

Se necesita un ordenador o dispositivo móvil capaz de ejecutar programas en lenguaje C.
Procesador y memoria suficiente para ejecutar el sistema operativo y compilador.
Requisitos de Software

### **Sistema Operativo:**

Cualquier sistema operativo compatible con compiladores de C, como Windows, macOS, Linux, etc.

### **Compilador de C:**

**Un compilador de C compatible instalado en el sistema, como:**

Para Windows: MinGW, Microsoft Visual Studio (con soporte para C), Cygwin.
Para macOS: Xcode con Clang, GCC a través de Homebrew.
Para Linux: GCC (GNU Compiler Collection), Clang.

**Librerías Estándar de C:**

Las librerías estándar de C como stdio.h, math.h, y time.h deben estar disponibles y accesibles para el compilador.
Detalles Adicionales
Entorno de Desarrollo Integrado (IDE):

Opcionalmente, un IDE como Visual Studio Code, Xcode, Eclipse o Code::Blocks puede facilitar el desarrollo y la depuración del código.

**Acceso a Internet:**

Para instalar o actualizar el compilador y las herramientas necesarias, así como para acceder a documentación adicional.

### **Instrucciones de Instalación**


Pasos para la Instalación y Compilación en Visual Studio Code (Windows)

### 1. Instalar Visual Studio Code
Si aún no tienes Visual Studio Code instalado, puedes descargarlo e instalarlo desde su sitio oficial.

### 2. Instalar MinGW (Minimalist GNU for Windows)
MinGW es un entorno de desarrollo para Windows que proporciona una implementación de GCC (GNU Compiler Collection), necesario para compilar programas en C.


Durante la instalación de MinGW, asegúrate de seleccionar al menos las siguientes componentes:

mingw32-base
mingw32-gcc-g++
msys-base
Después de la instalación, añade la ruta de MinGW al PATH del sistema:

Abre el menú de inicio y busca "Editar las variables de entorno del sistema".
Haz clic en "Variables de entorno".
En la sección "Variables del sistema", selecciona la variable PATH y haz clic en "Editar...".
Añade la ruta donde MinGW está instalado (por ejemplo, C:\MinGW\bin) al final de la lista separada por un punto y coma si no está ya presente.
Haz clic en "Aceptar" para cerrar todas las ventanas de configuración.

### 3. Clonar el Repositorio desde GitHub
Abre Visual Studio Code y sigue estos pasos:

Abrir Terminal Integrada:

Ve al menú View -> Terminal o usa el atajo `Ctrl + `` para abrir la terminal integrada en Visual Studio Code.
Clonar el Repositorio:

En la terminal, navega hasta el directorio donde deseas clonar el repositorio usando el comando cd ruta\hacia\el\directorio.
Clona el repositorio utilizando el comando git clone URL_del_repositorio donde URL_del_repositorio es la URL del repositorio en GitHub.
Por ejemplo:

git clone https://github.com/tu_usuario/tu_repositorio.git (link de ejemplo no funcional)
Esto creará una copia del repositorio en tu máquina local.
Abrir el Proyecto en Visual Studio Code:

Ve a File -> Open Folder... y selecciona la carpeta del repositorio clonado para abrirlo en Visual Studio Code.

### 4. Compilar y Ejecutar el Código
Configurar el Archivo de Configuración de Compilación:

Crea un archivo llamado tasks.json dentro de la carpeta .vscode en tu proyecto. Puedes crearlo manualmente o utilizando la funcionalidad de Visual Studio Code para generar tareas de compilación.

Compilar y Ejecutar:

Abre el archivo main.c en Visual Studio Code.
Pulsa Ctrl + Shift + B para compilar el código. Esto ejecutará el comando gcc especificado en tasks.json para compilar el archivo main.c.
Si no hay errores de compilación, se generará un archivo ejecutable main.exe en la misma carpeta donde se encuentra main.c.
Ejecutar el Programa:

Desde la terminal integrada en Visual Studio Code, puedes ejecutar el programa compilado escribiendo ./main.exe y presionando Enter.

### **Uso**
Instrucciones sobre cómo ejecutar el programa y proporcionar entradas (coordenadas geográficas). Ejemplos de comandos y posibles resultados.

Instrucciones para Ejecutar el Programa
Clonar el Repositorio y Preparar el Entorno:

Sigue los pasos descritos anteriormente para clonar el repositorio en tu máquina y configurar el entorno de desarrollo en Visual Studio Code con MinGW.
Abrir el Proyecto en Visual Studio Code:

Abre Visual Studio Code y abre la carpeta del repositorio clonado.
Configurar las Coordenadas Geográficas:

El programa solicitará al usuario ingresar las coordenadas geográficas (longitud y latitud) mediante la entrada estándar. Asegúrate de tener estas coordenadas listas para ingresarlas cuando se solicite.
Compilar el Código:

Abre el archivo main.c en Visual Studio Code y asegúrate de que tasks.json esté configurado correctamente para compilar el código usando GCC.

Presiona Ctrl + Shift + B para compilar el código. Esto generará un archivo ejecutable main.exe en la misma carpeta donde se encuentra main.c.

Ejecutar el Programa:

Desde la terminal integrada en Visual Studio Code (o desde una terminal externa si lo prefieres), ejecuta el programa compilado escribiendo ./main.exe y presionando Enter.
Ingresar las Coordenadas Geográficas:

El programa solicitará ingresar la longitud y la latitud en grados. Sigue las instrucciones que aparecen en la consola y proporciona las coordenadas geográficas adecuadas cuando se te solicite.
Ejemplos de Comandos y Posibles Resultados

### **EJEMPLOS**

Ejemplo 1: Coordenadas de Nueva York
Supongamos que las coordenadas geográficas para Nueva York son:

Longitud: -74.0060 grados
Latitud: 40.7128 grados
Ejecuta el programa desde la terminal integrada en Visual Studio Code:

./main.exe
El programa solicitará ingresar la longitud (en grados):

Ingrese la longitud (en grados): -74.0060
Luego, solicitará ingresar la latitud (en grados):

Ingrese la latitud (en grados): 40.7128
Después de ingresar las coordenadas, el programa calculará y mostrará la orientación óptima de los paneles solares:

Orientación óptima de los paneles solares:
Azimuth solar: 179.63 grados
Ángulo de elevación solar: 61.06 grados


Ejemplo 2: Coordenadas de Ciudad de México
Supongamos que las coordenadas geográficas para la Ciudad de México son:

Longitud: -99.1332 grados
Latitud: 19.4326 grados

Ejecuta el programa desde la terminal integrada en Visual Studio Code:

./main.exe

El programa solicitará ingresar la longitud (en grados):

Ingrese la longitud (en grados): -99.1332
Luego, solicitará ingresar la latitud (en grados):


Copiar códigoIngrese la latitud (en grados): 19.4326
Después de ingresar las coordenadas, el programa calculará y mostrará la orientación óptima de los paneles solares:

Orientación óptima de los paneles solares:
Azimuth solar: 180.16 grados
Ángulo de elevación solar: 83.61 grados


### **Notas Importantes**

Asegúrate de ingresar las coordenadas geográficas correctamente en el formato solicitado por el programa (grados decimales), el minimo error el programa puede marcar resultados que no funcionen o al error mismo del codigo.

Los resultados pueden variar dependiendo de la ubicación geográfica y la hora del día en que se ejecuta el programa debido a la naturaleza dinámica de la posición del sol.
