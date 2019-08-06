#ifndef BARRAMENTO_H
#define BARRAMENTO_H

#include "instrucoes.h"

typedef struct
{
    Inst instrucao;
    int tem_instrucao;
} barramento;

barramento BI;
barramento IR;
barramento RE[5];
barramento EW[5];

#define barBI 0
#define barIR 1
#define barRE 2
#define barEW 3
#define true 1
#define false 0

void inicializa_bar();

void escrita_bar(Inst instrucao, int tipo_bar);

Inst leitura_bar(int tipo_bar);

int verifica_bar(int tipo_bar);

#endif