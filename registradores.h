#ifndef REGISTRADORES_H
#define REGISTRADORES_H

#include <stdlib.h>
#include <stdio.h>

#define Z0 0
#define AT 1
#define V0 2
#define V1 3
#define A0 4
#define A1 5
#define A2 6
#define A3 7
#define T0 8
#define T1 9
#define T2 10
#define T3 11
#define T4 12
#define T5 13
#define T6 14
#define T7 15
#define S0 16
#define S1 17
#define S2 18
#define S3 19
#define S4 20
#define S5 21
#define S6 22
#define S7 23
#define T8 24
#define T9 25
#define K0 26
#define K1 27
#define GP 28
#define SP 29
#define FP 30
#define S8 30
#define RA 31
#define HI 32
#define LO 33

int bancoRegistradores[34];
int bufferRegistradores[34];
int bufferResultado;

int PC = 0;

void inicializarRegistradores();
void escreverRegistrador(int registrador, int valor);
int lerRegistrador(int registrador);
void printarBancoRegistradores();
#endif