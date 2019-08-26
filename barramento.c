#include <stdio.h>
#include "barramento.h"
#include "lista.h"

void inicializa_bar()
{
    BI.tem_instrucao = false;
    IR.tem_instrucao = false;
    for (int i = 0; i < 5; i++)
    {
        RE[i].tem_instrucao = false;
        EW[i].tem_instrucao = false;
    }
}

void excluir_bar(int tipo_bar, Inst in)
{
    switch (tipo_bar)
    {
    case barBI:

        BI.tem_instrucao = false;

        break;

    case barIR:

        IR.tem_instrucao = false;

        break;

    case barRE:

        for (int i = 0; i < 4; i++)
        {
            if (RE[i].tem_instrucao == true)
            {
                if (RE[i].instrucao.cont_clock > in.cont_clock)
                {

                    RE[i].tem_instrucao = false;
                }
                break;
            }
        }

        break;

    case barEW:

        for (int i = 0; i < 4; i++)
        {
            if (EW[i].tem_instrucao == true)
            {
                if (EW[i].instrucao.cont_clock > in.cont_clock)
                {

                    EW[i].tem_instrucao = false;
                }
                break;
            }
        }

        break;
    }
}

void escrita_bar(Inst instrucao, int tipo_bar)
{
    switch (tipo_bar)
    {
    case barBI:

        BI.instrucao = instrucao;
        BI.tem_instrucao = true;

        break;

    case barIR:

        IR.instrucao = instrucao;
        IR.tem_instrucao = true;

        break;

    case barRE:

        for (int i = 0; i < 5; i++)
        {
            if (RE[i].tem_instrucao == false)
            {
                RE[i].instrucao = instrucao;
                RE[i].tem_instrucao = true;
                break;
            }
        }

        break;

    case barEW:

        for (int i = 0; i < 5; i++)
        {
            if (EW[i].tem_instrucao == false)
            {
                EW[i].instrucao = instrucao;
                EW[i].tem_instrucao = true;
                break;
            }
        }

        break;
    }
}

Inst leitura_bar(int tipo_bar)
{
    Inst aux;
    switch (tipo_bar)
    {
    case barBI:

        aux = BI.instrucao;
        BI.tem_instrucao = false;

        return aux;

        break;

    case barIR:

        aux = IR.instrucao;
        IR.tem_instrucao = false;

        return aux;

        break;

    case barRE:

        for (int i = 0; i < 4; i++)
        {
            if (RE[i].tem_instrucao == true)
            {
                aux = RE[i].instrucao;
                RE[i].tem_instrucao = false;
                return aux;
                break;
            }
        }

        break;

    case barEW:

        for (int i = 0; i < 4; i++)
        {
            if (EW[i].tem_instrucao == true)
            {
                aux = EW[i].instrucao;
                EW[i].tem_instrucao = false;
                return aux;
                break;
            }
        }

        break;
    }
}

int verifica_bar(int tipo_bar)
{
    switch (tipo_bar)
    {
    case barBI:
        if (BI.tem_instrucao == false)
        {
            return 0;
        }
        return 1;
        break;

    case barIR:
        if (IR.tem_instrucao == false)
        {
            return 0;
        }
        return 1;
        break;

    case barRE:
        for (int i = 0; i < 5; i++)
        {
            if (RE[i].tem_instrucao == true)
            {
                return 1;
            }
        }
        return 0;
        break;

    case barEW:
        for (int i = 0; i < 5; i++)
        {
            if (EW[i].tem_instrucao == true)
            {
                return 1;
            }
        }
        return 0;
        break;
    }
}
