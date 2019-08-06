#include <stdio.h>
#include <stdlib.h>
#include "ula.h"
#include "instrucoes.h"

#define TRUE 1
#define FALSE 0

int descobrirOperacao(Inst in)
{

    int op;

    switch (in.opcode)
    {

    case 0b000000:

        switch (in.s_instrucao.func)
        {

        case 0b100000:

            op = ADD;
            break;

        case 0b100100:

            op = AND;
            break;

        case 0b011010:

            op = DIV;
            break;

        case 0b010000:

            op = MFHI;
            break;

        case 0b010010:

            op = MFLO;
            break;

        case 0b001011:

            op = MOVN;
            break;

        case 0b001010:

            op = MOVZ;
            break;

        case 0b010001:

            op = MTHI;
            break;

        case 0b010011:

            op = MTLO;
            break;

        case 0b000000:

            op = NOP;
            break;

        case 0b100111:

            op = NOR;
            break;

        case 0b100101:

            op = OR;
            break;

        case 0b100010:

            op = SUB;
            break;

        case 0b100110:

            op = XOR;
            break;

        case 0b001000:

            op = JR;
            break;
        }

        break;

    case 0b011100:

        switch (in.s2_instrucao.func)
        {

        case 0b000000:

            op = MADD;
            break;

        case 0b000100:

            op = MSUB;
            break;

        case 0b000010:

            op = MUL;
            break;

        case 0b011000:

            op = MULT;
            break;
        }

        break;

    case 0b001000:

        op = ADDI;
        break;

    case 0b001100:

        op = ANDI;
        break;

    case 0b000100:

        op = B;
        break;

    case 0b010100:

        op = BEQL;
        break;

    case 0b000111:

        op = BGTZ;
        break;

    case 0b000110:

        op = BLEZ;
        break;

    case 0b000101:

        op = BNE;
        break;

    case 0b001111:

        op = LUI;
        break;

    case 0b001101:

        op = ORI;
        break;

    case 0b001110:

        op = XORI;
        break;

    case 0b000010:

        op = J;
        break;

    case 0b000001:
        switch (in.r_instrucao.id)
        {
        case 0b00001:
            op = BGEZ;
            break;

        case 0b00000:
            op = BLTZ;
            break;
        }
    }

    return op;
}

int adicao(int op1, int op2)
{
    return op1 + op2;
}

int subtracao(int op1, int op2)
{
    return op1 - op2;
}

int multiplicacao(int op1, int op2)
{
    return op1 * op2;
}

int divisao(int op1, int op2)
{
    return op1 / op2;
}

int and (int op1, int op2)
{
    return op1 & op2;
}

int or (int op1, int op2)
{
    return op1 | op2;
}

int xor (int op1, int op2) {
    return op1 ^ op2;
}

    int not(int op)
{
    return !op;
}
int nor(int op1, int op2)
{
    return not(or (op1, op2));
}

int igual(int op1, int op2)
{
    if (op1 == op2)
        return TRUE;
    return FALSE;
}

int maior(int op1, int op2)
{
    if (op1 > op2)
        return TRUE;
    return FALSE;
}

int menor(int op1, int op2)
{
    if (op1 < op2)
        return TRUE;
    return FALSE;
}

int maiorIgual(int op1, int op2)
{
    return not(menor(op1, op2));
}

int menorIgual(int op1, int op2)
{
    return not(maior(op1, op2));
}

int shiftLeft(int n, int op)
{
    return op << n;
}

int shiftRight(int n, int op)
{
    return op >> n;
}
