#ifndef ULA_H
#define ULA_H

#include "instrucoes.h"

#define ADD 1
#define ADDI 2
#define AND 3
#define ANDI 4
#define B 5
#define BEQ 6
#define BEQL 7
#define BGEZ 8
#define BGTZ 9
#define BLEZ 10
#define BLTZ 11
#define BNE 12
#define DIV 13
#define J 14
#define JR 15
#define LUI 16
#define MADD 17
#define MFHI 18
#define MFLO 19
#define MOVN 20
#define MOVZ 21
#define MSUB 22
#define MTHI 23
#define MTLO 24
#define MUL 25
#define MULT 26
#define NOP 27
#define NOR 28
#define OR 29
#define ORI 30
#define SUB 31
#define XOR 32
#define XORI 33

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