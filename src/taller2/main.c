#include <stdio.h>
#include <iostring.h>
#include <lista.h>
#include <listadoble.h>
#include <pila.h>
#include <stdbool.h>

void imprimirEntero(void *dato);

//mover a header pila
//void ordenarPila( Pila *pila, int (*comparar)(void*,void*) );

int compEntero( void *a,void *b);

#define SIZE 7
int main()
{	
	
	Pila pila = {NULL,0,SIZE,imprimirEntero,NULL};
	
	int arreglo[SIZE] = {8,5,6,10,2,3,9};
	for(int i = 0; i < SIZE;i++)
		pushDato(&pila,arreglo + i);

	printf("\nPila original");
	imprimirPila(pila);
	printf("\n");

	ordenarPila(&pila,compEntero);

	printf("\nPila ordenada");
	imprimirPila(pila);
	printf("\n");

	return 0;
}

int compEntero( void *a,void *b)
{
	int *pA,*pB;
	pA = a;
	pB = b;
	return *pA - *pB;
}

void imprimirEntero(void *dato)
{
	int *datoA = dato;
	printf(" %d",*datoA);
}

/*
void ordenarPila( Pila *pila, int (*comparar)(void*,void*) ){
	if(pilaVacia(*pila))
		return;
		
	Pila p1 = {NULL,0,pila->capacidad,pila->imprimir,pila->liberar};
	Pila p2 = {NULL,0,pila->capacidad,pila->imprimir,pila->liberar};
	int *auxInt = NULL;
	
	while(!pilaLlena(p2)){
		
		//caso final
		if(!auxInt)
			auxInt = peekDato(pila);
		
		//buscar mas grande de la pila y mover a p1
		while(!pilaVacia(*pila)){
			if(comparar(auxInt,peekDato(pila)) < 0){
				auxInt = peekDato(pila);
			}
			pushDato(&p1,popDato(pila));
		}

		//meter los equivalentes a esos a pila 2, caso contrario a pila original
		while(!pilaVacia(p1)){
			if(comparar(auxInt,peekDato(&p1)) == 0){
				pushDato(&p2,popDato(&p1));
			}
			else
				pushDato(pila,popDato(&p1));
		}
		imprimirPila(p2);
		auxInt = NULL;

	}
	
	*pila = p2;
	//EN CASO DE QUE LA IMPRESION SE QUISIERA ALREVEZ ENTONCES COMENTAR LO DE DARRIBA
	//while(!pilaVacia(p2))
			//pushDato(pila,popDato(&p2));
}
			*/