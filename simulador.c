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

int main(/*int argc, char *argv[ ]*/)
{
	// if(strcmp(argv[1], "-h") == 0){
	// 	printf("\n\n---------------------------------------------HELP----------------------------------------------------\n");
	// 	printf("\n\t-h: help \n\t-i: arquivo assembly contendo programa a ser simulado \n\t-o: arquivo de saída contendo programa convertido para binário \n\t--detail: execução detalhada\n");
	// 	printf("\n\n-----------------------------------------------------------------------------------------------------\n");
	// }
	
	prog = fopen("prog.out", "w");
	clock = 1;
	int i = 0;
	unsigned int palavra[4];
	inicializar();
	tradutor();
	escritaMemoria();

	do
	{

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

	} while (i < 20); //(f->nroElem != 0 || listaVazia(listaExecucao) != 1 || listaVazia(listaIssue) != 1 || listaVazia(listaRead) !=1 || listaVazia(listaWriteB) !=1 || verifica_bar(barBI) || verifica_bar(barIR) || verifica_bar(barRE) || verifica_bar(barEW));

	fprintf(prog, "\n\nCiclos:\n");
	fprintf(prog, "\t%d cilcos\n", clock);
	fprintf(prog, "\nInstruções:\n \tEmitidas: ver o que colocar\n \tEfetivadas: ver o que colocar");

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