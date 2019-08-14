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
	escritaPipeline();
	execucao();
	leitura();
	emissao();
	buscaPipeline();

}while (listaVazia(listaExecucao) != 1 || listaVazia(listaIssue) != 1 || listaVazia(listaRead) != 1 || listaVazia(listaRead) !=1 || listaVazia(listaWriteB) !=1 )

		
		
		
		
		
		i++;
	}

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