#include<stdio.h>
#include "tradutor.h"

int main(){
    char texto[100];
    FILE *instrucoes = fopen("entrada.asm", "r");
    fread(&texto, sizeof(char), 100,instrucoes);
}