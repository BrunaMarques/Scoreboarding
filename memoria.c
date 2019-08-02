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
	char *palavra_bytes;
	int palavra, posicao, endereco, i = 0;

    while(fread(&palavra, sizeof(int), 1, instrucoes) == 1){
        // endereco = write_mem(palavra, endereco);
		i = 0;
    	*palavra_bytes = (char*) &palavra;

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