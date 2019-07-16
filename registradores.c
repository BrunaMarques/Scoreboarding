#include <stdlib.h>
#include <stdio.h>
#include "registradores.h"

bancoRegistradores[0] = 0;

void escreverRegistrador(int registrador, int valor){

    if (registrador == 0 && valor != 0){

        printf ("Não é possível escrever um valor diferente de 0 nesse registrador.\n");
    }

    else{

        bancoRegistradores[registrador] = valor;

    }
}

int lerRegistrador(int registrador){

    return bancoRegistradores[registrador];

}

void printarBancoRegistradores(){

    print("Registrador Z0 --> %d\n", bancoRegistradores[Z0]);
    print("Registrador AT --> %d\n", bancoRegistradores[AT]);
    print("Registrador V0 --> %d\n", bancoRegistradores[V0]);
    print("Registrador V1 --> %d\n", bancoRegistradores[V1]);   
    print("Registrador A0 --> %d\n", bancoRegistradores[A0]);
    print("Registrador A1 --> %d\n", bancoRegistradores[A1]);
    print("Registrador A2 --> %d\n", bancoRegistradores[A2]);
    print("Registrador A3 --> %d\n", bancoRegistradores[A3]);
    print("Registrador T0 --> %d\n", bancoRegistradores[T0]);
    print("Registrador T1 --> %d\n", bancoRegistradores[T1]);
    print("Registrador T2 --> %d\n", bancoRegistradores[T2]);
    print("Registrador T3 --> %d\n", bancoRegistradores[T3]);
    print("Registrador T4 --> %d\n", bancoRegistradores[T4]);
    print("Registrador T5 --> %d\n", bancoRegistradores[T5]);
    print("Registrador T6 --> %d\n", bancoRegistradores[T6]);
    print("Registrador T7 --> %d\n", bancoRegistradores[T7]);
    print("Registrador S0 --> %d\n", bancoRegistradores[S0]);
    print("Registrador S1 --> %d\n", bancoRegistradores[S1]);
    print("Registrador S2 --> %d\n", bancoRegistradores[S2]);
    print("Registrador S3 --> %d\n", bancoRegistradores[S3]);
    print("Registrador S4 --> %d\n", bancoRegistradores[S4]);
    print("Registrador S5 --> %d\n", bancoRegistradores[S5]);
    print("Registrador S6 --> %d\n", bancoRegistradores[S6]);
    print("Registrador S7 --> %d\n", bancoRegistradores[S7]);
    print("Registrador T8 --> %d\n", bancoRegistradores[T8]);
    print("Registrador T9 --> %d\n", bancoRegistradores[T9]);
    print("Registrador K0 --> %d\n", bancoRegistradores[K0]);
    print("Registrador K1 --> %d\n", bancoRegistradores[K1]);
    print("Registrador GP --> %d\n", bancoRegistradores[GP]);
    print("Registrador SP --> %d\n", bancoRegistradores[SP]);
    print("Registrador FP --> %d\n", bancoRegistradores[FP]);
    print("Registrador S8 / RA --> %d\n", bancoRegistradores[S8]);
    print("Registrador HI --> %d\n", bancoRegistradores[HI]);
    print("Registrador LO --> %d\n", bancoRegistradores[LO]);