#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simulador.h"
#include "ula.c"
#include "instrucoes.c"
#include "instrucoes.h"
#include "memoria.c"
#include "registradores.c"
#include "fila.h"
#include "pipeline.h"
#include "memoria.h"

int n = 20;

int main(){

	memoria = inicializaMemoria();
	escritaMemoria(n, memoria);
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