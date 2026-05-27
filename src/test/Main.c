#include <stdio.h>
#include <iostring.h>
#include <lista.h>
#include <listadoble.h>
#include <pila.h>
#include <cola.h>
#include "Alumno.h"

void imprimirEntero(void *dato);


int main()
{
	Pila pila = {NULL,0,4,imprimirEntero,NULL};
	Cola cola = {NULL,NULL,0,4,imprimirEntero};
	int arreglo[6] = {1,5,4,3,5,9};
	for(int i=0; i<6;i++)
	{
		pushDato(&pila,&arreglo[i]);
		agregarCola(&cola,&arreglo[i]);
	}
	
	imprimirPila(pila);
	imprimirCola(cola);
	
	for(int i=0; i<3;i++)
	{
		popDato(&pila);
		removerCola(&cola);
	}
	
	
	imprimirPila(pila);
	imprimirCola(cola);

	return 0;
}

void imprimirEntero(void *dato)
{
	int *datoA = dato;
	printf(" %d",*datoA);
}
