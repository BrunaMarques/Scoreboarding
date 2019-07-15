#define MASCARA 31
#define ESPECIAL 0b000000
#define ESPECIAL2 0b011100
#define SALTO 0b000010
#define REGIMM 0b000001



typedef struct
{
    unsigned int rs;
    unsigned int rt;
    unsigned int rd;
    unsigned int shamt;
    unsigned int func;
} S;

typedef struct
{
    unsigned int rs;
    unsigned int rt;
    unsigned int rd;
    unsigned int shamt;
    unsigned int func;
} S2;

typedef struct
{
    unsigned int rs;
    unsigned int rt;
    unsigned int imediato;
} I;

typedef struct
{
    unsigned int addr; //instruction adress
} Jump;

typedef struct
{
    unsigned int opcode;
    unsigned int rs;
    unsigned int id;
    unsigned int offset;
} R;

typedef struct
{
    unsigned int opcode;
    S s_instrucao;
    S2 s2_instrucao;
    Jump j_instrucao;
    I i_instrucao;
    R r_instrucao
} Inst;

Inst in;

void decodificacao(unsigned int palavra[]){
}