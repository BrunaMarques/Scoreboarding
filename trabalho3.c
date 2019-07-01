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
	unsigned int *instrucao = malloc(sizeof(char) * 4);

	for (int contPalavra=0; contPalavra<tamanho; contPalavra+=4){

		fscanf(instrucoes, "%X", instrucao);

		for (int contByte=0; contByte<4; contByte++){

			memoria[contPalavra-contByte+3] = *instrucao&0x0FF;
			*instrucao = (*instrucao>>8);

		}
	}
}

int leituraMemoria(unsigned int palavra[], char *memoria, int pc){

	for (int contByte=0; contByte<4; contByte++){
		palavra[contByte] = memoria[(4*pc)+contByte];

	}

	return ++pc;

}

int main(){

	char *memoria = inicializaMemoria();
	escritaMemoria(n, memoria);
	unsigned int palavra[4];
	int pc = 0;

	for (int i = 0; i<n; i++){

		printf("Memoria POS(%d): %X\n", i, memoria[i]);

	}

	printf("\n\n");

	for (int i = 0; i<4; i++){
		pc = leituraMemoria(palavra, memoria, pc);
		printf("Teste %d: %X\n", i+1, palavra[0]);
		printf("Teste %d: %X\n", i+1, palavra[1]);
		printf("Teste %d: %X\n", i+1, palavra[2]);
		printf("Teste %d: %X\n", i+1, palavra[3]);
		printf("\n\n");
	
	}

	return 0;
}