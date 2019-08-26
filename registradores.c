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

void printarBancoRegistradores(FILE *detail)
{

    fprintf(detail,"\tRegistrador Z0 --> %d\n", bancoRegistradores[Z0].valor);
    fprintf(detail,"\tRegistrador AT --> %d\n", bancoRegistradores[AT].valor);
    fprintf(detail,"\tRegistrador V0 --> %d\n", bancoRegistradores[V0].valor);
    fprintf(detail,"\tRegistrador V1 --> %d\n", bancoRegistradores[V1].valor);
    fprintf(detail,"\tRegistrador A0 --> %d\n", bancoRegistradores[A0].valor);
    fprintf(detail,"\tRegistrador A1 --> %d\n", bancoRegistradores[A1].valor);
    fprintf(detail,"\tRegistrador A2 --> %d\n", bancoRegistradores[A2].valor);
    fprintf(detail,"\tRegistrador A3 --> %d\n", bancoRegistradores[A3].valor);
    fprintf(detail,"\tRegistrador T0 --> %d\n", bancoRegistradores[T0].valor);
    fprintf(detail,"\tRegistrador T1 --> %d\n", bancoRegistradores[T1].valor);
    fprintf(detail,"\tRegistrador T2 --> %d\n", bancoRegistradores[T2].valor);
    fprintf(detail,"\tRegistrador T3 --> %d\n", bancoRegistradores[T3].valor);
    fprintf(detail,"\tRegistrador T4 --> %d\n", bancoRegistradores[T4].valor);
    fprintf(detail,"\tRegistrador T5 --> %d\n", bancoRegistradores[T5].valor);
    fprintf(detail,"\tRegistrador T6 --> %d\n", bancoRegistradores[T6].valor);
    fprintf(detail,"\tRegistrador T7 --> %d\n", bancoRegistradores[T7].valor);
    fprintf(detail,"\tRegistrador S0 --> %d\n", bancoRegistradores[S0].valor);
    fprintf(detail,"\tRegistrador S1 --> %d\n", bancoRegistradores[S1].valor);
    fprintf(detail,"\tRegistrador S2 --> %d\n", bancoRegistradores[S2].valor);
    fprintf(detail,"\tRegistrador S3 --> %d\n", bancoRegistradores[S3].valor);
    fprintf(detail,"\tRegistrador S4 --> %d\n", bancoRegistradores[S4].valor);
    fprintf(detail,"\tRegistrador S5 --> %d\n", bancoRegistradores[S5].valor);
    fprintf(detail,"\tRegistrador S6 --> %d\n", bancoRegistradores[S6].valor);
    fprintf(detail,"\tRegistrador S7 --> %d\n", bancoRegistradores[S7].valor);
    fprintf(detail,"\tRegistrador T8 --> %d\n", bancoRegistradores[T8].valor);
    fprintf(detail,"\tRegistrador T9 --> %d\n", bancoRegistradores[T9].valor);
    fprintf(detail,"\tRegistrador K0 --> %d\n", bancoRegistradores[K0].valor);
    fprintf(detail,"\tRegistrador K1 --> %d\n", bancoRegistradores[K1].valor);
    fprintf(detail,"\tRegistrador GP --> %d\n", bancoRegistradores[GP].valor);
    fprintf(detail,"\tRegistrador SP --> %d\n", bancoRegistradores[SP].valor);
    fprintf(detail,"\tRegistrador FP --> %d\n", bancoRegistradores[FP].valor);
    fprintf(detail,"\tRegistrador S8 / RA --> %d\n", bancoRegistradores[S8].valor);
    fprintf(detail,"\tRegistrador HI --> %d\n", bancoRegistradores[HI].valor);
    fprintf(detail,"\tRegistrador LO --> %d\n", bancoRegistradores[LO].valor);
}