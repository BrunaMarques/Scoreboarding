#include <stdio.h>
#include <stdlib.h>

#define n 32

/*int tradutor()
{
	unsigned int *aux = malloc(sizeof(char) * 8);
	FILE *instrucoes = fopen("entrada.txt", "r");
	//n vai ser a entrada c o tamanho
	unsigned char *memoria = malloc(sizeof(char) * n);
	for (int i = 0; i < n; i += 8)
	{
		fscanf(instrucoes, "%x", aux);
		memoria[i] = aux;
		printf("%X\n", *aux);
	}

	return 0;
}

int unidadesFuncionais(){
	
}

int emissao(){}

int busca()
{
}

int execução()
{
} 

int escrita(){}

int reordenacao(){}

int efetivacao(){}
*/

int main()
{
	unsigned int *aux = malloc(sizeof(char) * 8);
	FILE *instrucoes = fopen("entrada.txt", "r");
	//n vai ser a entrada c o tamanho
	unsigned char *memoria = malloc(sizeof(char) * n);
	for (int i = 0; i < n; i += 8)
	{
		fscanf(instrucoes, "%x", aux);
		memoria[i] = aux;
		printf("%X\n", *aux);
	}

	return 0;
}