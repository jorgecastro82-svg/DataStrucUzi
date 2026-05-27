#include <stdio.h>
#include <iostring.h>
#include <lista.h>
#include <listadoble.h>
#include "Alumno.h"

void imprimirEntero(void *dato);
void imprimirCadena(void *dato);

int compEntero( void *a,void *b);
int compCadenas( void *a,void *b);


int main()
{
	int arreglo[5] = {25,8,3,1000,6};
	char palabras[5][32] = {"tres","ocho","cuatro","Palafox","Nodo"};
	//INICIALIZAR VARIABLES LISTAS
	//CON APUNTADORES NULOS
	//CON SU FUNCION ESPECIFICA PARA IMPRIMIR
	//CON CANTIDAD CERO
	
	Lista cadenas = {NULL,NULL,0,&imprimirCadena,&compCadenas};
	Lista enteros   = {NULL,NULL,0,&imprimirEntero,&compEntero};
	for (int i= 0; i<5 ; i++)
	{
		agregarEnOrden(&cadenas,palabras[i]);
		agregarEnOrden(&enteros,&arreglo[i]);
	}

	printf("\n");
	imprimirLista(cadenas);
	printf("\n");
	imprimirLista(enteros);

	
	char *cadenaX = "cuatro";
	int numeroX = 6;
	eliminarDato(&cadenas,cadenaX);
	eliminarDato(&enteros,&numeroX);

	printf("\n");
	imprimirLista(cadenas);
	printf("\n");
	imprimirLista(enteros);
	
	printf("\n");
	
	char nuevasPalabras[3][32]= {"UABC","OXXO","NUEVO"};
	
	imprimirLista(cadenas);
	
	printf("\n INSERTANDO INICIO: %s",nuevasPalabras[0]); 
	insertarInicio(&cadenas, nuevasPalabras[0]);
	imprimirLista(cadenas);
	
	printf("\n INSERTANDO EN POSICION 2: %s",nuevasPalabras[1]);
	insertarEn(&cadenas, nuevasPalabras[1],2);
	imprimirLista(cadenas);
		
	printf("\n INSERTANDO EN POSICION 0: %s",nuevasPalabras[2]);
	insertarEn(&cadenas, nuevasPalabras[2],0);
	imprimirLista(cadenas);
	
	
	printf("\n ELIMINANDO POSICION 0");
	//asi es como estava en el main de la practica
	//imprimirLista(cadenas);
	//eliminarEn(&cadenas,0);
	//se cambio a ponerlos alrevez
	eliminarEn(&cadenas,0);
	imprimirLista(cadenas);
	
	
	printf("\n\n FIN DE PROGRAMA \n");
	return 0;
}

void imprimirEntero(void *dato)
{
	int *datoE = dato;
	printf(" %d", *datoE);
}

void imprimirCadena(void *dato)
{
	char *datoC = dato;
	printf(" %s", datoC);	
}



int compEntero( void *a,void *b)
{
	int *pA,*pB;
	pA = a;
	pB = b;
	return *pA - *pB;
}


int compCadenas( void *a,void *b)
{
	char *cadA,*cadB;
	cadA = a;
	cadB = b;
	return strcmp(cadA,cadB);
}