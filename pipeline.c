#include <stdio.h>
#include <stdlib.h>
#include "pipeline.h"
#include "barramento.h"

void buscaPipeline()
{
	if (filaVazia())
	{
		for (int i = 0; i < 4; i++)
		{
			unsigned int instMem[4];
			buscaMemoria(instMem);

			Inst instDecode = decodificacao(instMem);
			inserirElementoFila(instDecode); // não sei como passa esse ponteiro
			PC += 4;
		}
	}

	if (EMITIDA)
	{
		if (BI.tem_instrucao == false)
		{
			escrita_bar(excluirElementoFila(), barBI);
		}
		if (IR.tem_instrucao == false)
		{
			escrita_bar(excluirElementoFila(), barIR);
		}
		for (int i = 0; i < 5; i++)
		{
			if (RE[i].tem_instrucao == false)
			{
				escrita_bar(excluirElementoFila(), barRE);
			}
		}

		for (int i = 0; i < 5; i++)
		{
			if (EW[i].tem_instrucao == false)
			{
				escrita_bar(excluirElementoFila(), barEW);
			}
		}
	}
}
void emissao() //fazer pra todos
{
	if (EMITIDA)
	{
		if (BI.tem_instrucao == true)
		{
			EMITIDA = false;
			Inst in = leitura_bar(barBI);
		}
	}
}

void leitura(){
	if(verifica_bar(IR))
		IR.instrucao.posicao = inserirEelemLista(listaRead,IR.instrucao);
	for(int i = 0; i < listaRead.nroElem; i++){
		
	} 
	//return in. //buscar operando dependendo do tipo de instrução
}

Inst execucao()
//etapa de execução
{
	int operacao = descobrirOperacao(in);
	int registrador;
	switch (operacao)
	{
	case ADD:
		bufferRegistradores[in.s_instrucao.rd] = adicao(bancoRegistradores[in.s_instrucao.rs], bancoRegistradores[in.s_instrucao.rt]);
		return in.s_instrucao.rd;
		break;
	case AND:
		bufferRegistradores[in.s_instrucao.rd] = and(bancoRegistradores[in.s_instrucao.rs], bancoRegistradores[in.s_instrucao.rt]);
		break;
	case DIV:
		separarHILO(divisao(bancoRegistradores[in.s_instrucao.rs], bancoRegistradores[in.s_instrucao.rt]));
		return HI;
		break;
	case JR:
		PC = bancoRegistradores[in.s_instrucao.rs];
		return in.s_instrucao.rd;
	case MFHI:
		bufferRegistradores[in.s_instrucao.rd] = bancoRegistradores[HI];
		return in.s_instrucao.rd;
		break;
	case MFLO:
		bufferRegistradores[in.s_instrucao.rd] = bancoRegistradores[LO];
		return in.s_instrucao.rd;
		break;
	case MOVN:
		if (not(igual(bancoRegistradores[in.s_instrucao.rt], 0)))
			bufferRegistradores[in.s_instrucao.rd] = bancoRegistradores[in.s_instrucao.rs];
		return in.s_instrucao.rd;
		break;
	case MOVZ:
		if (igual(bancoRegistradores[in.s_instrucao.rt], 0))
			bufferRegistradores[in.s_instrucao.rd] = bancoRegistradores[in.s_instrucao.rs];
		return in.s_instrucao.rd;
		break;
	case MTHI:
		bufferRegistradores[HI] = bancoRegistradores[in.s_instrucao.rs];
		return HI;
		break;
	case MTLO:
		bufferRegistradores[LO] = bancoRegistradores[in.s_instrucao.rs];
		return LO;
		break;
	case MULT:
		separarHILO(multiplicacao(bancoRegistradores[in.s_instrucao.rs], bancoRegistradores[in.s_instrucao.rt]));
		return HI;
		break;
	case NOP:
		// nao faz nada por enquanto (no operation)//
		break;
	case NOR:
		bufferRegistradores[in.s_instrucao.rd] = nor(bancoRegistradores[in.s_instrucao.rs], bancoRegistradores[in.s_instrucao.rt]);
		return in.s_instrucao.rd;
		break;
	case OR:
		bufferRegistradores[in.s_instrucao.rd] = or (bancoRegistradores[in.s_instrucao.rs], bancoRegistradores[in.s_instrucao.rt]);
		return in.s_instrucao.rd;
		break;
	case SUB:
		bufferRegistradores[in.s_instrucao.rd] = subtracao(bancoRegistradores[in.s_instrucao.rs], bancoRegistradores[in.s_instrucao.rt]);
		return in.s_instrucao.rd;
		break;
	case XOR:
		bufferRegistradores[in.s_instrucao.rd] = xor(bancoRegistradores[in.s_instrucao.rs], bancoRegistradores[in.s_instrucao.rt]);
		return in.s_instrucao.rd;
		break;
	case MADD:
		bufferResultado = multiplicacao(bancoRegistradores[in.s_instrucao.rs], bancoRegistradores[in.s_instrucao.rt]);
		bufferResultado = adicao(bufferResultado, juntarHILO(bancoRegistradores[HI], bancoRegistradores[LO]));
		break; //arrumar
	case MSUB:
		bufferResultado = multiplicacao(bancoRegistradores[in.s_instrucao.rs], bancoRegistradores[in.s_instrucao.rt]);
		bufferResultado = subtracao(bufferResultado, juntarHILO(bancoRegistradores[HI], bancoRegistradores[LO]));
		break; //arrumar
	case MUL:
		bufferRegistradores[in.s_instrucao.rd] = multiplicacao(bancoRegistradores[in.s_instrucao.rs], bancoRegistradores[in.s_instrucao.rt]);
		return in.s_instrucao.rd;
		break;
	case ADDI:
		bufferRegistradores[in.s_instrucao.rt] = adicao(bancoRegistradores[in.s_instrucao.rs], in.i_instrucao.imediato);
		return in.s_instrucao.rt;
		break;
	case ANDI:
		bufferRegistradores[in.s_instrucao.rt] = and(bancoRegistradores[in.s_instrucao.rs], in.i_instrucao.imediato);
		return in.s_instrucao.rt;
		break;
	case B:
		PC += in.i_instrucao.imediato;
		break;
	case BEQ:
		if (igual(bancoRegistradores[in.s_instrucao.rs], bancoRegistradores[in.s_instrucao.rt]))
			PC += in.i_instrucao.imediato;
		break;
	case BEQL:
		if (igual(bancoRegistradores[in.s_instrucao.rs], bancoRegistradores[in.s_instrucao.rt]))
			PC += in.i_instrucao.imediato;
		break;
	case BGTZ:
		if (maior(bancoRegistradores[in.s_instrucao.rs], 0))
			PC += in.i_instrucao.imediato;
		break;
	case BLEZ:
		if (menorIgual(bancoRegistradores[in.s_instrucao.rs], 0))
			PC += in.i_instrucao.imediato;
		break;
	case BNE:
		if (not(igual(bancoRegistradores[in.s_instrucao.rs], bancoRegistradores[in.s_instrucao.rt])))
			PC += in.i_instrucao.imediato;
		break;
	case LUI:
		bufferRegistradores[in.s_instrucao.rt] = shiftLeft(in.i_instrucao.imediato, 16);
		return in.s_instrucao.rt;
		break;
	case ORI:
		bufferRegistradores[in.s_instrucao.rt] = or (bancoRegistradores[in.s_instrucao.rs], in.i_instrucao.imediato);
		return in.s_instrucao.rt;
		break;
	case XORI:
		bufferRegistradores[in.s_instrucao.rt] = xor(bancoRegistradores[in.s_instrucao.rs], in.i_instrucao.imediato);
		return in.s_instrucao.rt;
		break;
	case J:
		PC = in.j_instrucao.addr;
		break;
	case BGEZ:
		if (maiorIgual(bancoRegistradores[in.s_instrucao.rs], 0))
			PC += in.r_instrucao.offset;
		break;
	case BLTZ:
		if (menor(bancoRegistradores[in.s_instrucao.rs], 0))
			PC += in.r_instrucao.offset;
		break;
	default:
		printf("Operação não listada!");
		break;
	}
}

void escritaPipeline(int reg)
{
	bancoRegistradores[reg] = bufferRegistradores[reg];
	bufferRegistradores[reg] = infinito;
}