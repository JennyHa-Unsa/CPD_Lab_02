# Laboratorio 2 - Evaluación del desempeño de algoritmos y  comportamiento de la memoria caché

Este repositorio contiene una implementación y análisis de rendimiento de dos enfoques clásicos para la multiplicación de matrices en C++: la **Multiplicación Clásica** (fuerza bruta) y la **Multiplicación por Bloques** (optimizada para caché).

El objetivo es demostrar cómo la organización de los datos y el acceso a la memoria afectan drásticamente el tiempo de ejecución en operaciones matemáticas intensivas.

## 📂 Estructura del Repositorio

El proyecto está dividido en dos partes principales, cada una con su código fuente, ejecutable y resultados:

### Archivos preliminares
*   `1_bucles.cpp`: Pruebas preliminares o análisis de bucles anidados.
*   `1_bucles.csv` / `1_bucles.png`: Resultados de las pruebas preliminares.

### 1. Multiplicación Clásica
Implementación estándar $O(N^3)$ sin optimizaciones de memoria.
*   `2_multiplicacion_clasica.cpp`: Código fuente.
*   `2_multiplicacion_clasica`: Ejecutable compilado.
*   `resultados_multiplicacion_clasica.csv`: Datos crudos de tiempos de ejecución.
*   `2_clasica.png`: Gráfica de resultados.

### 2. Multiplicación por Bloques
Implementación optimizada que divide las matrices en sub-bloques para aprovechar la memoria caché del procesador.
*   `3_multiplicacion_bloques.cpp`: Código fuente.
*   `3_multiplicacion_bloques`: Ejecutable compilado.
*   `resultados_bloques.csv`: Datos crudos de tiempos de ejecución.
*   `3_bloques.png`: Gráfica de resultados.


---

## ️ Cómo Compilar y Ejecutar

Para ejecutar los programas, necesitas un compilador de C++ (como `g++`). Se recomienda usar optimizaciones básicas (`-O2`) para obtener resultados realistas, aunque el código funciona sin ellas.

Por ejemplo para el caso de la Multiplicación Clásica

Compila el código:
```bash
g++ -O2 -o 2_multiplicacion_clasica 2_multiplicacion_clasica.cpp
```
Ejecuta el programa:
```bash
./2_multiplicacion_clasica
```

**Nota:** Los programas generarán o actualizarán los archivos .csv correspondientes en el directorio actual con los tiempos medidos.
