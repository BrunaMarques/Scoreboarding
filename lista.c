#include <stdio.h>
#include <stdlib.h>
#define MAX 50
#include "instrucoes.h"


typedef struct{
    Inst lista_inst[MAX];
    int nroElem;
}LISTA;

LISTA *list;
int tam = 0;

void inicializarLista(){      //inicializar lista
    list =(LISTA*) malloc(sizeof(LISTA));
    list -> nroElem = 0;
    printf("\nLista inicializada");
}

int tamanho(){
    return list->nroElem;
}

void exibirLista(){
    int i;
    printf("\nLista ->");
    for(i=0;i<list->nroElem;i++)
        printf("%d",list->lista_inst[i].opcode);
    printf("<--");
}

int inserirLista(Inst ch, int i){
    int k;
    if((list->nroElem>=MAX))//verificar se a lista está cheia
        return 0; //lista cheia ou indice invalido
    if((list->nroElem>0)&&(i<list->nroElem)){
        for(k=list->nroElem; k>=(i+1); k--)
            list->lista_inst[k]=list->lista_inst[k-1];
    }
    list->lista_inst[i]=ch;
    list->nroElem++;
    //printf("\n\nInserido: %d\n",ch);
    return i;
}

int inserirEelemLista(Inst ch){
    int i=0;
    if(list->nroElem>=MAX)
        return 0; // lista cheia
    
    return inserirLista(ch,list->nroElem);

}

int excluirElem(int pos){
    int j;
    if(pos == -1)
        return 0; // nõ existe
    j=pos;
    printf("\nJ:%d", j);
    printf("N: %d", list->nroElem);
    for(j=pos; j < list->nroElem-1; j++){
        list->lista_inst[j]=list->lista_inst[j+1];
        printf("AAAAA");
    }

    list->nroElem--;
    //printf("\nExcluindo elemento  %d",ch);
    return 1;
}

int main(){
    Inst A, B, C;
    A.opcode = 0;
    B.opcode = 1;
    C.opcode = 2;
    inicializarLista();
    A.posicao = inserirEelemLista(A);
    
    B.posicao = inserirEelemLista(B);
    exibirLista();
    C.posicao = inserirEelemLista(C);
    exibirLista();
    excluirElem(B.posicao);
    exibirLista();

}