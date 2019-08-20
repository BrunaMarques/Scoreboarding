#ifndef TRADUTOR_H
#define TRADUTOR_H

#include "registradores.h"
#include "hash.h"

//instruções ESPECIAL
#define TADD 0b100000
#define TAND 0b100100
#define TDIV 0b11010
#define TJR 0b001001
#define TMFHI 0b010000
#define TMFLO 0b010010
#define TMOVN 0b001011
#define TMOVZ 0b001010
#define TMTHI 0b010001
#define TMTLO 0b010011
#define TMULT 0b011000
#define TNOP 0b000000
#define TNOR 0b100111
#define TOR 0b100101
#define TSUB 0b100010
#define TXOR 0b100110

//instruções ESPECIAL2
#define TMADD 0b000000
#define TMSUB 0b000100
#define TMUL 0b000010

//instruções IMEDIATO
#define TADDI 0b001000
#define TANDI 0b001100
#define TB 0b000100
#define TBEQ 0b000100
#define TBEQL 0b010100
#define TBGTZ 0b000111
#define TBLEZ 0b000110
#define TBNE 0b000101
#define TLUI 0b001111
#define TORI 0b001101
#define TXORI 0b001110

//instruções de SALTO
#define TJ 0b000010

//instruções REGIM
#define TBGEZ 0b00001
#define TBLTZ 0b00000

char texto[100], *aux;
int special[6], jump[2], regim[4], imediato[4];
FILE *instrucoes;
FILE *saidaBinario;
FILE *saidaHexa;
FILE *prog;
int qtd;

int registradores(char *aux);
void binarioSpecial(int vetor[], FILE *saidaBinario);
void binarioImediato(int vetor[], FILE *saidaBinario);
void binarioRegim(int vetor[], FILE *saidaBinario);
void binarioJump(int vetor[], FILE *saidaBinario);
void tradutorBin();
void tradutorHexa(FILE *saidaHexa, FILE *saidaBin);
void print_assembly(FILE *instrucoes);
void tradutor();

#endif






