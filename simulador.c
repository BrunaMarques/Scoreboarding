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

void executarPipeline(){
	prog = fopen("prog.out", "w");
	clock = 1;
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

		clock++;
		i++;

	}while(i<20); //while(!filaVazia() || listaVazia(listaExecucao) != 1 || listaVazia(listaIssue) != 1 || listaVazia(listaRead) !=1 || listaVazia(listaWriteB) !=1 || verifica_bar(barBI) || verifica_bar(barIR) || verifica_bar(barRE) || verifica_bar(barEW));

	fprintf(prog, "\n\nCiclos:\n");
	fprintf(prog, "\t%d cilcos\n", clock);
	fprintf(prog, "\nInstruções:\n \tEmitidas: ver o que colocar\n \tEfetivadas: ver o que colocar");

}

int main(int argc, char *argv[ ])
{
	printf("\n%d\n", argc);
	for(int i = 0; i < argc; i++){
		if(argc == 1){	
			printf("\n------------------------------------------------------ATENÇÃO----------------------------------------------------------------\n");
			printf("\n\tÉ preciso passar um parâmetro para executar o programa\n\tPara ajuda utilize \"./mips -h\" \n");
			printf("\n-----------------------------------------------------------------------------------------------------------------------------\n");
		}
		else if(strcmp(argv[i], "-h") == 0){
			printf("\n\n---------------------------------------------HELP----------------------------------------------------\n");
			printf("\n\t-h: help\n \n\t-i: arquivo assembly contendo programa a ser simulado: \n\t\tDeve-se utilizar \"-i nomedoarquivo.asm\"\n \n\t-o: arquivo de saída contendo programa convertido para binário\n \n\t--detail: execução detalhada");
			printf("\n\n-----------------------------------------------------------------------------------------------------\n");
		}
		else if(argc == 2){
			if (strcmp(argv[1], "-i") == 0){
				printf("\n------------------------------------------------------ATENÇÃO----------------------------------------------------------------\n");
				printf("\n\tÉ preciso passar o arquivo assembly!\n\tUtilize: \"./mips32 -i nomedoarquivo.asm\"\n\tPara ajuda, utilize: \"./mips32 -h\"\n");
				printf("\n-----------------------------------------------------------------------------------------------------------------------------\n");
				break;
			}

			if (strcmp(argv[1], "-o") == 0){
				printf("\n------------------------------------------------------ATENÇÃO----------------------------------------------------------------\n");
				printf("\n\tÉ preciso passar o arquivo de saida!\n\tUtilize: \"./mips32 -o nomedoarquivo.txt\"\\n\n\tCaso não tenha executado o programa, execute-o primeiron\n\tPara ajuda, utilize: \"./mips32 -h\"\n");
				printf("\n-----------------------------------------------------------------------------------------------------------------------------\n");
				break;
			}
		}

		else if (strcmp(argv[i], "-i") == 0){
			strcpy(entrada,argv[2]);
			strcpy(saida,"saida.txt");
			printf("\n\tArquivo de saída gerado com o nome genérico saida.txt!\n");
			executarPipeline();
		}

		else if (strcmp(argv[i], "-o") == 0){
			strcpy(entrada,argv[2]);
			strcpy(saida,argv[4]);
			executarPipeline();
		}

		else if(strcmp(argv[i], "--detail") == 0){
			detail = fopen("saidaDetalhada.txt", "w");
		}

		else if(strcmp(argv[1], "--detail") == 0){
			printf("\nExecute o programa ao menos uma vez!\n");
			break;
		}
		
		else if(strcmp(argv[2], "--detail") == 0){
			printf("\nExecute o programa ao menos uma vez!\n");
			break;
		}

		//else printf("\nComando não encontrado");


	}
	return 0;
}