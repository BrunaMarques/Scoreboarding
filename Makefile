ARQ=./*.c
CXX=gcc

all:
	$(CXX) simulador.c memoria.c instrucoes.c registradores.c fila.c pipeline.c