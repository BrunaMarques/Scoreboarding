#ifndef MEMORIA_H
#define MEMORIA_H

#include <stdio.h>
#include <stdlib.h>
#include "registradores.h"

#define TAMANHO_MEMORIA 512 //por enquanto memoria tem 512 bytes

char* memoria;

char *inicializaMemoria();

void escritaMemoria(int tamanho, char *memoria);

void buscaMemoria(unsigned int palavra[]);

#endif