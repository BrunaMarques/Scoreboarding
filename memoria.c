#include "memoria.h"

void inicializaMemoria()
{
	//procurar tamanho da memoria e por em n //
	memoria = (char*)malloc(sizeof(char) * TAMANHO_MEMORIA);
	printf("\nMemoria inicializada\n");
}

/*void escritaMemoria()
{	printf("começando a escrever");
	FILE *instrucoes = fopen("codigoHexa.txt", "r");
	char *palavra_bytes;
	int palavra = 0, posicao = 0, endereco = 0, i = 0;

    while(fread(&palavra, sizeof(int), 1, instrucoes) == 1){
        // endereco = write_mem(palavra, endereco);
		i = 0;
		printf("\n%d", palavra);
    	palavra_bytes = (char*) &palavra;

    	for(posicao = endereco; posicao < endereco + 4; posicao++){
    	    memoria[posicao] = palavra_bytes[i++];
			printf("\nteste: %X", palavra_bytes[i]);
    	}
		endereco += 4;
    }

}*/

void escritaMemoria()
{

	FILE *instrucoes = fopen("codigoHexa.txt", "r");
	int palavra = 0, contPalavra = 0;


	while(fread(&palavra, sizeof(int), 1, instrucoes) == 1){

		for (int contByte = 0; contByte < 4; contByte++)
		{

			memoria[contPalavra - contByte + 3] = palavra & 0x0FF;
			palavra = (palavra >> 8);
		}

		contPalavra+=4;
	}
}

void buscaMemoria(unsigned int palavra[])
{
	int contByte = 0;
	printf("\nPC = %d ", PC);
	for (contByte = 0; contByte < 4; contByte++)
	{
		palavra[contByte] = memoria[PC + contByte];
		// printf ("teste --> %X", palavra[contByte]);
	}


}