#ifndef BARRAMENTO_H
#define BARRAMENTO_H

#include "instrucoes.h"

typedef struct
{
    unsigned int opcode;
    E s_instrucao;
    E2 s2_instrucao;
    Jump j_instrucao;
    I i_instrucao;
    R r_instrucao;
} barramento;

barramento BI;
barramento IR;
barramento RE[5];
barramento EW[5];

#define barBI 0;
#define barIR 1;
#define barRE 2;
#define barEW 3;
#define sem_instrucao -1;

void inicializa_bar();

void escrita_bar(Inst instrucao, int tipo_bar);

Inst leitura_bar(int tipo_bar);

#endif