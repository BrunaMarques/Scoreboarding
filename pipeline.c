#include <stdio.h>
#include <stdlib.h>
#include "pipeline.h"
#include "memoria.h"
#include "fila.c"

buscaPipeline(unsigned int palavra, FILA fila, char *memoria, int pc){
    if(filaVazia){
        for(int i=0; i<4; i++)
            buscaMemoria(palavra, memoria, pc);
    
        int *instMem = decodificacao(palavra);
        inserirElementoFila(instMem); // não sei como passa esse ponteiro
    }
}
