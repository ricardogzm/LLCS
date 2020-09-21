#include "main.h"

int main() {
    int op;
    int cursor=0;
    char nombre[NOMBRE_MAX];
    Nodo *inicio = NULL;  //lista vacia
    Nodo *final = NULL;   //lista vacia

    printf("** Programa que inserta datos en una lista ligada. **\n");
    do {
        printf("\nSelecciona una opcion: \n");
        printf("1. Mostrar elementos de la lista \n");
        printf("2. Eliminar elemento inicial\n");
        printf("3. Eliminar elemento final\n");
        printf("4. Leer desde archivo\n");
        printf("6. Generar archivo aleatorio\n");
        printf("0. Salir\n");
        printf("> ");
        scanf("%d", &op);
        getchar();
        printf("\n");

        switch (op) {
            case 1:
                mostrar(&inicio);
                break;
//            case 2:
//                printf("Ingrese el nombre: ");
//                fgets(nombre, NOMBRE_MAX, stdin);
//                nombre[strcspn(nombre, "\n")] = 0; // Busca y elimina el salto de linea
//                printf("Ingrese el tiempoDeProc de ejecución: ");
//                scanf("%d", &tiempoDeProc);
//                insertar(tiempoDeProc, nombre, &inicio, &final);
//                break;
            case 2:
                eliminarI(&inicio, &final);
                break;
            case 3:
                eliminarF(&inicio, &final);
                break;
            case 4:
                printf("Ingresar nombre de archivo: ");
                fgets(nombre, NOMBRE_MAX, stdin);
                nombre[strcspn(nombre, "\n")] = 0;
                cursor=leerArchivo(nombre, &inicio, &final, cursor);
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
void insertar(int d, char *N, int priority, Nodo **inicio, Nodo **final) {
    //Creación del nodo
    Nodo *nv = (Nodo *) malloc(sizeof(Nodo));
    nv->tiempoDeProc = d;
    nv->priority = priority;
    strcpy(nv->nombre, N);

    //Insertar el nodo al final en la lista
    if (*inicio == NULL) {  //lista vacía
        nv->sig = nv;
        *inicio = *final = nv;  // insertamos primer elemento
    } else {
        nv->sig = *inicio;
        (*final)->sig = nv;  //actualizamos inicio
        *final = nv;
    }
}

void mostrar(Nodo **inicio) {
    if (*inicio == NULL) {
        printf("Lista vacia\n");
    } else {
        Nodo *aux;
        //Recorrer la lista hasta el último nodo
        aux = *inicio;

        do {
            printf("Proc: %s, TiempProc: %d, Prioridad: %d -> ", aux->nombre, aux->tiempoDeProc, aux->priority);
            aux = aux->sig;
        } while (aux != *inicio);

        printf("\n");
    }
}

//Función que elimina el nodo inicial
void eliminarI(Nodo **inicio, Nodo **final) {
    Nodo *aux;
    if (*inicio == NULL)
        printf("Lista vacía.\n");
    else {
        if (*inicio == *final) {  //Se libera memoria del único nodo y se restauran apuntadores
            free(*inicio);
            *inicio = *final = NULL;
        } else {    //Eliminación del nodo inicial
            aux = *inicio;
            *inicio = (*inicio)->sig;
            (*final)->sig = *inicio;
            free(aux);
        }
    }
}

//Función que elimina el nodo final
void eliminarF(Nodo **inicio, Nodo **final) {
    Nodo *aux, *aux2;
    if (*inicio == NULL)
        printf("Lista vacía.\n");
    else {
        if (*inicio == *final) {  //Se libera memoria del único nodo y se restauran apuntadores
            free(*inicio);
            *inicio = *final = NULL;
        } else {    //Eliminación del nodo final
            aux = *final;
            aux2 = *inicio;
            while (aux2->sig != *final)
                aux2 = aux2->sig;
            aux2->sig = *inicio;
            *final = aux2;
            free(aux);
        }
    }
}

int leerArchivo(char *nombreArchivo, Nodo **inicio, Nodo **final, int cursor) {
    FILE *f;
    int tiempo, priority;
    char nombre[NOMBRE_MAX];

    //Si no pudo abrir el archivo no hace nada y se sale del método.
    if ((f = fopen(nombreArchivo, "r")) == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return -1;
    }

    //Si lo pudo abrir, borra todos los elementos de la lista ligada
    while (*inicio != NULL) {
        eliminarI(inicio, final);
    }

    fseek(f, cursor, SEEK_SET);

    //Mientras la cantidad de elementos leídos con éxito sea mayor a 0 seguirá leyendo
    while (fscanf(f, "%s %d %d", nombre, &tiempo, &priority) > 2) {
        insertar(tiempo, nombre, priority, inicio, final);
    }
    return ftell(f);
    //Cierra el archivo
    fclose(f);
}

void despachar(Nodo **inicio, Nodo **final){

}