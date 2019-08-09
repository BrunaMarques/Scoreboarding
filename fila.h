#ifndef FILA_H
#define FILA_H

#include "instrucoes.h"
#include <stdbool.h>

#define MAX 4
// #define true 1
// #define false 0

// typedef int bool;

typedef struct {
    Inst fila_inst[MAX];
    int inicio;
    int nroElem;
} FILA;

FILA *f;

bool filaVazia();
void inicializarFila();
void exibirFila();
bool inserirElementoFila(Inst i);
Inst excluirElementoFila();

#endif