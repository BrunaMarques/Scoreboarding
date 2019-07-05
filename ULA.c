#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ADD 
int resultado;

void adicao(int op1, int op2){
	resultado = op1+op2;
}

void subtracao(int op1, int op2){
	resultado = op1-op2;
}

void multiplicacao(int op1, int op2){
	resultado = op1*op2;
}

void adicao(int op1, int op2){
	resultado = op1+op2;
}

void divisao(int op1, int op2){
	resultado = op1/op2;
}

void And(int op1, int op2){
	resultado = op1&op2;
}

void Or(int op1, int op2){
	resultado = op1/op2;
}

void Xor(int op1, int op2){
	resultado = op1/op2;
}

void LUI(int op1){
	resultado = op1 << 16;
}

void MADD(op1, op2){
	multiplicacao(op1,op2);
	
}

int ULA(int op1, int op2, int identificador){
switch (identificador){
	case ADD:
	case ADDI: 
		adicao(op1,op2);
	break;
	case SUB:
		subtracao(op1,op2);
	case MUL:
		multiplicacao(op1,op2);
	case DIV:
		divisao(op1,op2);
	case AND:
	case ANDI:
		And(op1,op2);
	case OR:
	case ORI:
		Or(op1,op2);
	case XOR:
	case XORI: 
		Xor(op1,op2);
default:
	break;
}