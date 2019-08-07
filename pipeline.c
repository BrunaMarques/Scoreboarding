#include <stdio.h>
#include <stdlib.h>
#include "pipeline.h"
#include "barramento.h"
#include "un_func.h"
#include "lista.h"

void buscaPipeline()
{
	if (filaVazia())
	{
		for (int i = 0; i < 4; i++)
		{
			unsigned int instMem[4];
			buscaMemoria(instMem);

			Inst instDecode = decodificacao(instMem);
			inserirElementoFila(instDecode);
			PC += 4;
		}
	}

	if (EMITIDA)
	{
		if (BI.tem_instrucao == false)
		{
			escrita_bar(excluirElementoFila(), barBI);
		}
	}
}
void emissao()
{
	if (EMITIDA)
	{
		if (BI.tem_instrucao == true)
		{
			EMITIDA = false;
			Inst in = leitura_bar(barBI);

			int operacao = descobrirOperacao(in);
			switch (operacao)
			{
			case ADD:
				if (!UF_ADD.status.Busy)
				{
				}
				break;
			case AND:
				break;
			case DIV:
				break;
			case JR:
				break;
			case MFHI:
				break;
			case MFLO:
				break;
			case MOVN:
				break;
			case MOVZ:
				break;
			case MTHI:
				break;
			case MTLO:
				break;
			case MULT:
				break;
			case NOP:
				break;
			case NOR:
				break;
			case OR:
				break;
			case SUB:
				break;
			case XOR:
				break;
			case MADD:
				break;
			case MSUB:
				break;
			case MUL:
				break;
			case ADDI:
				break;
			case ANDI:
				break;
			case B:
				break;
			case BEQ:
				break;
			case BEQL:
				break;
			case BGTZ:
				break;
			case BLEZ:
				break;
			case BNE:
				break;
			case LUI:
				break;
			case ORI:
				break;
			case XORI:
				break;
			case J:
				break;
			case BGEZ:
				break;
			case BLTZ:
				break;
			default:
				printf("Operação não listada!");
				break;
			}
		}
	}
}

void leitura()
{
	//return in. //buscar operando dependendo do tipo de instrução
}

int execucao()
//etapa de execução
{
	int operacao = descobrirOperacao(in);
	int registrador;
	switch (operacao)
	{
	case ADD:
		bufferRegistradores[in.s_instrucao.rd].valor = adicao(bancoRegistradores[in.s_instrucao.rs].valor, bancoRegistradores[in.s_instrucao.rt].valor);
		return in.s_instrucao.rd;
		break;
	case AND:
		bufferRegistradores[in.s_instrucao.rd].valor = and(bancoRegistradores[in.s_instrucao.rs].valor, bancoRegistradores[in.s_instrucao.rt].valor);
		break;
	case DIV:
		separarHILO(divisao(bancoRegistradores[in.s_instrucao.rs].valor, bancoRegistradores[in.s_instrucao.rt].valor));
		return HI;
		break;
	case JR:
		PC = bancoRegistradores[in.s_instrucao.rs].valor;
		return in.s_instrucao.rd;
	case MFHI:
		bufferRegistradores[in.s_instrucao.rd].valor = bancoRegistradores[HI].valor;
		return in.s_instrucao.rd;
		break;
	case MFLO:
		bufferRegistradores[in.s_instrucao.rd].valor = bancoRegistradores[LO].valor;
		return in.s_instrucao.rd;
		break;
	case MOVN:
		if (not(igual(bancoRegistradores[in.s_instrucao.rt].valor, 0)))
			bufferRegistradores[in.s_instrucao.rd].valor = bancoRegistradores[in.s_instrucao.rs].valor;
		return in.s_instrucao.rd;
		break;
	case MOVZ:
		if (igual(bancoRegistradores[in.s_instrucao.rt].valor, 0))
			bufferRegistradores[in.s_instrucao.rd].valor = bancoRegistradores[in.s_instrucao.rs].valor;
		return in.s_instrucao.rd;
		break;
	case MTHI:
		bufferRegistradores[HI].valor = bancoRegistradores[in.s_instrucao.rs].valor;
		return HI;
		break;
	case MTLO:
		bufferRegistradores[LO].valor = bancoRegistradores[in.s_instrucao.rs].valor;
		return LO;
		break;
	case MULT:
		separarHILO(multiplicacao(bancoRegistradores[in.s_instrucao.rs].valor, bancoRegistradores[in.s_instrucao.rt].valor));
		return HI;
		break;
	case NOP:
		// nao faz nada por enquanto (no operation)//
		break;
	case NOR:
		bufferRegistradores[in.s_instrucao.rd].valor = nor(bancoRegistradores[in.s_instrucao.rs].valor, bancoRegistradores[in.s_instrucao.rt].valor);
		return in.s_instrucao.rd;
		break;
	case OR:
		bufferRegistradores[in.s_instrucao.rd].valor = or (bancoRegistradores[in.s_instrucao.rs].valor, bancoRegistradores[in.s_instrucao.rt].valor);
		return in.s_instrucao.rd;
		break;
	case SUB:
		bufferRegistradores[in.s_instrucao.rd].valor = subtracao(bancoRegistradores[in.s_instrucao.rs].valor, bancoRegistradores[in.s_instrucao.rt].valor);
		return in.s_instrucao.rd;
		break;
	case XOR:
		bufferRegistradores[in.s_instrucao.rd].valor = xor(bancoRegistradores[in.s_instrucao.rs].valor, bancoRegistradores[in.s_instrucao.rt].valor);
		return in.s_instrucao.rd;
		break;
	case MADD:
		bufferResultado.valor = multiplicacao(bancoRegistradores[in.s_instrucao.rs].valor, bancoRegistradores[in.s_instrucao.rt].valor);
		bufferResultado.valor = adicao(bufferResultado.valor, juntarHILO(bancoRegistradores[HI].valor, bancoRegistradores[LO].valor));
		break; //arrumar
	case MSUB:
		bufferResultado.valor = multiplicacao(bancoRegistradores[in.s_instrucao.rs].valor, bancoRegistradores[in.s_instrucao.rt].valor);
		bufferResultado.valor = subtracao(bufferResultado.valor, juntarHILO(bancoRegistradores[HI].valor, bancoRegistradores[LO].valor));
		break; //arrumar
	case MUL:
		bufferRegistradores[in.s_instrucao.rd].valor = multiplicacao(bancoRegistradores[in.s_instrucao.rs].valor, bancoRegistradores[in.s_instrucao.rt].valor);
		return in.s_instrucao.rd;
		break;
	case ADDI:
		bufferRegistradores[in.s_instrucao.rt].valor = adicao(bancoRegistradores[in.s_instrucao.rs].valor, in.i_instrucao.imediato);
		return in.s_instrucao.rt;
		break;
	case ANDI:
		bufferRegistradores[in.s_instrucao.rt].valor = and(bancoRegistradores[in.s_instrucao.rs].valor, in.i_instrucao.imediato);
		return in.s_instrucao.rt;
		break;
	case B:
		PC += in.i_instrucao.imediato;
		break;
	case BEQ:
		if (igual(bancoRegistradores[in.s_instrucao.rs].valor, bancoRegistradores[in.s_instrucao.rt].valor))
			PC += in.i_instrucao.imediato;
		break;
	case BEQL:
		if (igual(bancoRegistradores[in.s_instrucao.rs].valor, bancoRegistradores[in.s_instrucao.rt].valor))
			PC += in.i_instrucao.imediato;
		break;
	case BGTZ:
		if (maior(bancoRegistradores[in.s_instrucao.rs].valor, 0))
			PC += in.i_instrucao.imediato;
		break;
	case BLEZ:
		if (menorIgual(bancoRegistradores[in.s_instrucao.rs].valor, 0))
			PC += in.i_instrucao.imediato;
		break;
	case BNE:
		if (not(igual(bancoRegistradores[in.s_instrucao.rs].valor, bancoRegistradores[in.s_instrucao.rt].valor)))
			PC += in.i_instrucao.imediato;
		break;
	case LUI:
		bufferRegistradores[in.s_instrucao.rt].valor = shiftLeft(in.i_instrucao.imediato, 16);
		return in.s_instrucao.rt;
		break;
	case ORI:
		bufferRegistradores[in.s_instrucao.rt].valor = or (bancoRegistradores[in.s_instrucao.rs].valor, in.i_instrucao.imediato);
		return in.s_instrucao.rt;
		break;
	case XORI:
		bufferRegistradores[in.s_instrucao.rt].valor = xor(bancoRegistradores[in.s_instrucao.rs].valor, in.i_instrucao.imediato);
		return in.s_instrucao.rt;
		break;
	case J:
		PC = in.j_instrucao.addr;
		break;
	case BGEZ:
		if (maiorIgual(bancoRegistradores[in.s_instrucao.rs].valor, 0))
			PC += in.r_instrucao.offset;
		break;
	case BLTZ:
		if (menor(bancoRegistradores[in.s_instrucao.rs].valor, 0))
			PC += in.r_instrucao.offset;
		break;
	default:
		printf("Operação não listada!");
		break;
	}
}

void escritaPipeline(int reg)
{
	bancoRegistradores[reg].valor = bufferRegistradores[reg].valor;
	bufferRegistradores[reg].valor = infinito;
}

void verifica_regEscrita(int reg)
{
	for (int i = 0; i < listaIssue.nroElem; i++)
	{
		if (listaIssue.lista_inst[i])
	}
}