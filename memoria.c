#include <stdio.h>
#include <stdlib.h>
#include "memoria.h"

char *inicializaMemoria()
{

	//procurar tamanho da memoria e por em n //
	char *memoria = malloc(sizeof(char) * n);
	return memoria;
}

void escritaMemoria(int tamanho, char *memoria)
{

	FILE *instrucoes = fopen("entrada.txt", "r");
	unsigned int *palavra = malloc(sizeof(char) * 4);

	for (int contPalavra = 0; contPalavra < tamanho; contPalavra += 4)
	{

		fscanf(instrucoes, "%X", palavra);

		for (int contByte = 0; contByte < 4; contByte++)
		{

			memoria[contPalavra - contByte + 3] = *palavra & 0x0FF;
			*palavra = (*palavra >> 8);
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