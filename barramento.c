#include <stdio.h>
#include "barramento.h"

void inicializa_bar()
{
    BI.opcode = sem_instrucao;
    IR.opcode = sem_instrucao;
    for (int i = 0; i < 5; i++)
    {
        RE[i].opcode = sem_instrucao;
        EW[i].opcode = sem_instrucao;
    }
}

void escrita_bar(Inst instrucao, int tipo_bar)
{
    switch (tipo_bar)
    {
    case barBI:

        BI = instrucao;

        break;

    case barIR:

        IR = instrucao;

        break;

    case barRE:

        for (int i = 0; i < 5; i++)
        {
            if (RE[i].opcode == sem_instrucao)
            {
                RE[i] = instrucao;
                break;
            }
        }

        break;

    case barEW:

        for (int i = 0; i < 5; i++)
        {
            if (EW[i].opcode == sem_instrucao)
            {
                EW[i] = instrucao;
                break;
            }
        }

        break;
    }
}

Inst leitura_bar(int tipo_bar)
{
    switch (tipo_bar)
    {
    case barBI:

        return BI;

        break;

    case barIR:

        return IR;

        break;

    case barRE:

        return RE;

        break;

    case barEW:

        return EW;

        break;
    }
}

int verifica_bar(int tipo_bar)
{
    switch (tipo_bar)
    {
    case barBI:
        if (BI.opcode == sem_instrucao)
        {
            return 0;
        }
        return 1;
        break;

    case barIR:
        if (IR.opcode == sem_instrucao)
        {
            return 0;
        }
        return 1;
        break;

    case barRE:
        for (int i = 0; i < 5; i++)
        {
            if (RE[i].opcode != sem_instrucao)
            {
                return 1;
            }
        }
        return 0;
        break;

    case barEW:
        for (int i = 0; i < 5; i++)
        {
            if (EW[i].opcode != sem_instrucao)
            {
                return 1;
            }
        }
        return 0;
        break;
    }
}
}