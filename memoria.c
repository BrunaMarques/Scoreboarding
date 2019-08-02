#include "memoria.h"

void inicializaMemoria()
{
	//procurar tamanho da memoria e por em n //
	memoria = (char*)malloc(sizeof(char) * TAMANHO_MEMORIA);
	printf("Memoria inicializada");
}

void escritaMemoria()
{	printf("começando a escrever");
	FILE *instrucoes = fopen("codigoHexa.txt", "r");
	char *palavra_bytes;
	int palavra = 0, posicao = 0, endereco = 0, i = 0;

    while(fread(&palavra, sizeof(int), 1, instrucoes) == 1){
        // endereco = write_mem(palavra, endereco);
		i = 0;
		printf("\n%d", palavra);
    	palavra_bytes = (char*) &palavra;

    	for(posicao = endereco; posicao < endereco + 4; posicao++){
    	    memoria[posicao] = palavra_bytes[i++];
    	}
		endereco += 4;
    }

}

void buscaMemoria(unsigned int palavra[])
{

	for (int contByte = 0; contByte < 4; contByte++)
	{
		palavra[contByte] = memoria[(4 * PC) + contByte];
	}
}