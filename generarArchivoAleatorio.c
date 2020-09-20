#include <stdio.h>
#include <stdlib.h>
# define MIN_PROCESOS 2
# define MAX_PROCESOS 500
# define MIN_LOTES 1
# define MAX_LOTES 50

void generarArchivoDeProcesosPorLotes(){
    FILE *fp;

    // Este está entre M y N
    int numeroTotalProcesos = rand () % (MAX_PROCESOS-MIN_PROCESOS+1) + MIN_PROCESOS;
    int tiempoProceso;
    int cantidadProcesosPorLote;
    int contadorProcesos = 0;

    fp = fopen ( "fichero.txt", "r+" );

    while (contadorProcesos < numeroTotalProcesos){
        cantidadProcesosPorLote = rand () % (MAX_LOTES-MIN_LOTES+1) + MIN_LOTES;
        for (int j = 0; j < cantidadProcesosPorLote && contadorProcesos < numeroTotalProcesos; j++){
            tiempoProceso = rand () % (30-1+1) + 1;
            fprintf(fp,"proceso%d %d \n",contadorProcesos,tiempoProceso);
            contadorProcesos ++;
        }
        fprintf(fp,"\n");
    }


    fclose ( fp );
}
