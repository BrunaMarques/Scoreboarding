#include "hash.h"

void inicializarHash(){
    Hash_Table = (Hash*)malloc(sizeof(Hash)*HASH_SIZE);
    for(int i = 0; i < HASH_SIZE; ++i){
        Hash_Table[i].linha = NONE;
    }
}

unsigned int hash(char* label){
    unsigned int h = 0;
	char c;
    while(c = *label++) h = h*9^c;
    return h % HASH_SIZE;
}

int inserirLabel(char* label, int linha){ //linha vai ser a linha, label a label
    label[strlen(label) - 1] = '\0';
    if (Hash_Table[hash(label)].linha != NONE) 
        return 0;
    Hash_Table[hash(label)].label = label;
    Hash_Table[hash(label)].linha = linha;
    printf("inseriu na hash");

}

int pegarEndereco(char* label){
    if (Hash_Table[hash(label)].linha == NONE){
        printf("Label não existentente.\n");
        exit(EXIT_FAILURE);
    }
    return Hash_Table[hash(label)].linha;
}