#include <stdio.h>
#include <stdlib.h>
#include "instrucoes.h"

void decodificacao(unsigned int palavra[]){

	int instrucao = palavra[0] << 24;
	instrucao += (palavra[1] << 16);
	instrucao += (palavra[2] << 8);
	instrucao += palavra[3];
	int tipo = instrucao >> 26 & MASCARA;

	switch (tipo){

		case ESPECIAL:

			in.opcode = instrucao >> 26 & MASCARA;
			in.s_instrucao.rs = instrucao >> 21 & MASCARA;
			in.s_instrucao.rd = instrucao >> 16 & MASCARA;
			in.s_instrucao.rt = instrucao >> 11 & MASCARA;
			in.s_instrucao.shamt = instrucao >> 6 & MASCARA;
			in.s_instrucao.func = instrucao & 63;

			break;

		case ESPECIAL2:

			in.opcode = instrucao >> 26 & MASCARA;
			in.s2_instrucao.rs = instrucao >> 21 & MASCARA;
			in.s2_instrucao.rd = instrucao >> 16 & MASCARA;
			in.s2_instrucao.rt = instrucao >> 11 & MASCARA;
			in.s2_instrucao.shamt = instrucao >> 6 & MASCARA;
			in.s2_instrucao.func = instrucao & 63;

			break;

		case SALTO:

			in.opcode = instrucao >> 26 & MASCARA;
			in.jump_instrucao.addr = instrucao & MASCARA;

			break;

		default:

			in.opcode = instrucao >> 26 & MASCARA;
			in.i_instrucao.rs = instrucao >> 21 & MASCARA;
			in.i_instrucao.rt = instrucao >> 16 & MASCARA;
			in.i_instrucao.imediato = instrucao & MASCARA;

			break;

	}

}