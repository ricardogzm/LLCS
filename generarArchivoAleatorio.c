#include "generarArchivoAleatorio.h"

void generarArchivoDeProcesosPorLotes(){
    FILE *fp;

    // Este está entre M y N
    int numeroTotalProcesos = rand () % (MAX_PROCESOS-MIN_PROCESOS+1) + MIN_PROCESOS;
    int tiempoProceso;
    int cantidadProcesosPorLote;
    int contadorProcesos = 0;
    int priority;

    fp = fopen ( "fichero.txt", "w" );
    srand(time(NULL));
    while (contadorProcesos < numeroTotalProcesos){
        cantidadProcesosPorLote = rand () % (MAX_LOTES-MIN_LOTES+1) + MIN_LOTES;
        for (int j = 0; j < cantidadProcesosPorLote && contadorProcesos < numeroTotalProcesos; j++){
            tiempoProceso = rand () % (30-1+1) + 1;
            priority = rand () % 6;
            fprintf(fp,"proceso%d %d %d\n", contadorProcesos, tiempoProceso, priority);
            contadorProcesos ++;
        }
        fprintf(fp,"#\n");
    }


    fclose ( fp );
}
