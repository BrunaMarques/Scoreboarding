#include <stdio.h>
#include <stdlib.h>

int n = 16;


char* inicializaMemoria(){
	//procurar tamanho da memoria e por em n // 
	char *memoria = malloc(sizeof(char) * n);
	return memoria;
}

void escritaMemoria(int tamanho, char *memoria){
	FILE *instrucoes = fopen("entrada.txt", "r");
	unsigned int *instrucao = malloc(sizeof(char) * 8);
	for (int contPalavra=0; contPalavra<tamanho; contPalavra+=4){
		fscanf(instrucoes, "%X", instrucao);
		for (int contByte=0; contByte<4; contByte++){
			memoria[contPalavra-contByte+3] = *instrucao&0x0FF;
			*instrucao = (*instrucao>>8);
		}
	}
}

int main()
{
	char *memoria = inicializaMemoria();
	escritaMemoria(n, memoria);

	for (int i = 0; i<n; i++){
		printf("Memoria: %X\n", memoria[i]);
	}

	//busca(memoria);

	return 0;
}