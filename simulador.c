#include "simulador.h"

int n = 20;

int main(){

	inicializaMemoria();
	escritaMemoria();
	inicializarRegistradores();
	// unsigned int palavra[4];
	// FILA fila;

	buscaPipeline();

	// for (int i = 0; i < n/4; i++){

	// 	buscaMemoria(palavra, memoria, pc);
	// 	decodificacao(palavra);
	// 	//op = descobrirOperacao();

	// }

	return 0;
	
}