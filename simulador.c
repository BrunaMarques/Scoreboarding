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

		printf("\nFILA: %d\n", f->nroElem);
		printf("\nAAAA: %d\n", f->fila_inst[0].opcode);
		printf("\nAAAA: %d\n", f->fila_inst[1].opcode);
		exibirFila();
		printf("\nLISTA EXECUÇÃO: %d\n", listaVazia(listaExecucao));
		printf("\nLISTA EMISSAO: %d\n", listaVazia(listaIssue));
		printf("\nLISTA READ: %d\n", listaVazia(listaRead));
		printf("\nLISTA ESCRITA: %d\n", listaVazia(listaWriteB));
		printf("\nBARRAMENTO BI: %d\n", verifica_bar(barBI));
		printf("\nBARRAMENTO IR: %d\n", verifica_bar(barIR));
		printf("\nBARRAMENTO RE: %d\n", verifica_bar(barRE));
		printf("\nBARRAMENTO EW: %d\n", verifica_bar(barEW));
		exibirFila();

		escritaPipeline();
		execucao();
		leitura();
		emissao();
		buscaPipeline();

		clock++;
		i++;

		printf("\nFILA: %d\n", f->nroElem);
		printf("\nAAAA: %d\n", f->fila_inst[0].opcode);
		printf("\nAAAA: %d\n", f->fila_inst[1].opcode);
		exibirFila();
		printf("\nLISTA EXECUÇÃO: %d\n", listaVazia(listaExecucao));
		printf("\nLISTA EMISSAO: %d\n", listaVazia(listaIssue));
		printf("\nLISTA READ: %d\n", listaVazia(listaRead));
		printf("\nLISTA ESCRITA: %d\n", listaVazia(listaWriteB));
		printf("\nBARRAMENTO BI: %d\n", verifica_bar(barBI));
		printf("\nBARRAMENTO IR: %d\n", verifica_bar(barIR));
		printf("\nBARRAMENTO RE: %d\n", verifica_bar(barRE));
		printf("\nBARRAMENTO EW: %d\n", verifica_bar(barEW));
		exibirFila();
		getchar();

	} while (filaVazia() == false || listaVazia(listaExecucao) != 1 || listaVazia(listaIssue) != 1 || listaVazia(listaRead) != 1 || listaVazia(listaWriteB) != 1 || verifica_bar(barBI) != 0 || verifica_bar(barIR) != 0 || verifica_bar(barRE) != 0 || verifica_bar(barEW) != 0);
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