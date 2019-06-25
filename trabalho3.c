#include <stdio.h>
#include <stdlib.h>

#define n 32
struct barreira_busca{
	unsigned int *reg = malloc(sizeof(char) * 8);
}b_busca;

struct  barreira_execucao{
	unsigned int *opcode = malloc(sizeof(char) * 6);
	unsigned int *rs = malloc(sizeof(char) * 5);
	unsigned int *rt = malloc(sizeof(char) * 5);
	unsigned int *immediate = malloc(sizeof(char) * 16);	
};

struct barreira_memoria{
	
};

struct barreira_alinhamento{
	
};

//struct barreira_escrita{
	
//};

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

void busca(unsigned char memoria, struct b_busca teste){
	//struct barreira_busca teste;
	//teste reg;
	
	unsigned int *IR = malloc(sizeof(char) * 8);
	for (int PC = 0; PC < n; PC += 8){
		IR = memoria[PC];
	}
	teste.reg = IR;
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