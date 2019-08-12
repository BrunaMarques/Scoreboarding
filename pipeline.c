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
			inserirElemLista(listaIssue, in);
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
				if (bancoRegistradores[HI].UF == semUF)
				{
					UFDIV.status.Busy = true;
					UFDIV.status.Op = DIV;
					UFDIV.status.Fi = HI;
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
				if (bancoRegistradores[HI].UF == semUF)
				{
					UFINT.status.Busy = true;
					UFINT.status.Op = MFHI;
					UFINT.status.Fi = HI;
					UFINT.status.Fj = semREG;
					UFINT.status.Fk = semREG;
					UFINT.status.Qj = semUF;
					UFINT.status.Qk = semUF;
					UFINT.status.Rj = (bancoRegistradores[in.s_instrucao.rs].UF == semUF) ? true : false;
					UFINT.status.Rk = (bancoRegistradores[in.s_instrucao.rt].UF == semUF) ? true : false;
					bancoRegistradores[HI].UF = UF_INT;
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
				if (bancoRegistradores[LO].UF == semUF)
				{
					UFINT.status.Busy = true;
					UFINT.status.Op = MFLO;
					UFINT.status.Fi = LO;
					UFINT.status.Fj = semREG;
					UFINT.status.Fk = semREG;
					UFINT.status.Qj = semUF;
					UFINT.status.Qk = semUF;
					UFINT.status.Rj = (bancoRegistradores[in.s_instrucao.rs].UF == semUF) ? true : false;
					UFINT.status.Rk = (bancoRegistradores[in.s_instrucao.rt].UF == semUF) ? true : false;
					bancoRegistradores[LO].UF = UF_INT;
					in.UF = UF_INT;
					escrita_bar(in, barIR);
					excluirElem(listaIssue, 0);
					EMITIDA = true;
				}
			}
			break;
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
		case MTHI: //ver se ta CERTO, SE PODE TIRAR O RD==SEMUF
		{
			UFINT.status.Busy = true;
			UFINT.status.Op = MTHI;
			UFINT.status.Fi = semREG;
			UFINT.status.Fj = HI;
			UFINT.status.Fk = semREG;
			UFINT.status.Qj = bancoRegistradores[HI].UF;
			UFINT.status.Qk = semUF;
			UFINT.status.Rj = (bancoRegistradores[HI].UF == semUF) ? true : false;
			UFINT.status.Rk = (bancoRegistradores[in.s_instrucao.rt].UF == semUF) ? true : false;
			bancoRegistradores[HI].UF = UF_INT;
			in.UF = UF_INT;
			escrita_bar(in, barIR);
			excluirElem(listaIssue, 0);
			EMITIDA = true;
		}
		break;
		case MTLO: //ver se ta certo
			if (!UFINT.status.Busy)
			{
				if (bancoRegistradores[LO].UF == semUF)
				{
					UFINT.status.Busy = true;
					UFINT.status.Op = MTLO;
					UFINT.status.Fi = semREG;
					UFINT.status.Fj = LO;
					UFINT.status.Fk = semREG;
					UFINT.status.Qj = bancoRegistradores[LO].UF;
					UFINT.status.Qk = semUF;
					UFINT.status.Rj = (bancoRegistradores[LO].UF == semUF) ? true : false;
					UFINT.status.Rk = (bancoRegistradores[in.s_instrucao.rt].UF == semUF) ? true : false;
					bancoRegistradores[LO].UF = UF_INT;
					in.UF = UF_INT;
					escrita_bar(in, barIR);
					excluirElem(listaIssue, 0);
					EMITIDA = true;
				}
			}
			break;
		case MULT: //ver se ta certo
			if (!UFMUL1.status.Busy)
			{
				UFMUL1.status.Busy = true;
				UFMUL1.status.Op = MUL;
				UFMUL1.status.Fi = semREG;
				UFMUL1.status.Fj = in.s_instrucao.rs;
				UFMUL1.status.Fk = in.s_instrucao.rt;
				UFMUL1.status.Qj = bancoRegistradores[in.s_instrucao.rs].UF;
				UFMUL1.status.Qk = bancoRegistradores[in.s_instrucao.rt].UF;
				UFMUL1.status.Rj = (bancoRegistradores[in.s_instrucao.rs].UF == semUF) ? true : false;
				UFMUL1.status.Rk = (bancoRegistradores[in.s_instrucao.rt].UF == semUF) ? true : false;
				in.UF = UF_MUL1;
				escrita_bar(in, barIR);
				excluirElem(listaIssue, 0);
				EMITIDA = true;
			}
			if (!UFMUL2.status.Busy)
			{
				UFMUL2.status.Busy = true;
				UFMUL2.status.Op = MUL;
				UFMUL2.status.Fi = semREG;
				UFMUL2.status.Fj = in.s_instrucao.rs;
				UFMUL2.status.Fk = in.s_instrucao.rt;
				UFMUL2.status.Qj = bancoRegistradores[in.s_instrucao.rs].UF;
				UFMUL2.status.Qk = bancoRegistradores[in.s_instrucao.rt].UF;
				UFMUL2.status.Rj = (bancoRegistradores[in.s_instrucao.rs].UF == semUF) ? true : false;
				UFMUL2.status.Rk = (bancoRegistradores[in.s_instrucao.rt].UF == semUF) ? true : false;
				in.UF = UF_MUL2;
				escrita_bar(in, barIR);
				excluirElem(listaIssue, 0);
				EMITIDA = true;
			}
			break;
		case NOP:
			if (!UFINT.status.Busy)
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
		case MADD: //ver se ta certo//destino é hi e lo
			if (!UFINT.status.Busy)
			{
				if (bancoRegistradores[HI].UF == semUF)
				{
					UFINT.status.Busy = true;
					UFINT.status.Op = MADD;
					UFINT.status.Fi = HI;
					UFINT.status.Fj = in.s2_instrucao.rs;
					UFINT.status.Fk = in.s2_instrucao.rt;
					UFINT.status.Qj = bancoRegistradores[in.s2_instrucao.rs].UF;
					UFINT.status.Qk = bancoRegistradores[in.s2_instrucao.rt].UF;
					UFINT.status.Rj = (bancoRegistradores[in.s2_instrucao.rs].UF == semUF) ? true : false;
					UFINT.status.Rk = (bancoRegistradores[in.s2_instrucao.rt].UF == semUF) ? true : false;
					bancoRegistradores[HI].UF = UF_INT;
					in.UF = UF_INT;
					escrita_bar(in, barIR);
					excluirElem(listaIssue, 0);
					EMITIDA = true;
				}
			}
			break;
		case MSUB: //ver se ta certo
			if (!UFINT.status.Busy)
			{
				if (bancoRegistradores[HI].UF == semUF)
				{
					UFINT.status.Busy = true;
					UFINT.status.Op = MSUB;
					UFINT.status.Fi = HI;
					UFINT.status.Fj = in.s2_instrucao.rs;
					UFINT.status.Fk = in.s2_instrucao.rt;
					UFINT.status.Qj = bancoRegistradores[in.s2_instrucao.rs].UF;
					UFINT.status.Qk = bancoRegistradores[in.s2_instrucao.rt].UF;
					UFINT.status.Rj = (bancoRegistradores[in.s2_instrucao.rs].UF == semUF) ? true : false;
					UFINT.status.Rk = (bancoRegistradores[in.s2_instrucao.rt].UF == semUF) ? true : false;
					bancoRegistradores[HI].UF = UF_INT;
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
				if (bancoRegistradores[in.s2_instrucao.rd].UF == semUF)
				{
					UFMUL1.status.Busy = true;
					UFMUL1.status.Op = MUL;
					UFMUL1.status.Fi = in.s2_instrucao.rd;
					UFMUL1.status.Fj = in.s2_instrucao.rs;
					UFMUL1.status.Fk = in.s2_instrucao.rt;
					UFMUL1.status.Qj = bancoRegistradores[in.s2_instrucao.rs].UF;
					UFMUL1.status.Qk = bancoRegistradores[in.s2_instrucao.rt].UF;
					UFMUL1.status.Rj = (bancoRegistradores[in.s2_instrucao.rs].UF == semUF) ? true : false;
					UFMUL1.status.Rk = (bancoRegistradores[in.s2_instrucao.rt].UF == semUF) ? true : false;
					bancoRegistradores[in.s2_instrucao.rd].UF = UF_MUL1;
					in.UF = UF_MUL1;
					escrita_bar(in, barIR);
					excluirElem(listaIssue, 0);
					EMITIDA = true;
				}
			}
			else if (!UFMUL2.status.Busy)
			{
				if (bancoRegistradores[in.s2_instrucao.rd].UF == semUF)
				{
					UFMUL2.status.Busy = true;
					UFMUL2.status.Op = MUL;
					UFMUL2.status.Fi = in.s2_instrucao.rd;
					UFMUL2.status.Fj = in.s2_instrucao.rs;
					UFMUL2.status.Fk = in.s2_instrucao.rt;
					UFMUL2.status.Qj = bancoRegistradores[in.s2_instrucao.rs].UF;
					UFMUL2.status.Qk = bancoRegistradores[in.s2_instrucao.rt].UF;
					UFMUL2.status.Rj = (bancoRegistradores[in.s2_instrucao.rs].UF == semUF) ? true : false;
					UFMUL2.status.Rk = (bancoRegistradores[in.s2_instrucao.rt].UF == semUF) ? true : false;
					bancoRegistradores[in.s2_instrucao.rd].UF = UF_MUL2;
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
				if (bancoRegistradores[in.i_instrucao.rt].UF == semUF)
				{
					UFINT.status.Busy = true;
					UFINT.status.Op = ADDI;
					UFINT.status.Fi = in.i_instrucao.rt;
					UFINT.status.Fj = in.i_instrucao.rs;
					UFINT.status.Fk = in.i_instrucao.imediato;
					UFINT.status.Qj = bancoRegistradores[in.i_instrucao.rs].UF;
					UFINT.status.Qk = bancoRegistradores[in.i_instrucao.imediato].UF;
					UFINT.status.Rj = (bancoRegistradores[in.i_instrucao.rs].UF == semUF) ? true : false;
					UFINT.status.Rk = (bancoRegistradores[in.i_instrucao.imediato].UF == semUF) ? true : false;
					bancoRegistradores[in.i_instrucao.rt].UF = UF_INT;
					in.UF = UF_INT;
					escrita_bar(in, barIR);
					excluirElem(listaIssue, 0);
					EMITIDA = true;
				}
			}
			break;
		case ANDI:
			if (!UFINT.status.Busy)
			{
				if (bancoRegistradores[in.i_instrucao.rt].UF == semUF)
				{
					UFINT.status.Busy = true;
					UFINT.status.Op = ANDI;
					UFINT.status.Fi = in.i_instrucao.rt;
					UFINT.status.Fj = in.i_instrucao.rs;
					UFINT.status.Fk = in.i_instrucao.imediato;
					UFINT.status.Qj = bancoRegistradores[in.i_instrucao.rs].UF;
					UFINT.status.Qk = bancoRegistradores[in.i_instrucao.imediato].UF;
					UFINT.status.Rj = (bancoRegistradores[in.i_instrucao.rs].UF == semUF) ? true : false;
					UFINT.status.Rk = (bancoRegistradores[in.i_instrucao.imediato].UF == semUF) ? true : false;
					bancoRegistradores[in.i_instrucao.rt].UF = UF_INT;
					in.UF = UF_INT;
					escrita_bar(in, barIR);
					excluirElem(listaIssue, 0);
					EMITIDA = true;
				}
			}
			break;
		case B: //ver se tá certo
			if (!UFINT.status.Busy)
			{
				UFINT.status.Busy = true;
				UFINT.status.Op = B;
				UFINT.status.Fi = semREG;
				UFINT.status.Fj = in.i_instrucao.imediato;
				UFINT.status.Fk = semREG;
				UFINT.status.Qj = bancoRegistradores[in.i_instrucao.imediato].UF;
				UFINT.status.Qk = semUF;
				UFINT.status.Rj = (bancoRegistradores[in.i_instrucao.imediato].UF == semUF) ? true : false;
				UFINT.status.Rk = (bancoRegistradores[in.i_instrucao.rt].UF == semUF) ? true : false;
				in.UF = UF_INT;
				escrita_bar(in, barIR);
				excluirElem(listaIssue, 0);
				EMITIDA = true;
			}
			break;
		case BEQ:
			if (!UFINT.status.Busy)
			{
				if (bancoRegistradores[in.i_instrucao.rs].UF == semUF)
				{
					UFINT.status.Busy = true;
					UFINT.status.Op = BEQ;
					UFINT.status.Fi = in.i_instrucao.rs;
					UFINT.status.Fj = in.i_instrucao.rt;
					UFINT.status.Fk = in.i_instrucao.imediato;
					UFINT.status.Qj = bancoRegistradores[in.i_instrucao.rt].UF;
					UFINT.status.Qk = bancoRegistradores[in.i_instrucao.imediato].UF;
					UFINT.status.Rj = (bancoRegistradores[in.i_instrucao.rt].UF == semUF) ? true : false;
					UFINT.status.Rk = (bancoRegistradores[in.i_instrucao.imediato].UF == semUF) ? true : false;
					bancoRegistradores[in.i_instrucao.rs].UF = UF_INT;
					in.UF = UF_INT;
					escrita_bar(in, barIR);
					excluirElem(listaIssue, 0);
					EMITIDA = true;
				}
			}
			break;
		case BEQL:
			if (!UFINT.status.Busy)
			{
				if (bancoRegistradores[in.i_instrucao.rs].UF == semUF)
				{
					UFINT.status.Busy = true;
					UFINT.status.Op = BEQL;
					UFINT.status.Fi = in.i_instrucao.rs;
					UFINT.status.Fj = in.i_instrucao.rt;
					UFINT.status.Fk = in.i_instrucao.imediato;
					UFINT.status.Qj = bancoRegistradores[in.i_instrucao.rt].UF;
					UFINT.status.Qk = bancoRegistradores[in.i_instrucao.imediato].UF;
					UFINT.status.Rj = (bancoRegistradores[in.i_instrucao.rt].UF == semUF) ? true : false;
					UFINT.status.Rk = (bancoRegistradores[in.i_instrucao.imediato].UF == semUF) ? true : false;
					bancoRegistradores[in.i_instrucao.rs].UF = UF_INT;
					in.UF = UF_INT;
					escrita_bar(in, barIR);
					excluirElem(listaIssue, 0);
					EMITIDA = true;
				}
			}
			break;
		case BGTZ: //ver se ta certo
			if (!UFINT.status.Busy)
			{
				if (bancoRegistradores[in.i_instrucao.rs].UF == semUF)
				{
					UFINT.status.Busy = true;
					UFINT.status.Op = BGTZ;
					UFINT.status.Fi = in.i_instrucao.rs;
					UFINT.status.Fj = semREG;
					UFINT.status.Fk = in.i_instrucao.imediato;
					UFINT.status.Qj = semUF;
					UFINT.status.Qk = bancoRegistradores[in.i_instrucao.imediato].UF;
					UFINT.status.Rj = (bancoRegistradores[in.i_instrucao.rt].UF == semUF) ? true : false;
					UFINT.status.Rk = (bancoRegistradores[in.i_instrucao.imediato].UF == semUF) ? true : false;
					bancoRegistradores[in.i_instrucao.rs].UF = UF_INT;
					in.UF = UF_INT;
					escrita_bar(in, barIR);
					excluirElem(listaIssue, 0);
					EMITIDA = true;
				}
			}
			break;
		case BLEZ: //ver se ta certo
			if (!UFINT.status.Busy)
			{
				if (bancoRegistradores[in.i_instrucao.rs].UF == semUF)
				{
					UFINT.status.Busy = true;
					UFINT.status.Op = BLEZ;
					UFINT.status.Fi = in.i_instrucao.rs;
					UFINT.status.Fj = semREG;
					UFINT.status.Fk = in.i_instrucao.imediato;
					UFINT.status.Qj = semUF;
					UFINT.status.Qk = bancoRegistradores[in.i_instrucao.imediato].UF;
					UFINT.status.Rj = (bancoRegistradores[in.i_instrucao.rt].UF == semUF) ? true : false;
					UFINT.status.Rk = (bancoRegistradores[in.i_instrucao.imediato].UF == semUF) ? true : false;
					bancoRegistradores[in.i_instrucao.rs].UF = UF_INT;
					in.UF = UF_INT;
					escrita_bar(in, barIR);
					excluirElem(listaIssue, 0);
					EMITIDA = true;
				}
			}
			break;
		case BNE:
			if (!UFINT.status.Busy)
			{
				if (bancoRegistradores[in.i_instrucao.rs].UF == semUF)
				{
					UFINT.status.Busy = true;
					UFINT.status.Op = BNE;
					UFINT.status.Fi = in.i_instrucao.rs;
					UFINT.status.Fj = in.i_instrucao.rt;
					UFINT.status.Fk = in.i_instrucao.imediato;
					UFINT.status.Qj = bancoRegistradores[in.i_instrucao.rt].UF;
					UFINT.status.Qk = bancoRegistradores[in.i_instrucao.imediato].UF;
					UFINT.status.Rj = (bancoRegistradores[in.i_instrucao.rt].UF == semUF) ? true : false;
					UFINT.status.Rk = (bancoRegistradores[in.i_instrucao.imediato].UF == semUF) ? true : false;
					bancoRegistradores[in.i_instrucao.rs].UF = UF_INT;
					in.UF = UF_INT;
					escrita_bar(in, barIR);
					excluirElem(listaIssue, 0);
					EMITIDA = true;
				}
			}
			break;
		case LUI: //ver se ta certo
			if (!UFINT.status.Busy)
			{
				if (bancoRegistradores[in.i_instrucao.rt].UF == semUF)
				{
					UFINT.status.Busy = true;
					UFINT.status.Op = LUI;
					UFINT.status.Fi = in.i_instrucao.rt;
					UFINT.status.Fj = in.i_instrucao.imediato;
					UFINT.status.Fk = semREG;
					UFINT.status.Qj = bancoRegistradores[in.i_instrucao.imediato].UF;
					UFINT.status.Qk = semUF;
					UFINT.status.Rj = (bancoRegistradores[in.i_instrucao.imediato].UF == semUF) ? true : false;
					UFINT.status.Rk = (bancoRegistradores[in.i_instrucao.rt].UF == semUF) ? true : false;
					bancoRegistradores[in.i_instrucao.rt].UF = UF_INT;
					in.UF = UF_INT;
					escrita_bar(in, barIR);
					excluirElem(listaIssue, 0);
					EMITIDA = true;
				}
			}
			break;
		case ORI:
			if (!UFINT.status.Busy)
			{
				if (bancoRegistradores[in.i_instrucao.rt].UF == semUF)
				{
					UFINT.status.Busy = true;
					UFINT.status.Op = ORI;
					UFINT.status.Fi = in.i_instrucao.rt;
					UFINT.status.Fj = in.i_instrucao.rs;
					UFINT.status.Fk = in.i_instrucao.imediato;
					UFINT.status.Qj = bancoRegistradores[in.i_instrucao.rs].UF;
					UFINT.status.Qk = bancoRegistradores[in.i_instrucao.imediato].UF;
					UFINT.status.Rj = (bancoRegistradores[in.i_instrucao.rs].UF == semUF) ? true : false;
					UFINT.status.Rk = (bancoRegistradores[in.i_instrucao.imediato].UF == semUF) ? true : false;
					bancoRegistradores[in.i_instrucao.rt].UF = UF_INT;
					in.UF = UF_INT;
					escrita_bar(in, barIR);
					excluirElem(listaIssue, 0);
					EMITIDA = true;
				}
			}
			break;
		case XORI:
			if (!UFINT.status.Busy)
			{
				if (bancoRegistradores[in.i_instrucao.rt].UF == semUF)
				{
					UFINT.status.Busy = true;
					UFINT.status.Op = XORI;
					UFINT.status.Fi = in.i_instrucao.rt;
					UFINT.status.Fj = in.i_instrucao.rs;
					UFINT.status.Fk = in.i_instrucao.imediato;
					UFINT.status.Qj = bancoRegistradores[in.i_instrucao.rs].UF;
					UFINT.status.Qk = bancoRegistradores[in.i_instrucao.imediato].UF;
					UFINT.status.Rj = (bancoRegistradores[in.i_instrucao.rs].UF == semUF) ? true : false;
					UFINT.status.Rk = (bancoRegistradores[in.i_instrucao.imediato].UF == semUF) ? true : false;
					bancoRegistradores[in.i_instrucao.rt].UF = UF_INT;
					in.UF = UF_INT;
					escrita_bar(in, barIR);
					excluirElem(listaIssue, 0);
					EMITIDA = true;
				}
			}
			break;
		case J:
			if (!UFINT.status.Busy)
			{
				UFINT.status.Busy = true;
				UFINT.status.Op = J;
				UFINT.status.Fi = semREG;
				UFINT.status.Fj = semREG;
				UFINT.status.Fk = semREG;
				UFINT.status.Qj = semUF;
				UFINT.status.Qk = semUF;
				UFINT.status.Rj = (bancoRegistradores[in.i_instrucao.rs].UF == semUF) ? true : false;
				UFINT.status.Rk = (bancoRegistradores[in.i_instrucao.rt].UF == semUF) ? true : false;
				in.UF = UF_INT;
				escrita_bar(in, barIR);
				excluirElem(listaIssue, 0);
				EMITIDA = true;
			}
			break;
		case BGEZ:
			if (!UFINT.status.Busy)
			{
				UFINT.status.Busy = true;
				UFINT.status.Op = BGEZ;
				UFINT.status.Fi = semREG;
				UFINT.status.Fj = in.i_instrucao.rs;
				UFINT.status.Fk = in.i_instrucao.imediato;
				UFINT.status.Qj = bancoRegistradores[in.i_instrucao.rs].UF;
				UFINT.status.Qk = bancoRegistradores[in.i_instrucao.imediato].UF;
				UFINT.status.Rj = (bancoRegistradores[in.i_instrucao.rs].UF == semUF) ? true : false;
				UFINT.status.Rk = (bancoRegistradores[in.i_instrucao.imediato].UF == semUF) ? true : false;
				in.UF = UF_INT;
				escrita_bar(in, barIR);
				excluirElem(listaIssue, 0);
				EMITIDA = true;
			}
			break;
		case BLTZ: //em saltos o destino é pc, só tem source

			if (!UFINT.status.Busy)
			{
				UFINT.status.Busy = true;
				UFINT.status.Op = BLTZ;
				UFINT.status.Fi = semREG;
				UFINT.status.Fj = in.i_instrucao.rs;
				UFINT.status.Fk = in.i_instrucao.imediato;
				UFINT.status.Qj = bancoRegistradores[in.i_instrucao.rs].UF;
				UFINT.status.Qk = bancoRegistradores[in.i_instrucao.imediato].UF;
				UFINT.status.Rj = (bancoRegistradores[in.i_instrucao.rs].UF == semUF) ? true : false;
				UFINT.status.Rk = (bancoRegistradores[in.i_instrucao.imediato].UF == semUF) ? true : false;
				in.UF = UF_INT;
				escrita_bar(in, barIR);
				excluirElem(listaIssue, 0);
				EMITIDA = true;
			}
			break;
		default:
			printf("Operação não listada!");
			break;
		}
	}
}

void leitura()
{
	if (verifica_bar(barIR))
	{
		Inst in;
		in = leitura_bar(barIR);
		inserirElemLista(listaRead, in);
	}
	for (int i = 0; i < listaRead->nroElem; i++)
	{
		switch (in.UF)
		{
		case UF_ADD:
			if ((UFADD.status.Fj != semREG) && (UFADD.status.Fk != semREG))
			{
				if ((bancoRegistradores[UFADD.status.Fj].UF == semUF) && (bancoRegistradores[UFADD.status.Fk].UF == semUF))
				{
					escrita_bar(in, barRE);
					excluirElem(listaRead, in.posicao);
				}
			}
			else if (UFADD.status.Fj != semREG)
			{
				if (bancoRegistradores[UFADD.status.Fj].UF == semUF)
				{
					escrita_bar(in, barRE);
					excluirElem(listaRead, in.posicao);
				}
			}
			else
			{
				escrita_bar(in, barRE);
				excluirElem(listaRead, in.posicao);
			}
			break;
		case UF_DIV:
			if ((UFDIV.status.Fj != semREG) && (UFDIV.status.Fk != semREG))
			{
				if ((bancoRegistradores[UFDIV.status.Fj].UF == semUF) && (bancoRegistradores[UFDIV.status.Fk].UF == semUF))
				{
					escrita_bar(in, barRE);
					excluirElem(listaRead, in.posicao);
				}
			}
			else if (UFDIV.status.Fj != semREG)
			{
				if (bancoRegistradores[UFDIV.status.Fj].UF == semUF)
				{
					escrita_bar(in, barRE);
					excluirElem(listaRead, in.posicao);
				}
			}
			break;
		case UF_INT:
			if ((UFINT.status.Fj != semREG) && (UFINT.status.Fk != semREG))
			{
				if ((bancoRegistradores[UFINT.status.Fj].UF == semUF) && (bancoRegistradores[UFINT.status.Fk].UF == semUF))
				{
					escrita_bar(in, barRE);
					excluirElem(listaRead, in.posicao);
				}
			}
			else if (UFINT.status.Fj != semREG)
			{
				if (bancoRegistradores[UFINT.status.Fj].UF == semUF)
				{
					escrita_bar(in, barRE);
					excluirElem(listaRead, in.posicao);
				}
			}
			else
			{
				escrita_bar(in, barRE);
				excluirElem(listaRead, in.posicao);
			}
			break;
		case UF_MUL1:
			if ((UFMUL1.status.Fj != semREG) && (UFMUL1.status.Fk != semREG))
			{
				if ((bancoRegistradores[UFMUL1.status.Fj].UF == semUF) && (bancoRegistradores[UFMUL1.status.Fk].UF == semUF))
				{
					escrita_bar(in, barRE);
					excluirElem(listaRead, in.posicao);
				}
			}
			else if (UFMUL1.status.Fj != semREG)
			{
				if (bancoRegistradores[UFMUL1.status.Fj].UF == semUF)
				{
					escrita_bar(in, barRE);
					excluirElem(listaRead, in.posicao);
				}
			}
			else
			{
				escrita_bar(in, barRE);
				excluirElem(listaRead, in.posicao);
			}
			break;
		case UF_MUL2:
			if ((UFMUL2.status.Fj != semREG) && (UFMUL2.status.Fk != semREG))
			{
				if ((bancoRegistradores[UFMUL2.status.Fj].UF == semUF) && (bancoRegistradores[UFMUL2.status.Fk].UF == semUF))
				{
					escrita_bar(in, barRE);
					excluirElem(listaRead, in.posicao);
				}
			}
			else if (UFMUL2.status.Fj != semREG)
			{
				if (bancoRegistradores[UFMUL2.status.Fj].UF == semUF)
				{
					escrita_bar(in, barRE);
					excluirElem(listaRead, in.posicao);
				}
			}
			else
			{
				escrita_bar(in, barRE);
				excluirElem(listaRead, in.posicao);
			}
			break;
		}
	}
}

void execucao()
//etapa de execução
{
	if (verifica_bar(barEW))
	{
		Inst in;
		in = leitura_bar(barEW);
		inserirElemLista(listaExecucao, in);
	}
	int operacao = descobrirOperacao(in);
	int registrador;
	switch (operacao)
	{
	case ADD:
		bufferRegistradores[in.s_instrucao.rd].valor = adicao(bancoRegistradores[in.s_instrucao.rs].valor, bancoRegistradores[in.s_instrucao.rt].valor);
		escrita_bar(in, barEW);
		excluirElem(listaExecucao, in.posicao);
		break;
	case AND:
		bufferRegistradores[in.s_instrucao.rd].valor = and(bancoRegistradores[in.s_instrucao.rs].valor, bancoRegistradores[in.s_instrucao.rt].valor);
		escrita_bar(in, barEW);
		excluirElem(listaExecucao, in.posicao);
		break;
	case DIV:
		separarHILO(divisao(bancoRegistradores[in.s_instrucao.rs].valor, bancoRegistradores[in.s_instrucao.rt].valor));
		escrita_bar(in, barEW);
		excluirElem(listaExecucao, in.posicao);
		break;
	case JR:
		PC = bancoRegistradores[in.s_instrucao.rs].valor;
		escrita_bar(in, barEW);
		excluirElem(listaExecucao, in.posicao);
	case MFHI:
		bufferRegistradores[in.s_instrucao.rd].valor = bancoRegistradores[HI].valor;
		escrita_bar(in, barEW);
		excluirElem(listaExecucao, in.posicao);
		break;
	case MFLO:
		bufferRegistradores[in.s_instrucao.rd].valor = bancoRegistradores[LO].valor;
		escrita_bar(in, barEW);
		excluirElem(listaExecucao, in.posicao);
		break;
	case MOVN:
		if (not(igual(bancoRegistradores[in.s_instrucao.rt].valor, 0)))
			bufferRegistradores[in.s_instrucao.rd].valor = bancoRegistradores[in.s_instrucao.rs].valor;
		escrita_bar(in, barEW);
		excluirElem(listaExecucao, in.posicao);
		break;
	case MOVZ:
		if (igual(bancoRegistradores[in.s_instrucao.rt].valor, 0))
			bufferRegistradores[in.s_instrucao.rd].valor = bancoRegistradores[in.s_instrucao.rs].valor;
		escrita_bar(in, barEW);
		excluirElem(listaExecucao, in.posicao);
		break;
	case MTHI: //ver isso
		bufferRegistradores[HI].valor = bancoRegistradores[in.s_instrucao.rs].valor;
		escrita_bar(in, barEW);
		excluirElem(listaExecucao, in.posicao);
		break;
	case MTLO:
		bufferRegistradores[LO].valor = bancoRegistradores[in.s_instrucao.rs].valor;
		escrita_bar(in, barEW);
		excluirElem(listaExecucao, in.posicao);
		break;
	case MULT:
		separarHILO(multiplicacao(bancoRegistradores[in.s_instrucao.rs].valor, bancoRegistradores[in.s_instrucao.rt].valor));
		escrita_bar(in, barEW);
		excluirElem(listaExecucao, in.posicao);
		break;
	case NOP:
		// nao faz nada por enquanto (no operation)//
		break;
	case NOR:
		bufferRegistradores[in.s_instrucao.rd].valor = nor(bancoRegistradores[in.s_instrucao.rs].valor, bancoRegistradores[in.s_instrucao.rt].valor);
		escrita_bar(in, barEW);
		excluirElem(listaExecucao, in.posicao);
		break;
	case OR:
		bufferRegistradores[in.s_instrucao.rd].valor = or (bancoRegistradores[in.s_instrucao.rs].valor, bancoRegistradores[in.s_instrucao.rt].valor);
		escrita_bar(in, barEW);
		excluirElem(listaExecucao, in.posicao);
		break;
	case SUB:
		bufferRegistradores[in.s_instrucao.rd].valor = subtracao(bancoRegistradores[in.s_instrucao.rs].valor, bancoRegistradores[in.s_instrucao.rt].valor);
		escrita_bar(in, barEW);
		excluirElem(listaExecucao, in.posicao);
		break;
	case XOR:
		bufferRegistradores[in.s_instrucao.rd].valor = xor(bancoRegistradores[in.s_instrucao.rs].valor, bancoRegistradores[in.s_instrucao.rt].valor);
		escrita_bar(in, barEW);
		excluirElem(listaExecucao, in.posicao);
		break;
	case MADD:
		bancoRegistradores[in.s2_instrucao.rd].valor = multiplicacao(bancoRegistradores[in.s2_instrucao.rs].valor, bancoRegistradores[in.s2_instrucao.rt].valor);
		bufferResultado.valor = adicao(bufferResultado.valor, juntarHILO(bancoRegistradores[HI].valor, bancoRegistradores[LO].valor));
		escrita_bar(in, barEW);
		excluirElem(listaExecucao, in.posicao);
		break;
	case MSUB:
		bancoRegistradores[in.s2_instrucao.rd].valor = multiplicacao(bancoRegistradores[in.s2_instrucao.rs].valor, bancoRegistradores[in.s2_instrucao.rt].valor);
		bufferResultado.valor = subtracao(bufferResultado.valor, juntarHILO(bancoRegistradores[HI].valor, bancoRegistradores[LO].valor));
		escrita_bar(in, barEW);
		excluirElem(listaExecucao, in.posicao);
		break;
	case MUL:
		bufferRegistradores[in.s2_instrucao.rd].valor = multiplicacao(bancoRegistradores[in.s2_instrucao.rs].valor, bancoRegistradores[in.s2_instrucao.rt].valor);
		escrita_bar(in, barEW);
		excluirElem(listaExecucao, in.posicao);
		break;
	case ADDI:
		bufferRegistradores[in.i_instrucao.rt].valor = adicao(bancoRegistradores[in.i_instrucao.rs].valor, in.i_instrucao.imediato);
		escrita_bar(in, barEW);
		excluirElem(listaExecucao, in.posicao);
		break;
	case ANDI:
		bufferRegistradores[in.s_instrucao.rt].valor = and(bancoRegistradores[in.s_instrucao.rs].valor, in.i_instrucao.imediato);
		escrita_bar(in, barEW);
		excluirElem(listaExecucao, in.posicao);
		break;
	case B:
		PC += in.i_instrucao.imediato;
		escrita_bar(in, barEW);
		excluirElem(listaExecucao, in.posicao);
		break;
	case BEQ:
		if (igual(bancoRegistradores[in.i_instrucao.rs].valor, bancoRegistradores[in.i_instrucao.rt].valor))
			PC += in.i_instrucao.imediato;
		escrita_bar(in, barEW);
		excluirElem(listaExecucao, in.posicao);
		break;
	case BEQL:
		if (igual(bancoRegistradores[in.i_instrucao.rs].valor, bancoRegistradores[in.i_instrucao.rt].valor))
			PC += in.i_instrucao.imediato;
		escrita_bar(in, barEW);
		excluirElem(listaExecucao, in.posicao);
		break;
	case BGTZ:
		if (maior(bancoRegistradores[in.i_instrucao.rs].valor, 0))
			PC += in.i_instrucao.imediato;
		escrita_bar(in, barEW);
		excluirElem(listaExecucao, in.posicao);
		break;
	case BLEZ:
		if (menorIgual(bancoRegistradores[in.i_instrucao.rs].valor, 0))
			PC += in.i_instrucao.imediato;
		escrita_bar(in, barEW);
		excluirElem(listaExecucao, in.posicao);
		break;
	case BNE:
		if (not(igual(bancoRegistradores[in.i_instrucao.rs].valor, bancoRegistradores[in.s_instrucao.rt].valor)))
			PC += in.i_instrucao.imediato;
		escrita_bar(in, barEW);
		excluirElem(listaExecucao, in.posicao);
		break;
	case LUI:
		bufferRegistradores[in.i_instrucao.rt].valor = shiftLeft(in.i_instrucao.imediato, 16);
		escrita_bar(in, barEW);
		excluirElem(listaExecucao, in.posicao);
		break;
	case ORI:
		bufferRegistradores[in.i_instrucao.rt].valor = or (bancoRegistradores[in.i_instrucao.rs].valor, in.i_instrucao.imediato);
		escrita_bar(in, barEW);
		excluirElem(listaExecucao, in.posicao);
		break;
	case XORI:
		bufferRegistradores[in.i_instrucao.rt].valor = xor(bancoRegistradores[in.i_instrucao.rs].valor, in.i_instrucao.imediato);
		escrita_bar(in, barEW);
		excluirElem(listaExecucao, in.posicao);
		break;
	case J:
		PC = in.j_instrucao.addr;
		escrita_bar(in, barEW);
		excluirElem(listaExecucao, in.posicao);
		break;
	case BGEZ:
		if (maiorIgual(bancoRegistradores[in.r_instrucao.rs].valor, 0))
			PC += in.r_instrucao.offset;
		escrita_bar(in, barEW);
		excluirElem(listaExecucao, in.posicao);
		break;
	case BLTZ:
		if (menor(bancoRegistradores[in.r_instrucao.rs].valor, 0))
			PC += in.r_instrucao.offset;
		escrita_bar(in, barEW);
		excluirElem(listaExecucao, in.posicao);
		break;
	}
}

void escritaPipeline(int reg)
{
	Inst in;
	while (verifica_bar(barEW))
	{
		in = leitura_bar(barEW);
		inserirElemLista(listaWriteB, in);
	}
	for (int i = 0; i < listaWriteB->nroElem; i++)
	{
		//bancoRegistradores[reg].valor;
		bancoRegistradores[reg].UF = semUF;
		UFINT.status.Busy = false;
		excluirElem(listaWriteB, in.posicao);
	}
}