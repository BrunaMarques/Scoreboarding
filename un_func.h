#ifndef UN_FUNC_H
#define UN_FUNC_H

typedef struct
{
    UF_status status;
} UnidadeFuncional;

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

#endif