#include <stdio.h>
#include <malloc.h>
#include <string.h>

void insertar(int d, char *N);
void eliminarI();
void eliminarF();
void mostrar();
void leerArchivo(char *nombreArchivo);

#define NOMBRE_MAX 100

//Definimos nuestros Nodos
typedef struct nodo {
    int tiempo;
    char nombre[NOMBRE_MAX];
    struct nodo *sig;
} Nodo;

//declarar el inicio de la lista
Nodo *inicio = NULL;  //lista vacia
Nodo *final = NULL;   //lista vacia

int main() {
    int op, tiempo;
    char nombre[NOMBRE_MAX];

    printf("Programa que inserta datos en una lista ligada\n");
    do {
        printf("Selecciona una opcion: \n");
        printf("1. Mostrar elementos de la lista \n");
        printf("2. Insertar un elemento al inicio de la lista \n");
        printf("3. Eliminar el inicio\n");
        printf("4. Eliminar el final\n");
        printf("5. Leer desde archivo\n");
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
                printf("Ingrese el nombre\n");
                fgets(nombre, NOMBRE_MAX, stdin );
                nombre[strcspn(nombre, "\n")] = 0; // Busca y elimina el salto de linea
                printf("Ingrese el tiempo de ejecucion\n");
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
            case 0:
                printf("Adios.\n");
                break;
            default:
                printf("Opcion invalida \n");
        }
    } while (op != 0);

    return 0;
}

//Insertar al inicio en la lista ligada
void insertar(int d, char *N) {
    //crear el nodo
    Nodo *nv = (Nodo *) malloc(sizeof(Nodo));
    nv->tiempo = d;
    strcpy(nv->nombre,N);


    //Insertar el nodo al final en la lista
    if (inicio == NULL) {  //lista vacia
        nv->sig = nv;
        inicio = final = nv;  // insertamos primer elemento
    } else{
        nv->sig = inicio;
        final->sig = nv;  //actualizamos inicio
        final = nv;
    }
}

void mostrar() {
    if (inicio == NULL) {  //lista vacia solo se inserta nodo
        printf("Lista vacia\n");
    } else {
        Nodo *aux;
        //recorrer la lista hasta el ultimo nodo
        aux = inicio;
        do {
            printf("Proceso: %s, Tiempo: %d, -> ",aux->nombre, aux->tiempo);
            aux = aux->sig;
        } while (aux != final);
        printf("Proceso: %s, Tiempo: %d",aux->nombre, aux->tiempo);

        printf("\n");
    }
}

void eliminarI() {
    Nodo *aux;
    if (inicio == NULL)
        printf("Lista vacia\n");
    else {
        if (inicio == final) {
            free(inicio);
            inicio = final = NULL;
        } else {
            aux = inicio;
            inicio = inicio->sig;
            final->sig = inicio;
            free(aux);
        }
    }
}

void eliminarF() {
    Nodo *aux, *aux2;
    if(inicio == NULL)
        printf("Lista vacia\n");
    else{
        if(inicio==final){
            free(inicio);
            inicio = final = NULL;
        } else{
            aux = final;
            aux2 = inicio;
            while (aux2->sig != final)
                aux2 = aux2 -> sig;
            aux2 -> sig = inicio;
            final = aux2;
            free(aux);
        }
    }
}

void leerArchivo(char *nombreArchivo) {
    FILE *f;
    int tiempo;
    char nombre[NOMBRE_MAX];

    if ((f = fopen(nombreArchivo, "r")) == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    while (inicio != NULL) {
        eliminarI();
    }

    while (fscanf(f, "%s %d", nombre, &tiempo) > 0) {
        insertar(tiempo, nombre);
    }

    fclose(f);
}
