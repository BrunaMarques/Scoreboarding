#include <stdio.h>
#include <stdlib.h>
#include "instrucoes.h"

Inst decodificacao(unsigned int palavra[])
//etapa de decodificação
{
	Inst in;
	int instrucao = palavra[0] << 24;
	instrucao += (palavra[1] << 16);
	instrucao += (palavra[2] << 8);
	instrucao += palavra[3];
	int tipo = instrucao >> 26 & MASCARA;

	switch (tipo)
	{

	case ESPECIAL:

		in.opcode = instrucao >> 26 & MASCARA;
		in.s_instrucao.rs = instrucao >> 21 & MASCARA;
		in.s_instrucao.rd = instrucao >> 16 & MASCARA;
		in.s_instrucao.rt = instrucao >> 11 & MASCARA;
		in.s_instrucao.shamt = instrucao >> 6 & MASCARA;
		in.s_instrucao.func = instrucao & 63;

		return in;

		break;

	case ESPECIAL2:

		in.opcode = instrucao >> 26 & MASCARA;
		in.s2_instrucao.rs = instrucao >> 21 & MASCARA;
		in.s2_instrucao.rd = instrucao >> 16 & MASCARA;
		in.s2_instrucao.rt = instrucao >> 11 & MASCARA;
		in.s2_instrucao.shamt = instrucao >> 6 & MASCARA;
		in.s2_instrucao.func = instrucao & 63;

		return in;

		break;

	case SALTO:

		in.opcode = instrucao >> 26 & MASCARA;
		in.j_instrucao.addr = instrucao & MASCARA;

		return in;

		break;

	case REGIMM:

		in.opcode = instrucao >> 26 & MASCARA;
		in.r_instrucao.rs = instrucao >> 21 & MASCARA;
		in.r_instrucao.id = instrucao >> 16 & MASCARA;
		in.r_instrucao.offset = instrucao & MASCARA;

		return in;

		break;

	default:

		in.opcode = instrucao >> 26 & MASCARA;
		in.i_instrucao.rs = instrucao >> 21 & MASCARA;
		in.i_instrucao.rt = instrucao >> 16 & MASCARA;
		in.i_instrucao.imediato = instrucao & MASCARA;

		return in;

		break;
	}
}

void separarHILO(int in)
//separa HI e LO
{

	bufferRegistradores[HI] = in >> 5;
	bufferRegistradores[LO] = (in << 5) / 32;
}

int juntarHILO(int hi, int lo)
//junta HI e LO
{

	return hi << 5 + lo;
}
void execucao()
//etapa de execução
{
	Inst in;
	int operacao = descobrirOperacao(in);
	int registrador;
	switch (operacao)
	{
	case ADD:
		bufferRegistradores[in.s_instrucao.rd] = adicao(bancoRegistradores[in.s_instrucao.rs], bancoRegistradores[in.s_instrucao.rt]);
		break;
	case AND:
		bufferRegistradores[in.s_instrucao.rd] = and(bancoRegistradores[in.s_instrucao.rs], bancoRegistradores[in.s_instrucao.rt]);
		break;
	case DIV:
		separarHILO(divisao(bancoRegistradores[in.s_instrucao.rs], bancoRegistradores[in.s_instrucao.rt]));
		break;
	case JR:
		PC = bancoRegistradores[in.s_instrucao.rs];
	case MFHI:
		bufferRegistradores[in.s_instrucao.rd] = bancoRegistradores[HI];
		break;
	case MFLO:
		bufferRegistradores[in.s_instrucao.rd] = bancoRegistradores[LO];
		break;
	case MOVN:
		if (not(igual(bancoRegistradores[in.s_instrucao.rt], 0)))
			bufferRegistradores[in.s_instrucao.rd] = bancoRegistradores[in.s_instrucao.rs];
		break;
	case MOVZ:
		if (igual(bancoRegistradores[in.s_instrucao.rt], 0))
			bufferRegistradores[in.s_instrucao.rd] = bancoRegistradores[in.s_instrucao.rs];
		break;
	case MTHI:
		bufferRegistradores[HI] = bancoRegistradores[in.s_instrucao.rs];
		break;
	case MTLO:
		bufferRegistradores[LO] = bancoRegistradores[in.s_instrucao.rs];
		break;
	case MULT:
		separarHILO(multiplicacao(bancoRegistradores[in.s_instrucao.rs], bancoRegistradores[in.s_instrucao.rt]));
		break;
	case NOP:
		// nao faz nada por enquanto (no operation)// 
		break;
	case NOR:
		bufferRegistradores[in.s_instrucao.rd] = nor(bancoRegistradores[in.s_instrucao.rs], bancoRegistradores[in.s_instrucao.rt]);
		break;
	case OR:
		bufferRegistradores[in.s_instrucao.rd] = or(bancoRegistradores[in.s_instrucao.rs], bancoRegistradores[in.s_instrucao.rt]);
		break;
	case SUB:
		bufferRegistradores[in.s_instrucao.rd] = subtracao(bancoRegistradores[in.s_instrucao.rs], bancoRegistradores[in.s_instrucao.rt]);
		break;
	case XOR:
		bufferRegistradores[in.s_instrucao.rd] = xor(bancoRegistradores[in.s_instrucao.rs], bancoRegistradores[in.s_instrucao.rt]);
		break;
	case MADD:
		bufferResultado = multiplicacao(bancoRegistradores[in.s_instrucao.rs], bancoRegistradores[in.s_instrucao.rt]);
		bufferResultado = adicao(bufferResultado, juntarHILO(bancoRegistradores[HI], bancoRegistradores[LO]));
		break;
	case MSUB:
		bufferResultado = multiplicacao(bancoRegistradores[in.s_instrucao.rs], bancoRegistradores[in.s_instrucao.rt]);
		bufferResultado = subtracao(bufferResultado, juntarHILO(bancoRegistradores[HI], bancoRegistradores[LO]));
		break;
	case MUL:
		bufferRegistradores[in.s_instrucao.rd] = multiplicacao(bancoRegistradores[in.s_instrucao.rs], bancoRegistradores[in.s_instrucao.rt]);
		break;
	case ADDI:
		bufferRegistradores[in.s_instrucao.rt] = adicao(bancoRegistradores[in.s_instrucao.rs], in.i_instrucao.imediato);
		break;
	case ANDI:
		bufferRegistradores[in.s_instrucao.rt] = and(bancoRegistradores[in.s_instrucao.rs], in.i_instrucao.imediato);
		break;
	case B:
		PC += in.i_instrucao.imediato;
		break;
	case BEQ:
		if (igual(bancoRegistradores[in.s_instrucao.rs], bancoRegistradores[in.s_instrucao.rt]))
			PC += in.i_instrucao.imediato;
		break;
	case BEQL:
		if (igual(bancoRegistradores[in.s_instrucao.rs], bancoRegistradores[in.s_instrucao.rt]))
			PC += in.i_instrucao.imediato;
		break;
	case BGTZ:
		if (maior(bancoRegistradores[in.s_instrucao.rs], 0))
			PC += in.i_instrucao.imediato;
		break;
	case BLEZ:
		if (menorIgual(bancoRegistradores[in.s_instrucao.rs], 0))
			PC += in.i_instrucao.imediato;
		break;
	case BNE:
		if (not(igual(bancoRegistradores[in.s_instrucao.rs], bancoRegistradores[in.s_instrucao.rt])))
			PC += in.i_instrucao.imediato;
		break;
	case LUI:
		bufferRegistradores[in.s_instrucao.rt] = shiftLeft(in.i_instrucao.imediato, 16);
		break;
	case ORI:
		bufferRegistradores[in.s_instrucao.rt] = or (bancoRegistradores[in.s_instrucao.rs], in.i_instrucao.imediato);
		break;
	case XORI:
		bufferRegistradores[in.s_instrucao.rt] = xor(bancoRegistradores[in.s_instrucao.rs], in.i_instrucao.imediato);
		break;
	case J:
		PC = in.j_instrucao.addr;
		break;
	case BGEZ:
		if (maiorIgual(bancoRegistradores[in.s_instrucao.rs], 0))
			PC += in.r_instrucao.offset;

	case BLTZ:
		if (menor(bancoRegistradores[in.s_instrucao.rs], 0))
			PC += in.r_instrucao.offset;
	default:
		printf("Operação não listada!");
		break;
	}
}

void escrita(Inst intrucao)
{
}
