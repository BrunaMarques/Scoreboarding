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
	printf("\n\t--------------busca--------------\n");
	printf("\nEMITIDA COMEÇO DA BUSCA: %d\n", EMITIDA);
	printf("\nQUANTIDADE %d\n", qtd);
	if (filaVazia() && (PC < (qtd * 4)))
	{
		for (int i = 0; i < 4; i++)
		{
			printf("\n PC: %d\n", PC);
			if (PC >= (qtd * 4))
			{
				break;
			}
			unsigned int instMem[4];
			buscaMemoria(instMem);

			Inst instDecode = decodificacao(instMem);
			inserirElementoFila(instDecode);
			PC += 4;
		}
	}
	printf("\nBARRAMENTO BI AAAA: %d\n", BI.instrucao.opcode);
	printf("\nBARRAMENTO BI AAAABBBBBBBBB: %d\n", verifica_bar(barBI));
	if (verifica_bar(barBI) == 0)
	{
		printf("ENTROU NO IFFFF\n");
		in = excluirElementoFila();
		int operacao = descobrirOperacao(in);
		printf("\nINSTRUCAO: %d\n", operacao);
		escrita_bar(in, barBI);
	}
	printf("\nBARRAMENTO BI AAAA: %d\n", BI.instrucao.opcode);
	printf("\nBARRAMENTO BI AAAABBBBBBBBB: %d\n", verifica_bar(barBI));
	printf("\nEMITIDA FIM DA BUSCA: %d\n", EMITIDA);
}
void emissao()
{
	printf("\n\t--------------emissão--------------\n");
	printf("\nEMITIDA COMEÇO DA EMISSÃO: %d\n", EMITIDA);
	if (EMITIDA)
	{
		if (verifica_bar(barBI))
		{
			printf("\nEMITIDA\n");
			EMITIDA = false;
			printf("\nBARRAMENTO BI AAAA: %d\n", BI.instrucao.opcode);
			printf("\nBARRAMENTO BI AAAABBBBBBBBB: %d\n", verifica_bar(barBI));
			in = leitura_bar(barBI);
			exibirLista(listaIssue);
			inserirElemLista(listaIssue, in);
			//printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
			exibirLista(listaIssue);
		}
	}
	printf("\nBARRAMENTO BI FORA: %d\n", BI.instrucao.opcode);
	if (!EMITIDA)
	{
		printf("\nBARRAMENTO BI AAAA: %d\n", BI.instrucao.opcode);
		printf("\nBARRAMENTO BI AAAABBBBBBBBB: %d\n", verifica_bar(barBI));
		printf("\nNÃO EMITIDA\n");
		in = listaIssue->lista_inst[0];
		int operacao = descobrirOperacao(in);
		printf("\nINSTRUÇÃO: %d\n", operacao);
		if (in.posicao != -1)
		{
			printf("ENTROU NO IF -1");
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
						// bancoRegistradores[in.s_instrucao.rs].UF = UF_ADD;
						// bancoRegistradores[in.s_instrucao.rt].UF = UF_ADD;
						in.UF = UF_ADD;
						in.qtd_cloc_prec = 2;
						escrita_bar(in, barIR);
						printf("\nADD\n");
						printf("barramento IR opcode: %d\n", IR.instrucao.opcode);
						printf("barramento IR RD: %d\n", IR.instrucao.s_instrucao.rd);
						printf("barramento IR RS: %d\n", IR.instrucao.s_instrucao.rs);
						printf("barramento IR RT: %d\n", IR.instrucao.s_instrucao.rt);
						//exibirLista(listaIssue);
						printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
						excluirElem(listaIssue, 0);
						//exibirLista(listaIssue);
						printf("posição elemento na lista issue: %d\n", listaIssue->lista_inst[in.posicao].posicao);
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
						escrita_bar(in, barIR);
						printf("\nAND\n");
						printf("barramento IR opcode: %d\n", IR.instrucao.opcode);
						printf("barramento IR RD: %d\n", IR.instrucao.s_instrucao.rd);
						printf("barramento IR RS: %d\n", IR.instrucao.s_instrucao.rs);
						printf("barramento IR RT: %d\n", IR.instrucao.s_instrucao.rt);
						//exibirLista(listaIssue);
						printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
						excluirElem(listaIssue, 0);
						//exibirLista(listaIssue);
						printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
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
						escrita_bar(in, barIR);
						printf("\nDIV\n");
						printf("barramento IR opcode: %d\n", IR.instrucao.opcode);
						printf("barramento IR RS: %d\n", IR.instrucao.s_instrucao.rs);
						printf("barramento IR RT: %d\n", IR.instrucao.s_instrucao.rt);
						//exibirLista(listaIssue);
						printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
						excluirElem(listaIssue, 0);
						//exibirLista(listaIssue);
						printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
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
					escrita_bar(in, barIR);
					printf("\nJR\n");
					printf("barramento IR opcode: %d\n", IR.instrucao.opcode);
					printf("barramento IR RS: %d\n", IR.instrucao.s_instrucao.rs);
					//exibirLista(listaIssue);
					printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
					excluirElem(listaIssue, 0);
					//exibirLista(listaIssue);
					printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
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
						escrita_bar(in, barIR);
						printf("\nMFHI\n");
						printf("barramento IR opcode: %d\n", IR.instrucao.opcode);
						printf("barramento IR RD: %d\n", IR.instrucao.s_instrucao.rd);
						//exibirLista(listaIssue);
						printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
						excluirElem(listaIssue, 0);
						//exibirLista(listaIssue);
						printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
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
						escrita_bar(in, barIR);
						printf("\nMFLO\n");
						printf("barramento IR opcode: %d\n", IR.instrucao.opcode);
						printf("barramento IR RD: %d\n", IR.instrucao.s_instrucao.rd);
						//exibirLista(listaIssue);
						printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
						excluirElem(listaIssue, 0);
						//exibirLista(listaIssue);
						printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
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
						escrita_bar(in, barIR);
						printf("\nMOVN\n");
						printf("barramento IR opcode: %d\n", IR.instrucao.opcode);
						printf("barramento IR RD: %d\n", IR.instrucao.s_instrucao.rd);
						printf("barramento IR RS: %d\n", IR.instrucao.s_instrucao.rs);
						printf("barramento IR RT: %d\n", IR.instrucao.s_instrucao.rt);
						//exibirLista(listaIssue);
						printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
						excluirElem(listaIssue, 0);
						//exibirLista(listaIssue);
						printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
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
						escrita_bar(in, barIR);
						printf("\nMOVZ\n");
						printf("barramento IR opcode: %d\n", IR.instrucao.opcode);
						printf("barramento IR RD: %d\n", IR.instrucao.s_instrucao.rd);
						printf("barramento IR RS: %d\n", IR.instrucao.s_instrucao.rs);
						printf("barramento IR RT: %d\n", IR.instrucao.s_instrucao.rt);
						//exibirLista(listaIssue);
						printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
						excluirElem(listaIssue, 0);
						//exibirLista(listaIssue);
						printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
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
						escrita_bar(in, barIR);
						printf("\nMTHI\n");
						printf("barramento IR opcode: %d\n", IR.instrucao.opcode);
						printf("barramento IR RS: %d\n", IR.instrucao.s_instrucao.rs);
						//exibirLista(listaIssue);
						printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
						excluirElem(listaIssue, 0);
						//exibirLista(listaIssue);
						printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
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
						escrita_bar(in, barIR);
						printf("\nMTLO\n");
						printf("barramento IR opcode: %d\n", IR.instrucao.opcode);
						printf("barramento IR RS: %d\n", IR.instrucao.s_instrucao.rs);
						//exibirLista(listaIssue);
						printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
						excluirElem(listaIssue, 0);
						//exibirLista(listaIssue);
						printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
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
						escrita_bar(in, barIR);
						printf("\nMUL\n");
						printf("barramento IR opcode: %d\n", IR.instrucao.opcode);
						printf("barramento IR RS: %d\n", IR.instrucao.s_instrucao.rs);
						printf("barramento IR RT: %d\n", IR.instrucao.s_instrucao.rt);
						//exibirLista(listaIssue);
						printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
						excluirElem(listaIssue, 0);
						//exibirLista(listaIssue);
						printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
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
							escrita_bar(in, barIR);
							printf("\nMUL\n");
							printf("barramento IR opcode: %d\n", IR.instrucao.opcode);
							printf("barramento IR RS: %d\n", IR.instrucao.s_instrucao.rs);
							printf("barramento IR RT: %d\n", IR.instrucao.s_instrucao.rt);
							//exibirLista(listaIssue);
							printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
							excluirElem(listaIssue, 0);
							//exibirLista(listaIssue);
							printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
							EMITIDA = true;
						}
					}
				}
				break;
			case NOP:
				if (!UFINT.status.Busy)
				{
					if (bancoRegistradores[in.s_instrucao.rd].UF == semUF)
					{
						UFINT.status.Busy = true;
						UFINT.status.Op = NOP;
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
						escrita_bar(in, barIR);
						printf("\nNOP\n");
						printf("barramento IR opcode: %d\n", IR.instrucao.opcode);
						printf("barramento IR RD: %d\n", IR.instrucao.s_instrucao.rd);
						printf("barramento IR RS: %d\n", IR.instrucao.s_instrucao.rs);
						printf("barramento IR RT: %d\n", IR.instrucao.s_instrucao.rt);
						//exibirLista(listaIssue);
						printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
						excluirElem(listaIssue, 0);
						//exibirLista(listaIssue);
						printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
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
						in.qtd_cloc_prec = 1;
						escrita_bar(in, barIR);
						printf("\nNOR\n");
						printf("barramento IR opcode: %d\n", IR.instrucao.opcode);
						printf("barramento IR RD: %d\n", IR.instrucao.s_instrucao.rd);
						printf("barramento IR RS: %d\n", IR.instrucao.s_instrucao.rs);
						printf("barramento IR RT: %d\n", IR.instrucao.s_instrucao.rt);
						//exibirLista(listaIssue);
						printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
						excluirElem(listaIssue, 0);
						//exibirLista(listaIssue);
						printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
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
						escrita_bar(in, barIR);
						printf("\nOR\n");
						printf("barramento IR opcode: %d\n", IR.instrucao.opcode);
						printf("barramento IR RD: %d\n", IR.instrucao.s_instrucao.rd);
						printf("barramento IR RS: %d\n", IR.instrucao.s_instrucao.rs);
						printf("barramento IR RT: %d\n", IR.instrucao.s_instrucao.rt);
						//exibirLista(listaIssue);
						printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
						excluirElem(listaIssue, 0);
						//exibirLista(listaIssue);
						printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
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
						escrita_bar(in, barIR);
						printf("\nSUB\n");
						printf("barramento IR opcode: %d\n", IR.instrucao.opcode);
						printf("barramento IR RD: %d\n", IR.instrucao.s_instrucao.rd);
						printf("barramento IR RS: %d\n", IR.instrucao.s_instrucao.rs);
						printf("barramento IR RT: %d\n", IR.instrucao.s_instrucao.rt);
						//exibirLista(listaIssue);
						printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
						excluirElem(listaIssue, 0);
						//exibirLista(listaIssue);
						printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
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
						escrita_bar(in, barIR);
						printf("\nXOR\n");
						printf("barramento IR opcode: %d\n", IR.instrucao.opcode);
						printf("barramento IR RD: %d\n", IR.instrucao.s_instrucao.rd);
						printf("barramento IR RS: %d\n", IR.instrucao.s_instrucao.rs);
						printf("barramento IR RT: %d\n", IR.instrucao.s_instrucao.rt);
						//exibirLista(listaIssue);
						printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
						excluirElem(listaIssue, 0);
						//exibirLista(listaIssue);
						printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
						EMITIDA = true;
					}
				}
				break;
			case MADD: //ver se ta certo//destino é hi e lo
				if (!UFMUL1.status.Busy)
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
						bancoRegistradores[HI].UF = UF_MUL1;
						bancoRegistradores[LO].UF = UF_MUL1;
						in.UF = UF_MUL1;
						in.qtd_cloc_prec = 5;
						escrita_bar(in, barIR);
						printf("\nMADD\n");
						printf("barramento IR opcode: %d\n", IR.instrucao.opcode);
						printf("barramento IR rd: %d\n", IR.instrucao.s2_instrucao.rd);
						printf("barramento IR rs: %d\n", IR.instrucao.s2_instrucao.rs);
						printf("barramento IR rt: %d\n", IR.instrucao.s2_instrucao.rt);
						//exibirLista(listaIssue);
						printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
						excluirElem(listaIssue, 0);
						//exibirLista(listaIssue);
						printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
						EMITIDA = true;
					}
				}
				else if (!UFMUL2.status.Busy)
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
						bancoRegistradores[HI].UF = UF_MUL2;
						bancoRegistradores[LO].UF = UF_MUL2;
						in.UF = UF_MUL2;
						in.qtd_cloc_prec = 5;
						escrita_bar(in, barIR);
						printf("\nMADD\n");
						printf("barramento IR opcode: %d\n", IR.instrucao.opcode);
						printf("barramento IR rd: %d\n", IR.instrucao.s2_instrucao.rd);
						printf("barramento IR rs: %d\n", IR.instrucao.s2_instrucao.rs);
						printf("barramento IR rt: %d\n", IR.instrucao.s2_instrucao.rt);
						//exibirLista(listaIssue);
						printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
						excluirElem(listaIssue, 0);
						//exibirLista(listaIssue);
						printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
						EMITIDA = true;
					}
				}
				break;
			case MSUB: //ver se ta certo
				if (!UFMUL1.status.Busy)
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
						bancoRegistradores[HI].UF = UF_MUL1;
						bancoRegistradores[LO].UF = UF_MUL1;
						in.UF = UF_MUL1;
						in.qtd_cloc_prec = 5;
						escrita_bar(in, barIR);
						printf("\nMSUB\n");
						printf("barramento IR opcode: %d\n", IR.instrucao.opcode);
						printf("barramento IR rd: %d\n", IR.instrucao.s2_instrucao.rd);
						printf("barramento IR rs: %d\n", IR.instrucao.s2_instrucao.rs);
						printf("barramento IR rt: %d\n", IR.instrucao.s2_instrucao.rt);
						//exibirLista(listaIssue);
						printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
						excluirElem(listaIssue, 0);
						//exibirLista(listaIssue);
						printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
						EMITIDA = true;
					}
				}
				else if (!UFMUL2.status.Busy)
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
						bancoRegistradores[HI].UF = UF_MUL2;
						bancoRegistradores[LO].UF = UF_MUL2;
						in.UF = UF_MUL2;
						in.qtd_cloc_prec = 5;
						escrita_bar(in, barIR);
						printf("\nMSUB\n");
						printf("barramento IR opcode: %d\n", IR.instrucao.opcode);
						printf("barramento IR rd: %d\n", IR.instrucao.s2_instrucao.rd);
						printf("barramento IR rs: %d\n", IR.instrucao.s2_instrucao.rs);
						printf("barramento IR rt: %d\n", IR.instrucao.s2_instrucao.rt);
						//exibirLista(listaIssue);
						printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
						excluirElem(listaIssue, 0);
						//exibirLista(listaIssue);
						printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
						EMITIDA = true;
					}
				}
				break;
			case MUL:
				if (!UFMUL1.status.Busy)
				{
					if (bancoRegistradores[in.s2_instrucao.rd].UF == semUF)
					{
						printf("\n Antes de atribuir: rt %d, rs %d\n", bancoRegistradores[in.s2_instrucao.rs].UF, bancoRegistradores[in.s2_instrucao.rt].UF);
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
						escrita_bar(in, barIR);
						printf("\n depois de atribuir: rt %d, rs %d\n", bancoRegistradores[in.s2_instrucao.rs].UF, bancoRegistradores[in.s2_instrucao.rt].UF);
						printf("\nMUL\n");
						printf("barramento IR opcode: %d\n", IR.instrucao.opcode);
						printf("barramento IR rd: %d\n", IR.instrucao.s2_instrucao.rd);
						printf("barramento IR rs: %d\n", IR.instrucao.s2_instrucao.rs);
						printf("barramento IR rt: %d\n", IR.instrucao.s2_instrucao.rt);
						//exibirLista(listaIssue);
						printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
						excluirElem(listaIssue, 0);
						//exibirLista(listaIssue);
						printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
						EMITIDA = true;
						printf("\n bem depois de atribuir: rt %d, rs %d\n", bancoRegistradores[in.s2_instrucao.rs].UF, bancoRegistradores[in.s2_instrucao.rt].UF);
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
						escrita_bar(in, barIR);
						printf("\nMUL\n");
						printf("barramento IR opcode: %d\n", IR.instrucao.opcode);
						printf("barramento IR rd: %d\n", IR.instrucao.s2_instrucao.rd);
						printf("barramento IR rs: %d\n", IR.instrucao.s2_instrucao.rs);
						printf("barramento IR rt: %d\n", IR.instrucao.s2_instrucao.rt);
						//exibirLista(listaIssue);
						printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
						excluirElem(listaIssue, 0);
						//exibirLista(listaIssue);
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
						UFINT.status.Fk = semREG;
						UFINT.status.Qj = bancoRegistradores[in.i_instrucao.rs].UF;
						UFINT.status.Qk = semUF;
						UFINT.status.Rj = (bancoRegistradores[in.i_instrucao.rs].UF == semUF) ? true : false;
						UFINT.status.Rk = (bancoRegistradores[in.i_instrucao.imediato].UF == semUF) ? true : false;
						bancoRegistradores[in.i_instrucao.rt].UF = UF_INT;
						in.UF = UF_INT;
						in.qtd_cloc_prec = 1;
						escrita_bar(in, barIR);
						printf("\nADDI\n");
						printf("barramento IR opcode: %d\n", IR.instrucao.opcode);
						printf("barramento IR RS: %d\n", IR.instrucao.i_instrucao.rs);
						printf("barramento IR RT: %d\n", IR.instrucao.i_instrucao.rt);
						printf("barramento IR IMM: %d\n", IR.instrucao.i_instrucao.imediato);
						//exibirLista(listaIssue);
						printf("posição elemento na lista issue: %d\n", listaIssue->lista_inst[in.posicao].posicao);
						excluirElem(listaIssue, 0);
						//exibirLista(listaIssue);
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
						UFINT.status.Fk = semREG;
						UFINT.status.Qj = bancoRegistradores[in.i_instrucao.rs].UF;
						UFINT.status.Qk = semUF;
						UFINT.status.Rj = (bancoRegistradores[in.i_instrucao.rs].UF == semUF) ? true : false;
						UFINT.status.Rk = (bancoRegistradores[in.i_instrucao.imediato].UF == semUF) ? true : false;
						bancoRegistradores[in.i_instrucao.rt].UF = UF_INT;
						in.UF = UF_INT;
						in.qtd_cloc_prec = 1;
						escrita_bar(in, barIR);
						printf("\nANDI\n");
						printf("barramento IR opcode: %d\n", IR.instrucao.opcode);
						printf("barramento IR RS: %d\n", IR.instrucao.i_instrucao.rs);
						printf("barramento IR RT: %d\n", IR.instrucao.i_instrucao.rt);
						printf("barramento IR IMM: %d\n", IR.instrucao.i_instrucao.imediato);
						//exibirLista(listaIssue);
						printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
						excluirElem(listaIssue, 0);
						//exibirLista(listaIssue);
						printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
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
					escrita_bar(in, barIR);
					printf("\nB\n");
					printf("barramento IR opcode: %d\n", IR.instrucao.opcode);
					printf("barramento IR IMM: %d\n", IR.instrucao.i_instrucao.imediato);
					//exibirLista(listaIssue);
					printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
					excluirElem(listaIssue, 0);
					//exibirLista(listaIssue);
					printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
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
					escrita_bar(in, barIR);
					printf("\nBEQ\n");
					printf("barramento IR opcode: %d\n", IR.instrucao.opcode);
					printf("barramento IR RS: %d\n", IR.instrucao.i_instrucao.rs);
					printf("barramento IR IMM: %d\n", IR.instrucao.i_instrucao.imediato);
					//exibirLista(listaIssue);
					printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
					excluirElem(listaIssue, 0);
					//exibirLista(listaIssue);
					printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
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
					escrita_bar(in, barIR);
					printf("\nBEQL\n");
					printf("barramento IR opcode: %d\n", IR.instrucao.opcode);
					printf("barramento IR RS: %d\n", IR.instrucao.i_instrucao.rs);
					printf("barramento IR RT: %d\n", IR.instrucao.i_instrucao.rt);
					printf("barramento IR IMM: %d\n", IR.instrucao.i_instrucao.imediato);
					//exibirLista(listaIssue);
					printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
					excluirElem(listaIssue, 0);
					//exibirLista(listaIssue);
					printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
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
					escrita_bar(in, barIR);
					printf("\nBGTZ\n");
					printf("barramento IR opcode: %d\n", IR.instrucao.opcode);
					printf("barramento IR RS: %d\n", IR.instrucao.i_instrucao.rs);
					printf("barramento IR IMM: %d\n", IR.instrucao.i_instrucao.imediato);
					//exibirLista(listaIssue);
					printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
					excluirElem(listaIssue, 0);
					//exibirLista(listaIssue);
					printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
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
					escrita_bar(in, barIR);
					printf("\nBLEZ\n");
					printf("barramento IR opcode: %d\n", IR.instrucao.opcode);
					printf("barramento IR RS: %d\n", IR.instrucao.i_instrucao.rs);
					printf("barramento IR IMM: %d\n", IR.instrucao.i_instrucao.imediato);
					//exibirLista(listaIssue);
					printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
					excluirElem(listaIssue, 0);
					//exibirLista(listaIssue);
					printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
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
					escrita_bar(in, barIR);
					printf("\nBNE\n");
					printf("barramento IR opcode: %d\n", IR.instrucao.opcode);
					printf("barramento IR RS: %d\n", IR.instrucao.i_instrucao.rs);
					printf("barramento IR RT: %d\n", IR.instrucao.i_instrucao.rt);
					//exibirLista(listaIssue);
					printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
					excluirElem(listaIssue, 0);
					//exibirLista(listaIssue);
					printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
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
					escrita_bar(in, barIR);
					printf("\nJUMP\n");
					printf("barramento IR opcode: %d\n", IR.instrucao.opcode);
					printf("barramento IR addr: %d\n", IR.instrucao.j_instrucao.addr);
					//exibirLista(listaIssue);
					printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
					excluirElem(listaIssue, 0);
					//exibirLista(listaIssue);
					printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
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
					escrita_bar(in, barIR);
					printf("\nBGEZ\n");
					printf("barramento IR opcode: %d\n", IR.instrucao.opcode);
					printf("barramento IR RS: %d\n", IR.instrucao.r_instrucao.rs);
					printf("barramento IR offset: %d\n", IR.instrucao.r_instrucao.offset);
					//exibirLista(listaIssue);
					printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
					excluirElem(listaIssue, 0);
					//exibirLista(listaIssue);
					printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
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
					escrita_bar(in, barIR);
					printf("\nBLTZ\n");
					printf("barramento IR opcode: %d\n", IR.instrucao.opcode);
					printf("barramento IR RS: %d\n", IR.instrucao.r_instrucao.rs);
					printf("barramento IR offset: %d\n", IR.instrucao.r_instrucao.offset);
					//exibirLista(listaIssue);
					printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
					excluirElem(listaIssue, 0);
					//exibirLista(listaIssue);
					printf("posição elemento na lista issue: %d", listaIssue->lista_inst[in.posicao].posicao);
					EMITIDA = true;
				}
				break;
			default:
				EMITIDA = true;
				break;
			}
		}
	}
	printf("\nEMITIDA FIM DA EMISSÃO: %d\n", EMITIDA);
}

void leitura()
{
	printf("\n\t--------------leitura--------------\n");
	printf("\nEMITIDA COMEÇO DA LEITURA: %d\n", EMITIDA);
	if (verifica_bar(barIR))
	{
		in = leitura_bar(barIR);
		inserirElemLista(listaRead, in);
		printf("\nBarramento IR: %d\n", IR.instrucao.opcode);
	}
	for (int i = 0; i < N; i++)
	{
		in = listaRead->lista_inst[i];
		int operacao = descobrirOperacao(in);
		printf("INSTRUÇÃO: %d\n", operacao);
		if (in.posicao == -1)
		{
			continue;
		}
		switch (in.UF)
		{
		case UF_ADD:
			printf("\n\nleitura case uf_add\n\n");
			if ((UFADD.status.Fj != semREG) && (UFADD.status.Fk != semREG))
			{
				printf("\nEntou no 1 if\n");
				if (((bancoRegistradores[in.s_instrucao.rs].UF == semUF) && (bancoRegistradores[in.s_instrucao.rt].UF == semUF)) || (bancoRegistradores[UFADD.status.Fi].UF == bancoRegistradores[UFADD.status.Fj].UF)) //ou fi = fk, ou os 3 iguais
				{
					// bancoRegistradores[in.s_instrucao.rs].UF = UF_ADD;
					// bancoRegistradores[in.s_instrucao.rt].UF = UF_ADD;
					printf("\nEntou no 2 if\n");
					escrita_bar(in, barRE);
					printf("barramento RE: %d\n", RE->instrucao.opcode);
					printf("posição na lista read: %d\n", listaRead->lista_inst[in.posicao].posicao);
					//exibirLista(listaRead);
					excluirElem(listaRead, in.posicao);
					printf("posição na lista read: %d\n", listaRead->lista_inst[in.posicao].posicao);
				}
			}
			else if (UFADD.status.Fj != semREG)
			{
				printf("\nEntou no else if  if\n");
				if ((bancoRegistradores[in.s_instrucao.rs].UF == semUF) || (bancoRegistradores[UFADD.status.Fi].UF == bancoRegistradores[UFADD.status.Fj].UF))
				{
					printf("\nEntou no if do else if if\n");
					escrita_bar(in, barRE);
					printf("barramento RE: %d\n", RE->instrucao.opcode);
					printf("posição na lista read: %d\n", listaRead->lista_inst[in.posicao].posicao);
					//exibirLista(listaRead);
					excluirElem(listaRead, in.posicao);
					printf("posição na lista read: %d\n", listaRead->lista_inst[in.posicao].posicao);
				}
			}
			else
			{
				printf("\nEntou no else\n");
				escrita_bar(in, barRE);
				printf("barramento RE: %d\n", RE->instrucao.opcode);
				printf("posição na lista read: %d\n", listaRead->lista_inst[in.posicao].posicao);
				//exibirLista(listaRead);
				excluirElem(listaRead, in.posicao);
				printf("posição na lista read: %d\n", listaRead->lista_inst[in.posicao].posicao);
			}
			break;
		case UF_DIV:
			printf("\n\nleitura case uf_div\n\n");
			if (((UFDIV.status.Fj != semREG) && (UFDIV.status.Fk != semREG)) || (UFADD.status.Fi == UFADD.status.Fj))
			{
				printf("\nEntou no primeiro if\n");
				if (((bancoRegistradores[in.s_instrucao.rs].UF == semUF) && (bancoRegistradores[in.s_instrucao.rt].UF == semUF)) || (bancoRegistradores[UFDIV.status.Fi].UF == bancoRegistradores[UFDIV.status.Fj].UF))
				{
					printf("\nEntou no if do if\n");
					escrita_bar(in, barRE);
					printf("barramento RE: %d\n", RE->instrucao.opcode);
					printf("posição na lista read: %d\n", listaRead->lista_inst[in.posicao].posicao);
					//exibirLista(listaRead);
					excluirElem(listaRead, in.posicao);
					printf("posição na lista read: %d\n", listaRead->lista_inst[in.posicao].posicao);
				}
			}
			else if (UFDIV.status.Fj != semREG)
			{
				printf("\nEntou no else if\n");
				if ((bancoRegistradores[UFDIV.status.Fj].UF == semUF) || (bancoRegistradores[UFDIV.status.Fi].UF == bancoRegistradores[UFDIV.status.Fj].UF))
				{
					printf("\nEntou no ifdo else if\n");
					escrita_bar(in, barRE);
					printf("barramento RE: %d\n", RE->instrucao.opcode);
					printf("posição na lista read: %d\n", listaRead->lista_inst[in.posicao].posicao);
					//exibirLista(listaRead);
					excluirElem(listaRead, in.posicao);
					printf("posição na lista read: %d\n", listaRead->lista_inst[in.posicao].posicao);
				}
			}
			break;
		case UF_INT:
			printf("\n\nleitura case uf_int\n\n");
			if ((UFINT.status.Fj != semREG) && (UFINT.status.Fk != semREG))
			{
				printf("\nEntou no 1 if\n");
				if (((bancoRegistradores[in.s_instrucao.rs].UF == semUF) && (bancoRegistradores[in.s_instrucao.rt].UF == semUF)) || (bancoRegistradores[UFINT.status.Fi].UF == bancoRegistradores[UFINT.status.Fj].UF))
				{
					printf("\nEntou no 2 if\n");
					escrita_bar(in, barRE);
					printf("barramento RE: %d\n", RE->instrucao.opcode);
					printf("posição na lista read: %d\n", listaRead->lista_inst[in.posicao].posicao);
					//exibirLista(listaRead);
					excluirElem(listaRead, in.posicao);
					printf("posição na lista read: %d\n", listaRead->lista_inst[in.posicao].posicao);
				}
			}
			else if (UFINT.status.Fj != semREG)
			{
				printf("\nEntou no else if\n");
				printf("\nFI: %d\n", bancoRegistradores[UFINT.status.Fi].UF);
				printf("\nFJ: %d\n", bancoRegistradores[UFINT.status.Fj].UF);
				printf("\nAQUI: %d\n", UFADD.status.Fi);
				printf("\nAQUI2: %d\n", UFADD.status.Fj);
				if ((bancoRegistradores[UFINT.status.Fj].UF == semUF) || (bancoRegistradores[UFINT.status.Fi].UF == bancoRegistradores[UFINT.status.Fj].UF))
				{
					printf("\nEntou no if do else if\n");
					escrita_bar(in, barRE);
					printf("barramento RE: %d\n", RE->instrucao.opcode);
					printf("posição na lista read: %d\n", listaRead->lista_inst[in.posicao].posicao);
					//exibirLista(listaRead);
					excluirElem(listaRead, in.posicao);
					printf("posição na lista read: %d\n", listaRead->lista_inst[in.posicao].posicao);
				}
			}
			else
			{
				printf("\nEntou no else \n");
				escrita_bar(in, barRE);
				printf("barramento RE: %d\n", RE->instrucao.opcode);
				printf("posição na lista read: %d\n", listaRead->lista_inst[in.posicao].posicao);
				//exibirLista(listaRead);
				excluirElem(listaRead, in.posicao);
				printf("posição na lista read: %d\n", listaRead->lista_inst[in.posicao].posicao);
			}
			break;
		case UF_MUL1:
			printf("\n\nleitura case uf_mul1\n\n");
			if ((UFMUL1.status.Fj != semREG) && (UFMUL1.status.Fk != semREG))
			{
				printf("\nEntou no 1 if\n");
				printf("UF: %d\n", UFMUL1.status.Fj);
				printf("UF: %d\n", UFMUL1.status.Fk);
				printf("UF: %d\n", bancoRegistradores[in.s2_instrucao.rs].UF);
				printf("UF: %d\n", bancoRegistradores[in.s2_instrucao.rt].UF);
				if ((bancoRegistradores[in.s2_instrucao.rs].UF == semUF) && (bancoRegistradores[in.s2_instrucao.rt].UF == semUF)) //|| (bancoRegistradores[UFMUL1.status.Fi].UF == bancoRegistradores[UFMUL1.status.Fj].UF))
				{
					printf("\nEntou no 2 if\n");
					escrita_bar(in, barRE);
					printf("barramento RE: %d\n", RE->instrucao.opcode);
					printf("posição na lista read: %d\n", listaRead->lista_inst[in.posicao].posicao);
					//exibirLista(listaRead);
					excluirElem(listaRead, in.posicao);
					printf("posição na lista read: %d\n", listaRead->lista_inst[in.posicao].posicao);
				}
			}
			else if (UFMUL1.status.Fj != semREG)
			{
				printf("\nEntou no else if\n");
				if ((bancoRegistradores[in.s2_instrucao.rs].UF == semUF) || (bancoRegistradores[in.s2_instrucao.rt].UF == bancoRegistradores[UFMUL1.status.Fj].UF))
				{
					escrita_bar(in, barRE);
					printf("barramento RE: %d\n", RE->instrucao.opcode);
					printf("posição na lista read: %d\n", listaRead->lista_inst[in.posicao].posicao);
					//exibirLista(listaRead);
					excluirElem(listaRead, in.posicao);
					printf("posição na lista read: %d\n", listaRead->lista_inst[in.posicao].posicao);
				}
			}
			else
			{
				printf("\nEntou no else if\n");
				escrita_bar(in, barRE);
				printf("barramento RE: %d\n", RE->instrucao.opcode);
				printf("posição na lista read: %d\n", listaRead->lista_inst[in.posicao].posicao);
				//exibirLista(listaRead);
				excluirElem(listaRead, in.posicao);
				printf("posição na lista read: %d\n", listaRead->lista_inst[in.posicao].posicao);
			}
			break;
		case UF_MUL2:
			printf("\n\nleitura case uf_mul2\n\n");
			if ((UFMUL2.status.Fj != semREG) && (UFMUL2.status.Fk != semREG))
			{
				printf("\nEntou no 1 if\n");
				if (((bancoRegistradores[in.s2_instrucao.rs].UF == semUF) && (bancoRegistradores[in.s2_instrucao.rt].UF == semUF)) || (bancoRegistradores[UFMUL2.status.Fi].UF == bancoRegistradores[UFMUL2.status.Fj].UF))
				{
					printf("\nEntou no 2 if\n");
					escrita_bar(in, barRE);
					printf("barramento RE: %d\n", RE->instrucao.opcode);
					printf("posição na lista read: %d\n", listaRead->lista_inst[in.posicao].posicao);
					//exibirLista(listaRead);
					excluirElem(listaRead, in.posicao);
					printf("posição na lista read: %d\n", listaRead->lista_inst[in.posicao].posicao);
				}
			}
			else if (UFMUL2.status.Fj != semREG)
			{
				printf("\nEntou no else if\n");
				if ((bancoRegistradores[in.s2_instrucao.rs].UF == semUF) || (bancoRegistradores[in.s2_instrucao.rt].UF == bancoRegistradores[UFMUL2.status.Fj].UF))
				{
					escrita_bar(in, barRE);
					printf("barramento RE: %d\n", RE->instrucao.opcode);
					printf("posição na lista read: %d\n", listaRead->lista_inst[in.posicao].posicao);
					//exibirLista(listaRead);
					excluirElem(listaRead, in.posicao);
					printf("posição na lista read: %d\n", listaRead->lista_inst[in.posicao].posicao);
				}
			}
			else
			{
				printf("\nEntou no else\n");
				escrita_bar(in, barRE);
				printf("barramento RE: %d\n", RE->instrucao.opcode);
				printf("posição na lista read: %d\n", listaRead->lista_inst[in.posicao].posicao);
				//exibirLista(listaRead);
				excluirElem(listaRead, in.posicao);
				printf("posição na lista read: %d\n", listaRead->lista_inst[in.posicao].posicao);
			}
			break;
		}
	}
	printf("\nEMITIDA FIM DA LEITURA: %d\n", EMITIDA);
}

void execucao()
//etapa de execução
{
	printf("\n\t--------------execução--------------\n");
	printf("\nEMITIDA COMEÇO DA EXECUÇÃO: %d\n", EMITIDA);
	while (verifica_bar(barRE))
	{
		in = leitura_bar(barRE);
		printf("barramento RE: %d", RE->instrucao.opcode);
		inserirElemLista(listaExecucao, in);
		printf("elemento na lista execução: %d", listaExecucao->lista_inst[in.posicao].posicao);
		//exibirLista(listaExecucao);
	}
	for (int i = 0; i < N; i++)
	{
		in = listaExecucao->lista_inst[i];
		int operacao = descobrirOperacao(in);
		printf("\nINSTRUÇÃO: %d\n", operacao);
		if (in.posicao == -1)
		{
			continue;
		}

		for (in.cont_clock = 0; in.cont_clock < in.qtd_cloc_prec; in.cont_clock++)
		{
			if (in.cont_clock == 0)
			{
				switch (operacao)
				{
				case ADD:
					bufferRegistradores[in.s_instrucao.rd].valor = adicao(bancoRegistradores[in.s_instrucao.rs].valor, bancoRegistradores[in.s_instrucao.rt].valor);
					printf("ADD opcode: %d\n", in.opcode);
					printf("ADD RS: %d\n", in.s_instrucao.rs);
					printf("ADD RT: %d\n", in.s_instrucao.rt);
					printf("ADD RD: %d\n", in.s_instrucao.rd);
					printf("ADD SHAMT: %d\n", in.s_instrucao.shamt);
					printf("ADD FUNC: %d\n", in.s_instrucao.func);
					printf("resultado ADD: %d\n", bufferRegistradores[in.s_instrucao.rd].valor);
					escrita_bar(in, barEW);
					printf("barramento EW: %d\n", EW->instrucao.opcode);
					//exibirLista(listaExecucao);
					printf("elemento na lista execução dentro do int: %d", listaExecucao->lista_inst[in.posicao].posicao);
					excluirElem(listaExecucao, in.posicao);
					printf("elemento na lista execução: %d", listaExecucao->lista_inst[in.posicao].posicao);
					break;
				case AND:
					bufferRegistradores[in.s_instrucao.rd].valor = and(bancoRegistradores[in.s_instrucao.rs].valor, bancoRegistradores[in.s_instrucao.rt].valor);
					printf("AND opcode: %d\n", in.opcode);
					printf("AND RS: %d\n", in.s_instrucao.rs);
					printf("AND RT: %d\n", in.s_instrucao.rt);
					printf("AND RD: %d\n", in.s_instrucao.rd);
					printf("AND SHAMT: %d\n", in.s_instrucao.shamt);
					printf("AND FUNC: %d\n", in.s_instrucao.func);
					printf("resultado AND: %d\n", bufferRegistradores[in.s_instrucao.rd].valor);
					escrita_bar(in, barEW);
					printf("barramento EW: %d\n", EW->instrucao.opcode);
					//exibirLista(listaExecucao);
					printf("elemento na lista execução dentro do int: %d", listaExecucao->lista_inst[in.posicao].posicao);
					excluirElem(listaExecucao, in.posicao);
					printf("elemento na lista execução: %d", listaExecucao->lista_inst[in.posicao].posicao);
					break;
				case DIV:
					bufferRegistradores[in.s_instrucao.rd].valor = divisao(bancoRegistradores[in.s_instrucao.rs].valor, bancoRegistradores[in.s_instrucao.rt].valor);
					bufferRegistradores[HI].valor = bufferRegistradores[in.s_instrucao.rd].valor;
					bufferRegistradores[LO].valor = bancoRegistradores[in.s_instrucao.rs].valor % bancoRegistradores[in.s_instrucao.rt].valor;
					printf("DIV opcode: %d\n", in.opcode);
					printf("DIV RS: %d\n", in.s_instrucao.rs);
					printf("DIV RT: %d\n", in.s_instrucao.rt);
					printf("DIV RD: %d\n", in.s_instrucao.rd);
					printf("DIV SHAMT: %d\n", in.s_instrucao.shamt);
					printf("DIV FUNC: %d\n", in.s_instrucao.func);
					//printf("resultado DIV: %d\n", bufferRegistradores[in.s_instrucao.rd].valor);
					escrita_bar(in, barEW);
					printf("barramento EW: %d\n", EW->instrucao.opcode);
					//exibirLista(listaExecucao);
					printf("elemento na lista execução dentro do divisao: %d", listaExecucao->lista_inst[in.posicao].posicao);
					excluirElem(listaExecucao, in.posicao);
					printf("elemento na lista execução: %d", listaExecucao->lista_inst[in.posicao].posicao);
					break;
				case JR:
					PC = bancoRegistradores[in.s_instrucao.rs].valor;
					printf("JR opcode: %d\n", in.opcode);
					printf("JR RS: %d\n", in.s_instrucao.rs);
					printf("JR RT: %d\n", in.s_instrucao.rt);
					printf("JR RD: %d\n", in.s_instrucao.rd);
					printf("JR SHAMT: %d\n", in.s_instrucao.shamt);
					printf("JR FUNC: %d\n", in.s_instrucao.func);
					printf("resultado/PC JR: %d\n", bufferRegistradores[in.s_instrucao.rs].valor);
					escrita_bar(in, barEW);
					printf("barramento EW: %d\n", EW->instrucao.opcode);
					//exibirLista(listaExecucao);
					printf("elemento na lista execução dentro do int: %d", listaExecucao->lista_inst[in.posicao].posicao);
					excluirElem(listaExecucao, in.posicao);
					printf("elemento na lista execução: %d", listaExecucao->lista_inst[in.posicao].posicao);
					break;
				case MFHI:
					bufferRegistradores[in.s_instrucao.rd].valor = bancoRegistradores[HI].valor;
					printf("MFHI opcode: %d\n", in.opcode);
					printf("MFHI RS: %d\n", in.s_instrucao.rs);
					printf("MFHI RT: %d\n", in.s_instrucao.rt);
					printf("MFHI RD: %d\n", in.s_instrucao.rd);
					printf("MFHI SHAMT: %d\n", in.s_instrucao.shamt);
					printf("MFHI FUNC: %d\n", in.s_instrucao.func);
					printf("resultado MFHI: %d\n", bufferRegistradores[in.s_instrucao.rd].valor);
					escrita_bar(in, barEW);
					printf("barramento EW: %d\n", EW->instrucao.opcode);
					//exibirLista(listaExecucao);
					printf("elemento na lista execução dentro do int: %d", listaExecucao->lista_inst[in.posicao].posicao);
					excluirElem(listaExecucao, in.posicao);
					printf("elemento na lista execução: %d", listaExecucao->lista_inst[in.posicao].posicao);
					break;
				case MFLO:
					bufferRegistradores[in.s_instrucao.rd].valor = bancoRegistradores[LO].valor;
					printf("MFLO opcode: %d\n", in.opcode);
					printf("MFLO RS: %d\n", in.s_instrucao.rs);
					printf("MFLO RT: %d\n", in.s_instrucao.rt);
					printf("MFLO RD: %d\n", in.s_instrucao.rd);
					printf("MFLO SHAMT: %d\n", in.s_instrucao.shamt);
					printf("MFLO FUNC: %d\n", in.s_instrucao.func);
					printf("resultado MFLO: %d\n", bufferRegistradores[in.s_instrucao.rd].valor);
					escrita_bar(in, barEW);
					printf("barramento EW: %d\n", EW->instrucao.opcode);
					//exibirLista(listaExecucao);
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
					printf("MOVN RD: %d\n", in.s_instrucao.rd);
					printf("MOVN SHAMT: %d\n", in.s_instrucao.shamt);
					printf("MOVN FUNC: %d\n", in.s_instrucao.func);
					printf("resultado MOVN: %d\n", bufferRegistradores[in.s_instrucao.rd].valor);
					escrita_bar(in, barEW);
					printf("barramento EW: %d\n", EW->instrucao.opcode);
					//exibirLista(listaExecucao);
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
					printf("MOVZ RD: %d\n", in.s_instrucao.rd);
					printf("MOVZ SHAMT: %d\n", in.s_instrucao.shamt);
					printf("MOVZ FUNC: %d\n", in.s_instrucao.func);
					printf("resultado MOVZ: %d\n", bufferRegistradores[in.s_instrucao.rd].valor);
					escrita_bar(in, barEW);
					printf("barramento EW: %d\n", EW->instrucao.opcode);
					//exibirLista(listaExecucao);
					printf("elemento na lista execução dentro do int: %d", listaExecucao->lista_inst[in.posicao].posicao);
					excluirElem(listaExecucao, in.posicao);
					printf("elemento na lista execução: %d", listaExecucao->lista_inst[in.posicao].posicao);
					break;
				case MTHI: //ver isso
					bufferRegistradores[HI].valor = bancoRegistradores[in.s_instrucao.rs].valor;
					printf("MTHI opcode: %d\n", in.opcode);
					printf("MTHI RS: %d\n", in.s_instrucao.rs);
					printf("MTHI RT: %d\n", in.s_instrucao.rt);
					printf("MTHI RD: %d\n", in.s_instrucao.rd);
					printf("MTHI SHAMT: %d\n", in.s_instrucao.shamt);
					printf("MTHI FUNC: %d\n", in.s_instrucao.func);
					printf("resultado MTHI: %d\n", bufferRegistradores[HI].valor);
					escrita_bar(in, barEW);
					printf("barramento EW: %d\n", EW->instrucao.opcode);
					//exibirLista(listaExecucao);
					printf("elemento na lista execução dentro do int: %d", listaExecucao->lista_inst[in.posicao].posicao);
					excluirElem(listaExecucao, in.posicao);
					printf("elemento na lista execução: %d", listaExecucao->lista_inst[in.posicao].posicao);
					break;
				case MTLO:
					bufferRegistradores[LO].valor = bancoRegistradores[in.s_instrucao.rs].valor;
					printf("MTLO opcode: %d\n", in.opcode);
					printf("MTLO RS: %d\n", in.s_instrucao.rs);
					printf("MTLO RT: %d\n", in.s_instrucao.rt);
					printf("MTLO RD: %d\n", in.s_instrucao.rd);
					printf("MTLO SHAMT: %d\n", in.s_instrucao.shamt);
					printf("MTLO FUNC: %d\n", in.s_instrucao.func);
					printf("resultado MTLO: %d\n", bufferRegistradores[LO].valor);
					escrita_bar(in, barEW);
					printf("barramento EW: %d\n", EW->instrucao.opcode);
					//exibirLista(listaExecucao);
					printf("elemento na lista execução dentro do int: %d", listaExecucao->lista_inst[in.posicao].posicao);
					excluirElem(listaExecucao, in.posicao);
					printf("elemento na lista execução: %d", listaExecucao->lista_inst[in.posicao].posicao);
					break;
				case MULT:
					separarHILO(multiplicacao(bancoRegistradores[in.s_instrucao.rs].valor, bancoRegistradores[in.s_instrucao.rt].valor));
					printf("MULT opcode: %d\n", in.opcode);
					printf("MULT RS: %d\n", in.s_instrucao.rs);
					printf("MULT RT: %d\n", in.s_instrucao.rt);
					printf("MULT RD: %d\n", in.s_instrucao.rd);
					printf("MULT SHAMT: %d\n", in.s_instrucao.shamt);
					printf("MULT FUNC: %d\n", in.s_instrucao.func);
					//printf("resultado MULT: %d\n", bufferRegistradores[in.i_instrucao.rt].valor);
					escrita_bar(in, barEW);
					printf("barramento EW: %d\n", EW->instrucao.opcode);
					//exibirLista(listaExecucao);
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
					printf("NOR RD: %d\n", in.s_instrucao.rd);
					printf("NOR SHAMT: %d\n", in.s_instrucao.shamt);
					printf("NOR FUNC: %d\n", in.s_instrucao.func);
					printf("resultado NOR: %d\n", bufferRegistradores[in.s_instrucao.rd].valor);
					escrita_bar(in, barEW);
					printf("barramento EW: %d\n", EW->instrucao.opcode);
					//exibirLista(listaExecucao);
					printf("elemento na lista execução dentro do int: %d", listaExecucao->lista_inst[in.posicao].posicao);
					excluirElem(listaExecucao, in.posicao);
					printf("elemento na lista execução: %d", listaExecucao->lista_inst[in.posicao].posicao);
					break;
				case OR:
					bufferRegistradores[in.s_instrucao.rd].valor = or (bancoRegistradores[in.s_instrucao.rs].valor, bancoRegistradores[in.s_instrucao.rt].valor);
					printf("OR opcode: %d\n", in.opcode);
					printf("OR RS: %d\n", in.s_instrucao.rs);
					printf("OR RT: %d\n", in.s_instrucao.rt);
					printf("OR RD: %d\n", in.s_instrucao.rd);
					printf("OR SHAMT: %d\n", in.s_instrucao.shamt);
					printf("OR FUNC: %d\n", in.s_instrucao.func);
					printf("resultado OR: %d\n", bufferRegistradores[in.s_instrucao.rd].valor);
					escrita_bar(in, barEW);
					printf("barramento EW: %d\n", EW->instrucao.opcode);
					//exibirLista(listaExecucao);
					printf("elemento na lista execução dentro do int: %d", listaExecucao->lista_inst[in.posicao].posicao);
					excluirElem(listaExecucao, in.posicao);
					printf("elemento na lista execução: %d", listaExecucao->lista_inst[in.posicao].posicao);
					break;
				case SUB:
					bufferRegistradores[in.s_instrucao.rd].valor = subtracao(bancoRegistradores[in.s_instrucao.rs].valor, bancoRegistradores[in.s_instrucao.rt].valor);
					printf("SUB opcode: %d\n", in.opcode);
					printf("SUB RS: %d\n", in.s_instrucao.rs);
					printf("SUB RT: %d\n", in.s_instrucao.rt);
					printf("SUB RD: %d\n", in.s_instrucao.rd);
					printf("SUB SHAMT: %d\n", in.s_instrucao.shamt);
					printf("SUB FUNC: %d\n", in.s_instrucao.func);
					printf("resultado SUB: %d\n", bufferRegistradores[in.s_instrucao.rd].valor);
					escrita_bar(in, barEW);
					printf("barramento EW: %d\n", EW->instrucao.opcode);
					//exibirLista(listaExecucao);
					printf("elemento na lista execução dentro do int: %d", listaExecucao->lista_inst[in.posicao].posicao);
					excluirElem(listaExecucao, in.posicao);
					printf("elemento na lista execução: %d", listaExecucao->lista_inst[in.posicao].posicao);
					break;
				case XOR:
					bufferRegistradores[in.s_instrucao.rd].valor = xor(bancoRegistradores[in.s_instrucao.rs].valor, bancoRegistradores[in.s_instrucao.rt].valor);
					printf("XOR opcode: %d\n", in.opcode);
					printf("XOR RS: %d\n", in.s_instrucao.rs);
					printf("XOR RT: %d\n", in.s_instrucao.rt);
					printf("XOR RD: %d\n", in.s_instrucao.rd);
					printf("XOR SHAMT: %d\n", in.s_instrucao.shamt);
					printf("XOR FUNC: %d\n", in.s_instrucao.func);
					printf("resultado XOR: %d\n", bufferRegistradores[in.s_instrucao.rd].valor);
					escrita_bar(in, barEW);
					printf("barramento EW: %d\n", EW->instrucao.opcode);
					//exibirLista(listaExecucao);
					printf("elemento na lista execução dentro do int: %d", listaExecucao->lista_inst[in.posicao].posicao);
					excluirElem(listaExecucao, in.posicao);
					printf("elemento na lista execução: %d", listaExecucao->lista_inst[in.posicao].posicao);
					break;
				case MADD: //MAIS SIG SOMA PRO HI E 16 MENOS SOMA PRO LO
					bufferRegistradores[in.s2_instrucao.rd].valor = multiplicacao(bancoRegistradores[in.s2_instrucao.rs].valor, bancoRegistradores[in.s2_instrucao.rt].valor);
					bufferRegistradores[HI].valor = adicao(bufferRegistradores[in.s2_instrucao.rd].valor >> 16, bancoRegistradores[HI].valor);
					bufferRegistradores[LO].valor = adicao(bufferRegistradores[in.s2_instrucao.rd].valor << 16, bancoRegistradores[LO].valor);
					//fazer o msm pro lo
					printf("MADD opcode: %d\n", in.opcode);
					printf("MADD RS: %d\n", in.s2_instrucao.rs);
					printf("MADD RT: %d\n", in.s2_instrucao.rt);
					printf("MADD RD: %d\n", in.s2_instrucao.rd);
					printf("MADD SHAMT: %d\n", in.s2_instrucao.shamt);
					printf("MADD FUNC: %d\n", in.s2_instrucao.func);
					printf("resultado MADD: %d\n", bufferRegistradores[HI].valor);
					escrita_bar(in, barEW);
					printf("barramento EW: %d\n", EW->instrucao.opcode);
					//exibirLista(listaExecucao);
					printf("elemento na lista execução dentro do int: %d", listaExecucao->lista_inst[in.posicao].posicao);
					excluirElem(listaExecucao, in.posicao);
					printf("elemento na lista execução: %d", listaExecucao->lista_inst[in.posicao].posicao);
					break;
				case MSUB:
					bancoRegistradores[in.s2_instrucao.rd].valor = multiplicacao(bancoRegistradores[in.s2_instrucao.rs].valor, bancoRegistradores[in.s2_instrucao.rt].valor);
					bufferRegistradores[HI].valor = subtracao(bufferResultado.valor, juntarHILO(bancoRegistradores[HI].valor, bancoRegistradores[LO].valor));
					printf("MSUB opcode: %d\n", in.opcode);
					printf("MSUB RS: %d\n", in.s2_instrucao.rs);
					printf("MSUB RT: %d\n", in.s2_instrucao.rt);
					printf("MSUB RD: %d\n", in.s2_instrucao.rd);
					printf("MSUB SHAMT: %d\n", in.s2_instrucao.shamt);
					printf("MSUB FUNC: %d\n", in.s2_instrucao.func);
					printf("resultado MSUB: %d\n", bufferRegistradores[HI].valor);
					escrita_bar(in, barEW);
					printf("barramento EW: %d\n", EW->instrucao.opcode);
					//exibirLista(listaExecucao);
					printf("elemento na lista execução dentro do int: %d", listaExecucao->lista_inst[in.posicao].posicao);
					excluirElem(listaExecucao, in.posicao);
					printf("elemento na lista execução: %d", listaExecucao->lista_inst[in.posicao].posicao);
					break;
				case MUL:
					bufferRegistradores[in.s2_instrucao.rd].valor = multiplicacao(bancoRegistradores[in.s2_instrucao.rs].valor, bancoRegistradores[in.s2_instrucao.rt].valor);
					printf("MUL opcode: %d\n", in.opcode);
					printf("MUL RS: %d\n", in.s2_instrucao.rs);
					printf("MUL RT: %d\n", in.s2_instrucao.rt);
					printf("MUL RD: %d\n", in.s2_instrucao.rd);
					printf("MUL SHAMT: %d\n", in.s2_instrucao.shamt);
					printf("MUL FUNC: %d\n", in.s2_instrucao.func);
					printf("resultado MUL: %d\n", bufferRegistradores[in.s2_instrucao.rd].valor);
					escrita_bar(in, barEW);
					printf("barramento EW: %d\n", EW->instrucao.opcode);
					//exibirLista(listaExecucao);
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
					//exibirLista(listaExecucao);
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
					//exibirLista(listaExecucao);
					printf("elemento na lista execução dentro do int: %d", listaExecucao->lista_inst[in.posicao].posicao);
					excluirElem(listaExecucao, in.posicao);
					printf("elemento na lista execução: %d", listaExecucao->lista_inst[in.posicao].posicao);
					break;
				case B:
					PC = in.i_instrucao.imediato; //arrumar em todos pra = só
					printf("B opcode: %d\n", in.opcode);
					printf("B RS: %d\n", in.i_instrucao.rs);
					printf("B RT: %d\n", in.i_instrucao.rt);
					printf("B IMM: %d\n", in.i_instrucao.imediato);
					printf("resultado/PC B: %d\n", PC);
					escrita_bar(in, barEW);
					printf("barramento EW: %d\n", EW->instrucao.opcode);
					//exibirLista(listaExecucao);
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
					printf("resultado/PC BEQ: %d\n", PC);
					escrita_bar(in, barEW);
					printf("barramento EW: %d\n", EW->instrucao.opcode);
					//exibirLista(listaExecucao);
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
					printf("resultado/PC BEQL: %d\n", PC);
					escrita_bar(in, barEW);
					printf("barramento EW: %d\n", EW->instrucao.opcode);
					//exibirLista(listaExecucao);
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
					printf("resultado/PC BGTZ: %d\n", PC);
					escrita_bar(in, barEW);
					printf("barramento EW: %d\n", EW->instrucao.opcode);
					//exibirLista(listaExecucao);
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
					printf("resultado/PC BLEZ: %d\n", PC);
					escrita_bar(in, barEW);
					printf("barramento EW: %d\n", EW->instrucao.opcode);
					//exibirLista(listaExecucao);
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
					printf("resultado/PC BNE: %d\n", PC);
					escrita_bar(in, barEW);
					printf("barramento EW: %d\n", EW->instrucao.opcode);
					//exibirLista(listaExecucao);
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
					//exibirLista(listaExecucao);
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
					//exibirLista(listaExecucao);
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
					//exibirLista(listaExecucao);
					printf("elemento na lista execução dentro do int: %d", listaExecucao->lista_inst[in.posicao].posicao);
					excluirElem(listaExecucao, in.posicao);
					printf("elemento na lista execução: %d", listaExecucao->lista_inst[in.posicao].posicao);
					break;
				case J:
					PC = in.j_instrucao.addr;
					printf("J opcode: %d\n", in.opcode);
					printf("J RS: %d\n", in.j_instrucao.addr);
					printf("resultado/PC J: %d\n", PC);
					escrita_bar(in, barEW);
					printf("barramento EW: %d\n", EW->instrucao.opcode);
					//exibirLista(listaExecucao);
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
					printf("resultado BGEZ: %d\n", PC);
					escrita_bar(in, barEW);
					printf("barramento EW: %d\n", EW->instrucao.opcode);
					//exibirLista(listaExecucao);
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
					printf("resultado BLTZ: %d\n", PC);
					escrita_bar(in, barEW);
					printf("barramento EW: %d\n", EW->instrucao.opcode);
					//exibirLista(listaExecucao);
					printf("elemento na lista execução dentro do int: %d", listaExecucao->lista_inst[in.posicao].posicao);
					excluirElem(listaExecucao, in.posicao);
					printf("elemento na lista execução: %d", listaExecucao->lista_inst[in.posicao].posicao);
					break;
				}
			}
		}
	}
	printf("\nEMITIDA FIM DA EXECUÇÃO: %d\n", EMITIDA);
}

void escritaPipeline()
{
	printf("\n\t--------------escrita--------------\n");
	printf("\nEMITIDA COMEÇO DA ESCRITA: %d\n", EMITIDA);
	while (verifica_bar(barEW))
	{
		in = leitura_bar(barEW);
		inserirElemLista(listaWriteB, in);
		//exibirLista(listaWriteB);
		printf("barramento EW: %d", EW->instrucao.opcode);
	}
	for (int i = 0; i < N; i++)
	{
		in = listaWriteB->lista_inst[i];
		int operacao = descobrirOperacao(in);
		printf("\nINSTRUÇÃO: %d\n", operacao);
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
			// bancoRegistradores[in.s_instrucao.rs].UF = semUF;
			// bancoRegistradores[in.s_instrucao.rt].UF = semUF;
			excluirElem(listaWriteB, in.posicao);
			break;
		case ESPECIAL2:

			bancoRegistradores[in.s2_instrucao.rd].valor = bufferRegistradores[in.s2_instrucao.rd].valor;
			bancoRegistradores[in.s2_instrucao.rd].UF = semUF;
			excluirElem(listaWriteB, in.posicao);
			break;
		case SALTO:

			bancoRegistradores[in.j_instrucao.addr].valor = bufferRegistradores[in.j_instrucao.addr].valor;
			bancoRegistradores[in.j_instrucao.addr].UF = semUF;
			excluirElem(listaWriteB, in.posicao);
			break;
		case REGIMM:

			bancoRegistradores[in.r_instrucao.rs].valor = bufferRegistradores[in.r_instrucao.rs].valor;
			bancoRegistradores[in.r_instrucao.rs].UF = semUF;
			excluirElem(listaWriteB, in.posicao);
			break;
		default:

			bancoRegistradores[in.i_instrucao.rt].valor = bufferRegistradores[in.i_instrucao.rt].valor;
			bancoRegistradores[in.i_instrucao.rt].UF = semUF;
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
	printf("\nEMITIDA FIM DA ESCRITA: %d\n", EMITIDA);
}
