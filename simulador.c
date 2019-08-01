#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simulador.h"
#include "ula.c"
#include "instrucoes.c"
#include "instrucoes.h"
#include "memoria.c"
#include "registradores.c"

int n = 20;

int main(){

	char *memoria = inicializaMemoria();
	escritaMemoria(n, memoria);
	unsigned int palavra[4];

	for (int i = 0; i < n/4; i++){

		buscaMemoria(palavra, memoria, pc);
		decodificacao(palavra);
		//op = descobrirOperacao();

	}

	return 0;
	
}