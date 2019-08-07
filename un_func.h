#ifndef UN_FUNC_H
#define UN_FUNC_H
#define qtd_uf = 5;

typedef struct
{
    UF_status status;
} UnidadeFuncional;

typedef struct
{
    int Busy, Fi, Fj, Fk, Qj, Qk, Rj, Rk, Op;
    UnidadeFuncional uf;
} UF_status;

UnidadeFuncional UFADD;
UnidadeFuncional UFMUL1;
UnidadeFuncional UFMUL2;
UnidadeFuncional UFDIV;
UnidadeFuncional UFINT;

#define UF_ADD 1
#define UF_MUL1 2
#define UF_MUL2 3
#define UF_DIV 4
#define UF_INT 5

UF_status.uf.busy_buff = FALSE;

UF_status *statusUF;

#endif