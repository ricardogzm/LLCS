#include <stdio.h>
#include <malloc.h>

void insertarAlInicio(int d);

void insertarAlFinal(int d);

void mostrar();

//Definimos nuestros Nodos
typedef struct nodo {
    int dato;
    struct nodo *sig;
} Nodo;

//declarar el inicio de la lista
Nodo * inicio = NULL;  //lista vacia

int main() {
    int op, dato, kk;

    printf("Programa que inserta datos en una lista ligada\n");
    do {
        printf("Selecciona una opcion: \n");
        printf("1. Mostrar elementos de la lista \n");
        printf("2. Insertar un elemento al inicio de la lista \n");
        printf("3. Insertar un elemento al final de la lista\n");
        printf("0. Salir\n");
        printf("Opcion: ");
        scanf("%d", &op);
        switch (op) {
            case 1:
                mostrar();
                break;
            case 2:
                printf("Ingrese elemento a incertar al inicio\n");
                scanf("%d", &dato);
                insertarAlInicio(dato);
                break;
            case 3:
                printf("Ingrese elemento a incertar al final\n");
                scanf("%d", &dato);
                insertarAlFinal(dato);
                break;
            case 0:
                printf("Bonito día\n");
                break;
            default:
                printf("Opcion invalida \n");
        }
    } while (op != 0);
    return 0;
}

//Insertar al inicio en la lista ligada
void insertarAlInicio(int d) {
    //crear el nodo
    Nodo *nv = (Nodo *) malloc(sizeof(Nodo));
    nv->dato = d;
    nv->sig = NULL;  //siempre NULL

    //Insertar el nodo al inicio en la lista
    if (inicio == NULL) { //lista vacia
        inicio = nv;  // insertamos primer elemento
    } else {
        nv->sig = inicio;
        inicio = nv;  //actualizamos inicio
    }
}

void insertarAlFinal(int d) {
    //crear el nodo
    Nodo *nv = (Nodo *) malloc(sizeof(Nodo));
    nv->dato = d;
    nv->sig = NULL;  //siempre NULL

    if (inicio == NULL) {  //lista vacia solo se inserta nodo
        inicio = nv;
    } else {
        Nodo *aux;
        //recorrer la lista hasta el ultimo nodo
        aux = inicio;
        while (aux->sig != NULL) {
            aux = aux->sig;
        }
        aux->sig = nv;
    }
}

void mostrar() {
    if (inicio == NULL) {  //lista vacia solo se inserta nodo
        printf("Lista vacia\n");
    } else {
        Nodo *aux;
        //recorrer la lista hasta el ultimo nodo
        aux = inicio;
        while (aux != NULL) {
            printf("%d -> ", aux->dato);
            aux = aux->sig;
        }
        printf("\n");
    }

}

