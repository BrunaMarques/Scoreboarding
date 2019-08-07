#ifndef HASH_H
#define HASH_H

#define HASH_SIZE 256
#define NONE -1

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct{
    int linha;
    char* label;
}Hash;

Hash* Hash_Table;

void inicializarHash();
unsigned int hash(char* label);
int inserirLabel(char* label, int linha);
int pegarEndereco(char* label);

#endif