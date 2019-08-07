#include "registradores.h"

void inicializarRegistradores()
{
    for (int i = 0; i < 34; ++i)
    {
        bancoRegistradores[i].valor = 0;
        bancoRegistradores[i].UF = semUF;
    }
    PC = 0;
}

void escreverRegistrador(int registrador, int valor)
{

    if (registrador == 0 && valor != 0)
    {

        printf("Não é possível escrever um valor diferente de 0 nesse registrador.\n");
    }

    else
    {

        bancoRegistradores[registrador].valor = valor;
    }
}

int lerRegistrador(int registrador)
{

    return bancoRegistradores[registrador].valor;
}

void printarBancoRegistradores()
{

    printf("Registrador Z0 --> %d\n", bancoRegistradores[Z0].valor);
    printf("Registrador AT --> %d\n", bancoRegistradores[AT].valor);
    printf("Registrador V0 --> %d\n", bancoRegistradores[V0].valor);
    printf("Registrador V1 --> %d\n", bancoRegistradores[V1].valor);
    printf("Registrador A0 --> %d\n", bancoRegistradores[A0].valor);
    printf("Registrador A1 --> %d\n", bancoRegistradores[A1].valor);
    printf("Registrador A2 --> %d\n", bancoRegistradores[A2].valor);
    printf("Registrador A3 --> %d\n", bancoRegistradores[A3].valor);
    printf("Registrador T0 --> %d\n", bancoRegistradores[T0].valor);
    printf("Registrador T1 --> %d\n", bancoRegistradores[T1].valor);
    printf("Registrador T2 --> %d\n", bancoRegistradores[T2].valor);
    printf("Registrador T3 --> %d\n", bancoRegistradores[T3].valor);
    printf("Registrador T4 --> %d\n", bancoRegistradores[T4].valor);
    printf("Registrador T5 --> %d\n", bancoRegistradores[T5].valor);
    printf("Registrador T6 --> %d\n", bancoRegistradores[T6].valor);
    printf("Registrador T7 --> %d\n", bancoRegistradores[T7].valor);
    printf("Registrador S0 --> %d\n", bancoRegistradores[S0].valor);
    printf("Registrador S1 --> %d\n", bancoRegistradores[S1].valor);
    printf("Registrador S2 --> %d\n", bancoRegistradores[S2].valor);
    printf("Registrador S3 --> %d\n", bancoRegistradores[S3].valor);
    printf("Registrador S4 --> %d\n", bancoRegistradores[S4].valor);
    printf("Registrador S5 --> %d\n", bancoRegistradores[S5].valor);
    printf("Registrador S6 --> %d\n", bancoRegistradores[S6].valor);
    printf("Registrador S7 --> %d\n", bancoRegistradores[S7].valor);
    printf("Registrador T8 --> %d\n", bancoRegistradores[T8].valor);
    printf("Registrador T9 --> %d\n", bancoRegistradores[T9].valor);
    printf("Registrador K0 --> %d\n", bancoRegistradores[K0].valor);
    printf("Registrador K1 --> %d\n", bancoRegistradores[K1].valor);
    printf("Registrador GP --> %d\n", bancoRegistradores[GP].valor);
    printf("Registrador SP --> %d\n", bancoRegistradores[SP].valor);
    printf("Registrador FP --> %d\n", bancoRegistradores[FP].valor);
    printf("Registrador S8 / RA --> %d\n", bancoRegistradores[S8].valor);
    printf("Registrador HI --> %d\n", bancoRegistradores[HI].valor);
    printf("Registrador LO --> %d\n", bancoRegistradores[LO].valor);
}