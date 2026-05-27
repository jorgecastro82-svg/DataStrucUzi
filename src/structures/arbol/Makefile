cflags = -Wall -Werror -std=c99 -O2 -c
dflags = -Wall -Werror-std=c99 -g
sourceNodo = ../nodos/nodoarbol.o
sourcePila = ../pila/pila.o
source = $(wildcard *.c)
source_o = $(wildcard *.o)
output = ../../../lib/libArbol.a

build :
	gcc $(cflags) $(source) 
	ar rcs $(output) $(source_o) $(sourceNodo) $(sourcePila) 
	@echo "Compilo Exitosamente!!!"