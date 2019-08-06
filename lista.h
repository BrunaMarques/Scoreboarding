void inicializarLista();
int tamanho();
void exibirLista();
int inserirLista(Inst ch, int i);
int inserirEelemLista(Inst ch);
int excluirElem(int pos);
int main();

typedef struct
{
    Inst lista_inst[MAX];
    int nroElem;
} LISTA;
