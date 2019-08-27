#include <stdio.h>
#include <stdlib.h>
#include "instrucoes.h"
#include "lista.h"

//int tam = 0;

void inicializarLista(LISTA **list)
{ //inicializar lista
    *list = (LISTA *)malloc(sizeof(LISTA));
    (*list)->nroElem = 0;
    //printf("\nLista inicializada");
    for (int i = 0; i < N; i++)
    {
        (*list)->lista_inst[i].posicao = excluido;
    }
}

int tamanho(LISTA *list)
{
    return list->nroElem;
}

void exibirLista(LISTA *list)
{
    int i;
    printf("\nLista: ");
    for (i = 0; i < N; i++)
    {
        if (list->lista_inst[i].posicao != excluido)
            printf("%d,", list->lista_inst[i].opcode);
    }
    printf(" \n");
}

int inserirElemLista(LISTA *list, Inst ch)
{
    if (list->nroElem == N)
    {
        printf("return 0");
        return 0; // lista cheia
    }
    else
    {
        for (int i = 0; i < N; i++)
        {

            if (list->lista_inst[i].posicao == excluido)
            {
                list->lista_inst[i] = ch;
                list->lista_inst[i].posicao = i;
                list->nroElem++;
                break;
            }
        }
    }
    return 1;
}

int excluirElem(LISTA *list, int pos)
{
    if (list->lista_inst[pos].posicao == excluido)
    {
        //printf("\nElemento já excluido");
    }
    list->lista_inst[pos].posicao = excluido;
    list->nroElem--;
    //printf("\nElemento excluido\n");
}

int listaVazia(LISTA *list)
{
    for (int i = 0; i < N; i++)
    {
        if (list->lista_inst[i].posicao == excluido)
            continue;
        else
            return 0;
    }
    return 1;
}

void esvaziarLista(LISTA *list, Inst in)
{
    for (int i = 0; i < N; i++)
    {
        if (list->lista_inst[i].cont_clock > in.cont_clock)
        {
            list->lista_inst[i].posicao = excluido;
            list->nroElem--;
        }
    }
}
