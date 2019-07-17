#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "tradutor.h"

int registradores(char *aux){
	printf("REG: %s. ", aux);
	if(strcasecmp(aux,"$zero") == 0)
		return Z0;
	else if(strcasecmp(aux,"$at") == 0)
		return AT;
	else if(strcasecmp(aux,"$v0") == 0)
		return V0;
	else if(strcasecmp(aux,"$v1") == 0)
		return V1;
	else if(strcasecmp(aux,"$a0") == 0)
		return A0;
	else if(strcasecmp(aux,"$a1") == 0)
		return A1;
	else if(strcasecmp(aux,"$a2") == 0)
		return A2;
	else if(strcasecmp(aux,"$a3") == 0)
		return A3;
	else if(strcasecmp(aux,"$t0") == 0)
		return T0;
	else if(strcasecmp(aux,"$t1") == 0)
		return T1;
	else if(strcasecmp(aux,"$t2") == 0)
		return T2;
	else if(strcasecmp(aux,"$t3") == 0)
		return T3;
	else if(strcasecmp(aux,"$t4") == 0)
		return T4;
	else if(strcasecmp(aux,"$t5") == 0)
		return T5;
	else if(strcasecmp(aux,"$t6") == 0)
		return T6;
	else if(strcasecmp(aux,"$t7") == 0)
		return T7;
	else if(strcasecmp(aux,"$s0") == 0)
		return S0;
	else if(strcasecmp(aux,"$s1") == 0)
		return S1;
	else if(strcasecmp(aux,"$s2") == 0)
		return S2;
	else if(strcasecmp(aux,"$s3") == 0)
		return S3;
	else if(strcasecmp(aux,"$s4") == 0)
		return S4;
	else if(strcasecmp(aux,"$s5") == 0)
		return S5;
	else if(strcasecmp(aux,"$s6") == 0)
		return S6;
	else if(strcasecmp(aux,"$s7") == 0)
		return S7;
	else if(strcasecmp(aux,"$t8") == 0)
		return T8;
	else if(strcasecmp(aux,"$t9") == 0)
		return T9;
	else if(strcasecmp(aux,"$k0") == 0)
		return K0;
	else if(strcasecmp(aux,"$k1") == 0)
		return K1;
	else if(strcasecmp(aux,"$gp") == 0)
		return GP;
	else if(strcasecmp(aux,"$SP") == 0)
		return SP;
	else if(strcasecmp(aux,"$s8") == 0)
		return S8;
	else if(strcasecmp(aux,"$fp") == 0)
		return FP;
	else if (strcasecmp(aux,"$ra") == 0)
		return RA;	
	else return aux;
}

void binarioSpecial(int vetor[], FILE *saida){
	int r;
	for (int i =0; i<6; i++){
			printf("\nFVetor%i = %d ", i, vetor[i]);
		}
	for(int i = 5; i >= 0; i--) {
		printf("AAAAAA%d\n", vetor[0]);
		r = vetor[0] >> i;
		if(r & 1)
			fputs("1",saida);
		else
			fputs("0", saida);
	}
 	for(int i = 4; i >= 0; i--) {
		r = vetor[1] >> i;
		if(r & 1) 
			fputs("1",saida);
		else 
			fputs("0", saida);
	 }
	for(int i = 4; i >= 0; i--) {
		r = vetor[2] >> i;
		if(r & 1) 
			fputs("1",saida);
		else 
			fputs("0", saida);
	}
	for(int i = 4; i >= 0; i--) {
		r = vetor[3] >> i;
		if(r & 1) 
			fputs("1",saida);
		else 
			fputs("0", saida);
	}
	for(int i = 4; i >= 0; i--) {
		r = vetor[4] >> i;
		if(r & 1) 
			fputs("1",saida);
		else 
			fputs("0", saida);
	}
	for(int i = 5; i >= 0; i--) {
		r = vetor[5] >> i;
		if(r & 1) 
			fputs("1",saida);
		else 
			fputs("0", saida);
	}
	fputs("\n",saida);
}

void binarioimediato(int vetor[], FILE *saida){
	int r;
	for(int i=0; i<6; i++)
		printf("\nVETOR: %d\n", vetor[i]);
	for(int i = 6; i > 0; i--) {
		r = vetor[0] >> i;
		if(r & 1) 
			fputs("a1",saida);
		else 
			fputs("a0", saida);
	}
 	for(int i = 5; i > 0; i--) {
		r = vetor[1] >> i;
		if(r & 1) 
			fputs("b1",saida);
		else 
			fputs("b0", saida);
	 }
	for(int i = 5; i > 0; i--) {
		r = vetor[2] >> i;
		if(r & 1) 
			fputs("c1",saida);
		else 
			fputs("c0", saida);
	}
	for(int i = 16; i > 0; i--) {
		r = vetor[3] >> i;
		if(r & 1) 
			fputs("d1",saida);
		else 
			fputs("d0", saida);
	}
	fputs("\n",saida);
}


int main(){
    char texto[1000], *aux;
	int special[6], jump[2], regim[4], imediato[4];

	int i = 0;
    FILE *instrucoes = fopen("teste.asm", "r");
	FILE *saida = fopen("saida.txt", "w");;
    //i = readfield(instrucoes,texto);
	//printf("%s", texto);
	
	
	while(fgets(texto, 1000, instrucoes) != NULL){
		printf("%s", texto);
		aux = strtok(texto, ",  \n\0");
		if( (strcasecmp(aux,"add") == 0) || (strcasecmp(aux,"and") == 0) || (strcasecmp(aux,"div") == 0) || (strcasecmp(aux,"jr") == 0) || (strcasecmp(aux,"mfhi") == 0) || (strcasecmp(aux,"mflo") == 0) ||(strcasecmp(aux,"movn") == 0) || (strcasecmp(aux,"movz") == 0) || (strcasecmp(aux,"mthi") == 0) || (strcasecmp(aux,"mtlo") == 0) || (strcasecmp(aux,"mult") == 0) || (strcasecmp(aux,"nop") == 0) || (strcasecmp(aux,"or") == 0) || (strcasecmp(aux,"sub") == 0) || (strcasecmp(aux,"xor") == 0)){
			special[0] = 0b000000;
			printf("%s", aux);
			if(strcasecmp(aux, "add") == 0){
				special[5] = ADD;
				aux = strtok(NULL, ", \n\0");
				special[3] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
				special[1] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
				special[2] = registradores(aux);
				special[4] = 0b00000;
				aux = strtok(NULL, ", \n\0");
			}
			else if (strcasecmp(aux ,"and") == 0){
				special[5] = AND;
				aux = strtok(NULL, ", \n\0");
				special[3] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
				special[1] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
				special[2] = registradores(aux);
				special[4] = 0b00000;
				aux = strtok(NULL, ", \n\0");
			}
			else if (strcasecmp(aux,"div") == 0){
				special[5] = DIV;
				aux = strtok(NULL, ", \n\0");
				special[1] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
				special[2] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
				special[3] = 0b00000;
				special[4] = 0b00000;
				aux = strtok(NULL, ", \n\0");
			} 
			else if (strcasecmp(aux,"jr") == 0){
				special[5] = JR;
				aux = strtok(NULL, ", \n\0");
				special[1] = registradores(aux);
				special[2] = 0b00000;
				special[3] = 0b00000;
				special[4] = 0b00000;
				aux = strtok(NULL, ", \n\0");
			}
			else if (strcasecmp(aux,"mfhi") == 0){
				special[5] = MFHI;
				aux = strtok(NULL, ", \n\0");
				special[3] = registradores(aux);
				special[2] = 0b00000;
				special[1] = 0b00000;
				special[4] = 0b00000;
				aux = strtok(NULL, ", \n\0");
			} 
			else if (strcasecmp(aux,"mflo") == 0){
				special[5] = MFLO;
				aux = strtok(NULL, ", \n\0");
				special[3] = 0b00000;
				special[1] = 0b00000;
				special[2] = 0b00000;
				special[4] = 0b00000;
				aux = strtok(NULL, ", \n\0");
				
			} 
			else if (strcasecmp(aux,"movn") == 0){
				special[5] = MOVN;
				aux = strtok(NULL, ", \n\0");
				special[3] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
				special[1] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
				special[2] = registradores(aux);
				special[4] = 0b00000;
				aux = strtok(NULL, ", \n\0");
			} 
					
			else if (strcasecmp(aux,"movz") == 0){
				special[5] = MOVZ;
				aux = strtok(NULL, ", \n\0");
				special[3] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
				special[1] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
				special[2] = registradores(aux);
				special[4] = 0b00000;
				aux = strtok(NULL, ", \n\0");
			} 
					
			else if (strcasecmp(aux,"mthi") == 0){
				special[5] = MTHI;
				aux = strtok(NULL, ", \n\0");
				special[1] = registradores(aux);
				special[2] = 0b00000;
				special[3] = 0b00000;
				special[4] = 0b00000;
				aux = strtok(NULL, ", \n\0");
			}
					
			else if (strcasecmp(aux,"mtlo") == 0){
				special[5] = MTLO;
				aux = strtok(NULL, ", \n\0");
				special[1] = registradores(aux);
				special[2] = 0b00000;
				special[3] = 0b00000;
				special[4] = 0b00000;
				aux = strtok(NULL, ", \n\0");
			}
					
			else if (strcasecmp(aux,"mult") == 0){
				special[5] = MULT;
				aux = strtok(NULL, ", \n\0");
				special[1] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
				special[2] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
				special[3] = 0b00000;
				special[4] = 0b00000;
				aux = strtok(NULL, ", \n\0");
			}
					
			else if (strcasecmp(aux,"nop") == 0){
				special[5] = NOP;
				special[1] = 0b00000;
				special[2] = 0b00000;
				special[3] = 0b00000;
				special[4] = 0b00000;
				aux = strtok(NULL, ", \n\0");
			}
					
			else if (strcasecmp(aux,"nor") == 0){
				special[5] = NOR;
				aux = strtok(NULL, ", \n\0");
				special[3] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
				special[1] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
				special[2] = registradores(aux);
				special[4] = 0b00000;
				aux = strtok(NULL, ", \n\0");
			}
					
			else if (strcasecmp(aux,"or") == 0){
				special[5] = OR;
				aux = strtok(NULL, ", \n\0");
				special[3] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
				special[1] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
				special[2] = registradores(aux);
				special[4] = 0b00000;
				aux = strtok(NULL, ", \n\0");
			} 
					
			else if (strcasecmp(aux,"sub") == 0){
				special[5] = SUB;
				aux = strtok(NULL, ", \n\0");
				special[3] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
				special[1] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
				special[2] = registradores(aux);
				special[4] = 0b00000;
				aux = strtok(NULL, ", \n\0");
			} 
					
			else{ 
				special[5] = XOR;
				aux = strtok(NULL, ", \n\0");
				special[3] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
				special[1] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
				special[2] = registradores(aux);
				special[4] = 0b00000;
				aux = strtok(NULL, ", \n\0");
			}
		binarioSpecial(special,saida);
		}	
		else if ((strcasecmp(aux,"madd") == 0) || (strcasecmp(aux,"msub") == 0) || (strcasecmp(aux,"mul") == 0)){
			special[0] = 0b011100;
			if(strcasecmp(aux,"madd") == 0){
				special[5] = MADD;
				aux = strtok(NULL, ", \n\0");
				special[1] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
				special[2] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
				special[3] = 0b00000;
				special[4] = 0b00000;
				aux = strtok(NULL, ", \n\0");
			}
			else if(strcasecmp(aux,"msub") == 0){
				special[5] = MSUB;
				aux = strtok(NULL, ", \n\0");
				special[1] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
				special[2] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
				special[3] = 0b00000;
				special[4] = 0b00000;
				aux = strtok(NULL, ", \n\0");
			}
			else{
				special[5] = MUL;
				aux = strtok(NULL, ", \n\0");
				special[3] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
				special[1] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
				special[2] = registradores(aux);
				special[4] = 0b00000;
				aux = strtok(NULL, ", \n\0");
			}
		binarioSpecial(special,saida);
		}
		else if (strcasecmp(aux,"j") == 0){
			jump[0] = J;
			aux = strtok(NULL, ", \n\0");
			jump[1] = registradores(aux);
			aux = strtok(NULL, ", \n\0");
		}
		else if((strcasecmp(aux,"bgez") == 0) || (strcasecmp(aux,"bltz") == 0)){
			regim[0] = 0b000001;
			if (strcasecmp(aux,"bgez") == 0){
				regim[2] = BGEZ;
				aux = strtok(NULL, ", \n\0");
				regim[1] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
				regim[3] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
			}
			else{
				regim[2] = BLTZ;
				aux = strtok(NULL, ", \n\0");
				regim[1] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
				regim[3] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
			}	
			aux = strtok(NULL, ", \n\0");
		}
		else{
			if(strcasecmp(aux ,"addi") == 0){
				imediato[0] = ADDI;
				aux = strtok(NULL, ", \n\0");
				imediato[2] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
				imediato[1] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
				imediato[3] = registradores(aux);					
				aux = strtok(NULL, ", \n\0");
			}
			else if(strcasecmp(aux,"andi") == 0){
				imediato[0] = ANDI;
				aux = strtok(NULL, ", \n\0");
				imediato[2] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
				imediato[1] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
				imediato[3] = registradores(aux);					
				aux = strtok(NULL, ", \n\0");
			}
			else if(strcasecmp(aux,"b") == 0){
				imediato[0] = B;
				aux = strtok(NULL, ", \n\0");
				imediato[1] = 0b00000;
				aux = strtok(NULL, ", \n\0");
				imediato[2] = 0b00000;
				aux = strtok(NULL, ", \n\0");
				imediato[3] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
			}
			else if(strcasecmp(aux,"beq") == 0){
				imediato[0] = BEQ;
				aux = strtok(NULL, ", \n\0");
				imediato[1] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
				imediato[2] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
				imediato[3] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
			}
			else if(strcasecmp(aux,"beql") == 0){
				imediato[0] = BEQL;
				aux = strtok(NULL, ", \n\0");
				imediato[1] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
				imediato[2] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
				imediato[3] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
			}
			else if(strcasecmp(aux,"bgtz") == 0){
				imediato[0] = BGTZ;
				aux = strtok(NULL, ", \n\0");
				imediato[1] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
				imediato[2] = 0b00000;
				aux = strtok(NULL, ", \n\0");
				imediato[3] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
			}
			else if(strcasecmp(aux,"blez") == 0){
				imediato[0] = BLEZ;
				aux = strtok(NULL, ", \n\0");
				imediato[1] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
				imediato[2] = 0b00000;
				aux = strtok(NULL, ", \n\0");
				imediato[3] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
			}
			else if(strcasecmp(aux,"bne") == 0){
				imediato[0] = BNE;
				aux = strtok(NULL, ", \n\0");
				imediato[1] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
				imediato[2] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
				imediato[3] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
			}
			else if(strcasecmp(aux,"lui") == 0){
				imediato[0] = LUI;
				aux = strtok(NULL, ", \n\0");
				imediato[1] = 0b00000;
				aux = strtok(NULL, ", \n\0");
				imediato[2] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
				imediato[3] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
			}
			else if(strcasecmp(aux,"ori") == 0){
				imediato[0] = ORI;
				aux = strtok(NULL, ", \n\0");
				imediato[2] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
				imediato[1] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
				imediato[3] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
			}
			else{
				imediato[0] = XORI;
				aux = strtok(NULL, ", \n\0");
				imediato[1] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
				imediato[2] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
				imediato[3] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
			}
		//binarioimediato(imediato, saida);
		}
		for (int i =0; i<6; i++){
			printf("\nVetor%i = %d ", i, special[i]);
		}

			

		
		//aux = strtok(texto, ", ");
		//printf("teste:%s", aux);
		

	}
	//arquivo(saida);
return 0;
}