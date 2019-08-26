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
#include "simulador.h"

#define infinito 2147483647;
//salvar pc antigo
//35 clocks pro teste do mul
void buscaPipeline();
void execucao();
void emissao();
void escritaPipeline();
void leitura();

#endif
