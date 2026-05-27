cflags = -std=c99 -O2 
dflags = -std=c99 -g
includes = -I ../iostring -I ../structures/tablashash/cuadratica -I ../structures/arbol -I ../structures/pila
libs = ../../lib -liostring -lHashQ -lArbol -lPila 
source = $(wildcard *.c) 
output = ../../bin/practica9

build :
	gcc $(cflags) $(source) -o $(output) $(includes) -L $(libs)
	@echo "Compilo Exitosamente!!!"
run :
	$(output).exe

