#ifndef INSTRUCOES_H
#define INSTRUCOES_H

#include "registradores.h"

#define MASCARA 31
#define ESPECIAL 0b000000
#define ESPECIAL2 0b011100
#define SALTO 0b000010
#define REGIMM 0b000001

typedef struct
{
    unsigned int rs;
    unsigned int rt;
    unsigned int rd;
    unsigned int shamt;
    unsigned int func;
}E;

typedef struct
{
    unsigned int rs;
    unsigned int rt;
    unsigned int rd;
    unsigned int shamt;
    unsigned int func;
}E2;

typedef struct
{
    unsigned int rs;
    unsigned int rt;
    unsigned int imediato;
}I;

typedef struct
{
    unsigned int addr; //instruction adress
}Jump;

typedef struct
{
    unsigned int opcode;
    unsigned int rs;
    unsigned int id;
    unsigned int offset;
}R;

typedef struct
{
    unsigned int opcode;
    E s_instrucao;
    E2 s2_instrucao;
    Jump j_instrucao;
    I i_instrucao;
    R r_instrucao;
}Inst;

// Inst in;

Inst decodificacao(unsigned int palavra[]);

void separarHILO(int in);

int juntarHILO(int hi, int lo);

#endif