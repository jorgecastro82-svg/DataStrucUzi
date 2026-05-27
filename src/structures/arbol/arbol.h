#ifndef ARBOL_H
#define ARBOL_H

#include "../nodos/nodoarbol.h"
#include <stdio.h>
#include "../../structures/pila/pila.h"


#define PREORDEN 1
#define ORDEN 2
#define POSTORDEN 3
#define INVERSO 4
#define IZQUIERDA 0
#define DERECHA 1

enum arbolComp{
	NO_IGUAL = 0,
	IGUAL_DATOS = 1,
	IGUAL_ESTRUCTURA = 2,
};

typedef struct
{
	NodoA *padre;
	NodoA *nodo;
	void *dato;
	int rama;
}Resultado;

typedef struct
{
	NodoA *raiz;
	int cantidad;
	void (*imprimir)(void*);
	int (*comparar)(void*,void*);
	void (*liberar)(void*);
}Arbol;

void invertirArbol(Arbol *arbol);
void *buscarDatoEnArbol(Arbol *arbol,void *dato);
void eliminarArbol(Arbol *arbol);
void insertarArbol(Arbol *arbol,void *dato);
void imprimirArbol(Arbol arbol);
void imprimirOrden(Arbol arbol,int opcion);
//solo se usara leftest child a la hora de subir al hijo derecho del nodo a eliminar
//rgihtest child no se usa pero serviria el mismo proposito si se subiera al hijo izquierdo
Resultado buscarDatoEnArbolRes(Arbol *arbol, void *dato);
NodoA *leftestNodeOf(NodoA* raiz);
//NodoA *rightestChild(NodoA* raiz); talves ni se ocupa
void *eliminarDato(Arbol *arbol, void *dato);
int getAlturaArbol(Arbol *arbol);
int getCantidadArbol(Arbol *arbol);
int compararArboles(Arbol *arbolA,Arbol *arbolB);
void llenarPilaConArbol(Arbol *arbol,Pila *pila);
void llenarArrayOrdenadoConArbol(Arbol *arbol,void **array,int size);
void equilibrarArbol(Arbol *arbol);

#endif