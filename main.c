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

void insertar(int d, char *N);

void eliminarI();

void eliminarF();

void mostrar();

void leerArchivo(char *nombreArchivo);

void generarArchivoDeProcesosPorLotes();

//Número máximo de caractéres para la cadena nombre
#define NOMBRE_MAX 100

//Definición del nodo que contiene el nombre y tiempo de ejecución
typedef struct nodo {
    int tiempo;
    char nombre[NOMBRE_MAX];
    struct nodo *sig;
} Nodo;

//Se declaran apuntadores para el inicio y final de la lista
Nodo *inicio = NULL;  //lista vacia
Nodo *final = NULL;   //lista vacia

int main() {
    int op, tiempo;
    char nombre[NOMBRE_MAX];

    printf("** Programa que inserta datos en una lista ligada. **\n");
    do {
        printf("\nSelecciona una opcion: \n");
        printf("1. Mostrar elementos de la lista \n");
        printf("2. Insertar un elemento al final\n");
        printf("3. Eliminar elemento inicial\n");
        printf("4. Eliminar elemento final\n");
        printf("5. Leer desde archivo\n");
        printf("6. Generar archivo aleatorio\n");
        printf("0. Salir\n");
        printf("> ");
        scanf("%d", &op);
        getchar();
        printf("\n");

        switch (op) {
            case 1:
                mostrar();
                break;
            case 2:
                printf("Ingrese el nombre: ");
                fgets(nombre, NOMBRE_MAX, stdin);
                nombre[strcspn(nombre, "\n")] = 0; // Busca y elimina el salto de linea
                printf("Ingrese el tiempo de ejecución: ");
                scanf("%d", &tiempo);
                insertar(tiempo, nombre);
                break;
            case 3:
                eliminarI();
                break;
            case 4:
                eliminarF();
                break;
            case 5:
                printf("Ingresar nombre de archivo: ");
                fgets(nombre, NOMBRE_MAX, stdin);
                nombre[strcspn(nombre, "\n")] = 0;
                leerArchivo(nombre);
                break;
            case 6:
                printf("Se genero un archivo de procesos");
                generarArchivoDeProcesosPorLotes();
                break;
            case 0:
                printf("Adiós.\n");
                break;
            default:
                printf("Opción inválida.\n");
        }
    } while (op != 0);

    return 0;
}

//Insertar al inicio en la lista ligada
void insertar(int d, char *N) {
    //Creación del nodo
    Nodo *nv = (Nodo *) malloc(sizeof(Nodo));
    nv->tiempo = d;
    strcpy(nv->nombre, N);

    //Insertar el nodo al final en la lista
    if (inicio == NULL) {  //lista vacía
        nv->sig = nv;
        inicio = final = nv;  // insertamos primer elemento
    } else {
        nv->sig = inicio;
        final->sig = nv;  //actualizamos inicio
        final = nv;
    }
}

void mostrar() {
    if (inicio == NULL) {
        printf("Lista vacia\n");
    } else {
        Nodo *aux;
        //Recorrer la lista hasta el último nodo
        aux = inicio;
        do {
            printf("Proceso: %s, Tiempo: %d, -> ", aux->nombre, aux->tiempo);
            aux = aux->sig;
        } while (aux != final);
        printf("Proceso: %s, Tiempo: %d", aux->nombre, aux->tiempo);

        printf("\n");
    }
}

//Función que elimina el nodo inicial
void eliminarI() {
    Nodo *aux;
    if (inicio == NULL)
        printf("Lista vacía.\n");
    else {
        if (inicio == final) {  //Se libera memoria del único nodo y se restauran apuntadores
            free(inicio);
            inicio = final = NULL;
        } else {    //Eliminación del nodo inicial
            aux = inicio;
            inicio = inicio->sig;
            final->sig = inicio;
            free(aux);
        }
    }
}

//Función que elimina el nodo final
void eliminarF() {
    Nodo *aux, *aux2;
    if (inicio == NULL)
        printf("Lista vacía.\n");
    else {
        if (inicio == final) {  //Se libera memoria del único nodo y se restauran apuntadores
            free(inicio);
            inicio = final = NULL;
        } else {    //Eliminación del nodo final
            aux = final;
            aux2 = inicio;
            while (aux2->sig != final)
                aux2 = aux2->sig;
            aux2->sig = inicio;
            final = aux2;
            free(aux);
        }
    }
}

void leerArchivo(char *nombreArchivo) {
    FILE *f;
    int tiempo;
    char nombre[NOMBRE_MAX];

    //Si no pudo abrir el archivo no hace nada y se sale del método.
    if ((f = fopen(nombreArchivo, "r")) == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    //Si lo pudo abrir, borra todos los elementos de la lista ligada
    while (inicio != NULL) {
        eliminarI();
    }

    //Mientras la cantidad de elementos leídos con éxito sea mayor a 0 seguirá leyendo
    while (fscanf(f, "%s %d", nombre, &tiempo) > 0) {
        insertar(tiempo, nombre);
    }

    //Cierra el archivo
    fclose(f);
}
