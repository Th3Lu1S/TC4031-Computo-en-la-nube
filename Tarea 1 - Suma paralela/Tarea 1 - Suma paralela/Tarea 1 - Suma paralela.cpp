// Tarea 1 - Suma paralela.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>     // Incluye la biblioteca para operaciones de entrada y salida
#include <omp.h>        // Incluye la biblioteca para usar OpenMP
#include <cstdlib>      // Incluye la biblioteca para generar n�meros aleatorios
#include <ctime>        // Incluye la biblioteca para inicializar la semilla de n�meros aleatorios

#define N 10000         //N - Ser� la cantidad de elementos a manejar en los arreglos
#define chunk 1000       //chunk - Ser� el tama�o que tendr�n los pedazos de los arreglos para que cada hilo creado se encargue de esta cantidad de elementos
#define mostrar 20     //mostrar - Permitir� manejar la cantidad de datos a imprimir

void imprimeArreglo(float * d); // Declaraci�n de una funci�n para imprimir los arreglos

int main()
{
    std::cout << "Verificando la ejecucion de las directivas OMP!\n";
    #ifdef _OPENMP
        std::cout << "OMP disponible y funcionando" << std::endl;       // Validar si podemos usar OpenMP sin ning�n problema
    # endif

    std::cout << "Sumando Arreglos en Paralelo!\n";     // Mensaje inicial para indicar el comienzo del programa
    float a[N], b[N], c[N];                             // Arreglos que almacenar�n los valores de entrada y salida
    int i;                                              // Variable para controlar los bucles

    std::srand(std::time(0));                           // Inicializaci�n de la semilla para generar n�meros aleatorios
    
    for (i = 0; i < N; i++)                             // Inicializaci�n de los arreglos "a" y "b" con valores aleatorios
    {
        a[i] = static_cast<float>(std::rand() % 100);   // Valores aleatorios entre 0 y 99
        b[i] = static_cast<float>(std::rand() % 100);   // Valores aleatorios entre 0 y 99
    }
    int pedazos = chunk;                               // Definici�n del tama�o de los pedazos que se usar�n en la distribuci�n del trabajo

    // Esta codigo paraleliza el bucle `for` usando OpenMP.
    // Las variables a, b, c y pedazos son compartidas por todos los hilos.
    // La variable `i` es privada para evitar condiciones de carrera (que no se mezcle con la de los ciclos de otro hilo).
    // El trabajo se divide de forma est�tica en trozos de tama�o 'pedazos'.
    #pragma omp parallel for \
    shared(a, b, c, pedazos) private(i) \
    schedule(static, pedazos)

    for (i = 0; i < N; i++)
        c[i] = a[i] + b[i];                             // Cada elemento del arreglo "c" es la suma de los correspondientes elementos de "a" y "b"

    // Impresi�n de los resultados de los arreglos iniciales y el arreglo resultado
    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo a: " << std::endl;
    imprimeArreglo(a);
    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo b: " << std::endl;
    imprimeArreglo(b);
    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo c: " << std::endl;
    imprimeArreglo(c);
}
// Implementaci�n de la funci�n para imprimir los arreglos
// Recibe como par�metro un apuntador al arreglo "d"
void imprimeArreglo(float * d)
{
    for (int x = 0; x < mostrar; x++)           // Itera s�lo sobre los primeros "mostrar" elementos del arreglo
        std::cout << d[x] << " - ";             // Imprime cada elemento seguido de un guion
    std::cout << std::endl;                     // Imprime una nueva l�nea al final para separar los resultados
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

