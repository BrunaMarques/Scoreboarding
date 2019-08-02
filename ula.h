#ifndef ULA_H
#define ULA_H

#include "instrucoes.h"

#define ADD 1
#define ADDI 2
#define AND 3
#define ANDI 4
#define B 5
#define BEQ 5
#define BEQL 6
#define BGEZ 7
#define BGTZ 8
#define BLEZ 9
#define BLTZ 10
#define BNE 11
#define DIV 12
#define J 13
#define JR 14
#define LUI 15
#define MADD 16
#define MFHI 17
#define MFLO 18
#define MOVN 19
#define MOVZ 20
#define MSUB 21
#define MTHI 22
#define MTLO 23
#define MUL 24
#define MULT 25
#define NOP 26
#define NOR 27
#define OR 28
#define ORI 29
#define SUB 30
#define XOR 31
#define XORI 32

int descobrirOperacao(Inst in);

int adicao(int op1, int op2);

int subtracao(int op1, int op2);

int multiplicacao(int op1, int op2);

int divisao(int op1, int op2);

int and (int op1, int op2);

int or (int op1, int op2);

int xor (int op1, int op2);

int not(int op);

int nor(int op1, int op2);

int igual(int op1, int op2);

int maior(int op1, int op2);

int menor(int op1, int op2);

int maiorIgual(int op1, int op2);

int menorIgual(int op1, int op2);

int shiftLeft(int n, int op);

int shiftRight(int n, int op);

#endif