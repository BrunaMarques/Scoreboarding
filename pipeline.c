#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pipeline.h"
#include "barramento.h"
#include "un_func.h"
#include "lista.h"
#include "ula.h"
#include "fila.h"

int EMITIDA = true;

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
			BI.instrucao.posicao = inserirElemLista(listaRead, BI.instrucao);
		}
	}
	if (!EMITIDA)
	{
		Inst in;
		in = listaIssue->lista_inst[0];
		int operacao = descobrirOperacao(in);
		switch (operacao)
		{
		case ADD:
			if (!UFADD.status.Busy)
			{
				if (bancoRegistradores[in.s_instrucao.rd].UF == semUF)
				{
					UFADD.status.Busy = true;
					UFADD.status.Op = ADD;
					UFADD.status.Fi = in.s_instrucao.rd;
					UFADD.status.Fj = in.s_instrucao.rs;
					UFADD.status.Fk = in.s_instrucao.rt;
					UFADD.status.Qj = bancoRegistradores[in.s_instrucao.rs].UF;
					UFADD.status.Qk = bancoRegistradores[in.s_instrucao.rt].UF;
					UFADD.status.Rj = (bancoRegistradores[in.s_instrucao.rs].UF == semUF) ? true : false;
					UFADD.status.Rk = (bancoRegistradores[in.s_instrucao.rt].UF == semUF) ? true : false;
					bancoRegistradores[in.s_instrucao.rd].UF = UF_ADD;
					in.UF = UF_ADD;
					escrita_bar(in, barIR);
					excluirElem(listaIssue, 0);
					EMITIDA = true;
				}
			}
			break;
		case AND:
			if (!UFINT.status.Busy)
			{
				if (bancoRegistradores[in.s_instrucao.rd].UF == semUF)
				{
					UFINT.status.Busy = true;
					UFINT.status.Op = AND;
					UFINT.status.Fi = in.s_instrucao.rd;
					UFINT.status.Fj = in.s_instrucao.rs;
					UFINT.status.Fk = in.s_instrucao.rt;
					UFINT.status.Qj = bancoRegistradores[in.s_instrucao.rs].UF;
					UFINT.status.Qk = bancoRegistradores[in.s_instrucao.rt].UF;
					UFINT.status.Rj = (bancoRegistradores[in.s_instrucao.rs].UF == semUF) ? true : false;
					UFINT.status.Rk = (bancoRegistradores[in.s_instrucao.rt].UF == semUF) ? true : false;
					bancoRegistradores[in.s_instrucao.rd].UF = UF_ADD;
					in.UF = UF_INT;
					escrita_bar(in, barIR);
					excluirElem(listaIssue, 0);
					EMITIDA = true;
				}
			}
			break;
		case DIV:
			if (!UFDIV.status.Busy)
			{
				if (bancoRegistradores[in.s_instrucao.rd].UF == semUF)
				{
					UFDIV.status.Busy = true;
					UFDIV.status.Op = DIV;
					UFDIV.status.Fi = bancoRegistradores[HI];
					UFDIV.status.Fj = in.s_instrucao.rs;
					UFDIV.status.Fk = in.s_instrucao.rt;
					UFDIV.status.Qj = bancoRegistradores[in.s_instrucao.rs].UF;
					UFDIV.status.Qk = bancoRegistradores[in.s_instrucao.rt].UF;
					UFDIV.status.Rj = (bancoRegistradores[in.s_instrucao.rs].UF == semUF) ? true : false;
					UFDIV.status.Rk = (bancoRegistradores[in.s_instrucao.rt].UF == semUF) ? true : false;
					bancoRegistradores[HI].UF = UF_DIV;
					bancoRegistradores[LO].UF = UF_DIV;
					in.UF = UF_DIV;
					escrita_bar(in, barIR);
					excluirElem(listaIssue, 0);
					EMITIDA = true;
				}
			}
			break;
		case JR:
			if (!UFINT.status.Busy)
			{

				UFINT.status.Busy = true;
				UFINT.status.Op = JR;
				UFINT.status.Fi = semREG;
				UFINT.status.Fj = in.s_instrucao.rs;
				UFINT.status.Fk = semREG;
				UFINT.status.Qj = bancoRegistradores[in.s_instrucao.rs].UF;
				UFINT.status.Qk = semUF;
				UFINT.status.Rj = (bancoRegistradores[in.s_instrucao.rs].UF == semUF) ? true : false;
				UFINT.status.Rk = semUF;
				in.UF = UF_INT;
				escrita_bar(in, barIR);
				excluirElem(listaIssue, 0);
				EMITIDA = true;
			}
			break;
		case MFHI:
			if (!UFINT.status.Busy)
			{
				if (bancoRegistradores[in.s_instrucao.rd].UF == semUF)
				{
					UFINT.status.Busy = true;
					UFINT.status.Op = MFHI;
					UFINT.status.Fi = in.s_instrucao.rd;
					UFINT.status.Fj = semUF;
					UFINT.status.Fk = semUF;
					UFINT.status.Qj = semUF;
					UFINT.status.Qk = semUF;
					UFINT.status.Rj = (bancoRegistradores[in.s_instrucao.rs].UF == semUF) ? true : false;
					UFINT.status.Rk = (bancoRegistradores[in.s_instrucao.rt].UF == semUF) ? true : false;
					bancoRegistradores[in.s_instrucao.rd].UF = UF_INT;
					in.UF = UF_INT;
					escrita_bar(in, barIR);
					excluirElem(listaIssue, 0);
					EMITIDA = true;
				}
			}
			break;
		case MFLO:
			if (!UFINT.status.Busy)
			{
				if (bancoRegistradores[in.s_instrucao.rd].UF == semUF)
				{
					UFINT.status.Busy = true;
					UFINT.status.Op = MFLO;
					UFINT.status.Fi = in.s_instrucao.rd;
					UFINT.status.Fj = semUF;
					UFINT.status.Fk = semUF;
					UFINT.status.Qj = semUF;
					UFINT.status.Qk = semUF;
					UFINT.status.Rj = (bancoRegistradores[in.s_instrucao.rs].UF == semUF) ? true : false;
					UFINT.status.Rk = (bancoRegistradores[in.s_instrucao.rt].UF == semUF) ? true : false;
					bancoRegistradores[in.s_instrucao.rd].UF = UF_INT;
					in.UF = UF_INT;
					escrita_bar(in, barIR);
					excluirElem(listaIssue, 0);
					EMITIDA = true;
				}
			}
			break;
<<<<<<< HEAD
=======
		case MFLO:
			// rd e hi
			break;
>>>>>>> f2b413a4adcf6256af545fa8d4960d2b58fc63a6
		case MOVN:
			if (!UFINT.status.Busy)
			{
				if (bancoRegistradores[in.s_instrucao.rd].UF == semUF)
				{
					UFINT.status.Busy = true;
					UFINT.status.Op = MOVN;
					UFINT.status.Fi = in.s_instrucao.rd;
					UFINT.status.Fj = in.s_instrucao.rs;
					UFINT.status.Fk = in.s_instrucao.rt;
					UFINT.status.Qj = bancoRegistradores[in.s_instrucao.rs].UF;
					UFINT.status.Qk = bancoRegistradores[in.s_instrucao.rt].UF;
					UFINT.status.Rj = (bancoRegistradores[in.s_instrucao.rs].UF == semUF) ? true : false;
					UFINT.status.Rk = (bancoRegistradores[in.s_instrucao.rt].UF == semUF) ? true : false;
					bancoRegistradores[in.s_instrucao.rd].UF = UF_INT;
					in.UF = UF_INT;
					escrita_bar(in, barIR);
					excluirElem(listaIssue, 0);
					EMITIDA = true;
				}
			}
			break;
		case MOVZ:
			if (!UFINT.status.Busy)
			{
				if (bancoRegistradores[in.s_instrucao.rd].UF == semUF)
				{
					UFINT.status.Busy = true;
					UFINT.status.Op = MOVZ;
					UFINT.status.Fi = in.s_instrucao.rd;
					UFINT.status.Fj = in.s_instrucao.rs;
					UFINT.status.Fk = in.s_instrucao.rt;
					UFINT.status.Qj = bancoRegistradores[in.s_instrucao.rs].UF;
					UFINT.status.Qk = bancoRegistradores[in.s_instrucao.rt].UF;
					UFINT.status.Rj = (bancoRegistradores[in.s_instrucao.rs].UF == semUF) ? true : false;
					UFINT.status.Rk = (bancoRegistradores[in.s_instrucao.rt].UF == semUF) ? true : false;
					bancoRegistradores[in.s_instrucao.rd].UF = UF_INT;
					in.UF = UF_INT;
					escrita_bar(in, barIR);
					excluirElem(listaIssue, 0);
					EMITIDA = true;
				}
			}
			break;
		case MTHI:
		{
			if (bancoRegistradores[in.s_instrucao.rd].UF == semUF)
			{
				UFINT.status.Busy = true;
				UFINT.status.Op = MTHI;
				UFINT.status.Fi = semUF;
				UFINT.status.Fj = in.s_instrucao.rs;
				UFINT.status.Fk = semUF;
				UFINT.status.Qj = bancoRegistradores[in.s_instrucao.rs].UF;
				UFINT.status.Qk = semUF;
				UFINT.status.Rj = (bancoRegistradores[in.s_instrucao.rs].UF == semUF) ? true : false;
				UFINT.status.Rk = semUF;
				bancoRegistradores[in.s_instrucao.rs].UF = UF_INT;
				in.UF = UF_INT;
				escrita_bar(in, barIR);
				excluirElem(listaIssue, 0);
				EMITIDA = true;
			}
		}
		break;
		case MTLO:
			if (!UF_INT.status.Busy)
			{
				if (bancoRegistradores[in.s_instrucao.rd].UF == semUF)
				{
					UFINT.status.Busy = true;
					UFINT.status.Op = MTLO;
					UFINT.status.Fi = semUF;
					UFINT.status.Fj = in.s_instrucao.rs;
					UFINT.status.Fk = semUF;
					UFINT.status.Qj = bancoRegistradores[in.s_instrucao.rs].UF;
					UFINT.status.Qk = semUF;
					UFINT.status.Rj = (bancoRegistradores[in.s_instrucao.rs].UF == semUF) ? true : false;
					UFINT.status.Rk = semUF;
					bancoRegistradores[in.s_instrucao.rs].UF = UF_INT;
					in.UF = UF_INT;
					escrita_bar(in, barIR);
					excluirElem(listaIssue, 0);
					EMITIDA = true;
				}
			}
			break;
		case MULT: //como sei se vai na mul 1 ou 2? tenho que fazer um if?
			if (!UFMUL1.status.Busy)
			{
				if (bancoRegistradores[in.s_instrucao.rd].UF == semUF)
				{
					UFMUL1.status.Busy = true;
					UFMUL1.status.Op = MUL;
					UFMUL1.status.Fi = semUF;
					UFMUL1.status.Fj = in.s_instrucao.rs;
					UFMUL1.status.Fk = in.s_instrucao.rt;
					UFMUL1.status.Qj = bancoRegistradores[in.s_instrucao.rs].UF;
					UFMUL1.status.Qk = bancoRegistradores[in.s_instrucao.rt].UF;
					UFMUL1.status.Rj = (bancoRegistradores[in.s_instrucao.rs].UF == semUF) ? true : false;
					UFMUL1.status.Rk = (bancoRegistradores[in.s_instrucao.rt].UF == semUF) ? true : false;
					bancoRegistradores[in.s_instrucao.rd].UF = UF_MUL1;
					in.UF = UF_MUL1;
					escrita_bar(in, barIR);
					excluirElem(listaIssue, 0);
					EMITIDA = true;
				}
			}
			break;
		case NOP:
			if (!UF_INT.status.Busy)
			{
				if (bancoRegistradores[in.s_instrucao.rd].UF == semUF)
				{
					UFINT.status.Fi = in.s_instrucao.rd;
					UFINT.status.Fj = in.s_instrucao.rs;
					UFINT.status.Fk = in.s_instrucao.rt;
					UFINT.status.Qj = bancoRegistradores[in.s_instrucao.rs].UF;
					UFINT.status.Qk = bancoRegistradores[in.s_instrucao.rt].UF;
					UFINT.status.Rj = (bancoRegistradores[in.s_instrucao.rs].UF == semUF) ? true : false;
					UFINT.status.Rk = (bancoRegistradores[in.s_instrucao.rt].UF == semUF) ? true : false;
					bancoRegistradores[in.s_instrucao.rd].UF = UF_INT;
					in.UF = UF_INT;
					escrita_bar(in, barIR);
					excluirElem(listaIssue, 0);
					EMITIDA = true;
				}
			}
			break;
		case NOR:
			if (!UFINT.status.Busy)
			{
				if (bancoRegistradores[in.s_instrucao.rd].UF == semUF)
				{
					UFINT.status.Busy = true;
					UFINT.status.Op = NOR;
					UFINT.status.Fi = in.s_instrucao.rd;
					UFINT.status.Fj = in.s_instrucao.rs;
					UFINT.status.Fk = in.s_instrucao.rt;
					UFINT.status.Qj = bancoRegistradores[in.s_instrucao.rs].UF;
					UFINT.status.Qk = bancoRegistradores[in.s_instrucao.rt].UF;
					UFINT.status.Rj = (bancoRegistradores[in.s_instrucao.rs].UF == semUF) ? true : false;
					UFINT.status.Rk = (bancoRegistradores[in.s_instrucao.rt].UF == semUF) ? true : false;
					bancoRegistradores[in.s_instrucao.rd].UF = UF_INT;
					in.UF = UF_INT;
					escrita_bar(in, barIR);
					excluirElem(listaIssue, 0);
					EMITIDA = true;
				}
			}
		case OR:
			if (!UFINT.status.Busy)
			{
				if (bancoRegistradores[in.s_instrucao.rd].UF == semUF)
				{
					UFINT.status.Busy = true;
					UFINT.status.Op = OR;
					UFINT.status.Fi = in.s_instrucao.rd;
					UFINT.status.Fj = in.s_instrucao.rs;
					UFINT.status.Fk = in.s_instrucao.rt;
					UFINT.status.Qj = bancoRegistradores[in.s_instrucao.rs].UF;
					UFINT.status.Qk = bancoRegistradores[in.s_instrucao.rt].UF;
					UFINT.status.Rj = (bancoRegistradores[in.s_instrucao.rs].UF == semUF) ? true : false;
					UFINT.status.Rk = (bancoRegistradores[in.s_instrucao.rt].UF == semUF) ? true : false;
					bancoRegistradores[in.s_instrucao.rd].UF = UF_INT;
					in.UF = UF_INT;
					escrita_bar(in, barIR);
					excluirElem(listaIssue, 0);
					EMITIDA = true;
				}
			}
			break;
		case SUB:
			if (!UFINT.status.Busy)
			{
				if (bancoRegistradores[in.s_instrucao.rd].UF == semUF)
				{
					UFINT.status.Busy = true;
					UFINT.status.Op = SUB;
					UFINT.status.Fi = in.s_instrucao.rd;
					UFINT.status.Fj = in.s_instrucao.rs;
					UFINT.status.Fk = in.s_instrucao.rt;
					UFINT.status.Qj = bancoRegistradores[in.s_instrucao.rs].UF;
					UFINT.status.Qk = bancoRegistradores[in.s_instrucao.rt].UF;
					UFINT.status.Rj = (bancoRegistradores[in.s_instrucao.rs].UF == semUF) ? true : false;
					UFINT.status.Rk = (bancoRegistradores[in.s_instrucao.rt].UF == semUF) ? true : false;
					bancoRegistradores[in.s_instrucao.rd].UF = UF_INT;
					in.UF = UF_INT;
					escrita_bar(in, barIR);
					excluirElem(listaIssue, 0);
					EMITIDA = true;
				}
			}
			break;
		case XOR:
			if (!UFINT.status.Busy)
			{
				if (bancoRegistradores[in.s_instrucao.rd].UF == semUF)
				{
					UFINT.status.Busy = true;
					UFINT.status.Op = XOR;
					UFINT.status.Fi = in.s_instrucao.rd;
					UFINT.status.Fj = in.s_instrucao.rs;
					UFINT.status.Fk = in.s_instrucao.rt;
					UFINT.status.Qj = bancoRegistradores[in.s_instrucao.rs].UF;
					UFINT.status.Qk = bancoRegistradores[in.s_instrucao.rt].UF;
					UFINT.status.Rj = (bancoRegistradores[in.s_instrucao.rs].UF == semUF) ? true : false;
					UFINT.status.Rk = (bancoRegistradores[in.s_instrucao.rt].UF == semUF) ? true : false;
					bancoRegistradores[in.s_instrucao.rd].UF = UF_INT;
					in.UF = UF_INT;
					escrita_bar(in, barIR);
					excluirElem(listaIssue, 0);
					EMITIDA = true;
				}
			}
			break;
		case MADD:
			if (!UFINT.status.Busy)
			{
				if (bancoRegistradores[in.s_instrucao.rd].UF == semUF)
				{
					UFINT.status.Busy = true;
					UFINT.status.Op = MADD;
					UFINT.status.Fi = semUF;
					UFINT.status.Fj = in.s_instrucao.rs;
					UFINT.status.Fk = in.s_instrucao.rt;
					UFINT.status.Qj = bancoRegistradores[in.s_instrucao.rs].UF;
					UFINT.status.Qk = bancoRegistradores[in.s_instrucao.rt].UF;
					UFINT.status.Rj = (bancoRegistradores[in.s_instrucao.rs].UF == semUF) ? true : false;
					UFINT.status.Rk = (bancoRegistradores[in.s_instrucao.rt].UF == semUF) ? true : false;
					bancoRegistradores[in.s_instrucao.rd].UF = UF_INT;
					in.UF = UF_INT;
					escrita_bar(in, barIR);
					excluirElem(listaIssue, 0);
					EMITIDA = true;
				}
			}
			break;
		case MSUB:
			if (!UFINT.status.Busy)
			{
				if (bancoRegistradores[in.s_instrucao.rd].UF == semUF)
				{
					UFINT.status.Busy = true;
					UFINT.status.Op = MSUB;
					UFINT.status.Fi = semUF;
					UFINT.status.Fj = in.s_instrucao.rs;
					UFINT.status.Fk = in.s_instrucao.rt;
					UFINT.status.Qj = bancoRegistradores[in.s_instrucao.rs].UF;
					UFINT.status.Qk = bancoRegistradores[in.s_instrucao.rt].UF;
					UFINT.status.Rj = (bancoRegistradores[in.s_instrucao.rs].UF == semUF) ? true : false;
					UFINT.status.Rk = (bancoRegistradores[in.s_instrucao.rt].UF == semUF) ? true : false;
					bancoRegistradores[in.s_instrucao.rd].UF = UF_INT;
					in.UF = UF_INT;
					escrita_bar(in, barIR);
					excluirElem(listaIssue, 0);
					EMITIDA = true;
				}
			}
			break;
		case MUL:
			if (!UFMUL1.status.Busy)
			{
				if (bancoRegistradores[in.s_instrucao.rd].UF == semUF)
				{
					UFMUL1.status.Busy = true;
					UFMUL1.status.Op = MUL;
					UFMUL1.status.Fi = in.s_instrucao.rd;
					UFMUL1.status.Fj = in.s_instrucao.rs;
					UFMUL1.status.Fk = in.s_instrucao.rt;
					UFMUL1.status.Qj = bancoRegistradores[in.s_instrucao.rs].UF;
					UFMUL1.status.Qk = bancoRegistradores[in.s_instrucao.rt].UF;
					UFMUL1.status.Rj = (bancoRegistradores[in.s_instrucao.rs].UF == semUF) ? true : false;
					UFMUL1.status.Rk = (bancoRegistradores[in.s_instrucao.rt].UF == semUF) ? true : false;
					bancoRegistradores[in.s_instrucao.rd].UF = UF_MUL1;
					in.UF = UF_MUL1;
					escrita_bar(in, barIR);
					excluirElem(listaIssue, 0);
					EMITIDA = true;
				}
			}
			else if (!UFMUL2.status.Busy)
			{
				if (bancoRegistradores[in.s_instrucao.rd].UF == semUF)
				{
					UFMUL2.status.Busy = true;
					UFMUL2.status.Op = MUL;
					UFMUL2.status.Fi = in.s_instrucao.rd;
					UFMUL2.status.Fj = in.s_instrucao.rs;
					UFMUL2.status.Fk = in.s_instrucao.rt;
					UFMUL2.status.Qj = bancoRegistradores[in.s_instrucao.rs].UF;
					UFMUL2.status.Qk = bancoRegistradores[in.s_instrucao.rt].UF;
					UFMUL2.status.Rj = (bancoRegistradores[in.s_instrucao.rs].UF == semUF) ? true : false;
					UFMUL2.status.Rk = (bancoRegistradores[in.s_instrucao.rt].UF == semUF) ? true : false;
					bancoRegistradores[in.s_instrucao.rd].UF = UF_MUL2;
					in.UF = UF_MUL2;
					escrita_bar(in, barIR);
					excluirElem(listaIssue, 0);
					EMITIDA = true;
				}
			}
			break;
		case ADDI:
			if (!UFINT.status.Busy)
			{
				if (bancoRegistradores[in.s_instrucao.rt].UF == semUF)
				{
					UFINT.status.Busy = true;
					UFINT.status.Op = ADDI;
					UFINT.status.Fi = in.i_instrucao.rt;
					UFINT.status.Fj = in.i_instrucao.rs;
					UFINT.status.Fk = in.i_instrucao.imediato;
					UFINT.status.Qj = bancoRegistradores[in.i_instrucao.imediato].UF;
					UFINT.status.Qk = bancoRegistradores[in.i_instrucao.rs].UF;
					UFINT.status.Rj = (bancoRegistradores[in.i_instrucao.imediato].UF == semUF) ? true : false;
					UFINT.status.Rk = (bancoRegistradores[in.i_instrucao.rs].UF == semUF) ? true : false;
					bancoRegistradores[in.i_instrucao.rt].UF = UF_INT;
					in.UF = UF_INT;
					escrita_bar(in, barIR);
					excluirElem(listaIssue, 0); //barramento.instrucao.posicao
					EMITIDA = true;
				}
			}
			break;
		case ANDI:
			if (!UFINT.status.Busy)
			{
				if (bancoRegistradores[in.s_instrucao.rd].UF == semUF)
				{
					UFINT.status.Busy = true;
					UFINT.status.Op = ANDI;
					UFINT.status.Fi = in.i_instrucao.rt;
					UFINT.status.Fj = in.i_instrucao.rs;
					UFINT.status.Fk = in.i_instrucao.imediato;
					UFINT.status.Qj = bancoRegistradores[in.i_instrucao.imediato].UF;
					UFINT.status.Qk = bancoRegistradores[in.i_instrucao.rs].UF;
					UFINT.status.Rj = (bancoRegistradores[in.i_instrucao.imediato].UF == semUF) ? true : false;
					UFINT.status.Rk = (bancoRegistradores[in.i_instrucao.rs].UF == semUF) ? true : false;
					bancoRegistradores[in.i_instrucao.rt].UF = UF_INT;
					in.UF = UF_INT;
					escrita_bar(in, barIR);
					excluirElem(listaIssue, 0); //barramento.instrucao.posicao
					EMITIDA = true;
				}
			}
			break;
		case B:
			if (!UFINT.status.Busy)
			{
				if (bancoRegistradores[in.s_instrucao.rd].UF == semUF)
				{
					UFINT.status.Busy = true;
					UFINT.status.Op = B;
					UFINT.status.Fi = semUF;
					UFINT.status.Fj = in.i_instrucao.rs;
					UFINT.status.Fk = semUF;
					UFINT.status.Qj = bancoRegistradores[in.s_instrucao.rs].UF;
					UFINT.status.Qk = semUF;
					UFINT.status.Rj = (bancoRegistradores[in.s_instrucao.rs].UF == semUF) ? true : false;
					UFINT.status.Rk = (bancoRegistradores[in.s_instrucao.rt].UF == semUF) ? true : false;
					bancoRegistradores[in.s_instrucao.rd].UF = UF_INT;
					in.UF = UF_INT;
					escrita_bar(in, barIR);
					excluirElem(listaIssue, 0); //barramento.instrucao.posicao
					EMITIDA = true;
				}
			}
			break;
		case BEQ:
			if (!UFINT.status.Busy)
			{
				if (bancoRegistradores[in.s_instrucao.rd].UF == semUF)
				{
					UFINT.status.Busy = true;
					UFINT.status.Op = MUL;
					UFINT.status.Fi = in.s_instrucao.rd;
					UFINT.status.Fj = in.s_instrucao.rs;
					UFINT.status.Fk = in.s_instrucao.rt;
					UFINT.status.Qj = bancoRegistradores[in.s_instrucao.rs].UF;
					UFINT.status.Qk = bancoRegistradores[in.s_instrucao.rt].UF;
					UFINT.status.Rj = (bancoRegistradores[in.s_instrucao.rs].UF == semUF) ? true : false;
					UFINT.status.Rk = (bancoRegistradores[in.s_instrucao.rt].UF == semUF) ? true : false;
					bancoRegistradores[in.s_instrucao.rd].UF = UF_INT;
					in.UF = UF_INT;
					escrita_bar(in, barIR);
					excluirElem(listaIssue, 0); //barramento.instrucao.posicao
					EMITIDA = true;
				}
			}
			break;
		case BEQL:
			//rs rt
			break;
		case BGTZ:
			//rs
			break;
		case BLEZ:
			//rs
			break;
		case BNE:
			//rs rt
			break;
		case LUI:
			if (!UFINT.status.Busy)
			{
				if (bancoRegistradores[in.s_instrucao.rd].UF == semUF)
				{
					UFINT.status.Busy = true;
					UFINT.status.Op = LUI;
					UFINT.status.Fi = semUF;
					UFINT.status.Fj = semUF;
					UFINT.status.Fk = in.s_instrucao.rt;
					UFINT.status.Qj = bancoRegistradores[in.s_instrucao.rs].UF;
					UFINT.status.Qk = bancoRegistradores[in.s_instrucao.rt].UF;
					UFINT.status.Rj = (bancoRegistradores[in.s_instrucao.rs].UF == semUF) ? true : false;
					UFINT.status.Rk = (bancoRegistradores[in.s_instrucao.rt].UF == semUF) ? true : false;
					bancoRegistradores[in.s_instrucao.rd].UF = UF_INT;
					in.UF = UF_INT;
					escrita_bar(in, barIR);
					excluirElem(listaIssue, 0); //barramento.instrucao.posicao
					EMITIDA = true;
				}
			}
			break;
		case ORI:
			if (!UFINT.status.Busy)
			{
				if (bancoRegistradores[in.s_instrucao.rd].UF == semUF)
				{
					UFINT.status.Busy = true;
					UFINT.status.Op = ORI;
					UFINT.status.Fi = in.i_instrucao.rt;
					UFINT.status.Fj = in.i_instrucao.rs;
					UFINT.status.Fk = in.i_instrucao.imediato;
					UFINT.status.Qj = bancoRegistradores[in.s_instrucao.rs].UF;
					UFINT.status.Qk = bancoRegistradores[in.s_instrucao.rt].UF;
					UFINT.status.Rj = (bancoRegistradores[in.s_instrucao.rs].UF == semUF) ? true : false;
					UFINT.status.Rk = (bancoRegistradores[in.s_instrucao.rt].UF == semUF) ? true : false;
					bancoRegistradores[in.s_instrucao.rd].UF = UF_INT;
					in.UF = UF_INT;
					escrita_bar(in, barIR);
					excluirElem(listaIssue, 0); //barramento.instrucao.posicao
					EMITIDA = true;
				}
			}
			break;
		case XORI:
			// rt rs
			break;
		case J:
			if (!UFINT.status.Busy)
			{
				if (bancoRegistradores[in.s_instrucao.rd].UF == semUF)
				{
					UFINT.status.Busy = true;
					UFINT.status.Op = J;
					UFINT.status.Fi = semUF;
					UFINT.status.Fj = semUF;
					UFINT.status.Fk = semUF;
					UFINT.status.Qj = bancoRegistradores[in.s_instrucao.rs].UF;
					UFINT.status.Qk = bancoRegistradores[in.s_instrucao.rt].UF;
					UFINT.status.Rj = (bancoRegistradores[in.s_instrucao.rs].UF == semUF) ? true : false;
					UFINT.status.Rk = (bancoRegistradores[in.s_instrucao.rt].UF == semUF) ? true : false;
					bancoRegistradores[in.s_instrucao.rd].UF = UF_INT;
					in.UF = UF_INT;
					escrita_bar(in, barIR);
					excluirElem(listaIssue, 0); //barramento.instrucao.posicao
					EMITIDA = true;
				}
			}
			break;
		case BGEZ: //rs e offset

			break;
		case BLTZ:
			break; //rs e offset
		default:
			printf("Operação não listada!");
			break;
		}
	}
}

void leitura()
{
	Inst in = listaRead->lista_inst[0];
	if (verifica_bar(barIR))
		IR.instrucao.posicao = inserirElemLista(listaRead, IR.instrucao);
	for (int i = 0; i < listaRead->nroElem; i++)
	{
		switch (in.UF)
		{
		case UF_ADD:
			if ((UFADD.status.Fj == semUF) && (UFADD.status.Fk == semUF))
			{ // n é só fazer UFADD.status.Rj ???
			}
			else if (UFADD.status.Fj == semUF)
			{
			}
			else
			{
				escrita_bar(in, barRE)
			}
			break;
		case UF_DIV:
			if ((UFDIV.status.Fj == semUF) && (UFDIV.status.Fk == semUF))
			{
			}
			else if (UFDIV.status.Fj == semUF)
			{
			}
			else
			{
			}
			break;
		case UF_INT:
			if ((UFINT.status.Fj == semUF) && (UFINT.status.Fk == semUF))
			{
				escrita_bar(in, barRE);
			}
			else if (UFINT.status.Fj == semUF)
			{
			}
			else
			{
			}
			break;
		case UF_MUL1:
			if ((UFMUL1.status.Fj == semUF) && (UFMUL1.status.Fk == semUF))
			{
			}
			else if (UFMUL1.status.Fj == semUF)
			{
			}
			else
			{
			}
			break;
		case UF_MUL2:
			if ((UFMUL2.status.Fj == semUF) && (UFMUL2.status.Fk == semUF))
			{
			}
			else if (UFMUL2.status.Fj == semUF)
			{
			}
			else
			{
			}
			break;
		}
		//pra cada instrução na lista de leitura verificar se os reg de origem tem alguma UF produzindo eles ainda, se n tiver ta ok e pode prosseguir
	}
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
		bancoRegistradores[in.s2_instrucao.rd].valor = multiplicacao(bancoRegistradores[in.s2_instrucao.rs].valor, bancoRegistradores[in.s2_instrucao.rt].valor);
		bufferResultado.valor = adicao(bufferResultado.valor, juntarHILO(bancoRegistradores[HI].valor, bancoRegistradores[LO].valor));
		break;
	case MSUB:
		bancoRegistradores[in.s2_instrucao.rd].valor = multiplicacao(bancoRegistradores[in.s2_instrucao.rs].valor, bancoRegistradores[in.s2_instrucao.rt].valor);
		bufferResultado.valor = subtracao(bufferResultado.valor, juntarHILO(bancoRegistradores[HI].valor, bancoRegistradores[LO].valor));
		break;
	case MUL:
		bufferRegistradores[in.s2_instrucao.rd].valor = multiplicacao(bancoRegistradores[in.s2_instrucao.rs].valor, bancoRegistradores[in.s2_instrucao.rt].valor);
		return in.s2_instrucao.rd;
		break;
	case ADDI:
		bufferRegistradores[in.i_instrucao.rt].valor = adicao(bancoRegistradores[in.i_instrucao.rs].valor, in.i_instrucao.imediato);
		return in.i_instrucao.rt;
		break;
	case ANDI:
		bufferRegistradores[in.s_instrucao.rt].valor = and(bancoRegistradores[in.s_instrucao.rs].valor, in.i_instrucao.imediato);
		return in.s_instrucao.rt;
		break;
	case B:
		PC += in.i_instrucao.imediato;
		break;
	case BEQ:
		if (igual(bancoRegistradores[in.i_instrucao.rs].valor, bancoRegistradores[in.i_instrucao.rt].valor))
			PC += in.i_instrucao.imediato;
		break;
	case BEQL:
		if (igual(bancoRegistradores[in.i_instrucao.rs].valor, bancoRegistradores[in.i_instrucao.rt].valor))
			PC += in.i_instrucao.imediato;
		break;
	case BGTZ:
		if (maior(bancoRegistradores[in.i_instrucao.rs].valor, 0))
			PC += in.i_instrucao.imediato;
		break;
	case BLEZ:
		if (menorIgual(bancoRegistradores[in.i_instrucao.rs].valor, 0))
			PC += in.i_instrucao.imediato;
		break;
	case BNE:
		if (not(igual(bancoRegistradores[in.i_instrucao.rs].valor, bancoRegistradores[in.s_instrucao.rt].valor)))
			PC += in.i_instrucao.imediato;
		break;
	case LUI:
		bufferRegistradores[in.i_instrucao.rt].valor = shiftLeft(in.i_instrucao.imediato, 16);
		return in.i_instrucao.rt;
		break;
	case ORI:
		bufferRegistradores[in.i_instrucao.rt].valor = or (bancoRegistradores[in.i_instrucao.rs].valor, in.i_instrucao.imediato);
		return in.i_instrucao.rt;
		break;
	case XORI:
		bufferRegistradores[in.i_instrucao.rt].valor = xor(bancoRegistradores[in.i_instrucao.rs].valor, in.i_instrucao.imediato);
		return in.i_instrucao.rt;
		break;
	case J:
		PC = in.j_instrucao.addr;
		break;
	case BGEZ:
		if (maiorIgual(bancoRegistradores[in.r_instrucao.rs].valor, 0))
			PC += in.r_instrucao.offset;
		break;
	case BLTZ:
		if (menor(bancoRegistradores[in.r_instrucao.rs].valor, 0))
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
	bancoRegistradores[reg].UF = semUF;
	excluirElem(listaWriteB, EW->instrucao.posicao);

	//liberar a uf, falar que nenuma uf ta produzindo o reg q eu escrevi, tirar a in da lista
}