typedef enum
{
    ADD_UF,
    MUL_UF,
    DIV_UF,
    INT_UF
} Tipo_UF;

typedef struct
{
    Tipo_UF tipo;
    UF_status status;
} UnidadeFuncional;