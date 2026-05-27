#include "pila.h"
 
void* peekPila(Pila pila)
{
	if(pilaVacia(pila))
		return NULL;
	else
		return pila.cima->dato;
}

//VERIFICIACION
int pilaVacia(Pila pila)
{
	return pila.cima == NULL && pila.cantidad==0;
}

int pilaLlena(Pila pila)
{
	return pila.cantidad == pila.capacidad;
}

//DATOS
void pushDato(Pila *pila,void *dato)
{
	if(pilaLlena(*pila))
	{
		printf("\nOVERFLOW");
		return;
	}
	Nodo *nuevaCima = crearNodo(dato);
	nuevaCima->sig = pila->cima;	
	pila->cima = nuevaCima; 
	pila->cantidad++;
}


void* popDato(Pila *pila)
{
	void *dato = NULL;
	if(pilaVacia(*pila))
	{
		printf("\nUNDERFLOW");
		return dato;	
	}
	Nodo *cimaVieja = pila->cima;
	pila->cima = pila->cima->sig;	
	dato = cimaVieja->dato;
	free(cimaVieja);
	pila->cantidad--;	
	return dato;
}

//peek dato
void* peekDato(Pila *pila){	
	return pila->cima->dato;
}

//NODOS
void pushNodo(Pila *pila,Nodo *nodo)
{
	if(pilaLlena(*pila))
	{
		printf("\nOVERFLOW");
		return;
	}
	nodo->sig = pila->cima;	
	pila->cima = nodo; 
	pila->cantidad++;
}

Nodo* popNodo(Pila *pila)
{
	Nodo *cimaVieja = NULL;
	if(pilaVacia(*pila))
	{
		printf("\nUNDERFLOW");
		return cimaVieja;	
	}
	cimaVieja = pila->cima;
	pila->cima = pila->cima->sig;	
	pila->cantidad--;	
	cimaVieja->sig = NULL;
	return cimaVieja;
} 

//VACIAR/ELIMINAR PILA
void vaciarPila(Pila *pila)
{
	while(!pilaVacia(*pila))
	{
		popDato(pila);
	}
}

void eliminarPila(Pila *pila)
{
	while(!pilaVacia(*pila))
	{
		void * dato = popDato(pila);
		if(pila->liberar)
			pila->liberar(dato);
	}	
}
 

//IMPRIMIR RESPETAR LIFO
void imprimirPila(Pila pila)
{	
		
	Pila aux = {NULL,0,-1,NULL,NULL};	
	printf("\n [%d]PILA:",pila.cantidad);
	//IMPRIMIR CIMAS ORIGINAL
	//REMOVER LOS NODOS DE LA ORIGINAL
	//PASARLOS A LA AUX
	while(!pilaVacia(pila))
	{
		printf("\n");
		pila.imprimir( pila.cima->dato);
		pushNodo( &aux , popNodo(&pila) );
	}	
	//RESTAURAR
	//REMOVER LOS NODOS DE LA AUX
	//PASARLOS A LA ORIGINAL
	while( !pilaVacia(aux))
	{
		pushNodo( &pila , popNodo(&aux) );
	}	
}

void ordenarPila( Pila *pila, int (*comparar)(void*,void*) ){
	if(pilaVacia(*pila))
		return;
		
	Pila p1 = {NULL,0,pila->capacidad,pila->imprimir,pila->liberar};
	Pila p2 = {NULL,0,pila->capacidad,pila->imprimir,pila->liberar};
	void *auxInt = NULL;
	
	while(!pilaVacia(*pila)){
		
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
		//imprimirPila(p2); solo para debugeo
		auxInt = NULL;

	}
	
	//*pila = p2;
	//EN CASO DE QUE LA IMPRESION SE QUISIERA ALREVEZ ENTONCES COMENTAR LO DE DARRIBA
	while(!pilaVacia(p2))
			pushDato(pila,popDato(&p2));
}