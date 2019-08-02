#include "simulador.h"

int n = 20;

int main(){
	
	inicializaMemoria();
	escritaMemoria();
	inicializarRegistradores();
	inicializarFila();
	// unsigned int palavra[4];
	// FILA fila;

	buscaPipeline();
	exibirFila();
	inicializa_bar();

	// for (int i = 0; i < n/4; i++){

	// 	buscaMemoria(palavra, memoria, pc);
	// 	decodificacao(palavra);
	// 	//op = descobrirOperacao();

	// }

	return 0;
	
}