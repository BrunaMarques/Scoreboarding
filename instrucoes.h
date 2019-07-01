struct R{
    unsigned int opcode;
    unsigned int rs;
    unsigned int rt;
    unsigned int rd;
    unsigned int shamt;
    unsigned int func;
};

struct I{
    unsigned int opcode;
    unsigned int rs;
    unsigned int rt;
    unsigned int immediate;
};

struct J{
    unsigned int opcode;
    unsigned int addr; //instruction adress
};