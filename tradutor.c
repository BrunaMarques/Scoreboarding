#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "tradutor.h"

int registradores(char *aux){
	//printf("REG: %s ", aux);
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


int main(){
    char texto[1000], *aux;
	int special[6], jump[2], regim[4], imediato[4];

	int i = 0;
    FILE *instrucoes = fopen("teste.asm", "r");
    //i = readfield(instrucoes,texto);
	//printf("%s", texto);
	
	
	while(fgets(texto, 1000, instrucoes) != NULL){
		printf("%s", texto);
		aux = strtok(texto, ", ");
		if( (strcasecmp(aux,"add") == 0) || (strcasecmp(aux,"and") == 0) || (strcasecmp(aux,"div") == 0) || (strcasecmp(aux,"jr") == 0) || (strcasecmp(aux,"mfhi") == 0) || (strcasecmp(aux,"mflo") == 0) ||(strcasecmp(aux,"movn") == 0) || (strcasecmp(aux,"movz") == 0) || (strcasecmp(aux,"mthi") == 0) || (strcasecmp(aux,"mtlo") == 0) || (strcasecmp(aux,"mult") == 0) || (strcasecmp(aux,"nop") == 0) || (strcasecmp(aux,"or") == 0) || (strcasecmp(aux,"sub") == 0) || (strcasecmp(aux,"xor") == 0)){
			special[0] = 0b000000;
			printf("%s", aux);
			if(strcasecmp(aux, "add") == 0){
				special[5] = ADD;
				aux = strtok(NULL, ", ");
				special[1] = registradores(aux);
				aux = strtok(NULL, ", ");
				special[2] = registradores(aux);
				aux = strtok(NULL, ", ");
				special[3] = registradores(aux);
				special[4] = 0b00000;
				//aux = strtok(NULL, ", ");
			}
			else if (strcasecmp(aux ,"and") == 0){
				aux = strtok(NULL, ", ");
				special[5] = AND;
				special[1] = registradores(aux);
				aux = strtok(NULL, ", ");
				special[2] = registradores(aux);
				aux = strtok(NULL, ", ");
				special[3] = registradores(aux);
				special[4] = 0b00000;
			}
			else if (strcasecmp(aux,"div") == 0){
				aux = strtok(NULL, ", ");
				special[5] = DIV;
				special[1] = registradores(aux);
				aux = strtok(NULL, ", ");
				special[2] = registradores(aux);
				aux = strtok(NULL, ", ");
				special[3] = registradores(aux);
				special[4] = 0b00000;
			} 
			else if (strcasecmp(aux,"jr") == 0){
				aux = strtok(NULL, ", ");
				special[5] = JR;
				special[1] = registradores(aux);
				aux = strtok(NULL, ", ");
				special[2] = registradores(aux);
				aux = strtok(NULL, ", ");
				special[3] = registradores(aux);
				special[4] = 0b00000;
			}
			else if (strcasecmp(aux,"mfhi") == 0){
				special[5] = MFHI;
				aux = strtok(NULL, ", ");
				special[1] = registradores(aux);
				aux = strtok(NULL, ", ");
				special[2] = registradores(aux);
				aux = strtok(NULL, ", ");
				special[3] = registradores(aux);
				special[4] = 0b00000;
			} 
			else if (strcasecmp(aux,"mflo") == 0){
				aux = strtok(NULL, ", ");
				special[5] = MFLO;
				special[1] = registradores(aux);
				aux = strtok(NULL, ", ");
				special[2] = registradores(aux);
				aux = strtok(NULL, ", ");
				special[3] = registradores(aux);
				special[4] = 0b00000;
				
			} 
			else if (strcasecmp(aux,"movn") == 0){
				aux = strtok(NULL, ", ");
				special[5] = MOVN;
				special[1] = registradores(aux);
				aux = strtok(NULL, ", ");
				special[2] = registradores(aux);
				aux = strtok(NULL, ", ");
				special[3] = registradores(aux);
				special[4] = 0b00000;
			} 
					
			else if (strcasecmp(aux,"movz") == 0){
				aux = strtok(NULL, ", ");
				special[5] = MOVZ;
				special[1] = registradores(aux);
				aux = strtok(NULL, ", ");
				special[2] = registradores(aux);
				aux = strtok(NULL, ", ");
				special[3] = registradores(aux);
				special[4] = 0b00000;
			} 
					
			else if (strcasecmp(aux,"mthi") == 0){
				aux = strtok(NULL, ", ");
				special[5] = MTHI;
				special[1] = registradores(aux);
				aux = strtok(NULL, ", ");
				special[2] = registradores(aux);
				aux = strtok(NULL, ", ");
				special[3] = registradores(aux);
				special[4] = 0b00000;
			}
					
			else if (strcasecmp(aux,"mtlo") == 0){
				aux = strtok(NULL, ", ");
				special[5] = MTLO;
				special[1] = registradores(aux);
				aux = strtok(NULL, ", ");
				special[2] = registradores(aux);
				aux = strtok(NULL, ", ");
				special[3] = registradores(aux);
				special[4] = 0b00000;
			}
					
			else if (strcasecmp(aux,"mult") == 0){
				aux = strtok(NULL, ", ");
				special[5] = MULT;
				special[1] = registradores(aux);
				aux = strtok(NULL, ", ");
				special[2] = registradores(aux);
				aux = strtok(NULL, ", ");
				special[3] = registradores(aux);
				special[4] = 0b00000;
			}
					
			else if (strcasecmp(aux,"nop") == 0){
				aux = strtok(NULL, ", ");
				special[5] = NOP;
				special[1] = registradores(aux);
				aux = strtok(NULL, ", ");
				special[2] = registradores(aux);
				aux = strtok(NULL, ", ");
				special[3] = registradores(aux);
				special[4] = 0b00000;
			}
					
			else if (strcasecmp(aux,"nor") == 0){
				aux = strtok(NULL, ", ");
				special[5] = NOR;
				special[1] = registradores(aux);
				aux = strtok(NULL, ", ");
				special[2] = registradores(aux);
				aux = strtok(NULL, ", ");
				special[3] = registradores(aux);
				special[4] = 0b00000;
			}
					
			else if (strcasecmp(aux,"or") == 0){
				aux = strtok(NULL, ", ");
				special[5] = OR;
				special[1] = registradores(aux);
				aux = strtok(NULL, ", ");
				special[2] = registradores(aux);
				aux = strtok(NULL, ", ");
				special[3] = registradores(aux);
				special[4] = 0b00000;
			} 
					
			else if (strcasecmp(aux,"sub") == 0){
				aux = strtok(NULL, ", ");
				special[5] = SUB;
				special[1] = registradores(aux);
				aux = strtok(NULL, ", ");
				special[2] = registradores(aux);
				aux = strtok(NULL, ", ");
				special[3] = registradores(aux);
				special[4] = 0b00000;
			} 
					
			else{ 
				aux = strtok(NULL, ", ");
				special[5] = XOR;
				special[1] = registradores(aux);
				aux = strtok(NULL, ", ");
				special[2] = registradores(aux);
				aux = strtok(NULL, ", ");
				special[3] = registradores(aux);
				special[4] = 0b00000;
			}
		}	
		else if ((strcasecmp(aux,"madd") == 0) || (strcasecmp(aux,"msub") == 0) || (strcasecmp(aux,"mul") == 0)){
			special[0] = 0b011100;
			if(strcasecmp(aux,"madd") == 0){
				special[5] = MADD;
				aux = strtok(NULL, ", ");
				special[1] = registradores(aux);
				aux = strtok(NULL, ", ");
				special[2] = registradores(aux);
				aux = strtok(NULL, ", ");
				special[3] = 0b00000;
				special[4] = 0b00000;
			}
			else if(strcasecmp(aux,"msub") == 0){
				special[5] = MSUB;
				aux = strtok(NULL, ", ");
				special[1] = registradores(aux);
				aux = strtok(NULL, ", ");
				special[2] = registradores(aux);
				aux = strtok(NULL, ", ");
				special[3] = 0b00000;
				special[4] = 0b00000;
			}
			else{
				special[5] = MUL;
				aux = strtok(NULL, ", ");
				special[1] = registradores(aux);
				aux = strtok(NULL, ", ");
				special[2] = registradores(aux);
				aux = strtok(NULL, ", ");
				special[3] = registradores(aux);
				special[4] = 0b00000;
			}
		}
		else if (strcasecmp(aux,"j") == 0){
			jump[0] = J;
			aux = strtok(NULL, ", ");
			jump[1] = registradores(aux);
		}
		else if((strcasecmp(aux,"bgez") == 0) || (strcasecmp(aux,"bltz") == 0)){
			regim[0] = 0b000001;
			if (strcasecmp(aux,"bgez") == 0){
				regim[2] = BGEZ;
				aux = strtok(NULL, ", ");
				special[1] = registradores(aux);
				aux = strtok(NULL, ", ");
				special[3] = registradores(aux);
			}
			else{
				regim[2] = BLTZ;
				aux = strtok(NULL, ", ");
				special[1] = registradores(aux);
				aux = strtok(NULL, ", ");
				special[3] = registradores(aux);
			}	
		}
		else{
			if(strcasecmp(aux ,"addi") == 0){
				imediato[0] = ADDI;
				aux = strtok(NULL, ", ");
				special[1] = registradores(aux);
				aux = strtok(NULL, ", ");
				special[2] = registradores(aux);
				aux = strtok(NULL, ", ");
				special[3] = registradores(aux);					
			}
			else if(strcasecmp(aux,"andi") == 0){
				imediato[0] = ANDI;
				aux = strtok(NULL, ", ");
				special[1] = registradores(aux);
				aux = strtok(NULL, ", ");
				special[2] = registradores(aux);
				aux = strtok(NULL, ", ");
				special[3] = registradores(aux);
			}
			else if(strcasecmp(aux,"b") == 0){
				imediato[0] = B;
				aux = strtok(NULL, ", ");
				special[1] = 0b00000;
				aux = strtok(NULL, ", ");
				special[2] = 0b00000;
				aux = strtok(NULL, ", ");
				special[3] = registradores(aux);
			}
			else if(strcasecmp(aux,"beq") == 0){
				imediato[0] = BEQ;
				aux = strtok(NULL, ", ");
				special[1] = registradores(aux);
				aux = strtok(NULL, ", ");
				special[2] = registradores(aux);
				aux = strtok(NULL, ", ");
				special[3] = registradores(aux);
			}
			else if(strcasecmp(aux,"beql") == 0){
				imediato[0] = BEQL;
				aux = strtok(NULL, ", ");
				special[1] = registradores(aux);
				aux = strtok(NULL, ", ");
				special[2] = registradores(aux);
				aux = strtok(NULL, ", ");
				special[3] = registradores(aux);
			}
			else if(strcasecmp(aux,"bgtz") == 0){
				imediato[0] = BGTZ;
				aux = strtok(NULL, ", ");
				special[1] = registradores(aux);
				aux = strtok(NULL, ", ");
				special[2] = 0b00000;
				aux = strtok(NULL, ", ");
				special[3] = registradores(aux);
			}
			else if(strcasecmp(aux,"blez") == 0){
				imediato[0] = BLEZ;
				aux = strtok(NULL, ", ");
				special[1] = registradores(aux);
				aux = strtok(NULL, ", ");
				special[2] = 0b00000;
				aux = strtok(NULL, ", ");
				special[3] = registradores(aux);
			}
			else if(strcasecmp(aux,"bne") == 0){
				imediato[0] = BNE;
				aux = strtok(NULL, ", ");
				special[1] = registradores(aux);
				aux = strtok(NULL, ", ");
				special[2] = registradores(aux);
				aux = strtok(NULL, ", ");
				special[3] = registradores(aux);
			}
			else if(strcasecmp(aux,"lui") == 0){
				imediato[0] = LUI;
				aux = strtok(NULL, ", ");
				special[1] = 0b00000;
				aux = strtok(NULL, ", ");
				special[2] = registradores(aux);
				aux = strtok(NULL, ", ");
				special[3] = registradores(aux);
			}
			else if(strcasecmp(aux,"ori") == 0){
				imediato[0] = ORI;
				aux = strtok(NULL, ", ");
				special[1] = registradores(aux);
				aux = strtok(NULL, ", ");
				special[2] = registradores(aux);
				aux = strtok(NULL, ", ");
				special[3] = registradores(aux);
			}
			else{
				imediato[0] = XORI;
				aux = strtok(NULL, ", ");
				special[1] = registradores(aux);
				aux = strtok(NULL, ", ");
				special[2] = registradores(aux);
				aux = strtok(NULL, ", ");
				special[3] = registradores(aux);
			}
		}
		printf("\nteste:%s", aux);
		for (int i =0; i<6; i++){
			printf(" %d ", special[i]);
		}
			

		
		//aux = strtok(texto, ", ");
		//printf("teste:%s", aux);
		

	}
return 0;
}