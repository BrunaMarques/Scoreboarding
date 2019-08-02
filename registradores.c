#include "registradores.h"

void inicializarRegistradores(){
    for(int i = 0; i < 34; ++i) bancoRegistradores[i] = 0;
    PC = 0;
}

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

    printf("Registrador Z0 --> %d\n", bancoRegistradores[Z0]);
    printf("Registrador AT --> %d\n", bancoRegistradores[AT]);
    printf("Registrador V0 --> %d\n", bancoRegistradores[V0]);
    printf("Registrador V1 --> %d\n", bancoRegistradores[V1]);   
    printf("Registrador A0 --> %d\n", bancoRegistradores[A0]);
    printf("Registrador A1 --> %d\n", bancoRegistradores[A1]);
    printf("Registrador A2 --> %d\n", bancoRegistradores[A2]);
    printf("Registrador A3 --> %d\n", bancoRegistradores[A3]);
    printf("Registrador T0 --> %d\n", bancoRegistradores[T0]);
    printf("Registrador T1 --> %d\n", bancoRegistradores[T1]);
    printf("Registrador T2 --> %d\n", bancoRegistradores[T2]);
    printf("Registrador T3 --> %d\n", bancoRegistradores[T3]);
    printf("Registrador T4 --> %d\n", bancoRegistradores[T4]);
    printf("Registrador T5 --> %d\n", bancoRegistradores[T5]);
    printf("Registrador T6 --> %d\n", bancoRegistradores[T6]);
    printf("Registrador T7 --> %d\n", bancoRegistradores[T7]);
    printf("Registrador S0 --> %d\n", bancoRegistradores[S0]);
    printf("Registrador S1 --> %d\n", bancoRegistradores[S1]);
    printf("Registrador S2 --> %d\n", bancoRegistradores[S2]);
    printf("Registrador S3 --> %d\n", bancoRegistradores[S3]);
    printf("Registrador S4 --> %d\n", bancoRegistradores[S4]);
    printf("Registrador S5 --> %d\n", bancoRegistradores[S5]);
    printf("Registrador S6 --> %d\n", bancoRegistradores[S6]);
    printf("Registrador S7 --> %d\n", bancoRegistradores[S7]);
    printf("Registrador T8 --> %d\n", bancoRegistradores[T8]);
    printf("Registrador T9 --> %d\n", bancoRegistradores[T9]);
    printf("Registrador K0 --> %d\n", bancoRegistradores[K0]);
    printf("Registrador K1 --> %d\n", bancoRegistradores[K1]);
    printf("Registrador GP --> %d\n", bancoRegistradores[GP]);
    printf("Registrador SP --> %d\n", bancoRegistradores[SP]);
    printf("Registrador FP --> %d\n", bancoRegistradores[FP]);
    printf("Registrador S8 / RA --> %d\n", bancoRegistradores[S8]);
    printf("Registrador HI --> %d\n", bancoRegistradores[HI]);
    printf("Registrador LO --> %d\n", bancoRegistradores[LO]);
}