ARQ=./*.c
CXX=gcc

all:
	$(CXX) simulador.c ula.c memoria.c instrucoes.c registradores.c fila.c pipeline.c barramento.c -o mips32