#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tradutor.h"

int readfield(FILE *arq, char* string){
	int i = 0;
	char ch = fgetc(arq);
	while (ch != EOF && ch != ' ' && ch != ','){
		string[i] = ch;
		i++;
		ch = fgetc(arq);
	}
	string[i] = '\0';
	return i;
}

int main(){
    char texto[100];
    FILE *instrucoes = fopen("entrada.asm", "r");
    readfield()
    
}