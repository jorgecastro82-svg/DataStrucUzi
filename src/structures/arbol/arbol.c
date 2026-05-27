#include "arbol.h"
#include <stdbool.h>
#include "../../structures/pila/pila.h"

void insertarArbolOrdenado(NodoA *raiz,void *dato,int (*comparar)(void*,void*))
{
	if(comparar(dato,raiz->dato)<=0)
	{
		//IZQUIERDA
		if(!raiz->izq)			
			raiz->izq = crearNodoA(dato);
		else if(!raiz->dch && comparar(dato,raiz->dato)==0)			
			raiz->dch = crearNodoA(dato);
		else			
			insertarArbolOrdenado(raiz->izq,dato,comparar);
	}
	else
	{
		//DERECHA
		if(raiz->dch)
			insertarArbolOrdenado(raiz->dch,dato,comparar);
		else
			raiz->dch = crearNodoA(dato);
	}
}

void insertarArbol(Arbol *arbol,void *dato)
{
	if(!arbol->raiz)
		arbol->raiz = crearNodoA(dato);
	else 
		insertarArbolOrdenado(arbol->raiz,dato,arbol->comparar);
	arbol->cantidad++;
}


void invertirNodoArbol(NodoA *raiz){
	if(!raiz)
		return;
	
	NodoA *temp = raiz->izq;
	raiz->izq = raiz->dch;
	raiz->dch = temp;
	invertirNodoArbol(raiz->izq);
	invertirNodoArbol(raiz->dch);	
}

void invertirArbol(Arbol *arbol){
	invertirNodoArbol(arbol->raiz);
}



void imprimir_arbol(NodoA* nodo, int nivel,void (*imprimir)(void*))
{
    int i;
    if (nodo != NULL)
        {
        printf(" ");
		imprimir(nodo->dato);
        if(nodo->dch)
        {
            printf("\n");
            for (i = 0; i < nivel+1; i++)
            {
                if(i==nivel)
                    printf(" |____R ");
                else
                    printf(" |      ");
            }
            imprimir_arbol(nodo->dch, nivel + 1,imprimir);
        }
        if(nodo->izq)
        {
            printf("\n");
            for (i = 0; i < nivel+1; i++)
            {
                printf(" |      ");
                //printf(" |      ");
            }
            printf("\n");
            for (i = 0; i < nivel+1; i++)
            {
                if(i==nivel)
                    printf(" |____L ");
                else
                    printf(" |      ");
            }
            imprimir_arbol(nodo->izq, nivel + 1,imprimir);
        }
    }
}

void imprimirArbol(Arbol arbol)
{
	imprimir_arbol(arbol.raiz,0,arbol.imprimir);
}

void preorden(NodoA *raiz,void (*imprimir)(void*))
{
	if(!raiz)
		return;
	printf(" ");
	imprimir(raiz->dato);
	preorden(raiz->izq,imprimir);
	preorden(raiz->dch,imprimir);
}

void orden(NodoA *raiz,void (*imprimir)(void*))
{
	if(!raiz)
		return;
	orden(raiz->izq,imprimir);
	printf(" ");
	imprimir(raiz->dato);
	orden(raiz->dch,imprimir);	
}

void inverso(NodoA *raiz,void (*imprimir)(void*))
{
	if(!raiz)
		return;
	inverso(raiz->dch,imprimir);	
	printf(" ");
	imprimir(raiz->dato);
	inverso(raiz->izq,imprimir);
}

void postorden(NodoA *raiz,void (*imprimir)(void*))
{
	if(!raiz)
		return;
	postorden(raiz->izq,imprimir);
	postorden(raiz->dch,imprimir);
	printf(" ");
	imprimir(raiz->dato);	
}


void imprimirOrden(Arbol arbol,int opcion)
{
	switch(opcion)
	{
		case PREORDEN: 
			preorden(arbol.raiz,arbol.imprimir);
			break;
		case ORDEN: 
			orden(arbol.raiz,arbol.imprimir);
			break;
		case INVERSO: 
			inverso(arbol.raiz,arbol.imprimir);
			break;
		case POSTORDEN: 
			postorden(arbol.raiz,arbol.imprimir);
			break;
	}
}


void eliminar_NodosA(NodoA *raiz,void (*liberar)(void*))
{
	if(!raiz)
		return;
	eliminar_NodosA(raiz->izq,liberar);
	eliminar_NodosA(raiz->dch,liberar);
	//LIBERAR
	if(liberar)
		liberar(raiz->dato);
	free(raiz);
}
 

void eliminarArbol(Arbol *arbol)
{
	eliminar_NodosA( arbol->raiz, arbol->liberar);
	arbol->raiz = NULL;
	arbol->cantidad = 0;
}

void *buscarDatoEnArbol(Arbol *arbol, void *dato){
	NodoA *raiz = arbol->raiz;
	if(!raiz)
		return NULL;
	
	while(raiz){
		//printf("\n%d",*((int *)raiz->dato)); //FUE PARA VER QUE TOMARA EL CAMINO CORRECTO
		if(arbol->comparar(raiz->dato,dato) == 0)
			return raiz->dato;
		if(raiz->izq && arbol->comparar(dato,raiz->dato) < 0)
			raiz = raiz->izq;
		else if(raiz->dch && arbol->comparar(dato,raiz->dato) > 0)
			raiz = raiz->dch;
		else
			return NULL;
	}
	// si llego hasta aqui entonces no lo encontro y se retorna null, aparte se pone por que make se queja
	return NULL;
}

Resultado buscarDatoEnArbolRes(Arbol *arbol, void *dato){
	NodoA *raiz = arbol->raiz;
	Resultado res = {0};

	if(!raiz)
		return res;
	
	while(raiz){
		if(arbol->comparar(raiz->dato,dato) == 0){
			res.nodo = raiz;
			return res;
		}
		res.padre = raiz;
		if(raiz->izq && arbol->comparar(dato,raiz->dato) < 0){
			raiz = raiz->izq;
			res.rama = IZQUIERDA;
		}
		else if(raiz->dch && arbol->comparar(dato,raiz->dato) > 0){
			raiz = raiz->dch;
			res.rama = DERECHA;
		}	
		else
			return (Resultado){0};
	}
	// si llego hasta aqui entonces no lo encontro y se retorna null, aparte se pone por que make se queja
	return (Resultado){0};
}

//funcion para eliminar dato pero, asegurando el orden en los nodos
void *eliminarDato(Arbol *arbol, void *dato){

	Resultado res = buscarDatoEnArbolRes(arbol,dato);
	NodoA *aux = NULL; //va ser la nueva raiz del subarbol 
	//En caso de nodo a eliminar es una hoja, solo se elimina y ya se asigno NULL

	//caso no se encuentra el dato
	if(!(res.nodo)){
		printf("\nDATO NO ENCONTRADO");
		return NULL;
	}

	//caso no tiene hijo derecho
	else if(!((res.nodo)->dch))
		aux = (res.nodo)->izq;
	//csao si tiene hijo derecho
	else{
		aux = (res.nodo)->dch;
		leftestNodeOf((res.nodo)->dch)->izq = (res.nodo)->izq;
	}

	//asignacion de aux al nuevo subarbol
	//caso nodo a eliminar es la raiz
	if(!(res.padre)){
		arbol->raiz = aux;
	}
	else{
		//caso derecho
		if(res.rama)
			(res.padre)->dch = aux;
		else
			(res.padre)->izq = aux;
	}

	free(res.nodo);
	return res.dato;
}

NodoA *leftestNodeOf(NodoA* raiz){
	if(!raiz)
		return NULL;
	if(!(raiz->izq))
		return raiz;
	
	while(raiz->izq){
		raiz = raiz->izq;
	}
	return raiz;
}

int getAlturaArbolNodo(NodoA *raiz){
	if(!raiz)
		return 0;
	int altIzq = getAlturaArbolNodo(raiz->izq);
	int altDch = getAlturaArbolNodo(raiz->dch);
	return 1 + ((altIzq > altDch) ? altIzq : altDch);

}

int getAlturaArbol(Arbol *arbol){
	return getAlturaArbolNodo(arbol->raiz);
}

int getCantidadArbolNodo(NodoA *raiz){
	if(!raiz)
		return 0;
	int cantIzq = getCantidadArbolNodo(raiz->izq);
	int cantDch = getCantidadArbolNodo(raiz->dch);
	return 1 + cantIzq + cantDch;

}

int getCantidadArbol(Arbol *arbol){
	return getCantidadArbolNodo(arbol->raiz);
}

bool compararEstructura(NodoA *raizA,NodoA *raizB,int (*comparar)(void*,void*)){
	if(!raizA && !raizB)
		return true;
	if((!raizA && raizB) || (!raizB && raizA) || comparar(raizA->dato,raizB->dato))
		return false;
	else if(!compararEstructura(raizA->izq,raizB->izq,comparar))
		return false;
	else
		return compararEstructura(raizA->dch,raizB->dch,comparar);	
}

bool compararDatos(Arbol *arbolA,Arbol *arbolB){
	//se hacen dos colas con los valores ordenados y se comparan los valores uno por uno
	Pila pilaA = {NULL,0,-1,arbolA->imprimir,NULL};
	Pila pilaB = {NULL,0,-1,arbolA->imprimir,NULL};

	llenarPilaConArbol(arbolA,&pilaA);
	llenarPilaConArbol(arbolB,&pilaB);

	//debugeo
	imprimirPila(pilaA);
	imprimirPila(pilaB);

	ordenarPila(&pilaA,arbolA->comparar);
	ordenarPila(&pilaB,arbolB->comparar);

	//debugeo
	imprimirPila(pilaA);
	imprimirPila(pilaB);
	
	bool sonIguales = true;

	void *datoA,*datoB;
	while(!pilaVacia(pilaA)){
		datoA = popDato(&pilaA);
		datoB = popDato(&pilaB);
		if(arbolA->comparar(datoA,datoB)){
			sonIguales = false;
			break;
		}
	}

	while(!pilaVacia(pilaA))
	{
		popDato(&pilaA);
		popDato(&pilaB);
	}
	return sonIguales;
}

int compararArboles(Arbol *arbolA,Arbol *arbolB){
	
	int igualdad = NO_IGUAL;
	//si no son el mismo tamanio pues se saben que no tienen la misma estructura ni mismos datos
	if(arbolA->cantidad != arbolB->cantidad)
		return igualdad;
	//funcion que compara estructura
	else if(compararEstructura(arbolA->raiz,arbolB->raiz,arbolA->comparar))
		igualdad = IGUAL_ESTRUCTURA;
	//funcion que compara mismos valores
	else if(compararDatos(arbolA,arbolB)){
		igualdad = IGUAL_DATOS;
	}
	return igualdad;
}

void llenarPilaConArbolNodo(NodoA *raiz,Pila *pila){
	if(!raiz)
		return;
	pushDato(pila,raiz->dato);
	llenarPilaConArbolNodo(raiz->dch,pila);
	llenarPilaConArbolNodo(raiz->izq,pila);
}

void llenarPilaConArbol(Arbol *arbol,Pila *pila){
	llenarPilaConArbolNodo(arbol->raiz,pila);
}

void llenarArrayOrdenadoConArbol(Arbol *arbol,void **array,int size){
	if(size <= 0)
		return;
	Pila pila = {NULL,0,-1,NULL,NULL};
	llenarPilaConArbol(arbol,&pila);
	ordenarPila(&pila,arbol->comparar);

	for(int i = 0; i < size;i++){
		array[i] = popDato(&pila);
	}


}

void extraerMitades(void**arr1,void**arr2,int longitud,int *i)
{
	if(longitud <= 0)
		return;
	int mitad = longitud/2;
	//EXTRAER MITAD
	arr2[*i] = arr1[mitad];
	(*i)++;
	//IZQUIERDA
	extraerMitades(arr1,arr2,mitad,i);
	//DERECHA
	extraerMitades(arr1+mitad+1,arr2,longitud-1-mitad,i);	
}

void equilibrarArbol(Arbol *arbol){
	if(!arbol->raiz){
		printf("ESTA VACIO");
		return;
	}
	
	int factorEquilibrio = getAlturaArbolNodo(arbol->raiz->izq) - getAlturaArbolNodo(arbol->raiz->dch);
	//caso desequilibrado
	if(abs(factorEquilibrio) <= 1){
		printf("YA ESTA EQUILIBRADO SU FACTOR DE EQUILIBRO ES: %d",factorEquilibrio);
		return;
	}
	printf("NO ESTA EQUILIBRADO SU FACTOR DE EQUILIBRO ES: %d",factorEquilibrio);

	//arreglos para extraer mitades
	void *arr1[arbol->cantidad];
	void *arr2[arbol->cantidad];

	//funcion que ordena datos en una pila
	llenarArrayOrdenadoConArbol(arbol,arr1,arbol->cantidad);

	//se guarda la funcion de liberar de arbol, se va eliminar arbol sin eliminar los datos, solo los nodos
	void (*liberar)(void*) = arbol->liberar;
	arbol->liberar = NULL;
	eliminarArbol(arbol);

	//se meten equilibradamente a arbol
	int i = 0;
	extraerMitades(arr1,arr2,9,&i);
	printf("\n");
	for(i = 0;i<9;i++){
		insertarArbol(arbol,arr2[i]);
	}

	arbol->liberar = liberar;
}