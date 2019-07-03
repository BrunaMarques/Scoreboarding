#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trabalho3.h"

#define MASCARA 31;
#define ESPECIAL 0b000000;
#define ESPECIAL2 0b011100;
#define SALTO 0b000010;
#define IMEDIATO 0b001000;

int n = 16;

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

int decodificacao(unsigned int palavra[])
{
	int instrucao = palavra[0] << 24;
	instrucao += (palavra[1] << 16);
	instrucao += (palavra[2] << 8);
	instrucao += palavra[3];
	printf("Decodificado: %d\n\n", instrucao);

	int tipo = instrucao >> 26 & MASCARA;

	switch (tipo)
	{
	case ESPECIAL:
		in.opcode = instrucao >> 26 & MASCARA;
		in.r_instrucao.rs = instrucao >> 21 & MASCARA;
		in.r_instrucao.rd = instrucao >> 16 & MASCARA;
		in.r_instrucao.rt = instrucao >> 11 & MASCARA;
		in.r_instrucao.shamt = instrucao >> 6 & MASCARA;
		in.r_instrucao.func = instrucao & MASCARA;
		break;
	case IMEDIATO:
		in.opcode = instrucao >> 26 & MASCARA;
		in.i_instrucao.rs = instrucao >> 21 & MASCARA;
		in.i_instrucao.rt = instrucao >> 16 & MASCARA;
		in.i_instrucao.imediato = instrucao & MASCARA;
		break;
	case SALTO:
		in.opcode = instrucao >> 26 & MASCARA;
		in.jump_instrucao.addr = instrucao & MASCARA;
		break;
	default:
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

	for (int i = 0; i < 4; i++)
	{
		pc = buscaMemoria(palavra, memoria, pc);
		printf("Teste %d: %X\n", i + 1, palavra[0]);
		printf("Teste %d: %X\n", i + 1, palavra[1]);
		printf("Teste %d: %X\n", i + 1, palavra[2]);
		printf("Teste %d: %X\n", i + 1, palavra[3]);
		printf("\n\n");
		decodificacao(palavra);
	}

	return 0;
}