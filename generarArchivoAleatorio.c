#include "generarArchivoAleatorio.h"

void generarArchivoDeProcesosPorLotes(){
    FILE *fp, *nombres;

    // Este está entre M y N
    int numeroTotalProcesos = rand () % (MAX_PROCESOS-MIN_PROCESOS+1) + MIN_PROCESOS;
    int tiempoProceso;
    int cantidadProcesosPorLote;
    int contadorProcesos = 0;
    int priority;
    char nombresParaProcesos[200][200];
    int contador = 0;

    // Creando los nombres para cada lote de procesos
    nombres = fopen("nombres.txt","r");
    if (nombres == NULL)
        exit(1);
    else
    {
        printf("\nEl contenido del archivo de prueba es \n\n");
        while (feof(nombres) == 0)
        {
            fgets(nombresParaProcesos[contador],100,nombres);
            nombresParaProcesos[contador][strcspn(nombresParaProcesos[contador], "\r\n")] = 0;
            contador ++;
        }
    }
    fclose(nombres);

    // Creando el archivo para leer los lotes
    fp = fopen ( "fichero.txt", "w" );
    srand(time(NULL));
    contador = 0;
    while (contadorProcesos < numeroTotalProcesos){
        cantidadProcesosPorLote = rand () % (MAX_LOTES-MIN_LOTES+1) + MIN_LOTES;
        for (int j = 0; j < cantidadProcesosPorLote && contadorProcesos < numeroTotalProcesos; j++){
            tiempoProceso = rand () % (30-1+1) + 1;
            priority = rand () % 6;
            fprintf(fp,"%s%d %d %d\n",nombresParaProcesos[contador], contadorProcesos, tiempoProceso, priority);
            contadorProcesos ++;
        }
        contador ++;
        fprintf(fp,"#\n");
    }


    fclose ( fp );
}
