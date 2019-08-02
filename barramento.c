#include <stdio.h>
#include "barramento.h"

void inicializa_bar()
{
    BI.instrucao.opcode = sem_instrucao;
    IR.instrucao.opcode = sem_instrucao;
    for (int i = 0; i < 5; i++)
    {
        RE[i].instrucao.opcode = sem_instrucao;
        EW[i].instrucao.opcode = sem_instrucao;
    }
}

void escrita_bar(Inst instrucao, int tipo_bar)
{
    switch (tipo_bar)
    {
    case barBI:

        BI.instrucao = instrucao;

        break;

    case barIR:

        IR.instrucao = instrucao;

        break;

    case barRE:

        for (int i = 0; i < 5; i++)
        {
            if (RE[i].instrucao.opcode == sem_instrucao)
            {
                RE[i].instrucao = instrucao;
                break;
            }
        }

        break;

    case barEW:

        for (int i = 0; i < 5; i++)
        {
            if (EW[i].instrucao.opcode == sem_instrucao)
            {
                EW[i].instrucao = instrucao;
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

        return BI.instrucao;

        break;

    case barIR:

        return IR.instrucao;

        break;

    case barRE:

        return RE.instrucao;

        break;

    case barEW:

        return EW.instrucao;

        break;
    }
}

int verifica_bar(int tipo_bar)
{
    switch (tipo_bar)
    {
    case barBI:
        if (BI.instrucao.opcode == sem_instrucao)
        {
            return 0;
        }
        return 1;
        break;

    case barIR:
        if (IR.instrucao.opcode == sem_instrucao)
        {
            return 0;
        }
        return 1;
        break;

    case barRE:
        for (int i = 0; i < 5; i++)
        {
            if (RE[i].instrucao.opcode != sem_instrucao)
            {
                return 1;
            }
        }
        return 0;
        break;

    case barEW:
        for (int i = 0; i < 5; i++)
        {
            if (EW[i].instrucao.opcode != sem_instrucao)
            {
                return 1;
            }
        }
        return 0;
        break;
    }
}
