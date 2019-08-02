#include "memoria.h"

char *inicializaMemoria()
{

	//procurar tamanho da memoria e por em n //
	char *memoria_aux = (char*)malloc(sizeof(char) * TAMANHO_MEMORIA);
	return memoria_aux;
}

void escritaMemoria(int tamanho, char *memoria)
{

	FILE *instrucoes = fopen("entrada.txt", "r");
	unsigned int *palavra = (unsigned int*)malloc(sizeof(char) * 4);

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

void buscaMemoria(unsigned int palavra[])
{

	for (int contByte = 0; contByte < 4; contByte++)
	{
		palavra[contByte] = memoria[(4 * PC) + contByte];
	}
}