#include <stdio.h>
#include <stdlib.h>
#include "un_func.h"

#define qtd_uf = 5;

typedef struct
{
    int Busy, Fi, Fj, Fk, Qj, Qk, Rj, Rk, Op;
    UnidadeFuncional uf;
} UF_status;

UF_status *statusUF;

void issue(op, rt, r1, r2)
{
    for (int i = 0; i < qtf_uf; i++)
    {
        statusUF = (UF_status *)malloc(sizeof(statusUF) * qtd_uf);
        int Result;
        if (!UF_status.uf.busy_buff AND !Result[rt])
        {
            statusUF[i].Busy = true;
            statusUF[i].Op = op;
            statusUF[i].Fi = rt;
            statusUF[i].Fj = r1;
            statusUF[i].Fk = r2;
            statusUF[i].Qj = Result[r1];
            statusUF[i].Qk = Result[r2];
            statusUF[i].Rj = Qj == 0;
            statusUF[i].Rk = Qk == 0;
            statusUF[i].Result[rt] = FU;
        }
    }
}