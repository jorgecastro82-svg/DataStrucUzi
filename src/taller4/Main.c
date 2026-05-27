
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>
#include <iostring.h>
#include <heap.h>
#include <arbol.h>
#include <pila.h>

int* crearEntero(int);
int compararEntero(void*,void*);
void imprimirEntero(void*);


int main(void)
{
	Heap heap = crearHeap(HEAP_MAX,compararEntero,imprimirEntero);
	printf("\n INICIO");
	insertarHeap(&heap, crearEntero(7));
	insertarHeap(&heap, crearEntero(4));
	insertarHeap(&heap, crearEntero(5));
	insertarHeap(&heap, crearEntero(2));
	insertarHeap(&heap, crearEntero(1));
	insertarHeap(&heap, crearEntero(3));
	
	imprimirHeap(heap);
	printf("\n");
	imprimirArbol(heapToTree(&heap,imprimirEntero,compararEntero));
	
	heap.tipo = HEAP_MIN;
	heapify(&heap);
	imprimirHeap(heap);
	printf("\n");
	imprimirArbol(heapToTree(&heap,imprimirEntero,compararEntero));
	
	while(heap.cantidad)
	{
		printf("\n Cantidad:  %d",heap.cantidad);
		void *dato = eliminarHeap(&heap);
		printf("\n Dato eliminado: ");
		imprimirEntero(dato);
		free(dato);
	}



	printf("\n\n FIN DE PROGRAMA\n");
	
	
	return 0;
}



int* crearEntero(int dato)
{
	int *nuevo = malloc(sizeof(int));
	*nuevo = dato;
	return nuevo;
}

int compararEntero(void*a,void*b)
{
	int *aa = a,*bb=b;
	if(*aa==*bb)return 0;
	else if(*aa<*bb)return -1;
	else return 1;
}

void imprimirEntero(void *a)
{
	int *aa=a;
	printf("%d",*aa);
}