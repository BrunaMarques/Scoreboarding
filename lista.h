typedef struct
{
    Inst lista_inst[MAX];
    int nroElem;
} LISTA;

LISTA *listaIssue;
LISTA *listaRead;
LISTA *listaExecucao;
LISTA *listaWriteB;

void inicializarLista(LISTA *list);
int tamanho(LISTA *list);
void exibirLista(LISTA *list);
int inserirEelemLista(LISTA *list, Inst ch);
int excluirElem(LISTA *list, int pos);
//int main();