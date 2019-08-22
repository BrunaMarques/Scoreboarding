#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "tradutor.h"

int registradores(char *aux){
	if((strcasecmp(aux,"$zero") == 0) || (strcasecmp(aux,"$0") == 0))
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
	else return atoi(aux);
}

void binarioSpecial(int vetor[], FILE *saidaBinario){ //Transformar em binário
	int r;
	for(int i = 5; i >= 0; i--) {
		r = vetor[0] >> i;
		if(r & 1)
			fputs("1",saidaBinario);
		else
			fputs("0", saidaBinario);
	}
 	for(int i = 4; i >= 0; i--) {
		r = vetor[1] >> i;
		if(r & 1) 
			fputs("1",saidaBinario);
		else 
			fputs("0", saidaBinario);
	 }
	for(int i = 4; i >= 0; i--) {
		r = vetor[2] >> i;
		if(r & 1) 
			fputs("1",saidaBinario);
		else 
			fputs("0", saidaBinario);
	}
	for(int i = 4; i >= 0; i--) {
		r = vetor[3] >> i;
		if(r & 1) 
			fputs("1",saidaBinario);
		else 
			fputs("0", saidaBinario);
	}
	for(int i = 4; i >= 0; i--) {
		r = vetor[4] >> i;
		if(r & 1) 
			fputs("1",saidaBinario);
		else 
			fputs("0", saidaBinario);
	}
	for(int i = 5; i >= 0; i--) {
		r = vetor[5] >> i;
		if(r & 1) 
			fputs("1",saidaBinario);
		else 
			fputs("0", saidaBinario);
	}
	fputs("\n",saidaBinario);
}

void binarioImediato(int vetor[], FILE *saidaBinario){
	int r;
	for(int i = 5; i >= 0; i--) {
		r = vetor[0] >> i;
		if(r & 1) 
			fputs("1",saidaBinario);
		else 
			fputs("0", saidaBinario);
	}
 	for(int i = 4; i >= 0; i--) {
		r = vetor[1] >> i;
		if(r & 1) 
			fputs("1",saidaBinario);
		else 
			fputs("0", saidaBinario);
	 }
	for(int i = 4; i >= 0; i--) {
		r = vetor[2] >> i;
		if(r & 1) 
			fputs("1",saidaBinario);
		else 
			fputs("0", saidaBinario);
	}
	for(int i = 15; i >= 0; i--) {
		r = vetor[3] >> i;
		if(r & 1) 
			fputs("1",saidaBinario);
		else 
			fputs("0", saidaBinario);
	}
	fputs("\n",saidaBinario);
}

void binarioRegim(int vetor[], FILE *saidaBinario){
	int r;
	for(int i = 5; i >= 0; i--) {
		r = vetor[0] >> i;
		if(r & 1) 
			fputs("1",saidaBinario);
		else 
			fputs("0", saidaBinario);
	}
 	for(int i = 4; i >= 0; i--) {
		r = vetor[1] >> i;
		if(r & 1) 
			fputs("1",saidaBinario);
		else 
			fputs("0", saidaBinario);
	 }
	for(int i = 4; i >= 0; i--) {
		r = vetor[2] >> i;
		if(r & 1) 
			fputs("1",saidaBinario);
		else 
			fputs("0", saidaBinario);
	}
	for(int i = 15; i >= 0; i--) {
		r = vetor[3] >> i;
		if(r & 1) 
			fputs("1",saidaBinario);
		else 
			fputs("0", saidaBinario);
	}
	fputs("\n",saidaBinario);
}

void binarioJump(int vetor[], FILE *saidaBinario){
	int r;
	for(int i = 5; i >= 0; i--) {
		r = vetor[0] >> i;
		if(r & 1) 
			fputs("1",saidaBinario);
		else 
			fputs("0", saidaBinario);
	}
 	for(int i = 25; i >= 0; i--) {
		r = vetor[1] >> i;
		if(r & 1) 
			fputs("1",saidaBinario);
		else 
			fputs("0", saidaBinario);
	 }
	fputs("\n",saidaBinario);
}

void tradutorBin(FILE *instrucoes, FILE *saidaBinario){
	int linhas = 0;
	qtd = 0;
	inicializarHash();
	while(fgets(texto, 100, instrucoes) != NULL){
		aux = strtok(texto, ",  \n\0");
		linhas++;
		if((strcasecmp(aux,"add") == 0) || (strcasecmp(aux,"and") == 0) || (strcasecmp(aux,"div") == 0) || (strcasecmp(aux,"jr") == 0) || (strcasecmp(aux,"mfhi") == 0) || (strcasecmp(aux,"mflo") == 0) ||(strcasecmp(aux,"movn") == 0) || (strcasecmp(aux,"movz") == 0) || (strcasecmp(aux,"mthi") == 0) || (strcasecmp(aux,"mtlo") == 0) || (strcasecmp(aux,"mult") == 0) || (strcasecmp(aux,"nop") == 0) || (strcasecmp(aux,"or") == 0) || (strcasecmp(aux,"sub") == 0) || (strcasecmp(aux,"xor") == 0) || (strcasecmp(aux,"nor") == 0) || (strcasecmp(aux,"madd") == 0) || (strcasecmp(aux,"msub") == 0) || (strcasecmp(aux,"mul") == 0) ||(strcasecmp(aux,"j") == 0) || (strcasecmp(aux,"bgez") == 0) || (strcasecmp(aux,"bltz") == 0) || (strcasecmp(aux,"addi") == 0) || (strcasecmp(aux,"andi") == 0) || (strcasecmp(aux,"b") == 0) || (strcasecmp(aux,"beq") == 0) || (strcasecmp(aux,"beql") == 0) || (strcasecmp(aux,"bgtz") == 0) || (strcasecmp(aux,"blez") == 0) || (strcasecmp(aux,"bne") == 0) || (strcasecmp(aux,"lui") == 0) || (strcasecmp(aux,"ori") == 0) || (strcasecmp(aux,"xori") == 0)){
			qtd++;
		}
		else
		{
			hash(aux);
			inserirLabel(aux, linhas*4);
		}
		// ((strcasecmp(aux,"add") == 0) || (strcasecmp(aux,"and") == 0) || (strcasecmp(aux,"div") == 0) || (strcasecmp(aux,"jr") == 0) || (strcasecmp(aux,"mfhi") == 0) || (strcasecmp(aux,"mflo") == 0) ||(strcasecmp(aux,"movn") == 0) || (strcasecmp(aux,"movz") == 0) || (strcasecmp(aux,"mthi") == 0) || (strcasecmp(aux,"mtlo") == 0) || (strcasecmp(aux,"mult") == 0) || (strcasecmp(aux,"nop") == 0) || (strcasecmp(aux,"or") == 0) || (strcasecmp(aux,"sub") == 0) || (strcasecmp(aux,"xor") == 0) || (strcasecmp(aux,"nor") == 0) || (strcasecmp(aux,"madd") == 0) || (strcasecmp(aux,"msub") == 0) || (strcasecmp(aux,"mul") == 0) ||(strcasecmp(aux,"j") == 0) || (strcasecmp(aux,"bgez") == 0) || (strcasecmp(aux,"bltz") == 0) || (strcasecmp(aux,"addi") == 0) || (strcasecmp(aux,"andi") == 0) || (strcasecmp(aux,"b") == 0) || (strcasecmp(aux,"beq") == 0) || (strcasecmp(aux,"beql") == 0) || (strcasecmp(aux,"bgtz") == 0) || (strcasecmp(aux,"blez") == 0) || (strcasecmp(aux,"bne") == 0) || (strcasecmp(aux,"lui") == 0) || (strcasecmp(aux,"ori") == 0) || (strcasecmp(aux,"xori") == 0))?  : inserirLabel(aux, linhas);
		
	}
	fseek(instrucoes, 0, SEEK_SET);
	while(fgets(texto, 100, instrucoes) != NULL){ //pegar as instruções
		aux = strtok(texto, ",  \n\0"); //vai pegar até virgula, espaço, quebra de linha e fim de arquivo, para separra cada instrução ou registrador
		if( (strcasecmp(aux,"add") == 0) || (strcasecmp(aux,"and") == 0) || (strcasecmp(aux,"div") == 0) || (strcasecmp(aux,"jr") == 0) || (strcasecmp(aux,"mfhi") == 0) || (strcasecmp(aux,"mflo") == 0) ||(strcasecmp(aux,"movn") == 0) || (strcasecmp(aux,"movz") == 0) || (strcasecmp(aux,"mthi") == 0) || (strcasecmp(aux,"mtlo") == 0) || (strcasecmp(aux,"mult") == 0) || (strcasecmp(aux,"nop") == 0) || (strcasecmp(aux,"or") == 0) || (strcasecmp(aux,"sub") == 0) || (strcasecmp(aux,"xor") == 0) || (strcasecmp(aux,"nor") == 0)){
			special[0] = 0b000000; //pega opcode 
			if(strcasecmp(aux, "add") == 0){
				special[5] = TADD;
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
				special[5] = TAND;
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
				special[5] = TDIV;
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
				special[5] = TJR;
				aux = strtok(NULL, ", \n\0");
				special[1] = registradores(aux);
				special[2] = 0b00000;
				special[3] = 0b00000;
				special[4] = 0b00000;
				aux = strtok(NULL, ", \n\0");
			}
			else if (strcasecmp(aux,"mfhi") == 0){
				special[5] = TMFHI;
				aux = strtok(NULL, ", \n\0");
				special[3] = registradores(aux);
				special[2] = 0b00000;
				special[1] = 0b00000;
				special[4] = 0b00000;
				aux = strtok(NULL, ", \n\0");
			} 
			else if (strcasecmp(aux,"mflo") == 0){
				special[5] = TMFLO;
				aux = strtok(NULL, ", \n\0");
				special[3] = registradores(aux);
				special[1] = 0b00000;
				special[2] = 0b00000;
				special[4] = 0b00000;
				aux = strtok(NULL, ", \n\0");
				
			} 
			else if (strcasecmp(aux,"movn") == 0){
				special[5] = TMOVN;
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
				special[5] = TMOVZ;
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
				special[5] = TMTHI;
				aux = strtok(NULL, ", \n\0");
				special[1] = registradores(aux);
				special[2] = 0b00000;
				special[3] = 0b00000;
				special[4] = 0b00000;
				aux = strtok(NULL, ", \n\0");
			}
					
			else if (strcasecmp(aux,"mtlo") == 0){
				special[5] = TMTLO;
				aux = strtok(NULL, ", \n\0");
				special[1] = registradores(aux);
				special[2] = 0b00000;
				special[3] = 0b00000;
				special[4] = 0b00000;
				aux = strtok(NULL, ", \n\0");
			}
					
			else if (strcasecmp(aux,"mult") == 0){
				special[5] = TMULT;
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
				special[5] = TNOP;
				special[1] = 0b00000;
				special[2] = 0b00000;
				special[3] = 0b00000;
				special[4] = 0b00000;
				aux = strtok(NULL, ", \n\0");
			}
			else if (strcasecmp(aux,"nor") == 0){
				special[5] = TNOR;
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
				special[5] = TOR;
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
				special[5] = TSUB;
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
				special[5] = TXOR;
				aux = strtok(NULL, ", \n\0");
				special[3] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
				special[1] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
				special[2] = registradores(aux);
				special[4] = 0b00000;
				aux = strtok(NULL, ", \n\0");
			}
		binarioSpecial(special,saidaBinario);
		}	
		else if ((strcasecmp(aux,"madd") == 0) || (strcasecmp(aux,"msub") == 0) || (strcasecmp(aux,"mul") == 0)){
			special[0] = 0b011100;
			if(strcasecmp(aux,"madd") == 0){
				special[5] = TMADD;
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
				special[5] = TMSUB;
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
				special[5] = TMUL;
				aux = strtok(NULL, ", \n\0");
				special[3] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
				special[1] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
				special[2] = registradores(aux);
				special[4] = 0b00000;
				aux = strtok(NULL, ", \n\0");
			}
		binarioSpecial(special,saidaBinario);
		}
		else if (strcasecmp(aux,"j") == 0){
			jump[0] = TJ;
			aux = strtok(NULL, ", \n\0");
			hash(aux);
			jump[1] = pegarEndereco(aux);
			aux = strtok(NULL, ", \n\0");
		binarioJump(jump,saidaBinario);
		}
		else if((strcasecmp(aux,"bgez") == 0) || (strcasecmp(aux,"bltz") == 0)){
			regim[0] = 0b000001;
			if (strcasecmp(aux,"bgez") == 0){
				regim[2] = TBGEZ;
				aux = strtok(NULL, ", \n\0");
				regim[1] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
				hash(aux);
				regim[3] = pegarEndereco(aux);
				aux = strtok(NULL, ", \n\0");
			}
			else{
				regim[2] = TBLTZ;
				aux = strtok(NULL, ", \n\0");
				regim[1] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
				hash(aux);
				regim[3] = pegarEndereco(aux);
				aux = strtok(NULL, ", \n\0");
			}	
		binarioRegim(regim, saidaBinario);
		}
		else if((strcasecmp(aux,"addi") == 0) || (strcasecmp(aux,"andi") == 0) || (strcasecmp(aux,"b") == 0) || (strcasecmp(aux,"beq") == 0) || (strcasecmp(aux,"beql") == 0) || (strcasecmp(aux,"bgtz") == 0) || (strcasecmp(aux,"blez") == 0) || (strcasecmp(aux,"bne") == 0) || (strcasecmp(aux,"lui") == 0) || (strcasecmp(aux,"ori") == 0) || (strcasecmp(aux,"xori") == 0)){
			if(strcasecmp(aux ,"addi") == 0){
				imediato[0] = TADDI;
				aux = strtok(NULL, ", \n\0");
				imediato[2] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
				imediato[1] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
				imediato[3] = registradores(aux);					
				aux = strtok(NULL, ", \n\0");
			}
			else if(strcasecmp(aux,"andi") == 0){
				imediato[0] = TANDI;
				aux = strtok(NULL, ", \n\0");
				imediato[2] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
				imediato[1] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
				imediato[3] = registradores(aux);					
				aux = strtok(NULL, ", \n\0");
			}
			else if(strcasecmp(aux,"b") == 0){
				imediato[0] = TB;
				aux = strtok(NULL, ", \n\0");
				imediato[1] = 0b00000;
				imediato[2] = 0b00000;
				hash(aux);
				imediato[3] = pegarEndereco(aux);
				aux = strtok(NULL, ", \n\0");
			}
			else if(strcasecmp(aux,"beq") == 0){
				imediato[0] = TBEQ;
				aux = strtok(NULL, ", \n\0");
				imediato[1] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
				imediato[2] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
				hash(aux);
				imediato[3] = pegarEndereco(aux);
				aux = strtok(NULL, ", \n\0");
			}
			else if(strcasecmp(aux,"beql") == 0){
				imediato[0] = TBEQL;
				aux = strtok(NULL, ", \n\0");
				imediato[1] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
				imediato[2] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
				hash(aux);
				imediato[3] = pegarEndereco(aux);
				aux = strtok(NULL, ", \n\0");
			}
			else if(strcasecmp(aux,"bgtz") == 0){
				imediato[0] = TBGTZ;
				aux = strtok(NULL, ", \n\0");
				imediato[1] = registradores(aux);
				imediato[2] = 0b00000;
				aux = strtok(NULL, ", \n\0");
				hash(aux);
				imediato[3] = pegarEndereco(aux);
				aux = strtok(NULL, ", \n\0");
			}
			else if(strcasecmp(aux,"blez") == 0){
				imediato[0] = TBLEZ;
				aux = strtok(NULL, ", \n\0");
				imediato[1] = registradores(aux);
				imediato[2] = 0b00000;
				aux = strtok(NULL, ", \n\0");
				hash(aux);
				imediato[3] = pegarEndereco(aux);
				aux = strtok(NULL, ", \n\0");
			}
			else if(strcasecmp(aux,"bne") == 0){
				imediato[0] = TBNE;
				aux = strtok(NULL, ", \n\0");
				imediato[1] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
				imediato[2] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
				hash(aux);
				imediato[3] = pegarEndereco(aux);
				aux = strtok(NULL, ", \n\0");
			}
			else if(strcasecmp(aux,"lui") == 0){
				imediato[0] = TLUI;
				imediato[1] = 0b00000;
				aux = strtok(NULL, ", \n\0");
				imediato[2] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
				imediato[3] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
			}
			else if(strcasecmp(aux,"ori") == 0){
				imediato[0] = TORI;
				aux = strtok(NULL, ", \n\0");
				imediato[2] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
				imediato[1] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
				imediato[3] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
			}
			else{
				imediato[0] = TXORI;
				aux = strtok(NULL, ", \n\0");
				imediato[1] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
				imediato[2] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
				imediato[3] = registradores(aux);
				aux = strtok(NULL, ", \n\0");
			}
		binarioImediato(imediato, saidaBinario);
		}
		else{
			aux = strtok(NULL, ", \n\0");
			//aqui vai ser a label tem que fazer a hash
		}
		
	}
}

void tradutorHexa(FILE *saidaHexa, FILE *saidaBin){
	char bin[34], *aux; 
	int numero;
	while(fgets(bin, 34, saidaBin) != NULL){
		// printf("tamanho %d\n", (int)strlen(bin));
		bin[strlen(bin)] = '\0';
		numero = (int)strtol(bin, NULL, 2); //converte para a base 2 e depois pra int
		fprintf(prog, "\n\t%X", numero);
		fwrite(&numero, sizeof(int), 1, saidaHexa); //escreve no arquivo
		//fwrite("\n", 1, 1, saidaHexa);
		if(detail != NULL){
			fprintf(detail, "\n\t%X", numero);
		}

	}

}

void print_assembly(FILE *instrucoes){
	char *aux, texto[100];
	while(fgets(texto, 100, instrucoes) != NULL){
		aux = strtok(texto, "\n\0");
		//printf("%s\n", aux);
		fprintf(prog, "\t%s", aux);
		fprintf(prog, "\n");
		if(detail != NULL){
		fprintf(detail, "\t%s", aux);
		fprintf(detail, "\n");
		}
	}
}

void tradutor(){
	instrucoes = fopen(entrada, "r");
	saidaBinario = fopen("codigoBinario.txt", "w+");
	saidaHexa = fopen(saida, "w+");
	//printf("\nPrograma:\n");
	fprintf(prog,"Programa:\n");
	if(detail != NULL)
		fprintf(detail,"Programa:\n");
	print_assembly(instrucoes);
	fseek(instrucoes, 0, SEEK_SET); //voltar para o começo s
	tradutorBin(instrucoes, saidaBinario);
	fseek(saidaBinario, 0, SEEK_SET);
	fprintf(prog, "\nBinário:");
	if(detail != NULL)
		fprintf(detail, "\nBinário:");
	tradutorHexa(saidaHexa, saidaBinario);
	fclose(saidaBinario);
	fclose(saidaHexa);
}

