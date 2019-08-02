#include <stdio.h>
#include <stdlib.h>
#include "pipeline.h"
#include "memoria.h"
#include "registradores.h"

void buscaPipeline(){
    if(filaVazia()){
        for(int i=0; i<4; i++){
            unsigned int instMem[4];
            buscaMemoria(instMem);
    
            Inst instDecode = decodificacao(instMem);
            inserirElementoFila(instDecode); // não sei como passa esse ponteiro
        }
    }
}
