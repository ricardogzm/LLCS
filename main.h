/*
 * Curso: Sistemas Operativos I
 * Integrantes: Juan Pablo Andrade Miron
 *              Ricardo Guzmán García
 *              Edgar Rafael Medina Lozano
 * 8 de septiembre del 2020
 */

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "generarArchivoAleatorio.h"

//Número máximo de caractéres para la cadena nombre
#define NOMBRE_MAX 100

//Definición del nodo que contiene el nombre y tiempoDeProc de ejecución
typedef struct nodo {
    int tiempoDeProc, priority;
    char nombre[NOMBRE_MAX];
    struct nodo *sig;
} Nodo;

void insertar(int d, char *N, int priority, Nodo **inicio, Nodo **final);

void eliminarI(Nodo **inicio, Nodo **final);

void eliminarF(Nodo **inicio, Nodo **final);

void mostrar(Nodo **inicio);

int leerArchivo(char *nombreArchivo, Nodo **inicio, Nodo **final, int cursor);

void generarArchivoDeProcesosPorLotes();

void despachar(Nodo **inicio, Nodo **final, int *tiempo);