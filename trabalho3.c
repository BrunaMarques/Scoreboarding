#include <stdio.h>
#include <stdlib.h>

#define n 32
struct barreira{
	unsigned int *reg = malloc(sizeof(char) * 8);
};


//fazer uma struct barreira para cada estágio

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

int regsStatus(){
	
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

void busca(unsigned char memoria){
	unsigned int *IR = malloc(sizeof(char) * 8);
	for (int PC = 0; PC < n; PC += 8){
		IR = memoria[PC];
	}
	barreira.reg = IR;
}

int main()
{
	unsigned int *aux = malloc(sizeof(char) * 8);
	FILE *instrucoes = fopen("entrada.txt", "r");
	//n vai ser a entrada c o tamanho
	unsigned char *memoria = malloc(sizeof(char) * n);
	for (int i = 0; i < n; i += 8){
		fscanf(instrucoes, "%x", aux);
		memoria[i] = aux;
		printf("AUX: %X\n", *aux);
	}

	//busca(memoria);

	// for (int i = 0; i < n; i += 8){
	// 	printf("%X\n", memoria[i]);
	// }

	return 0;
}