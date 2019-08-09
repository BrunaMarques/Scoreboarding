#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

bool filaVazia(){
    if (f->nroElem == 0){
        return true;
    }
    return false;
}

void inicializarFila() {
    f =(FILA*) malloc(sizeof(FILA));
    f->inicio=0;
    f->nroElem=0;
}

void exibirFila() {
    int i = f->inicio;
    int temp;
    printf("Fila: \" ");
    for (temp = 0; temp < f->nroElem; temp++) {
        printf("%i ", f->fila_inst[i].opcode);
        i = (i + 1) % MAX;
    }
    printf("\"\n");
} 

bool inserirElementoFila(Inst i) {
    if (f->nroElem >= MAX) 
        return false;
    int posicao = (f->inicio + f->nroElem) % MAX;
    f->fila_inst[posicao] = i;
    f->nroElem++;
    return true;
}

Inst excluirElementoFila() {
    Inst aux = f->fila_inst[f->inicio];
    f->inicio = (f->inicio+1) % MAX;
    f->nroElem--;
    return aux;
}

// int main(){
//     Inst A, B, C;
//     A.opcode = 0;
//     B.opcode = 1;
//     C.opcode = 2;
//     inicializarFila();
//     filaVazia();
//     inserirElementoFila(A);
//     inserirElementoFila(B);
//     inserirElementoFila(C);
//     exibirFila();
//     excluirElementoFila();
//     exibirFila();
//     filaVazia();
//     excluirElementoFila();
//     excluirElementoFila();
//     exibirFila();
//     if(filaVazia())
//         printf("VAZIAAAAA");
// }