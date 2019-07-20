typedef enum
{
    ADD_UF,
    MUL_UF,
    2 DIV_UF,
    2 ou 1 INT_UF
} Tipo_UF;

typedef struct
{
    Tipo_UF tipo;
    UF_status status;
} UnidadeFuncional;