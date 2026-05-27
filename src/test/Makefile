cflags = -Wall -Werror -std=c99 -O2
dflags = -Wall -Werror -std=c99 -g
includes = -I ../iostring -I ../structures/nodos -I ../structures/lista -I ../structures/lista -I ../structures/listadoble -I ../structures/pila -I ../structures/cola
libs = ../../lib -liostring -lLista -lListaDoble -lPila -lCola
source = $(wildcard *.c) 
output = ../../bin/test

build :
	gcc $(cflags) $(source) -o $(output) $(includes) -L $(libs)
	@echo "Compilo Exitosamente!!!"
rebuild:
	make -C ..\iostring
	make -C ..\structures\nodos
	make -C ..\structures\lista
	make -C ..\structures\listadoble
	make -C ..\structures\pila
	make -C ..\structures\cola
	gcc $(cflags) $(source) -o $(output) $(includes) -L $(libs)
	@echo "Compilo Exitosamente!!!"