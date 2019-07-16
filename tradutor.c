#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tradutor.h"

int registradores(char *aux){
	if(aux == "$zero")
		return Z0;
	else if(aux == "at")
		return AT;
	else if(aux == "v0")
		return V0;
	else if(aux == "v1")
		return V1;
	else if(aux == "a0")
		return A0;
	else if(aux == "a1")
		return A1;
	else if(aux == "a2")
		return A2;
	else if(aux == "a3")
		return A3;
	else if(aux == "t0")
		return T0;
	else if(aux == "t1")
		return T1;
	else if(aux == "t2")
		return T2;
	else if(aux == "t3")
		return T3;
	else if(aux == "t4")
		return T4;
	else if(aux == "t5")
		return T5;
	else if(aux == "t6")
		return T6;
	else if(aux == "t7")
		return T7;
	else if(aux == "s0")
		return S0;
	else if(aux == "s1")
		return S1;
	else if(aux == "s2")
		return S2;
	else if(aux == "s3")
		return S3;
	else if(aux == "s4")
		return S4;
	else if(aux == "s5")
		return S5;
	else if(aux == "s6")
		return S6;
	else if(aux == "s7")
		return S7;
	else if(aux == "t8")
		return T8;
	else if(aux == "t9")
		return T9;
	else if(aux == "k0")
		return K0;
	else if(aux == "k1")
		return K1;
	else if(aux == "gp")
		return GP;
	else if(aux == "SP")
		return SP;
	else if(aux == "s8")
		return S8;
	else if(aux == "fp")
		return FP;
	else if (aux == "ra")
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
		while (aux != NULL){
			if(aux == "add" || "and" || "div" || "jr" || "mfhi" || "mflo" ||"movn" || "movz" || "mthi" || "mtlo" || "mult" || "nop" || "or" || "sub" || "xor"){
				special[0] = 0b000000;
				if(aux == "add"){
					aux = strtok(NULL, ", ");
					special[5] = ADD;
					special[1] = registradores(aux);
					aux = strtok(NULL, ", ");
					special[2] = registradores(aux);
					aux = strtok(NULL, ", ");
					special[3] = registradores(aux);
					special[4] = 0b00000;
				}
				else if (aux == "and"){
					aux = strtok(NULL, ", ");
					special[5] = AND;
					special[1] = registradores(aux);
					aux = strtok(NULL, ", ");
					special[2] = registradores(aux);
					aux = strtok(NULL, ", ");
					special[3] = registradores(aux);
					special[4] = 0b00000;
				}
				else if (aux == "div" ){
					aux = strtok(NULL, ", ");
					special[5] = DIV;
					special[1] = registradores(aux);
					aux = strtok(NULL, ", ");
					special[2] = registradores(aux);
					aux = strtok(NULL, ", ");
					special[3] = registradores(aux);
					special[4] = 0b00000;
				} 
				else if (aux == "jr"){
					aux = strtok(NULL, ", ");
					special[5] = JR;
					special[1] = registradores(aux);
					aux = strtok(NULL, ", ");
					special[2] = registradores(aux);
					aux = strtok(NULL, ", ");
					special[3] = registradores(aux);
					special[4] = 0b00000;
				}
				else if (aux == "mfhi"){
					special[5] = MFHI;
					aux = strtok(NULL, ", ");
					special[1] = registradores(aux);
					aux = strtok(NULL, ", ");
					special[2] = registradores(aux);
					aux = strtok(NULL, ", ");
					special[3] = registradores(aux);
					special[4] = 0b00000;
				} 
				else if (aux == "mflo"){
					aux = strtok(NULL, ", ");
					special[5] = MFLO;
					special[1] = registradores(aux);
					aux = strtok(NULL, ", ");
					special[2] = registradores(aux);
					aux = strtok(NULL, ", ");
					special[3] = registradores(aux);
					special[4] = 0b00000;
					
				} 
				else if (aux == "movn"){
					aux = strtok(NULL, ", ");
					special[5] = MOVN;
					special[1] = registradores(aux);
					aux = strtok(NULL, ", ");
					special[2] = registradores(aux);
					aux = strtok(NULL, ", ");
					special[3] = registradores(aux);
					special[4] = 0b00000;
				} 
					
				else if (aux == "movz"){
					aux = strtok(NULL, ", ");
					special[5] = MOVZ;
					special[1] = registradores(aux);
					aux = strtok(NULL, ", ");
					special[2] = registradores(aux);
					aux = strtok(NULL, ", ");
					special[3] = registradores(aux);
					special[4] = 0b00000;
				} 
					
				else if (aux == "mthi"){
					aux = strtok(NULL, ", ");
					special[5] = MTHI;
					special[1] = registradores(aux);
					aux = strtok(NULL, ", ");
					special[2] = registradores(aux);
					aux = strtok(NULL, ", ");
					special[3] = registradores(aux);
					special[4] = 0b00000;
				}
					
				else if (aux == "mtlo"){
					aux = strtok(NULL, ", ");
					special[5] = MTLO;
					special[1] = registradores(aux);
					aux = strtok(NULL, ", ");
					special[2] = registradores(aux);
					aux = strtok(NULL, ", ");
					special[3] = registradores(aux);
					special[4] = 0b00000;
				}
					
				else if (aux == "mult"){
					aux = strtok(NULL, ", ");
					special[5] = MULT;
					special[1] = registradores(aux);
					aux = strtok(NULL, ", ");
					special[2] = registradores(aux);
					aux = strtok(NULL, ", ");
					special[3] = registradores(aux);
					special[4] = 0b00000;
				}
					
				else if (aux == "nop"){
					aux = strtok(NULL, ", ");
					special[5] = NOP;
					special[1] = registradores(aux);
					aux = strtok(NULL, ", ");
					special[2] = registradores(aux);
					aux = strtok(NULL, ", ");
					special[3] = registradores(aux);
					special[4] = 0b00000;
				}
					
				else if (aux == "nor"){
					aux = strtok(NULL, ", ");
					special[5] = NOR;
					special[1] = registradores(aux);
					aux = strtok(NULL, ", ");
					special[2] = registradores(aux);
					aux = strtok(NULL, ", ");
					special[3] = registradores(aux);
					special[4] = 0b00000;
				}
					
				else if (aux == "or"){
					aux = strtok(NULL, ", ");
					special[5] = OR;
					special[1] = registradores(aux);
					aux = strtok(NULL, ", ");
					special[2] = registradores(aux);
					aux = strtok(NULL, ", ");
					special[3] = registradores(aux);
					special[4] = 0b00000;
				} 
					
				else if (aux == "sub"){
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
			else if (aux == "madd" || "msub" || "mul"){
				special[0] = 0b011100;
				if(aux == "madd"){
					special[5] = MADD;
					aux = strtok(NULL, ", ");
					special[1] = registradores(aux);
					aux = strtok(NULL, ", ");
					special[2] = registradores(aux);
					aux = strtok(NULL, ", ");
					special[3] = 0b00000;
					special[4] = 0b00000;
				}
				else if(aux == "msub"){
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
			else if (aux == "j"){
				special[0] = J;
				aux = strtok(NULL, ", ");
				special[1] = registradores(aux);
			}
			else if(aux == "bgez" || "bltz"){
				regim[0] = 0b000001;
				if (aux == "bgez"){
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
				if(aux == "addi"){
					imediato[0] = ADDI;
					aux = strtok(NULL, ", ");
					special[1] = registradores(aux);
					aux = strtok(NULL, ", ");
					special[2] = registradores(aux);
					aux = strtok(NULL, ", ");
					special[3] = registradores(aux);					
				}
				else if(aux == "andi"){
					imediato[0] = ANDI;
					aux = strtok(NULL, ", ");
					special[1] = registradores(aux);
					aux = strtok(NULL, ", ");
					special[2] = registradores(aux);
					aux = strtok(NULL, ", ");
					special[3] = registradores(aux);
				}
				else if(aux == "b"){
					imediato[0] = B;
					aux = strtok(NULL, ", ");
					special[1] = 0b00000;
					aux = strtok(NULL, ", ");
					special[2] = 0b00000;
					aux = strtok(NULL, ", ");
					special[3] = registradores(aux);
				}
				else if(aux == "beq"){
					imediato[0] = BEQ;
					aux = strtok(NULL, ", ");
					special[1] = registradores(aux);
					aux = strtok(NULL, ", ");
					special[2] = registradores(aux);
					aux = strtok(NULL, ", ");
					special[3] = registradores(aux);
				}
				else if(aux == "beql"){
					imediato[0] = BEQL;
					aux = strtok(NULL, ", ");
					special[1] = registradores(aux);
					aux = strtok(NULL, ", ");
					special[2] = registradores(aux);
					aux = strtok(NULL, ", ");
					special[3] = registradores(aux);
				}
				else if(aux == "bgtz"){
					imediato[0] = BGTZ;
					aux = strtok(NULL, ", ");
					special[1] = registradores(aux);
					aux = strtok(NULL, ", ");
					special[2] = 0b00000;
					aux = strtok(NULL, ", ");
					special[3] = registradores(aux);
				}
				else if(aux == "blez"){
					imediato[0] = BLEZ;
					aux = strtok(NULL, ", ");
					special[1] = registradores(aux);
					aux = strtok(NULL, ", ");
					special[2] = 0b00000;
					aux = strtok(NULL, ", ");
					special[3] = registradores(aux);
				}
				else if(aux == "bne"){
					imediato[0] = BNE;
					aux = strtok(NULL, ", ");
					special[1] = registradores(aux);
					aux = strtok(NULL, ", ");
					special[2] = registradores(aux);
					aux = strtok(NULL, ", ");
					special[3] = registradores(aux);
				}
				else if(aux == "lui"){
					imediato[0] = LUI;
					aux = strtok(NULL, ", ");
					special[1] = 0b00000;
					aux = strtok(NULL, ", ");
					special[2] = registradores(aux);
					aux = strtok(NULL, ", ");
					special[3] = registradores(aux);
				}
				else if(aux == "ori"){
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
			
			
			printf("teste:%s", aux);
			break;
			
		}
		
		//aux = strtok(texto, ", ");
		//printf("teste:%s", aux);
		break;

	}
return 0;
}