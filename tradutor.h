#ifndef TRADUTOR_H
#define TRADUTOR_H

#include "registradores.h"
#include "hash.h"

//instruções ESPECIAL
#define ADD 0b100000
#define AND 0b100100
#define DIV 0b11010
#define JR 0b001001
#define MFHI 0b010000
#define MFLO 0b010010
#define MOVN 0b001011
#define MOVZ 0b001010
#define MTHI 0b010001
#define MTLO 0b010011
#define MULT 0b011000
#define NOP 0b000000
#define NOR 0b100111
#define OR 0b100101
#define SUB 0b100010
#define XOR 0b100110

//instruções ESPECIAL2
#define MADD 0b000000
#define MSUB 0b000100
#define MUL 0b000010

//instruções IMEDIATO
#define ADDI 0b001000
#define ANDI 0b001100
#define B 0b000100
#define BEQ 0b000100
#define BEQL 0b010100
#define BGTZ 0b000111
#define BLEZ 0b000110
#define BNE 0b000101
#define LUI 0b001111
#define ORI 0b001101
#define XORI 0b001110

//instruções de SALTO
#define J 0b000010

//instruções REGIM
#define BGEZ 0b00001
#define BLTZ 0b00000

char texto[100], *aux;
int special[6], jump[2], regim[4], imediato[4];
FILE *instrucoes;
FILE *saidaBinario;
FILE *saidaHexa;

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






