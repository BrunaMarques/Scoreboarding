#include <stdio.h>
#include <stdlib.h>
#include "instrucoes.h"
#include "lista.h"

//int tam = 0;

void inicializarLista(LISTA **list)
{ //inicializar lista
    *list = (LISTA *)malloc(sizeof(LISTA));
    (*list)->nroElem = 0;
    printf("\nLista inicializada");
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

// int inserirLista(LISTA *list, Inst ch, int i)
// {
//     int k;
//     if ((list->nroElem >= N)) //verificar se a lista está cheia
//         return 0;               //lista cheia ou indice invalido
//     if ((list->nroElem > 0) && (i < list->nroElem))
//     {
//         for (k = list->nroElem; k >= (i + 1); k--)
//             list->lista_inst[k] = list->lista_inst[k - 1];
//     }
//     list->lista_inst[i] = ch;
//     list->nroElem++;
//     list->lista_inst[i].posicao = i;
//     //printf("\n\nInserido: %d\n",ch);
//     return i;
// }

// int inserirLista(LISTA *list, Inst ch, int i)
// {
//     if ((list->nroElem >= N)) //verificar se a lista está cheia
//         return 0;               //lista cheia ou indice invalido
//     if ((list->nroElem > 0) && (i < list->nroElem))
//     {
//         for (int k = 0; k < N; k++)
//             if (list->lista_inst[k].posicao == excluido)
//                 list->lista_inst[k] = ch;
//     }
//     list->nroElem++;
//     list->lista_inst[i].posicao = i;
//     //printf("\n\nInserido: %d\n",ch);
//     return i;
// }

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
                printf("\nPosicao: %d\n", list->lista_inst[i].posicao);
                list->nroElem++;
                printf("\nElemento inserido na lista!\n");
                break;
            }
        }
    }
    return 1;
    //printf("\n\nInserido: %d\n",ch);
}

// int excluirElem(LISTA *list, int pos)
// {
//     int j;
//     if (pos == -1)
//         return 0; // nõ existe
//     j = pos;
//     printf("\nJ:%d", j);
//     printf("N: %d", list->nroElem);
//     for (j = pos; j < list->nroElem - 1; j++)
//     {
//         list->lista_inst[j] = list->lista_inst[j + 1];
//         list->lista_inst[j].posicao = j;
//     }

//     list->nroElem--;
//     //printf("\nExcluindo elemento  %d",ch);
//     return 1;
// }

int excluirElem(LISTA *list, int pos)
{
    if (list->lista_inst[pos].posicao == excluido)
    {
        printf("\nElemento já excluido");
    }
    list->lista_inst[pos].posicao = excluido;
    list->nroElem--;
    printf("\nElemento excluido\n");
}

int listaVazia(LISTA *list)
{
    for (int i = 0; i < N; i++)
    {
        //printf("\nteste: %d", list->lista_inst[i].posicao);
        if (list->lista_inst[i].posicao == excluido)
            continue;
        else
            return 0;
    }
    return 1;
}

// int main()
// {
//         LISTA *l;
//     Inst A, B, C;
//     A.opcode = 0;
//     B.opcode = 1;
//     C.opcode = 2;
//     inicializarLista(&l);
//     printf("\nVazia? %d\n" ,listaVazia(l));
//     inserirElemLista(l,A);
//     inserirElemLista(l, B);
//     exibirLista(l);
//     printf("\nVazia? %d\n" ,listaVazia(l));
//     inserirElemLista(l, C);
//     exibirLista(l);
//     printf("\nVazia? %d\n" ,listaVazia(l));
//     printf("\nB: %d", l->lista_inst[B.posicao].posicao);
//     excluirElem(l, B.posicao);
//     printf("\nB: %d", l->lista_inst[B.posicao].posicao);
//     exibirLista(l);
// }