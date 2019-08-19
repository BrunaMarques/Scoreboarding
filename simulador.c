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
	clock = 1;
	int i = 0;
	unsigned int palavra[4];
	inicializar();
	tradutor();
	escritaMemoria();
	

do{
		
	// buscaPipeline();
	// emissao();
	// leitura();
	// execucao();
	// escritaPipeline();
	
	escritaPipeline();
	execucao();
	leitura();
	emissao();
	buscaPipeline();


	clock++;
	i++;

}while(i>10);//(f->nroElem != 0 || listaVazia(listaExecucao) != 1 || listaVazia(listaIssue) != 1 || listaVazia(listaRead) !=1 || listaVazia(listaWriteB) !=1 || verifica_bar(barBI) || verifica_bar(barIR) || verifica_bar(barRE) || verifica_bar(barEW));


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