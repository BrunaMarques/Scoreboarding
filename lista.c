#include <stdio.h>
#define MAX 50

typedef int TIPOCHAVE;

typedef struct{
    TIPOCHAVE chave;

}REGISTRO;

typedef struct{
    REGISTRO a[MAX];
    int nroElem;

}LISTA;

int tam = 0;

void inicializar(LISTA *list){      //inicializar lista
    list -> nroElem = 0;
    printf("\nLista inicializada");
}

int tamanho(LISTA list){
    return list.nroElem;
}

void exibir(LISTA list){
    int i;
    printf("\nLista ->");
    for(i=0;i<list.nroElem;i++)
        printf("%d",list.a[i].chave);
}

int inserirEelemento(TIPOCHAVE ch, int i, LISTA*list){
    int k;
    if((list->nroElem>=MAX))//verificar se a lista está cheia
        return 0; //lista cheia ou indice invalido
    if((list->nroElem>0)&&(i<list->nroElem)){
        for(k=list->nroElem; k>=(i+1); k--)
            list->a[k]=list->a[k-1];
    }
    list->a[i].chave=ch;
    list->nroElem++;
    printf("\n\nInserido: %d\n",ch);
    return 1;
}

int inserirEelemOrd(TIPOCHAVE ch, LISTA *list){
    int i=0;
    if(list->nroElem>=MAX)
        return 0; // lista cheia

    while(i<list->nroElem && list->a[i].chave<ch)
        i++;

    if(list->a[i].chave == ch)
        return 0;

    return inserirEelemento(ch,i,list);
}

int buscaSeq(TIPOCHAVE ch, LISTA list){
    int i=0;

    while(i<list.nroElem){
        if(ch == list.a[i].chave)
            return i; //achou
        i++;
    }
    return -1; //não achou
}

int excluirElem(TIPOCHAVE ch, LISTA *list){
    int pos, j;
    pos=buscaSeq(ch, *list);
    if(pos == -1)
        return 0; // nõ existe

    for(j=pos; j < list->nroElem-1; j++)
        list->a[j]=list->a[j+1];

    list->nroElem--;
    printf("\nExcluindo elemento  %d",ch);
    return 1;
}

int main(){
    LISTA listaEstatica, listaEstatica3;
    inicializar(&listaEstatica);
    inserirEelemOrd(2,&listaEstatica);
    exibir(listaEstatica);
    inserirEelemOrd(5,&listaEstatica);
    exibir(listaEstatica);
    inserirEelemOrd(1,&listaEstatica);
    exibir(listaEstatica);
    excluirElem(1, &listaEstatica);
    exibir(listaEstatica);
}