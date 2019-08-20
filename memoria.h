#ifndef MEMORIA_H
#define MEMORIA_H

#include <stdio.h>
#include <stdlib.h>
#include "registradores.h"
#include "tradutor.h"

#define TAMANHO_MEMORIA 512 //por enquanto memoria tem 512 bytes

char* memoria;

void inicializaMemoria();

void escritaMemoria();

void buscaMemoria(unsigned int palavra[]);

#endif