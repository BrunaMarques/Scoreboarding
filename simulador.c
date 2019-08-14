#include "simulador.h"
#include "tradutor.h"
#include "pipeline.h"

int n = 20;
void inicializar()
{
	inicializarLista(&listaExecucao);
	inicializarLista(&listaIssue);
	inicializarLista(&listaRead);
	inicializarLista(&listaWriteB);
	inicializarFila();
	inicializaMemoria();
	inicializarRegistradores();
}

int main()
{
	int i = 0;
	unsigned int palavra[4];
	inicializar();
	tradutor();
	escritaMemoria();
	

do{
	buscaPipeline();
	printf("\nLista E:\n");
	exibirLista(listaExecucao);
	printf("\nLista I:\n");
	exibirLista(listaIssue);
	printf("\nLista R:\n");
	exibirLista(listaRead);
	printf("\nLista WB:\n");
	exibirLista(listaWriteB);

	emissao();
	printf("\nLista E:\n");
	exibirLista(listaExecucao);
	printf("\nLista I:\n");
	exibirLista(listaIssue);
	printf("\nLista R:\n");
	exibirLista(listaRead);
	printf("\nLista WB:\n");
	exibirLista(listaWriteB);
	
	leitura();
	printf("\nLista E:\n");
	exibirLista(listaExecucao);
	printf("\nLista I:\n");
	exibirLista(listaIssue);
	printf("\nLista R:\n");
	exibirLista(listaRead);
	printf("\nLista WB:\n");
	exibirLista(listaWriteB);
	
	execucao();
	printf("\nLista E:\n");
	exibirLista(listaExecucao);
	printf("\nLista I:\n");
	exibirLista(listaIssue);
	printf("\nLista R:\n");
	exibirLista(listaRead);
	printf("\nLista WB:\n");
	exibirLista(listaWriteB);
	
	escritaPipeline();
	
	// escritaPipeline();
	// execucao();
	// leitura();
	// emissao();
	// buscaPipeline();
	printf("\nLista E:\n");
	exibirLista(listaExecucao);
	printf("\nLista I:\n");
	exibirLista(listaIssue);
	printf("\nLista R:\n");
	exibirLista(listaRead);
	printf("\nLista WB:\n");
	exibirLista(listaWriteB);

	i++;

}while(i<4);//while (listaVazia(listaExecucao) != 1 && listaVazia(listaIssue) != 1 && listaVazia(listaRead) !=1 && listaVazia(listaWriteB) !=1);


	//buscaPipeline();
	//inicializarFila();
	// unsigned int palavra[4];
	// FILA fila;

	//buscaPipeline();
	//exibirFila();
	//inicializa_bar();

	// for (int i = 0; i < n/4; i++){

	// 	buscaMemoria(palavra, memoria, pc);
	// 	decodificacao(palavra);
	// 	//op = descobrirOperacao();

	// }

	return 0;
}