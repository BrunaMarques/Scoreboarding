#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pipeline.h"
#include "barramento.h"
#include "un_func.h"
#include "lista.h"
#include "ula.h"
#include "fila.h"
#include "instrucoes.h"
#include "tradutor.h"

int EMITIDA = true;

void buscaPipeline()
{
	if (filaVazia() && (PC < (qtd * 4)))
	{
		if (detail != NULL)
		{
			fprintf(detail, "\n\tBusca:\n");
		}
		for (int i = 0; i < 4; i++)
		{
			if (PC >= (qtd * 4))
			{
				break;
			}
			unsigned char instMem[4];
			buscaMemoria(instMem);

			Inst instDecode = decodificacao(instMem);
			inserirElementoFila(instDecode);
			printar(instDecode);
			int operacao = descobrirOperacao(instDecode);
			switch (operacao)
			{
			case JR:
				PC_ant = PC + 4;
				PC = bancoRegistradores[instDecode.s_instrucao.rs].valor - 4;
				break;
			case B:
				PC_ant = PC + 4;
				PC = instDecode.i_instrucao.imediato - 4;
				break;
			case BEQ:
				PC_ant = PC + 4;
				PC = instDecode.i_instrucao.imediato - 4;
				break;
			case BEQL:
				PC_ant = PC + 4;
				PC = instDecode.i_instrucao.imediato - 4;
				break;
			case BGTZ:
				PC = instDecode.i_instrucao.imediato - 4;
				break;
			case BLEZ:
				PC_ant = PC + 4;
				PC = instDecode.i_instrucao.imediato - 4;
				break;
			case BNE:
				PC_ant = PC + 4;
				PC = instDecode.i_instrucao.imediato - 4;
				break;
			case J:
				PC_ant = PC + 4;
				PC = instDecode.j_instrucao.addr - 4;
				break;
			case BGEZ:
				PC_ant = PC + 4;
				PC = instDecode.r_instrucao.offset - 4;
				break;
			case BLTZ:
				PC_ant = PC + 4;
				PC = instDecode.r_instrucao.offset - 4;
				break;
			default:
				PC += 4;
				break;
			}
		}
	}
	if (EMITIDA)
	{
		if (verifica_bar(barBI) == 0)
		{

			if (f->nroElem > 0)
			{
				in = excluirElementoFila();
				int operacao = descobrirOperacao(in);
				escrita_bar(in, barBI);
			}
		}
	}
}
void emissao()
{
	if (EMITIDA)
	{
		if (verifica_bar(barBI))
		{
			emitidas++;
			if (detail != NULL)
			{
				fprintf(detail, "\n\tEmissão:\n");
			}
			EMITIDA = false;
			in = leitura_bar(barBI);
			printar(in);
			inserirElemLista(listaIssue, in);
		}
	}
	if (!EMITIDA)
	{
		in = listaIssue->lista_inst[0];
		int operacao = descobrirOperacao(in);
		if (in.posicao != -1)
		{
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
						in.qtd_cloc_prec = 2;
						in.cont_clock = clock;
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
						bancoRegistradores[in.s_instrucao.rd].UF = UF_INT;
						in.UF = UF_INT;
						in.qtd_cloc_prec = 1;
						in.cont_clock = clock;
						escrita_bar(in, barIR);
						excluirElem(listaIssue, 0);
						EMITIDA = true;
					}
				}
				break;
			case DIV:
				if (!UFDIV.status.Busy)
				{
					if ((bancoRegistradores[HI].UF == semUF) && (bancoRegistradores[LO].UF == semUF))
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
						in.qtd_cloc_prec = 5;
						in.cont_clock = clock;
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
					in.qtd_cloc_prec = 1;
					in.cont_clock = clock;
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
						in.qtd_cloc_prec = 1;
						in.cont_clock = clock;
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
						in.qtd_cloc_prec = 1;
						in.cont_clock = clock;
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
						in.qtd_cloc_prec = 1;
						in.cont_clock = clock;
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
						in.qtd_cloc_prec = 1;
						in.cont_clock = clock;
						escrita_bar(in, barIR);
						excluirElem(listaIssue, 0);
						EMITIDA = true;
					}
				}
				break;
			case MTHI:
				if (!UFINT.status.Busy)
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
						in.qtd_cloc_prec = 1;
						in.cont_clock = clock;
						escrita_bar(in, barIR);
						excluirElem(listaIssue, 0);
						EMITIDA = true;
					}
				}
				break;
			case MTLO:
				if (!UFINT.status.Busy)
				{
					if (bancoRegistradores[HI].UF == semUF)
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
						in.qtd_cloc_prec = 1;
						in.cont_clock = clock;
						escrita_bar(in, barIR);
						excluirElem(listaIssue, 0);
						EMITIDA = true;
					}
				}
				break;

			case MULT:
				if (!UFMUL1.status.Busy)
				{
					if ((bancoRegistradores[HI].UF == semUF) && (bancoRegistradores[LO].UF == semUF))
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
						bancoRegistradores[HI].UF = UF_MUL1;
						bancoRegistradores[LO].UF = UF_MUL1;
						in.UF = UF_MUL1;
						in.qtd_cloc_prec = 5;
						in.cont_clock = clock;
						escrita_bar(in, barIR);
						excluirElem(listaIssue, 0);
						EMITIDA = true;
					}

					if (!UFMUL2.status.Busy)
					{
						if ((bancoRegistradores[HI].UF == semUF) && (bancoRegistradores[LO].UF == semUF))
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
							bancoRegistradores[HI].UF = UF_MUL2;
							bancoRegistradores[LO].UF = UF_MUL2;
							in.UF = UF_MUL2;
							in.qtd_cloc_prec = 5;
							in.cont_clock = clock;
							escrita_bar(in, barIR);
							excluirElem(listaIssue, 0);
							EMITIDA = true;
						}
					}
				}
				break;
			case NOP:
				if (!UFINT.status.Busy)
				{
					UFINT.status.Busy = true;
					UFINT.status.Op = NOP;
					UFINT.status.Fi = semREG;
					UFINT.status.Fj = semREG;
					UFINT.status.Fk = semREG;
					UFINT.status.Qj = semUF;
					UFINT.status.Qk = semUF;
					UFINT.status.Rj = (bancoRegistradores[in.s_instrucao.rs].UF == semUF) ? true : false;
					UFINT.status.Rk = (bancoRegistradores[in.s_instrucao.rt].UF == semUF) ? true : false;
					in.UF = UF_INT;
					in.qtd_cloc_prec = 1;
					in.cont_clock = clock;
					escrita_bar(in, barIR);
					excluirElem(listaIssue, 0);
					EMITIDA = true;
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
						in.qtd_cloc_prec = 1;
						in.cont_clock = clock;
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
						in.qtd_cloc_prec = 1;
						in.cont_clock = clock;
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
						in.qtd_cloc_prec = 2;
						in.cont_clock = clock;
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
						in.qtd_cloc_prec = 1;
						in.cont_clock = clock;
						escrita_bar(in, barIR);
						excluirElem(listaIssue, 0);
						EMITIDA = true;
					}
				}
				break;
			case MADD: //ver se ta certo//destino é hi e lo
				if (!UFMUL1.status.Busy)
				{
					if ((bancoRegistradores[HI].UF == semUF) && (bancoRegistradores[LO].UF == semUF))
					{
						UFMUL1.status.Busy = true;
						UFMUL1.status.Op = MADD;
						UFMUL1.status.Fi = HI;
						UFMUL1.status.Fj = in.s2_instrucao.rs;
						UFMUL1.status.Fk = in.s2_instrucao.rt;
						UFMUL1.status.Qj = bancoRegistradores[in.s2_instrucao.rs].UF;
						UFMUL1.status.Qk = bancoRegistradores[in.s2_instrucao.rt].UF;
						UFMUL1.status.Rj = (bancoRegistradores[in.s2_instrucao.rs].UF == semUF) ? true : false;
						UFMUL1.status.Rk = (bancoRegistradores[in.s2_instrucao.rt].UF == semUF) ? true : false;
						bancoRegistradores[HI].UF = UF_MUL1;
						bancoRegistradores[LO].UF = UF_MUL1;
						in.UF = UF_MUL1;
						in.qtd_cloc_prec = 5;
						in.cont_clock = clock;
						escrita_bar(in, barIR);
						excluirElem(listaIssue, 0);
						EMITIDA = true;
					}
				}
				else if (!UFMUL2.status.Busy)
				{
					if ((bancoRegistradores[HI].UF == semUF) && (bancoRegistradores[LO].UF == semUF))
					{
						UFMUL2.status.Busy = true;
						UFMUL2.status.Op = MADD;
						UFMUL2.status.Fi = HI;
						UFMUL2.status.Fj = in.s2_instrucao.rs;
						UFMUL2.status.Fk = in.s2_instrucao.rt;
						UFMUL2.status.Qj = bancoRegistradores[in.s2_instrucao.rs].UF;
						UFMUL2.status.Qk = bancoRegistradores[in.s2_instrucao.rt].UF;
						UFMUL2.status.Rj = (bancoRegistradores[in.s2_instrucao.rs].UF == semUF) ? true : false;
						UFMUL2.status.Rk = (bancoRegistradores[in.s2_instrucao.rt].UF == semUF) ? true : false;
						bancoRegistradores[HI].UF = UF_MUL2;
						bancoRegistradores[LO].UF = UF_MUL2;
						in.UF = UF_MUL2;
						in.qtd_cloc_prec = 5;
						in.cont_clock = clock;
						escrita_bar(in, barIR);
						excluirElem(listaIssue, 0);
						EMITIDA = true;
					}
				}
				break;
			case MSUB: //ver se ta certo
				if (!UFMUL1.status.Busy)
				{
					if ((bancoRegistradores[HI].UF == semUF) && (bancoRegistradores[LO].UF == semUF))
					{
						UFMUL1.status.Busy = true;
						UFMUL1.status.Op = MSUB;
						UFMUL1.status.Fi = HI;
						UFMUL1.status.Fj = in.s2_instrucao.rs;
						UFMUL1.status.Fk = in.s2_instrucao.rt;
						UFMUL1.status.Qj = bancoRegistradores[in.s2_instrucao.rs].UF;
						UFMUL1.status.Qk = bancoRegistradores[in.s2_instrucao.rt].UF;
						UFMUL1.status.Rj = (bancoRegistradores[in.s2_instrucao.rs].UF == semUF) ? true : false;
						UFMUL1.status.Rk = (bancoRegistradores[in.s2_instrucao.rt].UF == semUF) ? true : false;
						bancoRegistradores[HI].UF = UF_MUL1;
						bancoRegistradores[LO].UF = UF_MUL1;
						in.UF = UF_MUL1;
						in.qtd_cloc_prec = 5;
						in.cont_clock = clock;
						escrita_bar(in, barIR);
						excluirElem(listaIssue, 0);
						EMITIDA = true;
					}
				}
				else if (!UFMUL2.status.Busy)
				{
					if ((bancoRegistradores[HI].UF == semUF) && (bancoRegistradores[LO].UF == semUF))
					{
						UFMUL2.status.Busy = true;
						UFMUL2.status.Op = MSUB;
						UFMUL2.status.Fi = HI;
						UFMUL2.status.Fj = in.s2_instrucao.rs;
						UFMUL2.status.Fk = in.s2_instrucao.rt;
						UFMUL2.status.Qj = bancoRegistradores[in.s2_instrucao.rs].UF;
						UFMUL2.status.Qk = bancoRegistradores[in.s2_instrucao.rt].UF;
						UFMUL2.status.Rj = (bancoRegistradores[in.s2_instrucao.rs].UF == semUF) ? true : false;
						UFMUL2.status.Rk = (bancoRegistradores[in.s2_instrucao.rt].UF == semUF) ? true : false;
						bancoRegistradores[HI].UF = UF_MUL2;
						bancoRegistradores[LO].UF = UF_MUL2;
						in.UF = UF_MUL2;
						in.qtd_cloc_prec = 5;
						in.cont_clock = clock;
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
						in.qtd_cloc_prec = 5;
						in.cont_clock = clock;
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
						in.qtd_cloc_prec = 5;
						in.cont_clock = clock;
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
						UFINT.status.Fk = semREG;
						UFINT.status.Qj = bancoRegistradores[in.i_instrucao.rs].UF;
						UFINT.status.Qk = semUF;
						UFINT.status.Rj = (bancoRegistradores[in.i_instrucao.rs].UF == semUF) ? true : false;
						UFINT.status.Rk = (bancoRegistradores[in.i_instrucao.imediato].UF == semUF) ? true : false;
						bancoRegistradores[in.i_instrucao.rt].UF = UF_INT;
						in.UF = UF_INT;
						in.qtd_cloc_prec = 1;
						in.cont_clock = clock;
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
						UFINT.status.Fk = semREG;
						UFINT.status.Qj = bancoRegistradores[in.i_instrucao.rs].UF;
						UFINT.status.Qk = semUF;
						UFINT.status.Rj = (bancoRegistradores[in.i_instrucao.rs].UF == semUF) ? true : false;
						UFINT.status.Rk = (bancoRegistradores[in.i_instrucao.imediato].UF == semUF) ? true : false;
						bancoRegistradores[in.i_instrucao.rt].UF = UF_INT;
						in.UF = UF_INT;
						in.qtd_cloc_prec = 1;
						in.cont_clock = clock;
						escrita_bar(in, barIR);
						excluirElem(listaIssue, 0);
						EMITIDA = true;
					}
				}
				break;
			case B:
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
					in.qtd_cloc_prec = 1;
					in.cont_clock = clock;
					escrita_bar(in, barIR);
					excluirElem(listaIssue, 0);
					EMITIDA = true;
				}
				break;
			case BEQ:
				if (!UFINT.status.Busy)
				{
					UFINT.status.Busy = true;
					UFINT.status.Op = BEQ;
					UFINT.status.Fi = semREG;
					UFINT.status.Fj = in.i_instrucao.rs;
					UFINT.status.Fk = in.i_instrucao.rt;
					UFINT.status.Qj = bancoRegistradores[in.i_instrucao.rs].UF;
					UFINT.status.Qk = bancoRegistradores[in.i_instrucao.rt].UF;
					UFINT.status.Rj = (bancoRegistradores[in.i_instrucao.rs].UF == semUF) ? true : false;
					UFINT.status.Rk = (bancoRegistradores[in.i_instrucao.rt].UF == semUF) ? true : false;
					in.UF = UF_INT;
					in.qtd_cloc_prec = 1;
					in.cont_clock = clock;
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
					UFINT.status.Fi = semREG;
					UFINT.status.Fj = in.i_instrucao.rs;
					UFINT.status.Fk = in.i_instrucao.rt;
					UFINT.status.Qj = bancoRegistradores[in.i_instrucao.rs].UF;
					UFINT.status.Qk = bancoRegistradores[in.i_instrucao.rt].UF;
					UFINT.status.Rj = (bancoRegistradores[in.i_instrucao.rs].UF == semUF) ? true : false;
					UFINT.status.Rk = (bancoRegistradores[in.i_instrucao.rt].UF == semUF) ? true : false;
					in.UF = UF_INT;
					in.qtd_cloc_prec = 1;
					in.cont_clock = clock;
					escrita_bar(in, barIR);
					excluirElem(listaIssue, 0);
					EMITIDA = true;
				}
				break;
			case BGTZ:
				if (!UFINT.status.Busy)
				{
					UFINT.status.Busy = true;
					UFINT.status.Op = BGTZ;
					UFINT.status.Fi = semREG;
					UFINT.status.Fj = in.i_instrucao.rs;
					UFINT.status.Fk = in.i_instrucao.rt;
					UFINT.status.Qj = bancoRegistradores[in.i_instrucao.rs].UF;
					UFINT.status.Qk = bancoRegistradores[in.i_instrucao.rt].UF;
					UFINT.status.Rj = (bancoRegistradores[in.i_instrucao.rs].UF == semUF) ? true : false;
					UFINT.status.Rk = (bancoRegistradores[in.i_instrucao.rt].UF == semUF) ? true : false;
					in.UF = UF_INT;
					in.qtd_cloc_prec = 1;
					in.cont_clock = clock;
					escrita_bar(in, barIR);
					excluirElem(listaIssue, 0);
					EMITIDA = true;
				}
				break;
			case BLEZ:
				if (!UFINT.status.Busy)
				{
					UFINT.status.Busy = true;
					UFINT.status.Op = BLEZ;
					UFINT.status.Fi = semREG;
					UFINT.status.Fj = in.i_instrucao.rs;
					UFINT.status.Fk = semREG;
					UFINT.status.Qj = bancoRegistradores[in.i_instrucao.rs].UF;
					UFINT.status.Qk = semUF;
					UFINT.status.Rj = (bancoRegistradores[in.i_instrucao.rt].UF == semUF) ? true : false;
					UFINT.status.Rk = (bancoRegistradores[in.i_instrucao.imediato].UF == semUF) ? true : false;
					in.UF = UF_INT;
					in.qtd_cloc_prec = 1;
					in.cont_clock = clock;
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
					UFINT.status.Fi = semREG;
					UFINT.status.Fj = in.i_instrucao.rs;
					UFINT.status.Fk = in.i_instrucao.rt;
					UFINT.status.Qj = bancoRegistradores[in.i_instrucao.rs].UF;
					UFINT.status.Qk = bancoRegistradores[in.i_instrucao.rt].UF;
					UFINT.status.Rj = (bancoRegistradores[in.i_instrucao.rs].UF == semUF) ? true : false;
					UFINT.status.Rk = (bancoRegistradores[in.i_instrucao.rt].UF == semUF) ? true : false;
					in.UF = UF_INT;
					in.qtd_cloc_prec = 1;
					in.cont_clock = clock;
					escrita_bar(in, barIR);
					excluirElem(listaIssue, 0);
					EMITIDA = true;
				}
				break;

			case LUI:
				if (!UFINT.status.Busy)
				{
					if (bancoRegistradores[in.i_instrucao.rt].UF == semUF)
					{
						UFINT.status.Busy = true;
						UFINT.status.Op = LUI;
						UFINT.status.Fi = in.i_instrucao.rt;
						UFINT.status.Fj = semREG;
						UFINT.status.Fk = semREG;
						UFINT.status.Qj = semUF;
						UFINT.status.Qk = semUF;
						UFINT.status.Rj = (bancoRegistradores[in.i_instrucao.imediato].UF == semUF) ? true : false;
						UFINT.status.Rk = (bancoRegistradores[in.i_instrucao.rt].UF == semUF) ? true : false;
						bancoRegistradores[in.i_instrucao.rt].UF = UF_INT;
						in.UF = UF_INT;
						in.qtd_cloc_prec = 1;
						in.cont_clock = clock;
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
						UFINT.status.Fk = semREG;
						UFINT.status.Qj = bancoRegistradores[in.i_instrucao.rs].UF;
						UFINT.status.Qk = semUF;
						UFINT.status.Rj = (bancoRegistradores[in.i_instrucao.rs].UF == semUF) ? true : false;
						UFINT.status.Rk = (bancoRegistradores[in.i_instrucao.imediato].UF == semUF) ? true : false;
						bancoRegistradores[in.i_instrucao.rt].UF = UF_INT;
						in.UF = UF_INT;
						in.qtd_cloc_prec = 1;
						in.cont_clock = clock;
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
						UFINT.status.Fk = semREG;
						UFINT.status.Qj = bancoRegistradores[in.i_instrucao.rs].UF;
						UFINT.status.Qk = semUF;
						UFINT.status.Rj = (bancoRegistradores[in.i_instrucao.rs].UF == semUF) ? true : false;
						UFINT.status.Rk = (bancoRegistradores[in.i_instrucao.imediato].UF == semUF) ? true : false;
						bancoRegistradores[in.i_instrucao.rt].UF = UF_INT;
						in.UF = UF_INT;
						in.qtd_cloc_prec = 1;
						in.cont_clock = clock;
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
					UFINT.status.Rj = (bancoRegistradores[in.j_instrucao.addr].UF == semUF) ? true : false;
					UFINT.status.Rk = semUF;
					in.UF = UF_INT;
					in.qtd_cloc_prec = 1;
					in.cont_clock = clock;
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
					UFINT.status.Fj = in.r_instrucao.rs;
					UFINT.status.Fk = semREG;
					UFINT.status.Qj = bancoRegistradores[in.r_instrucao.rs].UF;
					UFINT.status.Qk = semUF;
					UFINT.status.Rj = (bancoRegistradores[in.r_instrucao.rs].UF == semUF) ? true : false;
					UFINT.status.Rk = (bancoRegistradores[in.r_instrucao.offset].UF == semUF) ? true : false;
					in.UF = UF_INT;
					in.qtd_cloc_prec = 1;
					in.cont_clock = clock;
					escrita_bar(in, barIR);
					excluirElem(listaIssue, 0);
					EMITIDA = true;
				}
				break;
			case BLTZ:
				if (!UFINT.status.Busy)
				{
					UFINT.status.Busy = true;
					UFINT.status.Op = BLTZ;
					UFINT.status.Fi = semREG;
					UFINT.status.Fj = in.r_instrucao.rs;
					UFINT.status.Fk = semREG;
					UFINT.status.Qj = bancoRegistradores[in.r_instrucao.rs].UF;
					UFINT.status.Qk = semUF;
					UFINT.status.Rj = (bancoRegistradores[in.r_instrucao.rs].UF == semUF) ? true : false;
					UFINT.status.Rk = (bancoRegistradores[in.r_instrucao.offset].UF == semUF) ? true : false;
					in.UF = UF_INT;
					in.qtd_cloc_prec = 1;
					in.cont_clock = clock;
					escrita_bar(in, barIR);
					excluirElem(listaIssue, 0);
					EMITIDA = true;
				}
				break;
			default:
				EMITIDA = true;
				break;
			}
		}
	}
}

void leitura()
{
	if (verifica_bar(barIR))
	{
		if (detail != NULL)
		{
			fprintf(detail, "\n\tLeitura:\n");
		}
		in = leitura_bar(barIR);
		inserirElemLista(listaRead, in);
	}
	for (int i = 0; i < N; i++)
	{
		in = listaRead->lista_inst[i];
		if (listaRead->lista_inst[i].posicao != -1)
		{
			printar(in);
		}
		int operacao = descobrirOperacao(in);
		if (in.posicao == -1)
		{
			continue;
		}
		switch (in.UF)
		{
		case UF_ADD:
			if ((UFADD.status.Fj != semREG) && (UFADD.status.Fk != semREG))
			{
				if (((bancoRegistradores[UFADD.status.Fj].UF == semUF) && (bancoRegistradores[UFADD.status.Fk].UF == semUF)) || (bancoRegistradores[UFADD.status.Fi].UF == bancoRegistradores[UFADD.status.Fj].UF) || (bancoRegistradores[UFADD.status.Fi].UF == bancoRegistradores[UFADD.status.Fk].UF) || (bancoRegistradores[UFADD.status.Fi].UF == bancoRegistradores[UFADD.status.Fj].UF == bancoRegistradores[UFADD.status.Fk].UF))
				{
					escrita_bar(in, barRE);
					excluirElem(listaRead, in.posicao);
				}
			}
			else if (UFADD.status.Fj != semREG)
			{
				if ((bancoRegistradores[UFADD.status.Fj].UF == semUF) || (bancoRegistradores[UFADD.status.Fi].UF == bancoRegistradores[UFADD.status.Fj].UF))
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
				if (((bancoRegistradores[UFDIV.status.Fj].UF == semUF) && (bancoRegistradores[UFDIV.status.Fk].UF == semUF)) || (bancoRegistradores[UFDIV.status.Fi].UF == bancoRegistradores[UFDIV.status.Fj].UF) || (bancoRegistradores[UFDIV.status.Fi].UF == bancoRegistradores[UFDIV.status.Fk].UF) || (bancoRegistradores[UFDIV.status.Fi].UF == bancoRegistradores[UFDIV.status.Fj].UF == bancoRegistradores[UFDIV.status.Fk].UF))
				{
					escrita_bar(in, barRE);
					excluirElem(listaRead, in.posicao);
				}
			}
			else if (UFDIV.status.Fj != semREG)
			{
				if ((bancoRegistradores[UFDIV.status.Fj].UF == semUF) || (bancoRegistradores[UFDIV.status.Fi].UF == bancoRegistradores[UFDIV.status.Fj].UF))
				{
					escrita_bar(in, barRE);
					excluirElem(listaRead, in.posicao);
				}
			}
			break;
		case UF_INT:
			if ((UFINT.status.Fj != semREG) && (UFINT.status.Fk != semREG))
			{
				if (((bancoRegistradores[UFINT.status.Fj].UF == semUF) && (bancoRegistradores[UFINT.status.Fk].UF == semUF)) || (bancoRegistradores[UFINT.status.Fi].UF == bancoRegistradores[UFINT.status.Fj].UF) || (bancoRegistradores[UFINT.status.Fi].UF == bancoRegistradores[UFINT.status.Fk].UF) || (bancoRegistradores[UFINT.status.Fi].UF == bancoRegistradores[UFINT.status.Fj].UF == bancoRegistradores[UFINT.status.Fk].UF))
				{
					escrita_bar(in, barRE);
					excluirElem(listaRead, in.posicao);
				}
			}
			else if (UFINT.status.Fj != semREG)
			{
				if ((bancoRegistradores[UFINT.status.Fj].UF == semUF) || (bancoRegistradores[UFINT.status.Fi].UF == bancoRegistradores[UFINT.status.Fj].UF))
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
				if (((bancoRegistradores[UFMUL1.status.Fj].UF == semUF) && (bancoRegistradores[UFMUL1.status.Fk].UF == semUF)) || (bancoRegistradores[UFMUL1.status.Fi].UF == bancoRegistradores[UFMUL1.status.Fj].UF) || (bancoRegistradores[UFMUL1.status.Fi].UF == bancoRegistradores[UFMUL1.status.Fk].UF) || (bancoRegistradores[UFMUL1.status.Fi].UF == bancoRegistradores[UFMUL1.status.Fj].UF == bancoRegistradores[UFMUL1.status.Fk].UF))
				{
					escrita_bar(in, barRE);
					excluirElem(listaRead, in.posicao);
				}
			}
			else if (UFMUL1.status.Fj != semREG)
			{
				if ((bancoRegistradores[UFMUL1.status.Fj].UF == semUF) || (bancoRegistradores[UFMUL1.status.Fi].UF == bancoRegistradores[UFMUL1.status.Fj].UF))
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
				if (((bancoRegistradores[UFMUL2.status.Fj].UF == semUF) && (bancoRegistradores[UFMUL2.status.Fk].UF == semUF)) || (bancoRegistradores[UFMUL2.status.Fi].UF == bancoRegistradores[UFMUL2.status.Fj].UF) || (bancoRegistradores[UFMUL2.status.Fi].UF == bancoRegistradores[UFMUL2.status.Fk].UF) || (bancoRegistradores[UFMUL2.status.Fi].UF == bancoRegistradores[UFMUL2.status.Fj].UF == bancoRegistradores[UFMUL2.status.Fk].UF))
				{
					escrita_bar(in, barRE);
					excluirElem(listaRead, in.posicao);
				}
			}
			else if (UFMUL2.status.Fj != semREG)
			{
				if ((bancoRegistradores[UFMUL2.status.Fj].UF == semUF) || (bancoRegistradores[UFMUL2.status.Fk].UF == bancoRegistradores[UFMUL2.status.Fj].UF))
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

	while (verifica_bar(barRE))
	{

		in = leitura_bar(barRE);
		// printar(in);

		inserirElemLista(listaExecucao, in);
	}
	for (int i = 0; i < N; i++)
	{
		in = listaExecucao->lista_inst[i];
		if (listaExecucao->lista_inst[i].posicao != -1)
		{
			if (detail != NULL)
			{
				fprintf(detail, "\n\tExecução\n");
			}
			printar(in);
		}
		int operacao = descobrirOperacao(in);
		if (in.posicao == -1)
		{
			continue;
		}

		switch (operacao)
		{
		case ADD:
			listaExecucao->lista_inst[i].qtd_cloc_prec--;
			if (listaExecucao->lista_inst[i].qtd_cloc_prec == 0)
			{
				bufferRegistradores[in.s_instrucao.rd].valor = adicao(bancoRegistradores[in.s_instrucao.rs].valor, bancoRegistradores[in.s_instrucao.rt].valor);
				escrita_bar(in, barEW);
				excluirElem(listaExecucao, in.posicao);
			}
			else
			{
				break;
			}
		case AND:
			listaExecucao->lista_inst[i].qtd_cloc_prec--;
			if (listaExecucao->lista_inst[i].qtd_cloc_prec == 0)
			{
				bufferRegistradores[in.s_instrucao.rd].valor = and(bancoRegistradores[in.s_instrucao.rs].valor, bancoRegistradores[in.s_instrucao.rt].valor);
				escrita_bar(in, barEW);
				excluirElem(listaExecucao, in.posicao);
			}
			break;
		case DIV:
			listaExecucao->lista_inst[i].qtd_cloc_prec--;
			if (listaExecucao->lista_inst[i].qtd_cloc_prec == 0)
			{
				bufferRegistradores[HI].valor = divisao(bancoRegistradores[in.s_instrucao.rs].valor, bancoRegistradores[in.s_instrucao.rt].valor);
				bufferRegistradores[LO].valor = (bancoRegistradores[in.s_instrucao.rs].valor % bancoRegistradores[in.s_instrucao.rt].valor);
				escrita_bar(in, barEW);
				excluirElem(listaExecucao, in.posicao);
			}
			break;
		case JR:
			listaExecucao->lista_inst[i].qtd_cloc_prec--;
			if (listaExecucao->lista_inst[i].qtd_cloc_prec == 0)
			{
				saltou++;
				tomado++;
				escrita_bar(in, barEW);
				excluirElem(listaExecucao, in.posicao);
			}
			break;
		case MFHI:
			listaExecucao->lista_inst[i].qtd_cloc_prec--;

			if (listaExecucao->lista_inst[i].qtd_cloc_prec == 0)
			{
				bufferRegistradores[in.s_instrucao.rd].valor = bufferRegistradores[HI].valor;
				escrita_bar(in, barEW);
				excluirElem(listaExecucao, in.posicao);
			}
			break;
		case MFLO:
			listaExecucao->lista_inst[i].qtd_cloc_prec--;
			if (listaExecucao->lista_inst[i].qtd_cloc_prec == 0)
			{
				bufferRegistradores[in.s_instrucao.rd].valor = bancoRegistradores[LO].valor;
				escrita_bar(in, barEW);
				excluirElem(listaExecucao, in.posicao);
			}
			break;
		case MOVN:
			listaExecucao->lista_inst[i].qtd_cloc_prec--;
			if (listaExecucao->lista_inst[i].qtd_cloc_prec == 0)
			{
				if (not(igual(bancoRegistradores[in.s_instrucao.rt].valor, 0)))
					bufferRegistradores[in.s_instrucao.rd].valor = bancoRegistradores[in.s_instrucao.rs].valor;
				escrita_bar(in, barEW);
				excluirElem(listaExecucao, in.posicao);
			}
			break;
		case MOVZ:
			listaExecucao->lista_inst[i].qtd_cloc_prec--;
			if (listaExecucao->lista_inst[i].qtd_cloc_prec == 0)
			{
				if (igual(bancoRegistradores[in.s_instrucao.rt].valor, 0))
					bufferRegistradores[in.s_instrucao.rd].valor = bancoRegistradores[in.s_instrucao.rs].valor;
				escrita_bar(in, barEW);
				excluirElem(listaExecucao, in.posicao);
			}
			break;
		case MTHI:
			listaExecucao->lista_inst[i].qtd_cloc_prec--;
			if (listaExecucao->lista_inst[i].qtd_cloc_prec == 0)
			{
				bufferRegistradores[HI].valor = bancoRegistradores[in.s_instrucao.rs].valor;
				escrita_bar(in, barEW);
				excluirElem(listaExecucao, in.posicao);
			}
			break;
		case MTLO:
			listaExecucao->lista_inst[i].qtd_cloc_prec--;
			if (listaExecucao->lista_inst[i].qtd_cloc_prec == 0)
			{
				bufferRegistradores[LO].valor = bancoRegistradores[in.s_instrucao.rs].valor;
				escrita_bar(in, barEW);
				excluirElem(listaExecucao, in.posicao);
			}
			break;
		case MULT:
			listaExecucao->lista_inst[i].qtd_cloc_prec--;
			if (listaExecucao->lista_inst[i].qtd_cloc_prec == 0)
			{
				bufferRegistradores[HI].valor = ((multiplicacao(bancoRegistradores[in.s_instrucao.rs].valor, bancoRegistradores[in.s_instrucao.rt].valor)) >> 16);
				bufferRegistradores[LO].valor = ((multiplicacao(bancoRegistradores[in.s_instrucao.rs].valor, bancoRegistradores[in.s_instrucao.rt].valor)) << 16);
				escrita_bar(in, barEW);
				excluirElem(listaExecucao, in.posicao);
			}
			break;
		case NOP:
			listaExecucao->lista_inst[i].qtd_cloc_prec--;
			if (listaExecucao->lista_inst[i].qtd_cloc_prec == 0)
			{
				bancoRegistradores[Z0].valor >> 0;
			}

			break;
		case NOR:
			listaExecucao->lista_inst[i].qtd_cloc_prec--;
			if (listaExecucao->lista_inst[i].qtd_cloc_prec == 0)
			{
				bufferRegistradores[in.s_instrucao.rd].valor = nor(bancoRegistradores[in.s_instrucao.rs].valor, bancoRegistradores[in.s_instrucao.rt].valor);
				escrita_bar(in, barEW);
				excluirElem(listaExecucao, in.posicao);
			}
			break;
		case OR:
			listaExecucao->lista_inst[i].qtd_cloc_prec--;
			if (listaExecucao->lista_inst[i].qtd_cloc_prec == 0)
			{
				bufferRegistradores[in.s_instrucao.rd].valor = or (bancoRegistradores[in.s_instrucao.rs].valor, bancoRegistradores[in.s_instrucao.rt].valor);
				escrita_bar(in, barEW);
				excluirElem(listaExecucao, in.posicao);
			}
			break;
		case SUB:
			listaExecucao->lista_inst[i].qtd_cloc_prec--;
			if (listaExecucao->lista_inst[i].qtd_cloc_prec == 0)
			{
				bufferRegistradores[in.s_instrucao.rd].valor = subtracao(bancoRegistradores[in.s_instrucao.rs].valor, bancoRegistradores[in.s_instrucao.rt].valor);
				escrita_bar(in, barEW);
				excluirElem(listaExecucao, in.posicao);
			}
			break;
		case XOR:
			listaExecucao->lista_inst[i].qtd_cloc_prec--;
			if (listaExecucao->lista_inst[i].qtd_cloc_prec == 0)
			{
				bufferRegistradores[in.s_instrucao.rd].valor = xor(bancoRegistradores[in.s_instrucao.rs].valor, bancoRegistradores[in.s_instrucao.rt].valor);
				escrita_bar(in, barEW);
				excluirElem(listaExecucao, in.posicao);
			}
			break;
		case MADD:
			listaExecucao->lista_inst[i].qtd_cloc_prec--;
			if (listaExecucao->lista_inst[i].qtd_cloc_prec == 0)
			{
				bufferRegistradores[in.s2_instrucao.rd].valor = multiplicacao(bancoRegistradores[in.s2_instrucao.rs].valor, bancoRegistradores[in.s2_instrucao.rt].valor);
				bufferRegistradores[HI].valor = adicao(bufferRegistradores[in.s2_instrucao.rd].valor >> 16, bancoRegistradores[HI].valor);
				bufferRegistradores[LO].valor = adicao(bufferRegistradores[in.s2_instrucao.rd].valor << 16, bancoRegistradores[LO].valor);
				escrita_bar(in, barEW);
				excluirElem(listaExecucao, in.posicao);
			}
			break;
		case MSUB:
			listaExecucao->lista_inst[i].qtd_cloc_prec--;
			if (listaExecucao->lista_inst[i].qtd_cloc_prec == 0)
			{
				bufferRegistradores[in.s2_instrucao.rd].valor = multiplicacao(bancoRegistradores[in.s2_instrucao.rs].valor, bancoRegistradores[in.s2_instrucao.rt].valor);
				bufferRegistradores[HI].valor = subtracao(bufferRegistradores[in.s2_instrucao.rd].valor >> 16, bancoRegistradores[HI].valor);
				bufferRegistradores[LO].valor = subtracao(bufferRegistradores[in.s2_instrucao.rd].valor << 16, bancoRegistradores[LO].valor);
				escrita_bar(in, barEW);
				excluirElem(listaExecucao, in.posicao);
			}
			break;
		case MUL:
			listaExecucao->lista_inst[i].qtd_cloc_prec--;
			if (listaExecucao->lista_inst[i].qtd_cloc_prec == 0)
			{
				bufferRegistradores[in.s2_instrucao.rd].valor = multiplicacao(bancoRegistradores[in.s2_instrucao.rs].valor, bancoRegistradores[in.s2_instrucao.rt].valor);
				escrita_bar(in, barEW);
				excluirElem(listaExecucao, in.posicao);
			}
			break;
		case ADDI:
			listaExecucao->lista_inst[i].qtd_cloc_prec--;
			if (listaExecucao->lista_inst[i].qtd_cloc_prec == 0)
			{
				bufferRegistradores[in.i_instrucao.rt].valor = adicao(bancoRegistradores[in.i_instrucao.rs].valor, in.i_instrucao.imediato);
				escrita_bar(in, barEW);
				excluirElem(listaExecucao, in.posicao);
			}
			break;
		case ANDI:
			listaExecucao->lista_inst[i].qtd_cloc_prec--;
			if (listaExecucao->lista_inst[i].qtd_cloc_prec == 0)
			{
				bufferRegistradores[in.i_instrucao.rt].valor = and(bancoRegistradores[in.i_instrucao.rs].valor, in.i_instrucao.imediato);
				escrita_bar(in, barEW);
				excluirElem(listaExecucao, in.posicao);
			}
			break;
		case B:
			listaExecucao->lista_inst[i].qtd_cloc_prec--;
			if (listaExecucao->lista_inst[i].qtd_cloc_prec == 0)
			{
				saltou++;
				tomado++;
				escrita_bar(in, barEW);
				excluirElem(listaExecucao, in.posicao);
			}
			break;
		case BEQ:
			listaExecucao->lista_inst[i].qtd_cloc_prec--;
			if (listaExecucao->lista_inst[i].qtd_cloc_prec == 0)
			{
				if (igual(bancoRegistradores[in.i_instrucao.rs].valor, bancoRegistradores[in.i_instrucao.rt].valor))
				{
					tomado++;
					saltou++;
				}
				else
				{
					naotomado++;
					PC = PC_ant;
					esvaziarLista(listaIssue, in);
					esvaziarLista(listaRead, in);
					esvaziarLista(listaExecucao, in);
					esvaziarLista(listaWriteB, in);
					excluir_bar(barBI, in);
					excluir_bar(barIR, in);
					excluir_bar(barRE, in);
					excluir_bar(barEW, in);
				}
				escrita_bar(in, barEW);
				excluirElem(listaExecucao, in.posicao);
			}
			break;
		case BEQL:
			listaExecucao->lista_inst[i].qtd_cloc_prec--;
			if (listaExecucao->lista_inst[i].qtd_cloc_prec == 0)
			{
				if (igual(bancoRegistradores[in.i_instrucao.rs].valor, bancoRegistradores[in.i_instrucao.rt].valor))
				{
					tomado++;
					saltou++;
				}
				else
				{
					naotomado++;
					PC = PC_ant;
					esvaziarLista(listaIssue, in);
					esvaziarLista(listaRead, in);
					esvaziarLista(listaExecucao, in);
					esvaziarLista(listaWriteB, in);
					excluir_bar(barBI, in);
					excluir_bar(barIR, in);
					excluir_bar(barRE, in);
					excluir_bar(barEW, in);
				}
				escrita_bar(in, barEW);
				;
				excluirElem(listaExecucao, in.posicao);
			}
			break;
		case BGTZ:
			listaExecucao->lista_inst[i].qtd_cloc_prec--;
			if (listaExecucao->lista_inst[i].qtd_cloc_prec == 0)
			{
				if (maior(bancoRegistradores[in.i_instrucao.rs].valor, 0))
				{
					tomado++;
					saltou++;
				}
				else
				{
					naotomado++;
					PC = PC_ant;
					esvaziarLista(listaIssue, in);
					esvaziarLista(listaRead, in);
					esvaziarLista(listaExecucao, in);
					esvaziarLista(listaWriteB, in);
					excluir_bar(barBI, in);
					excluir_bar(barIR, in);
					excluir_bar(barRE, in);
					excluir_bar(barEW, in);
				}
				escrita_bar(in, barEW);
				excluirElem(listaExecucao, in.posicao);
			}
			break;
		case BLEZ:
			listaExecucao->lista_inst[i].qtd_cloc_prec--;
			if (listaExecucao->lista_inst[i].qtd_cloc_prec == 0)
			{
				if (menorIgual(bancoRegistradores[in.i_instrucao.rs].valor, 0))
				{
					saltou++;
					tomado++;
				}
				else
				{
					naotomado++;
					PC = PC_ant;
					esvaziarLista(listaIssue, in);
					esvaziarLista(listaRead, in);
					esvaziarLista(listaExecucao, in);
					esvaziarLista(listaWriteB, in);
					excluir_bar(barBI, in);
					excluir_bar(barIR, in);
					excluir_bar(barRE, in);
					excluir_bar(barEW, in);
				}
				escrita_bar(in, barEW);
				excluirElem(listaExecucao, in.posicao);
			}
			break;
		case BNE:
			listaExecucao->lista_inst[i].qtd_cloc_prec--;
			if (listaExecucao->lista_inst[i].qtd_cloc_prec == 0)
			{
				int aux1 = bancoRegistradores[in.i_instrucao.rs].valor;
				int aux2 = bancoRegistradores[in.i_instrucao.rt].valor;
				//if (not(igual(bancoRegistradores[in.i_instrucao.rs].valor, bancoRegistradores[in.s_instrucao.rt].valor)))
				if (not(igual(aux1, aux2)))
				{
					tomado++;
					saltou++;
					//PC = in.i_instrucao.imediato;
				}
				else
				{
					naotomado++;
					PC = PC_ant;
					esvaziarLista(listaIssue, in);
					esvaziarLista(listaRead, in);
					esvaziarLista(listaExecucao, in);
					esvaziarLista(listaWriteB, in);
					excluir_bar(barBI, in);
					excluir_bar(barIR, in);
					excluir_bar(barRE, in);
					excluir_bar(barEW, in);
				}
				escrita_bar(in, barEW);
				excluirElem(listaExecucao, in.posicao);
			}
			break;
		case LUI:
			listaExecucao->lista_inst[i].qtd_cloc_prec--;
			if (listaExecucao->lista_inst[i].qtd_cloc_prec == 0)
			{
				bufferRegistradores[in.i_instrucao.rt].valor = shiftLeft(in.i_instrucao.imediato, 16);
				escrita_bar(in, barEW);
				excluirElem(listaExecucao, in.posicao);
			}
			break;
		case ORI:
			listaExecucao->lista_inst[i].qtd_cloc_prec--;
			if (listaExecucao->lista_inst[i].qtd_cloc_prec == 0)
			{
				bufferRegistradores[in.i_instrucao.rt].valor = or (bancoRegistradores[in.i_instrucao.rs].valor, in.i_instrucao.imediato);
				escrita_bar(in, barEW);
				excluirElem(listaExecucao, in.posicao);
			}
			break;
		case XORI:
			listaExecucao->lista_inst[i].qtd_cloc_prec--;
			if (listaExecucao->lista_inst[i].qtd_cloc_prec == 0)
			{
				bufferRegistradores[in.i_instrucao.rt].valor = xor(bancoRegistradores[in.i_instrucao.rs].valor, in.i_instrucao.imediato);
				escrita_bar(in, barEW);
				excluirElem(listaExecucao, in.posicao);
			}
			break;
		case J:
			listaExecucao->lista_inst[i].qtd_cloc_prec--;
			if (listaExecucao->lista_inst[i].qtd_cloc_prec == 0)
			{
				saltou++;
				tomado++;
				escrita_bar(in, barEW);
				excluirElem(listaExecucao, in.posicao);
			}
			break;
		case BGEZ:
			listaExecucao->lista_inst[i].qtd_cloc_prec--;
			if (listaExecucao->lista_inst[i].qtd_cloc_prec == 0)
			{
				if (maiorIgual(bancoRegistradores[in.r_instrucao.rs].valor, 0))
				{
					tomado++;
					saltou++;
				}
				else
				{
					naotomado++;
					PC = PC_ant;
					esvaziarLista(listaIssue, in);
					esvaziarLista(listaRead, in);
					esvaziarLista(listaExecucao, in);
					esvaziarLista(listaWriteB, in);
					excluir_bar(barBI, in);
					excluir_bar(barIR, in);
					excluir_bar(barRE, in);
					excluir_bar(barEW, in);
				}
				escrita_bar(in, barEW);
				excluirElem(listaExecucao, in.posicao);
			}
			break;
		case BLTZ:
			listaExecucao->lista_inst[i].qtd_cloc_prec--;
			if (listaExecucao->lista_inst[i].qtd_cloc_prec == 0)
			{
				if (menor(bancoRegistradores[in.r_instrucao.rs].valor, 0))
				{
					tomado++;
					saltou++;
				}
				else
				{
					naotomado++;
					PC = PC_ant;
					esvaziarLista(listaIssue, in);
					esvaziarLista(listaRead, in);
					esvaziarLista(listaExecucao, in);
					esvaziarLista(listaWriteB, in);
					excluir_bar(barBI, in);
					excluir_bar(barIR, in);
					excluir_bar(barRE, in);
					excluir_bar(barEW, in);
				}
				escrita_bar(in, barEW);
				excluirElem(listaExecucao, in.posicao);
			}
			break;
		}
	}
}

void escritaPipeline()
{
	while (verifica_bar(barEW))
	{
		efetivadas++;
		in = leitura_bar(barEW);
		inserirElemLista(listaWriteB, in);
	}
	for (int i = 0; i < N; i++)
	{
		in = listaWriteB->lista_inst[i];
		if (listaWriteB->lista_inst[i].posicao != -1)
		{
			if (detail != NULL)
			{
				fprintf(detail, "\n\tEscrita\n");
			}
			printar(in);
		}
		int operacao = descobrirOperacao(in);
		if (in.posicao == -1)
		{

			continue;
		}
		switch (operacao)
		{
		case ADD:

			bancoRegistradores[in.s_instrucao.rd].valor = bufferRegistradores[in.s_instrucao.rd].valor;
			bancoRegistradores[in.s_instrucao.rd].UF = semUF;
			excluirElem(listaWriteB, in.posicao);
			break;

		case AND:

			bancoRegistradores[in.s_instrucao.rd].valor = bufferRegistradores[in.s_instrucao.rd].valor;
			bancoRegistradores[in.s_instrucao.rd].UF = semUF;
			excluirElem(listaWriteB, in.posicao);
			break;

		case DIV:

			bancoRegistradores[HI].valor = bufferRegistradores[HI].valor;
			bancoRegistradores[LO].valor = bufferRegistradores[LO].valor;
			bancoRegistradores[HI].UF = semUF;
			bancoRegistradores[LO].UF = semUF;
			excluirElem(listaWriteB, in.posicao);
			break;

		case JR:

			PC = bancoRegistradores[in.s_instrucao.rs].valor;
			excluirElem(listaWriteB, in.posicao);
			break;

		case MFHI:

			bancoRegistradores[in.s_instrucao.rd].valor = bufferRegistradores[in.s_instrucao.rd].valor;
			bancoRegistradores[in.s_instrucao.rd].UF = semUF;
			excluirElem(listaWriteB, in.posicao);
			break;

		case MFLO:

			bancoRegistradores[in.s_instrucao.rd].valor = bufferRegistradores[in.s_instrucao.rd].valor;
			bancoRegistradores[in.s_instrucao.rd].UF = semUF;
			excluirElem(listaWriteB, in.posicao);
			break;

		case MOVN:

			bancoRegistradores[in.s_instrucao.rd].valor = bufferRegistradores[in.s_instrucao.rd].valor;
			bancoRegistradores[in.s_instrucao.rd].UF = semUF;
			excluirElem(listaWriteB, in.posicao);
			break;

		case MOVZ:

			bancoRegistradores[in.s_instrucao.rd].valor = bufferRegistradores[in.s_instrucao.rd].valor;
			bancoRegistradores[in.s_instrucao.rd].UF = semUF;
			excluirElem(listaWriteB, in.posicao);
			break;

		case MTHI:

			bancoRegistradores[HI].valor = bufferRegistradores[HI].valor;
			bancoRegistradores[HI].UF = semUF;
			excluirElem(listaWriteB, in.posicao);
			break;

		case MTLO:

			bancoRegistradores[LO].valor = bufferRegistradores[HI].valor;
			bancoRegistradores[LO].UF = semUF;
			excluirElem(listaWriteB, in.posicao);
			break;

		case MULT:

			bancoRegistradores[HI].valor = bufferRegistradores[HI].valor;
			bancoRegistradores[LO].valor = bufferRegistradores[LO].valor;
			bancoRegistradores[HI].UF = semUF;
			bancoRegistradores[LO].UF = semUF;
			excluirElem(listaWriteB, in.posicao);
			break;

		case NOP:

			excluirElem(listaWriteB, in.posicao);
			break;

		case NOR:

			bancoRegistradores[in.s_instrucao.rd].valor = bufferRegistradores[in.s_instrucao.rd].valor;
			bancoRegistradores[in.s_instrucao.rd].UF = semUF;
			excluirElem(listaWriteB, in.posicao);
			break;

		case OR:

			bancoRegistradores[in.s_instrucao.rd].valor = bufferRegistradores[in.s_instrucao.rd].valor;
			bancoRegistradores[in.s_instrucao.rd].UF = semUF;
			excluirElem(listaWriteB, in.posicao);
			break;

		case SUB:

			bancoRegistradores[in.s_instrucao.rd].valor = bufferRegistradores[in.s_instrucao.rd].valor;
			bancoRegistradores[in.s_instrucao.rd].UF = semUF;
			excluirElem(listaWriteB, in.posicao);
			break;

		case XOR:

			bancoRegistradores[in.s_instrucao.rd].valor = bufferRegistradores[in.s_instrucao.rd].valor;
			bancoRegistradores[in.s_instrucao.rd].UF = semUF;
			excluirElem(listaWriteB, in.posicao);
			break;

		case MADD:

			bancoRegistradores[HI].valor = bufferRegistradores[HI].valor;
			bancoRegistradores[LO].valor = bufferRegistradores[LO].valor;
			bancoRegistradores[HI].UF = semUF;
			bancoRegistradores[LO].UF = semUF;
			excluirElem(listaWriteB, in.posicao);
			break;

		case MSUB:

			bancoRegistradores[HI].valor = bufferRegistradores[HI].valor;
			bancoRegistradores[LO].valor = bufferRegistradores[LO].valor;
			bancoRegistradores[HI].UF = semUF;
			bancoRegistradores[LO].UF = semUF;
			excluirElem(listaWriteB, in.posicao);
			break;

		case MUL:

			bancoRegistradores[in.s2_instrucao.rd].valor = bufferRegistradores[in.s2_instrucao.rd].valor;
			bancoRegistradores[in.s2_instrucao.rd].UF = semUF;
			excluirElem(listaWriteB, in.posicao);
			break;

		case ADDI:

			bancoRegistradores[in.i_instrucao.rt].valor = bufferRegistradores[in.i_instrucao.rt].valor;
			bancoRegistradores[in.i_instrucao.rt].UF = semUF;
			excluirElem(listaWriteB, in.posicao);
			break;

		case ANDI:

			bancoRegistradores[in.i_instrucao.rt].valor = bufferRegistradores[in.i_instrucao.rt].valor;
			bancoRegistradores[in.i_instrucao.rt].UF = semUF;
			excluirElem(listaWriteB, in.posicao);
			break;

		case B:

			excluirElem(listaWriteB, in.posicao);
			break;

		case BEQ:

			excluirElem(listaWriteB, in.posicao);
			break;

		case BEQL:

			excluirElem(listaWriteB, in.posicao);
			break;

		case BGTZ:

			excluirElem(listaWriteB, in.posicao);
			break;

		case BLEZ:

			excluirElem(listaWriteB, in.posicao);
			break;

		case BNE:

			excluirElem(listaWriteB, in.posicao);
			break;

		case LUI:

			bancoRegistradores[in.i_instrucao.rt].valor = bufferRegistradores[in.i_instrucao.rt].valor;
			bancoRegistradores[in.i_instrucao.rt].UF = semUF;
			excluirElem(listaWriteB, in.posicao);
			break;

		case ORI:

			bancoRegistradores[in.i_instrucao.rt].valor = bufferRegistradores[in.i_instrucao.rt].valor;
			bancoRegistradores[in.i_instrucao.rt].UF = semUF;
			excluirElem(listaWriteB, in.posicao);
			break;

		case XORI:

			bancoRegistradores[in.i_instrucao.rt].valor = bufferRegistradores[in.i_instrucao.rt].valor;
			bancoRegistradores[in.i_instrucao.rt].UF = semUF;
			excluirElem(listaWriteB, in.posicao);
			break;

		case J:

			excluirElem(listaWriteB, in.posicao);
			break;

		case BGEZ:

			excluirElem(listaWriteB, in.posicao);
			break;

		case BLTZ:

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