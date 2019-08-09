#ifndef LISTA_H
#define LISTA_H
#define N 5

typedef struct
{
    Inst lista_inst[N];
    int nroElem;
} LISTA ;

LISTA *listaIssue;
LISTA *listaRead;
LISTA *listaExecucao;
LISTA *listaWriteB;

void inicializarLista(LISTA *list);
int tamanho(LISTA *list);
void exibirLista(LISTA *list);
int inserirElemLista(LISTA *list, Inst ch);
int excluirElem(LISTA *list, int pos);
//int main();

#endif