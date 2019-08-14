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
	printf("----busca------");
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
	printf("\n-----emissao------\n");
	if (EMITIDA)
	{
		if (BI.tem_instrucao == true)
		{
			EMITIDA = false;
			printf("barramento BI: %d", BI.instrucao.opcode);
			in = leitura_bar(barBI);
			exibirLista(listaIssue);
			inserirElemLista(listaIssue, in);
			//printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
			exibirLista(listaIssue);
		}
	}
	if (!EMITIDA)
	{
		in = listaIssue->lista_inst[0];
		int operacao = descobrirOperacao(in);
		for (int i = 0; i < listaWriteB->nroElem; i++)
		{
			in = listaWriteB->lista_inst[i];
			if (in.posicao == -1)
			{
				continue;
			}
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
						printf("\nADD\n");
						printf("barramento IR opcode: %d\n", IR.instrucao.opcode);
						printf("barramento IR RS: %d\n", IR.instrucao.s_instrucao.rd);
						printf("barramento IR RT: %d\n", IR.instrucao.s_instrucao.rs);
						printf("barramento IR IMM: %d\n", IR.instrucao.s_instrucao.rt);
						exibirLista(listaIssue);
						printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
						excluirElem(listaIssue, 0);
						exibirLista(listaIssue);
						printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
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
						UFINT.status.Fj = semREG;
						UFINT.status.Fk = semREG;
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
						UFINT.status.Fj = semREG;
						UFINT.status.Fk = semREG;
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
				if (bancoRegistradores[HI].UF == semUF)
				{
					UFINT.status.Busy = true;
					UFINT.status.Op = MTHI;
					UFINT.status.Fi = HI;
					UFINT.status.Fj = in.s_instrucao.rs;
					UFINT.status.Fk = semREG;
					UFINT.status.Qj = bancoRegistradores[in.s_instrucao.rs].UF;
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
			case MTLO:
				if (!UFINT.status.Busy)
				{
					if (bancoRegistradores[LO].UF == semUF)
					{
						UFINT.status.Busy = true;
						UFINT.status.Op = MTLO;
						UFINT.status.Fi = LO;
						UFINT.status.Fj = in.s_instrucao.rs;
						UFINT.status.Fk = semREG;
						UFINT.status.Qj = bancoRegistradores[in.s_instrucao.rs].UF;
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
			case MULT:
				if (!UFMUL1.status.Busy)
				{
					if (bancoRegistradores[HI].UF == semUF)
					{
						UFMUL1.status.Busy = true;
						UFMUL1.status.Op = MULT;
						UFMUL1.status.Fi = HI;
						UFMUL1.status.Fj = in.s_instrucao.rs;
						UFMUL1.status.Fk = in.s_instrucao.rt;
						UFMUL1.status.Qj = bancoRegistradores[in.s_instrucao.rs].UF;
						UFMUL1.status.Qk = bancoRegistradores[in.s_instrucao.rt].UF;
						UFMUL1.status.Rj = (bancoRegistradores[in.s_instrucao.rs].UF == semUF) ? true : false;
						UFMUL1.status.Rk = (bancoRegistradores[in.s_instrucao.rt].UF == semUF) ? true : false;
						bancoRegistradores[HI].UF = UF_INT;
						in.UF = UF_MUL1;
						escrita_bar(in, barIR);
						excluirElem(listaIssue, 0);
						EMITIDA = true;
					}
				}
				if (!UFMUL2.status.Busy)
				{
					if (bancoRegistradores[HI].UF == semUF)
					{
						UFMUL2.status.Busy = true;
						UFMUL2.status.Op = MULT;
						UFMUL2.status.Fi = HI;
						UFMUL2.status.Fj = in.s_instrucao.rs;
						UFMUL2.status.Fk = in.s_instrucao.rt;
						UFMUL2.status.Qj = bancoRegistradores[in.s_instrucao.rs].UF;
						UFMUL2.status.Qk = bancoRegistradores[in.s_instrucao.rt].UF;
						UFMUL2.status.Rj = (bancoRegistradores[in.s_instrucao.rs].UF == semUF) ? true : false;
						UFMUL2.status.Rk = (bancoRegistradores[in.s_instrucao.rt].UF == semUF) ? true : false;
						bancoRegistradores[HI].UF = UF_INT;
						in.UF = UF_MUL2;
						escrita_bar(in, barIR);
						excluirElem(listaIssue, 0);
						EMITIDA = true;
					}
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
					if ((bancoRegistradores[HI].UF == semUF) && (bancoRegistradores[LO].UF == semUF))
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
						bancoRegistradores[LO].UF = UF_INT;
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
					if ((bancoRegistradores[HI].UF == semUF) && (bancoRegistradores[LO].UF == semUF))
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
						printf("\nMUL\n");
						printf("barramento IR opcode: %d\n", IR.instrucao.opcode);
						printf("barramento IR RS: %d\n", IR.instrucao.s2_instrucao.rd);
						printf("barramento IR RT: %d\n", IR.instrucao.s2_instrucao.rs);
						printf("barramento IR IMM: %d\n", IR.instrucao.s2_instrucao.rt);
						exibirLista(listaIssue);
						printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
						excluirElem(listaIssue, 0);
						exibirLista(listaIssue);
						printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
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
						printf("\nMUL\n");
						printf("barramento IR opcode: %d\n", IR.instrucao.opcode);
						printf("barramento IR RS: %d\n", IR.instrucao.s2_instrucao.rd);
						printf("barramento IR RT: %d\n", IR.instrucao.s2_instrucao.rs);
						printf("barramento IR IMM: %d\n", IR.instrucao.s2_instrucao.rt);
						exibirLista(listaIssue);
						printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
						excluirElem(listaIssue, 0);
						exibirLista(listaIssue);
						printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
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
						printf("\nADDI\n");
						printf("barramento IR opcode: %d\n", IR.instrucao.opcode);
						printf("barramento IR RS: %d\n", IR.instrucao.i_instrucao.rs);
						printf("barramento IR RT: %d\n", IR.instrucao.i_instrucao.rt);
						printf("barramento IR IMM: %d\n", IR.instrucao.i_instrucao.imediato);
						exibirLista(listaIssue);
						printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
						excluirElem(listaIssue, 0);
						exibirLista(listaIssue);
						printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
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
						printf("\nANDI\n");
						printf("barramento IR opcode: %d\n", IR.instrucao.opcode);
						printf("barramento IR RS: %d\n", IR.instrucao.i_instrucao.rs);
						printf("barramento IR RT: %d\n", IR.instrucao.i_instrucao.rt);
						printf("barramento IR IMM: %d\n", IR.instrucao.i_instrucao.imediato);
						exibirLista(listaIssue);
						printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
						excluirElem(listaIssue, 0);
						exibirLista(listaIssue);
						printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
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
					UFINT.status.Fj = semREG;
					UFINT.status.Fk = semREG;
					UFINT.status.Qj = semUF;
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
				if (!UFINT.status.Busy) //não sei oq colocar, rt e imediato ou rs e rt??
				{
					UFINT.status.Busy = true;
					UFINT.status.Op = BEQ;
					UFINT.status.Fi = semREG;
					UFINT.status.Fj = in.i_instrucao.rs;
					UFINT.status.Fk = in.i_instrucao.rt;
					UFINT.status.Qj = bancoRegistradores[in.i_instrucao.rt].UF;
					UFINT.status.Qk = bancoRegistradores[in.i_instrucao.imediato].UF;
					UFINT.status.Rj = (bancoRegistradores[in.i_instrucao.rt].UF == semUF) ? true : false;
					UFINT.status.Rk = (bancoRegistradores[in.i_instrucao.imediato].UF == semUF) ? true : false;
					in.UF = UF_INT;
					escrita_bar(in, barIR);
					excluirElem(listaIssue, 0);
					EMITIDA = true;
				}
				break;
			case BEQL:
				if (!UFINT.status.Busy)
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
					in.UF = UF_INT;
					escrita_bar(in, barIR);
					excluirElem(listaIssue, 0);
					EMITIDA = true;
				}
				break;
			case BGTZ: //ver se ta certo
				if (!UFINT.status.Busy)
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
					in.UF = UF_INT;
					escrita_bar(in, barIR);
					excluirElem(listaIssue, 0);
					EMITIDA = true;
				}
				break;
			case BLEZ: //ver se ta certo
				if (!UFINT.status.Busy)
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
					in.UF = UF_INT;
					escrita_bar(in, barIR);
					excluirElem(listaIssue, 0);
					EMITIDA = true;
				}
				break;
			case BNE:
				if (!UFINT.status.Busy)
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
					in.UF = UF_INT;
					escrita_bar(in, barIR);
					excluirElem(listaIssue, 0);
					EMITIDA = true;
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
}

void leitura()
{
	printf("\n----leitura------\n");
	if (verifica_bar(barIR))
	{
		in = leitura_bar(barIR);
		inserirElemLista(listaRead, IR.instrucao);
		printf("\nBarramento IR: %d\n", IR.instrucao.opcode);
	}
	for (int i = 0; i < listaRead->nroElem; i++)
	{
		in = listaRead->lista_inst[i];
		if (in.posicao == -1)
		{
			continue;
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
						printf("barramento RE: %d\n", RE->instrucao.opcode);
						printf("posição na lista read: %d\n", listaRead->lista_inst[in.posicao].posicao);
						exibirLista(listaRead);
						excluirElem(listaRead, in.posicao);
						printf("posição na lista read: %d\n", listaRead->lista_inst[in.posicao].posicao);
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
}

void execucao()
//etapa de execução
{
	printf("\n----execucao------\n");
	while (verifica_bar(barRE))
	{
		in = leitura_bar(barRE);
		printf("barramento RE: %d", RE->instrucao.opcode);
		inserirElemLista(listaExecucao, in);
		printf("elemento na lista execução: %d", listaExecucao->lista_inst[in.posicao].posicao);
		exibirLista(listaExecucao);
	}
	for (int i = 0; i < listaExecucao->nroElem; i++)
	{
		in = listaExecucao->lista_inst[i];
		if (in.posicao == -1)
		{
			continue;
		}
		int operacao = descobrirOperacao(in);
		int registrador;
		switch (operacao)
		{
		case ADD:
			bufferRegistradores[in.s_instrucao.rd].valor = adicao(bancoRegistradores[in.s_instrucao.rs].valor, bancoRegistradores[in.s_instrucao.rt].valor);
			printf("ADD opcode: %d\n", in.opcode);
			printf("ADD RS: %d\n", in.s_instrucao.rs);
			printf("ADD RT: %d\n", in.s_instrucao.rt);
			printf("ADD IMM: %d\n", in.s_instrucao.rd);
			printf("ADD IMM: %d\n", in.s_instrucao.shamt);
			printf("ADD IMM: %d\n", in.s_instrucao.func);
			printf("resultado ADD: %d\n", bufferRegistradores[in.i_instrucao.rt].valor);
			escrita_bar(in, barEW);
			printf("barramento EW: %d\n", EW->instrucao.opcode);
			exibirLista(listaExecucao);
			printf("elemento na lista execução dentro do int: %d", listaExecucao->lista_inst[in.posicao].posicao);
			excluirElem(listaExecucao, in.posicao);
			printf("elemento na lista execução: %d", listaExecucao->lista_inst[in.posicao].posicao);
			break;
		case AND:
			bufferRegistradores[in.s_instrucao.rd].valor = and(bancoRegistradores[in.s_instrucao.rs].valor, bancoRegistradores[in.s_instrucao.rt].valor);
			printf("AND opcode: %d\n", in.opcode);
			printf("AND RS: %d\n", in.s_instrucao.rs);
			printf("AND RT: %d\n", in.s_instrucao.rt);
			printf("AND IMM: %d\n", in.s_instrucao.rd);
			printf("AND IMM: %d\n", in.s_instrucao.shamt);
			printf("AND IMM: %d\n", in.s_instrucao.func);
			printf("resultado AND: %d\n", bufferRegistradores[in.i_instrucao.rt].valor);
			escrita_bar(in, barEW);
			printf("barramento EW: %d\n", EW->instrucao.opcode);
			exibirLista(listaExecucao);
			printf("elemento na lista execução dentro do int: %d", listaExecucao->lista_inst[in.posicao].posicao);
			excluirElem(listaExecucao, in.posicao);
			printf("elemento na lista execução: %d", listaExecucao->lista_inst[in.posicao].posicao);
			break;
		case DIV:
			separarHILO(divisao(bancoRegistradores[in.s_instrucao.rs].valor, bancoRegistradores[in.s_instrucao.rt].valor));
			printf("DIV opcode: %d\n", in.opcode);
			printf("DIV RS: %d\n", in.s_instrucao.rs);
			printf("DIV RT: %d\n", in.s_instrucao.rt);
			printf("DIV IMM: %d\n", in.s_instrucao.rd);
			printf("DIV IMM: %d\n", in.s_instrucao.shamt);
			printf("DIV IMM: %d\n", in.s_instrucao.func);
			printf("resultado DIV: %d\n", bufferRegistradores[in.i_instrucao.rt].valor);
			escrita_bar(in, barEW);
			printf("barramento EW: %d\n", EW->instrucao.opcode);
			exibirLista(listaExecucao);
			printf("elemento na lista execução dentro do divisao: %d", listaExecucao->lista_inst[in.posicao].posicao);
			excluirElem(listaExecucao, in.posicao);
			printf("elemento na lista execução: %d", listaExecucao->lista_inst[in.posicao].posicao);
			break;
		case JR:
			PC = bancoRegistradores[in.s_instrucao.rs].valor;
			printf("JR opcode: %d\n", in.opcode);
			printf("JR RS: %d\n", in.s_instrucao.rs);
			printf("JR RT: %d\n", in.s_instrucao.rt);
			printf("JR IMM: %d\n", in.s_instrucao.rd);
			printf("JR IMM: %d\n", in.s_instrucao.shamt);
			printf("JR IMM: %d\n", in.s_instrucao.func);
			printf("resultado JR: %d\n", bufferRegistradores[in.i_instrucao.rt].valor);
			escrita_bar(in, barEW);
			printf("barramento EW: %d\n", EW->instrucao.opcode);
			exibirLista(listaExecucao);
			printf("elemento na lista execução dentro do int: %d", listaExecucao->lista_inst[in.posicao].posicao);
			excluirElem(listaExecucao, in.posicao);
			printf("elemento na lista execução: %d", listaExecucao->lista_inst[in.posicao].posicao);
			break;
		case MFHI:
			bufferRegistradores[in.s_instrucao.rd].valor = bancoRegistradores[HI].valor;
			printf("MFHI opcode: %d\n", in.opcode);
			printf("MFHI RS: %d\n", in.s_instrucao.rs);
			printf("MFHI RT: %d\n", in.s_instrucao.rt);
			printf("MFHI IMM: %d\n", in.s_instrucao.rd);
			printf("MFHI IMM: %d\n", in.s_instrucao.shamt);
			printf("MFHI IMM: %d\n", in.s_instrucao.func);
			printf("resultado MFHI: %d\n", bufferRegistradores[in.i_instrucao.rt].valor);
			escrita_bar(in, barEW);
			printf("barramento EW: %d\n", EW->instrucao.opcode);
			exibirLista(listaExecucao);
			printf("elemento na lista execução dentro do int: %d", listaExecucao->lista_inst[in.posicao].posicao);
			excluirElem(listaExecucao, in.posicao);
			printf("elemento na lista execução: %d", listaExecucao->lista_inst[in.posicao].posicao);
			break;
		case MFLO:
			bufferRegistradores[in.s_instrucao.rd].valor = bancoRegistradores[LO].valor;
			printf("MFLO opcode: %d\n", in.opcode);
			printf("MFLO RS: %d\n", in.s_instrucao.rs);
			printf("MFLO RT: %d\n", in.s_instrucao.rt);
			printf("MFLO IMM: %d\n", in.s_instrucao.rd);
			printf("MFLO IMM: %d\n", in.s_instrucao.shamt);
			printf("MFLO IMM: %d\n", in.s_instrucao.func);
			printf("resultado MFLO: %d\n", bufferRegistradores[in.i_instrucao.rt].valor);
			escrita_bar(in, barEW);
			printf("barramento EW: %d\n", EW->instrucao.opcode);
			exibirLista(listaExecucao);
			printf("elemento na lista execução dentro do int: %d", listaExecucao->lista_inst[in.posicao].posicao);
			excluirElem(listaExecucao, in.posicao);
			printf("elemento na lista execução: %d", listaExecucao->lista_inst[in.posicao].posicao);
			break;
		case MOVN:
			if (not(igual(bancoRegistradores[in.s_instrucao.rt].valor, 0)))
				bufferRegistradores[in.s_instrucao.rd].valor = bancoRegistradores[in.s_instrucao.rs].valor;
			printf("MOVN opcode: %d\n", in.opcode);
			printf("MOVN RS: %d\n", in.s_instrucao.rs);
			printf("MOVN RT: %d\n", in.s_instrucao.rt);
			printf("MOVN IMM: %d\n", in.s_instrucao.rd);
			printf("MOVN IMM: %d\n", in.s_instrucao.shamt);
			printf("MOVN IMM: %d\n", in.s_instrucao.func);
			printf("resultado MOVN: %d\n", bufferRegistradores[in.i_instrucao.rt].valor);
			escrita_bar(in, barEW);
			printf("barramento EW: %d\n", EW->instrucao.opcode);
			exibirLista(listaExecucao);
			printf("elemento na lista execução dentro do int: %d", listaExecucao->lista_inst[in.posicao].posicao);
			excluirElem(listaExecucao, in.posicao);
			printf("elemento na lista execução: %d", listaExecucao->lista_inst[in.posicao].posicao);
			break;
		case MOVZ:
			if (igual(bancoRegistradores[in.s_instrucao.rt].valor, 0))
				bufferRegistradores[in.s_instrucao.rd].valor = bancoRegistradores[in.s_instrucao.rs].valor;
			printf("MOVZ opcode: %d\n", in.opcode);
			printf("MOVZ RS: %d\n", in.s_instrucao.rs);
			printf("MOVZ RT: %d\n", in.s_instrucao.rt);
			printf("MOVZ IMM: %d\n", in.s_instrucao.rd);
			printf("MOVZ IMM: %d\n", in.s_instrucao.shamt);
			printf("MOVZ IMM: %d\n", in.s_instrucao.func);
			printf("resultado MOVZ: %d\n", bufferRegistradores[in.i_instrucao.rt].valor);
			escrita_bar(in, barEW);
			printf("barramento EW: %d\n", EW->instrucao.opcode);
			exibirLista(listaExecucao);
			printf("elemento na lista execução dentro do int: %d", listaExecucao->lista_inst[in.posicao].posicao);
			excluirElem(listaExecucao, in.posicao);
			printf("elemento na lista execução: %d", listaExecucao->lista_inst[in.posicao].posicao);
			break;
		case MTHI: //ver isso
			bufferRegistradores[HI].valor = bancoRegistradores[in.s_instrucao.rs].valor;
			printf("MTHI opcode: %d\n", in.opcode);
			printf("MTHI RS: %d\n", in.s_instrucao.rs);
			printf("MTHI RT: %d\n", in.s_instrucao.rt);
			printf("MTHI IMM: %d\n", in.s_instrucao.rd);
			printf("MTHI IMM: %d\n", in.s_instrucao.shamt);
			printf("MTHI IMM: %d\n", in.s_instrucao.func);
			printf("resultado MTHI: %d\n", bufferRegistradores[in.i_instrucao.rt].valor);
			escrita_bar(in, barEW);
			printf("barramento EW: %d\n", EW->instrucao.opcode);
			exibirLista(listaExecucao);
			printf("elemento na lista execução dentro do int: %d", listaExecucao->lista_inst[in.posicao].posicao);
			excluirElem(listaExecucao, in.posicao);
			printf("elemento na lista execução: %d", listaExecucao->lista_inst[in.posicao].posicao);
			break;
		case MTLO:
			bufferRegistradores[LO].valor = bancoRegistradores[in.s_instrucao.rs].valor;
			printf("MTLO opcode: %d\n", in.opcode);
			printf("MTLO RS: %d\n", in.s_instrucao.rs);
			printf("MTLO RT: %d\n", in.s_instrucao.rt);
			printf("MTLO IMM: %d\n", in.s_instrucao.rd);
			printf("MTLO IMM: %d\n", in.s_instrucao.shamt);
			printf("MTLO IMM: %d\n", in.s_instrucao.func);
			printf("resultado MTLO: %d\n", bufferRegistradores[in.i_instrucao.rt].valor);
			escrita_bar(in, barEW);
			printf("barramento EW: %d\n", EW->instrucao.opcode);
			exibirLista(listaExecucao);
			printf("elemento na lista execução dentro do int: %d", listaExecucao->lista_inst[in.posicao].posicao);
			excluirElem(listaExecucao, in.posicao);
			printf("elemento na lista execução: %d", listaExecucao->lista_inst[in.posicao].posicao);
			break;
		case MULT:
			separarHILO(multiplicacao(bancoRegistradores[in.s_instrucao.rs].valor, bancoRegistradores[in.s_instrucao.rt].valor));
			printf("MULT opcode: %d\n", in.opcode);
			printf("MULT RS: %d\n", in.s_instrucao.rs);
			printf("MULT RT: %d\n", in.s_instrucao.rt);
			printf("MULT IMM: %d\n", in.s_instrucao.rd);
			printf("MULT IMM: %d\n", in.s_instrucao.shamt);
			printf("MULT IMM: %d\n", in.s_instrucao.func);
			printf("resultado MULT: %d\n", bufferRegistradores[in.i_instrucao.rt].valor);
			escrita_bar(in, barEW);
			printf("barramento EW: %d\n", EW->instrucao.opcode);
			exibirLista(listaExecucao);
			printf("elemento na lista execução dentro do mul: %d", listaExecucao->lista_inst[in.posicao].posicao);
			excluirElem(listaExecucao, in.posicao);
			printf("elemento na lista execução: %d", listaExecucao->lista_inst[in.posicao].posicao);
			break;
			break;
		case NOP:
			// nao faz nada por enquanto (no operation)//
			break;
		case NOR:
			bufferRegistradores[in.s_instrucao.rd].valor = nor(bancoRegistradores[in.s_instrucao.rs].valor, bancoRegistradores[in.s_instrucao.rt].valor);
			printf("NOR opcode: %d\n", in.opcode);
			printf("NOR RS: %d\n", in.s_instrucao.rs);
			printf("NOR RT: %d\n", in.s_instrucao.rt);
			printf("NOR IMM: %d\n", in.s_instrucao.rd);
			printf("NOR IMM: %d\n", in.s_instrucao.shamt);
			printf("NOR IMM: %d\n", in.s_instrucao.func);
			printf("resultado NOR: %d\n", bufferRegistradores[in.i_instrucao.rt].valor);
			escrita_bar(in, barEW);
			printf("barramento EW: %d\n", EW->instrucao.opcode);
			exibirLista(listaExecucao);
			printf("elemento na lista execução dentro do int: %d", listaExecucao->lista_inst[in.posicao].posicao);
			excluirElem(listaExecucao, in.posicao);
			printf("elemento na lista execução: %d", listaExecucao->lista_inst[in.posicao].posicao);
			break;
		case OR:
			bufferRegistradores[in.s_instrucao.rd].valor = or (bancoRegistradores[in.s_instrucao.rs].valor, bancoRegistradores[in.s_instrucao.rt].valor);
			printf("OR opcode: %d\n", in.opcode);
			printf("OR RS: %d\n", in.s_instrucao.rs);
			printf("OR RT: %d\n", in.s_instrucao.rt);
			printf("OR IMM: %d\n", in.s_instrucao.rd);
			printf("OR IMM: %d\n", in.s_instrucao.shamt);
			printf("OR IMM: %d\n", in.s_instrucao.func);
			printf("resultado OR: %d\n", bufferRegistradores[in.i_instrucao.rt].valor);
			escrita_bar(in, barEW);
			printf("barramento EW: %d\n", EW->instrucao.opcode);
			exibirLista(listaExecucao);
			printf("elemento na lista execução dentro do int: %d", listaExecucao->lista_inst[in.posicao].posicao);
			excluirElem(listaExecucao, in.posicao);
			printf("elemento na lista execução: %d", listaExecucao->lista_inst[in.posicao].posicao);
			break;
		case SUB:
			bufferRegistradores[in.s_instrucao.rd].valor = subtracao(bancoRegistradores[in.s_instrucao.rs].valor, bancoRegistradores[in.s_instrucao.rt].valor);
			printf("SUB opcode: %d\n", in.opcode);
			printf("SUB RS: %d\n", in.s_instrucao.rs);
			printf("SUB RT: %d\n", in.s_instrucao.rt);
			printf("SUB IMM: %d\n", in.s_instrucao.rd);
			printf("SUB IMM: %d\n", in.s_instrucao.shamt);
			printf("SUB IMM: %d\n", in.s_instrucao.func);
			printf("resultado SUB: %d\n", bufferRegistradores[in.i_instrucao.rt].valor);
			escrita_bar(in, barEW);
			printf("barramento EW: %d\n", EW->instrucao.opcode);
			exibirLista(listaExecucao);
			printf("elemento na lista execução dentro do int: %d", listaExecucao->lista_inst[in.posicao].posicao);
			excluirElem(listaExecucao, in.posicao);
			printf("elemento na lista execução: %d", listaExecucao->lista_inst[in.posicao].posicao);
			break;
		case XOR:
			bufferRegistradores[in.s_instrucao.rd].valor = xor(bancoRegistradores[in.s_instrucao.rs].valor, bancoRegistradores[in.s_instrucao.rt].valor);
			printf("XOR opcode: %d\n", in.opcode);
			printf("XOR RS: %d\n", in.s_instrucao.rs);
			printf("XOR RT: %d\n", in.s_instrucao.rt);
			printf("XOR IMM: %d\n", in.s_instrucao.rd);
			printf("XOR IMM: %d\n", in.s_instrucao.shamt);
			printf("XOR IMM: %d\n", in.s_instrucao.func);
			printf("resultado XOR: %d\n", bufferRegistradores[in.i_instrucao.rt].valor);
			escrita_bar(in, barEW);
			printf("barramento EW: %d\n", EW->instrucao.opcode);
			exibirLista(listaExecucao);
			printf("elemento na lista execução dentro do int: %d", listaExecucao->lista_inst[in.posicao].posicao);
			excluirElem(listaExecucao, in.posicao);
			printf("elemento na lista execução: %d", listaExecucao->lista_inst[in.posicao].posicao);
			break;
		case MADD: //MAIS SIG SOMA PRO HI E 16 MENOS SOMA PRO LO
			bufferRegistradores[in.s2_instrucao.rd].valor = multiplicacao(bancoRegistradores[in.s2_instrucao.rs].valor, bancoRegistradores[in.s2_instrucao.rt].valor);
			bufferRegistradores[HI].valor = adicao(bufferRegistradores[in.s2_instrucao.rd].valor >> 16, bancoRegistradores[HI].valor);
			//fazer o msm pro lo
			printf("MADD opcode: %d\n", in.opcode);
			printf("MADD RS: %d\n", in.s2_instrucao.rs);
			printf("MADD RT: %d\n", in.s2_instrucao.rt);
			printf("MADD IMM: %d\n", in.s2_instrucao.rd);
			printf("MADD IMM: %d\n", in.s2_instrucao.shamt);
			printf("MADD IMM: %d\n", in.s2_instrucao.func);
			printf("resultado MADD: %d\n", bufferRegistradores[in.i_instrucao.rt].valor);
			escrita_bar(in, barEW);
			printf("barramento EW: %d\n", EW->instrucao.opcode);
			exibirLista(listaExecucao);
			printf("elemento na lista execução dentro do int: %d", listaExecucao->lista_inst[in.posicao].posicao);
			excluirElem(listaExecucao, in.posicao);
			printf("elemento na lista execução: %d", listaExecucao->lista_inst[in.posicao].posicao);
			break;
		case MSUB:
			bancoRegistradores[in.s2_instrucao.rd].valor = multiplicacao(bancoRegistradores[in.s2_instrucao.rs].valor, bancoRegistradores[in.s2_instrucao.rt].valor);
			bufferResultado.valor = subtracao(bufferResultado.valor, juntarHILO(bancoRegistradores[HI].valor, bancoRegistradores[LO].valor));
			printf("MSUB opcode: %d\n", in.opcode);
			printf("MSUB RS: %d\n", in.s2_instrucao.rs);
			printf("MSUB RT: %d\n", in.s2_instrucao.rt);
			printf("MSUB IMM: %d\n", in.s2_instrucao.rd);
			printf("MSUB IMM: %d\n", in.s2_instrucao.shamt);
			printf("MSUB IMM: %d\n", in.s2_instrucao.func);
			printf("resultado MSUB: %d\n", bufferRegistradores[in.i_instrucao.rt].valor);
			escrita_bar(in, barEW);
			printf("barramento EW: %d\n", EW->instrucao.opcode);
			exibirLista(listaExecucao);
			printf("elemento na lista execução dentro do int: %d", listaExecucao->lista_inst[in.posicao].posicao);
			excluirElem(listaExecucao, in.posicao);
			printf("elemento na lista execução: %d", listaExecucao->lista_inst[in.posicao].posicao);
			break;
		case MUL:
			bufferRegistradores[in.s2_instrucao.rd].valor = multiplicacao(bancoRegistradores[in.s2_instrucao.rs].valor, bancoRegistradores[in.s2_instrucao.rt].valor);
			printf("MUL opcode: %d\n", in.opcode);
			printf("MUL RS: %d\n", in.s2_instrucao.rs);
			printf("MUL RT: %d\n", in.s2_instrucao.rt);
			printf("MUL IMM: %d\n", in.s2_instrucao.rd);
			printf("MUL IMM: %d\n", in.s2_instrucao.shamt);
			printf("MUL IMM: %d\n", in.s2_instrucao.func);
			printf("resultado MUL: %d\n", bufferRegistradores[in.i_instrucao.rt].valor);
			escrita_bar(in, barEW);
			printf("barramento EW: %d\n", EW->instrucao.opcode);
			exibirLista(listaExecucao);
			printf("elemento na lista execução dentro do mul: %d", listaExecucao->lista_inst[in.posicao].posicao);
			excluirElem(listaExecucao, in.posicao);
			printf("elemento na lista execução: %d", listaExecucao->lista_inst[in.posicao].posicao);
			break;
		case ADDI:
			bufferRegistradores[in.i_instrucao.rt].valor = adicao(bancoRegistradores[in.i_instrucao.rs].valor, in.i_instrucao.imediato);
			printf("ADDI opcode: %d\n", in.opcode);
			printf("ADDI RS: %d\n", in.i_instrucao.rs);
			printf("ADDI RT: %d\n", in.i_instrucao.rt);
			printf("ADDI IMM: %d\n", in.i_instrucao.imediato);
			printf("resultado ADDI: %d\n", bufferRegistradores[in.i_instrucao.rt].valor);
			escrita_bar(in, barEW);
			printf("barramento EW: %d\n", EW->instrucao.opcode);
			exibirLista(listaExecucao);
			printf("elemento na lista execução dentro do add: %d", listaExecucao->lista_inst[in.posicao].posicao);
			excluirElem(listaExecucao, in.posicao);
			printf("elemento na lista execução: %d", listaExecucao->lista_inst[in.posicao].posicao);
			break;
		case ANDI:
			bufferRegistradores[in.s_instrucao.rt].valor = and(bancoRegistradores[in.s_instrucao.rs].valor, in.i_instrucao.imediato);
			printf("ANDI opcode: %d\n", in.opcode);
			printf("ANDI RS: %d\n", in.i_instrucao.rs);
			printf("ANDI RT: %d\n", in.i_instrucao.rt);
			printf("ANDI IMM: %d\n", in.i_instrucao.imediato);
			printf("resultado ANDI: %d\n", bufferRegistradores[in.i_instrucao.rt].valor);
			escrita_bar(in, barEW);
			printf("barramento EW: %d\n", EW->instrucao.opcode);
			exibirLista(listaExecucao);
			printf("elemento na lista execução dentro do int: %d", listaExecucao->lista_inst[in.posicao].posicao);
			excluirElem(listaExecucao, in.posicao);
			printf("elemento na lista execução: %d", listaExecucao->lista_inst[in.posicao].posicao);
			break;
		case B:
			PC += in.i_instrucao.imediato;
			printf("B opcode: %d\n", in.opcode);
			printf("B RS: %d\n", in.i_instrucao.rs);
			printf("B RT: %d\n", in.i_instrucao.rt);
			printf("B IMM: %d\n", in.i_instrucao.imediato);
			printf("resultado B: %d\n", bufferRegistradores[in.i_instrucao.rt].valor);
			escrita_bar(in, barEW);
			printf("barramento EW: %d\n", EW->instrucao.opcode);
			exibirLista(listaExecucao);
			printf("elemento na lista execução dentro do int: %d", listaExecucao->lista_inst[in.posicao].posicao);
			excluirElem(listaExecucao, in.posicao);
			printf("elemento na lista execução: %d", listaExecucao->lista_inst[in.posicao].posicao);
			break;
		case BEQ:
			if (igual(bancoRegistradores[in.i_instrucao.rs].valor, bancoRegistradores[in.i_instrucao.rt].valor))
				PC += in.i_instrucao.imediato;
			printf("BEQ opcode: %d\n", in.opcode);
			printf("BEQ RS: %d\n", in.i_instrucao.rs);
			printf("BEQ RT: %d\n", in.i_instrucao.rt);
			printf("BEQ IMM: %d\n", in.i_instrucao.imediato);
			printf("resultado BEQ: %d\n", bufferRegistradores[in.i_instrucao.rt].valor);
			escrita_bar(in, barEW);
			printf("barramento EW: %d\n", EW->instrucao.opcode);
			exibirLista(listaExecucao);
			printf("elemento na lista execução dentro do int: %d", listaExecucao->lista_inst[in.posicao].posicao);
			excluirElem(listaExecucao, in.posicao);
			printf("elemento na lista execução: %d", listaExecucao->lista_inst[in.posicao].posicao);
			break;
		case BEQL:
			if (igual(bancoRegistradores[in.i_instrucao.rs].valor, bancoRegistradores[in.i_instrucao.rt].valor))
				PC += in.i_instrucao.imediato;
			printf("BEQL opcode: %d\n", in.opcode);
			printf("BEQL RS: %d\n", in.i_instrucao.rs);
			printf("BEQL RT: %d\n", in.i_instrucao.rt);
			printf("BEQL IMM: %d\n", in.i_instrucao.imediato);
			printf("resultado BEQL: %d\n", bufferRegistradores[in.i_instrucao.rt].valor);
			escrita_bar(in, barEW);
			printf("barramento EW: %d\n", EW->instrucao.opcode);
			exibirLista(listaExecucao);
			printf("elemento na lista execução dentro do int: %d", listaExecucao->lista_inst[in.posicao].posicao);
			excluirElem(listaExecucao, in.posicao);
			printf("elemento na lista execução: %d", listaExecucao->lista_inst[in.posicao].posicao);
			break;
		case BGTZ: //ta certo??
			if (maior(bancoRegistradores[in.i_instrucao.rs].valor, 0))
				PC += in.i_instrucao.imediato;
			printf("BGTZ opcode: %d\n", in.opcode);
			printf("BGTZ RS: %d\n", in.i_instrucao.rs);
			printf("BGTZ RT: %d\n", in.i_instrucao.rt);
			printf("BGTZ IMM: %d\n", in.i_instrucao.imediato);
			printf("resultado BGTZ: %d\n", bufferRegistradores[in.i_instrucao.rt].valor);
			escrita_bar(in, barEW);
			printf("barramento EW: %d\n", EW->instrucao.opcode);
			exibirLista(listaExecucao);
			printf("elemento na lista execução dentro do int: %d", listaExecucao->lista_inst[in.posicao].posicao);
			excluirElem(listaExecucao, in.posicao);
			printf("elemento na lista execução: %d", listaExecucao->lista_inst[in.posicao].posicao);
			break;
		case BLEZ:
			if (menorIgual(bancoRegistradores[in.i_instrucao.rs].valor, 0))
				PC += in.i_instrucao.imediato;
			printf("BLEZ opcode: %d\n", in.opcode);
			printf("BLEZ RS: %d\n", in.i_instrucao.rs);
			printf("BLEZ RT: %d\n", in.i_instrucao.rt);
			printf("BLEZ IMM: %d\n", in.i_instrucao.imediato);
			printf("resultado BLEZ: %d\n", bufferRegistradores[in.i_instrucao.rt].valor);
			escrita_bar(in, barEW);
			printf("barramento EW: %d\n", EW->instrucao.opcode);
			exibirLista(listaExecucao);
			printf("elemento na lista execução dentro do int: %d", listaExecucao->lista_inst[in.posicao].posicao);
			excluirElem(listaExecucao, in.posicao);
			printf("elemento na lista execução: %d", listaExecucao->lista_inst[in.posicao].posicao);
			break;
		case BNE:
			if (not(igual(bancoRegistradores[in.i_instrucao.rs].valor, bancoRegistradores[in.s_instrucao.rt].valor)))
				PC += in.i_instrucao.imediato;
			printf("BNE opcode: %d\n", in.opcode);
			printf("BNE RS: %d\n", in.i_instrucao.rs);
			printf("BNE RT: %d\n", in.i_instrucao.rt);
			printf("BNE IMM: %d\n", in.i_instrucao.imediato);
			printf("resultado BNE: %d\n", bufferRegistradores[in.i_instrucao.rt].valor);
			escrita_bar(in, barEW);
			printf("barramento EW: %d\n", EW->instrucao.opcode);
			exibirLista(listaExecucao);
			printf("elemento na lista execução dentro do int: %d", listaExecucao->lista_inst[in.posicao].posicao);
			excluirElem(listaExecucao, in.posicao);
			printf("elemento na lista execução: %d", listaExecucao->lista_inst[in.posicao].posicao);
			break;
		case LUI:
			bufferRegistradores[in.i_instrucao.rt].valor = shiftLeft(in.i_instrucao.imediato, 16);
			printf("LUI opcode: %d\n", in.opcode);
			printf("LUI RS: %d\n", in.i_instrucao.rs);
			printf("LUI RT: %d\n", in.i_instrucao.rt);
			printf("LUI IMM: %d\n", in.i_instrucao.imediato);
			printf("resultado LUI: %d\n", bufferRegistradores[in.i_instrucao.rt].valor);
			escrita_bar(in, barEW);
			printf("barramento EW: %d\n", EW->instrucao.opcode);
			exibirLista(listaExecucao);
			printf("elemento na lista execução dentro do int: %d", listaExecucao->lista_inst[in.posicao].posicao);
			excluirElem(listaExecucao, in.posicao);
			printf("elemento na lista execução: %d", listaExecucao->lista_inst[in.posicao].posicao);
			break;
		case ORI:
			bufferRegistradores[in.i_instrucao.rt].valor = or (bancoRegistradores[in.i_instrucao.rs].valor, in.i_instrucao.imediato);
			printf("ORI opcode: %d\n", in.opcode);
			printf("ORI RS: %d\n", in.i_instrucao.rs);
			printf("ORI RT: %d\n", in.i_instrucao.rt);
			printf("ORI IMM: %d\n", in.i_instrucao.imediato);
			printf("resultado ORI: %d\n", bufferRegistradores[in.i_instrucao.rt].valor);
			escrita_bar(in, barEW);
			printf("barramento EW: %d\n", EW->instrucao.opcode);
			exibirLista(listaExecucao);
			printf("elemento na lista execução dentro do int: %d", listaExecucao->lista_inst[in.posicao].posicao);
			excluirElem(listaExecucao, in.posicao);
			printf("elemento na lista execução: %d", listaExecucao->lista_inst[in.posicao].posicao);
			break;
		case XORI:
			bufferRegistradores[in.i_instrucao.rt].valor = xor(bancoRegistradores[in.i_instrucao.rs].valor, in.i_instrucao.imediato);
			printf("XORI opcode: %d\n", in.opcode);
			printf("XORI RS: %d\n", in.i_instrucao.rs);
			printf("XORI RT: %d\n", in.i_instrucao.rt);
			printf("XORI IMM: %d\n", in.i_instrucao.imediato);
			printf("resultado XORI: %d\n", bufferRegistradores[in.i_instrucao.rt].valor);
			escrita_bar(in, barEW);
			printf("barramento EW: %d\n", EW->instrucao.opcode);
			exibirLista(listaExecucao);
			printf("elemento na lista execução dentro do int: %d", listaExecucao->lista_inst[in.posicao].posicao);
			excluirElem(listaExecucao, in.posicao);
			printf("elemento na lista execução: %d", listaExecucao->lista_inst[in.posicao].posicao);
			break;
		case J:
			PC = in.j_instrucao.addr;
			printf("J opcode: %d\n", in.opcode);
			printf("J RS: %d\n", in.j_instrucao.addr);
			printf("resultado J: %d\n", bufferRegistradores[in.i_instrucao.rt].valor);
			escrita_bar(in, barEW);
			printf("barramento EW: %d\n", EW->instrucao.opcode);
			exibirLista(listaExecucao);
			printf("elemento na lista execução dentro do int: %d", listaExecucao->lista_inst[in.posicao].posicao);
			excluirElem(listaExecucao, in.posicao);
			printf("elemento na lista execução: %d", listaExecucao->lista_inst[in.posicao].posicao);
			break;
		case BGEZ:
			if (maiorIgual(bancoRegistradores[in.r_instrucao.rs].valor, 0))
				PC += in.r_instrucao.offset;
			printf("BGEZ opcode: %d\n", in.opcode);
			printf("BGEZ RS: %d\n", in.r_instrucao.rs);
			printf("BGEZ RT: %d\n", in.r_instrucao.id);
			printf("BGEZ RT: %d\n", in.r_instrucao.offset);
			printf("resultado BGEZ: %d\n", bufferRegistradores[in.i_instrucao.rt].valor);
			escrita_bar(in, barEW);
			printf("barramento EW: %d\n", EW->instrucao.opcode);
			exibirLista(listaExecucao);
			printf("elemento na lista execução dentro do int: %d", listaExecucao->lista_inst[in.posicao].posicao);
			excluirElem(listaExecucao, in.posicao);
			printf("elemento na lista execução: %d", listaExecucao->lista_inst[in.posicao].posicao);
			break;
		case BLTZ:
			if (menor(bancoRegistradores[in.r_instrucao.rs].valor, 0))
				PC += in.r_instrucao.offset;
			printf("BLTZ opcode: %d\n", in.opcode);
			printf("BLTZ RS: %d\n", in.r_instrucao.rs);
			printf("BLTZ RT: %d\n", in.r_instrucao.id);
			printf("BLTZ RT: %d\n", in.r_instrucao.offset);
			printf("resultado BLTZ: %d\n", bufferRegistradores[in.i_instrucao.rt].valor);
			escrita_bar(in, barEW);
			printf("barramento EW: %d\n", EW->instrucao.opcode);
			exibirLista(listaExecucao);
			printf("elemento na lista execução dentro do int: %d", listaExecucao->lista_inst[in.posicao].posicao);
			excluirElem(listaExecucao, in.posicao);
			printf("elemento na lista execução: %d", listaExecucao->lista_inst[in.posicao].posicao);
			break;
		}
	}
}

void escritaPipeline()
{
	printf("\n-----escrita------\n");
	while (verifica_bar(barEW))
	{
		in = leitura_bar(barEW);
		inserirElemLista(listaWriteB, in);
		exibirLista(listaWriteB);
		printf("barramento EW: %d", EW->instrucao.opcode);
	}
	for (int i = 0; i < listaWriteB->nroElem; i++)
	{
		in = listaWriteB->lista_inst[i];
		if (in.posicao == -1)
		{
			continue;
		}
		int tipo = in.opcode;
		switch (tipo)
		{
		case ESPECIAL:

			bancoRegistradores[in.s_instrucao.rd].valor = bufferRegistradores[in.s_instrucao.rd].valor;
			bancoRegistradores[in.s_instrucao.rd].UF = semUF;
			excluirElem(listaWriteB, in.posicao);
			break;
		case ESPECIAL2:
			bancoRegistradores[in.s2_instrucao.rd].valor = bufferRegistradores[in.s2_instrucao.rd].valor;
			bancoRegistradores[in.s2_instrucao.rd].UF = semUF;
			UFINT.status.Busy = false;
			excluirElem(listaWriteB, in.posicao);
			break;
		case SALTO:
			bancoRegistradores[in.j_instrucao.addr].valor = bufferRegistradores[in.j_instrucao.addr].valor;
			bancoRegistradores[in.j_instrucao.addr].UF = semUF;
			UFINT.status.Busy = false;
			excluirElem(listaWriteB, in.posicao);
			break;
		case REGIMM:
			bancoRegistradores[in.r_instrucao.rs].valor = bufferRegistradores[in.r_instrucao.rs].valor;
			bancoRegistradores[in.r_instrucao.rs].UF = semUF;
			UFINT.status.Busy = false;
			excluirElem(listaWriteB, in.posicao);
			break;
		default:
			bancoRegistradores[in.i_instrucao.rt].valor = bufferRegistradores[in.i_instrucao.rt].valor;
			bancoRegistradores[in.i_instrucao.rt].UF = semUF;
			UFINT.status.Busy = false;
			excluirElem(listaWriteB, in.posicao);
			break;
		}
		switch (in.UF)
		{
		case UF_INT:
			UFINT.status.Busy = false;
			break;
		case UF_ADD:
			UFADD.status.Busy = false;
			break;
		case UF_DIV:
			UFDIV.status.Busy = false;
			break;
		case UF_MUL1:
			UFMUL1.status.Busy = false;
			break;
		case UF_MUL2:
			UFMUL2.status.Busy = false;
			break;
		}
	}
}