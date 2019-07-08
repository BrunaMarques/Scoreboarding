#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simulador.h"
#include "ula.c"
#include "instrucoes.c"
#include "registradores.c"

int n = 20;

char *inicializaMemoria()
{

	//procurar tamanho da memoria e por em n //
	char *memoria = malloc(sizeof(char) * n);
	return memoria;
}

void escritaMemoria(int tamanho, char *memoria)
{
	FILE *instrucoes = fopen("entrada.txt", "r");
	unsigned int *instrucao = malloc(sizeof(char) * 4);

	for (int contPalavra = 0; contPalavra < tamanho; contPalavra += 4)
	{

		fscanf(instrucoes, "%X", instrucao);

		for (int contByte = 0; contByte < 4; contByte++)
		{

			memoria[contPalavra - contByte + 3] = *instrucao & 0x0FF;
			*instrucao = (*instrucao >> 8);
		}
	}
}

int buscaMemoria(unsigned int palavra[], char *memoria, int pc)
{

	for (int contByte = 0; contByte < 4; contByte++)
	{
		palavra[contByte] = memoria[(4 * pc) + contByte];
	}

	return ++pc;
}

void decodificacao(unsigned int palavra[])
{
	int instrucao = palavra[0] << 24; //tem que ser global
	instrucao += (palavra[1] << 16);
	instrucao += (palavra[2] << 8);
	instrucao += palavra[3];
	printf("Decodificado: %d\n\n", instrucao);
	int tipo = instrucao >> 26 & MASCARA;

	switch (tipo)
	{

	case ESPECIAL:

		in.opcode = instrucao >> 26 & MASCARA;
		printf("especial opcode: %d\n", in.opcode);
		in.s_instrucao.rs = instrucao >> 21 & MASCARA;
		printf("especial rs: %d\n", in.s_instrucao.rs);
		in.s_instrucao.rd = instrucao >> 16 & MASCARA;
		printf("especial rd: %d\n", in.s_instrucao.rd);
		in.s_instrucao.rt = instrucao >> 11 & MASCARA;
		printf("especial rt: %d\n", in.s_instrucao.rt);
		in.s_instrucao.shamt = instrucao >> 6 & MASCARA;
		printf("especial shamt: %d\n", in.s_instrucao.shamt);
		in.s_instrucao.func = instrucao & 63;
		printf("especial func: %d\n", in.s_instrucao.func);

		break;

	case ESPECIAL2:

		in.opcode = instrucao >> 26 & MASCARA;
		printf("especial opcode: %d\n", in.opcode);
		in.s2_instrucao.rs = instrucao >> 21 & MASCARA;
		printf("especial rs: %d\n", in.s2_instrucao.rs);
		in.s2_instrucao.rd = instrucao >> 16 & MASCARA;
		printf("especial rd: %d\n", in.s2_instrucao.rd);
		in.s2_instrucao.rt = instrucao >> 11 & MASCARA;
		printf("especial rt: %d\n", in.s2_instrucao.rt);
		in.s2_instrucao.shamt = instrucao >> 6 & MASCARA;
		printf("especial shamt: %d\n", in.s2_instrucao.shamt);
		in.s2_instrucao.func = instrucao & 63;
		printf("especial func: %d\n", in.s2_instrucao.func);

		break;

	case SALTO:

		in.opcode = instrucao >> 26 & MASCARA;
		printf("jump opcode: %d\n", in.opcode);
		in.jump_instrucao.addr = instrucao & MASCARA;
		printf("jump addr: %d\n", in.jump_instrucao.addr);

		break;

	default:

		in.opcode = instrucao >> 26 & MASCARA;
		printf("imediato opcode: %d\n", in.opcode);
		in.i_instrucao.rs = instrucao >> 21 & MASCARA;
		printf("imediato rs: %d\n", in.i_instrucao.rs);
		in.i_instrucao.rt = instrucao >> 16 & MASCARA;
		printf("imediato rt: %d\n", in.i_instrucao.rt);
		in.i_instrucao.imediato = instrucao & MASCARA;
		printf("imediato opcode: %d\n", in.i_instrucao.imediato);

		break;
	}
}

int main()
{

	char *memoria = inicializaMemoria();
	escritaMemoria(n, memoria);
	unsigned int palavra[4];
	int pc = 0;

	for (int i = 0; i < n; i++)
	{

		printf("Memoria POS(%d): %X\n", i, memoria[i]);
	}

	printf("\n\n");

	for (int i = 0; i < n / 4; i++)
	{

		pc = buscaMemoria(palavra, memoria, pc);
		printf("Teste %d: %X\n", i + 1, palavra[0]);
		printf("Teste %d: %X\n", i + 1, palavra[1]);
		printf("Teste %d: %X\n", i + 1, palavra[2]);
		printf("Teste %d: %X\n", i + 1, palavra[3]);
		printf("\n\n");
		decodificacao(palavra);
		op = descobrirOperacao();

		return 0;
	}