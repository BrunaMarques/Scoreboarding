typedef struct
{
    Inst lista_inst[MAX];
    int nroElem;
} LISTA;

LISTA listaIssue;
LISTA listaRead;
LISTA listaExecucao;
LISTA listaWriteB;

void inicializarLista();
int tamanho();
void exibirLista();
int inserirEelemLista(Inst ch);
int excluirElem(int pos);
//int main();