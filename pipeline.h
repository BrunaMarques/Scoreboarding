#ifndef PIPELINE_H
#define PIPELINE_H

#include "fila.h"
#include "instrucoes.h"
#include "ula.h"
#include "memoria.h"
#include "registradores.h"
#include "barramento.h"
#include "lista.h"
#include <stdbool.h>

int EMITIDA = true;

#define infinito 2147483647;

void buscaPipeline();
int execucao();
void emissao();
void escritaPipeline();

#endif
