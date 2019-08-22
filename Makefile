ARQ=./*.c
CXX=gcc

all:
	$(CXX) tradutor.c simulador.c ula.c memoria.c instrucoes.c registradores.c fila.c lista.c pipeline.c barramento.c hash.c print.c -o mips32