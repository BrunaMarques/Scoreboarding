#include <stdio.h>
#include <stdlib.h>
#include "instrucoes.h"
#include "ula.h"

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
		printf("opcode: %d rs: %d rt: %d rd: %d funct: %d\n", in.opcode, in.s_instrucao.rs, in.s_instrucao.rt, in.s_instrucao.rd, in.s_instrucao.func);

		return in;

		break;

	case ESPECIAL2:

		in.opcode = instrucao >> 26 & MASCARA;
		in.s2_instrucao.rs = instrucao >> 21 & MASCARA;
		in.s2_instrucao.rd = instrucao >> 16 & MASCARA;
		in.s2_instrucao.rt = instrucao >> 11 & MASCARA;
		in.s2_instrucao.shamt = instrucao >> 6 & MASCARA;
		in.s2_instrucao.func = instrucao & 63;
		printf("opcode: %d rs: %d rt: %d rd: %d funct: %d\n", in.opcode, in.s2_instrucao.rs, in.s2_instrucao.rt, in.s2_instrucao.rd, in.s2_instrucao.func);
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
		printf("opcode: %d rs: %d rt: %d imediato: %d\n", in.opcode, in.i_instrucao.rs, in.i_instrucao.rt, in.i_instrucao.imediato);
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

void escrita(Inst intrucao)
{
}
