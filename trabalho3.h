typedef struct {
    unsigned int rs;
    unsigned int rt;
    unsigned int rd;
    unsigned int shamt;
    unsigned int func;
}R;

typedef struct {
    unsigned int rs;
    unsigned int rt;
    unsigned int rd;
    unsigned int shamt;
    unsigned int func;
}R2;

typedef struct {
    unsigned int rs;
    unsigned int rt;
    unsigned int imediato;
}I;

typedef struct {
    unsigned int addr; //instruction adress
}J;

typedef struct {
    unsigned int opcode;
    R r_instrucao;
    R2 r2_instrucao;
    J jump_instrucao;
    I I_instucao;
}Inst;

Inst in;
