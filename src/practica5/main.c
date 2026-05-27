#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include <time.h>
#include <iostring.h>
#include <arbol.h>
#include <pila.h>

int* crearEntero(int);
int compararEntero(void*,void*);
void imprimirEntero(void*);

void myprintf(char *msg,char *formato,...);

char dispMenu();
char myInputChar(char *str);
int myInputNumero(char *str);

int main(void)
{
	Arbol arbolA;
	arbolA.raiz = NULL;
	arbolA.cantidad = 0;
	arbolA.imprimir = &imprimirEntero;
	arbolA.comparar = &compararEntero;
	arbolA.liberar = &free;

	Arbol arbolB;
	arbolB.raiz = NULL;
	arbolB.cantidad = 0;
	arbolB.imprimir = &imprimirEntero;
	arbolB.comparar = &compararEntero;
	arbolB.liberar = &free;
	
	int *auxIntPtr = NULL;

	while(true){
		switch(dispMenu()){
			case '1':
				auxIntPtr = crearEntero(myInputNumero("\nIndique numero a ingresar: "));
				insertarArbol(&arbolA,auxIntPtr);
				
			break;

			case '2':
				auxIntPtr = crearEntero(myInputNumero("\nIndique numero a ingresar: "));
				insertarArbol(&arbolB, auxIntPtr);
			break;

			case '3':
				imprimirArbol(arbolA);
			break;

			case '4':
				imprimirArbol(arbolB);
			break;

			case '5':
				switch(compararArboles(&arbolA,&arbolB)){
					case NO_IGUAL:
						printf("\nLOS ARBOLES NO SON IGUALES EN ESTRUCTURA NI DATOS");
					break;

					case IGUAL_ESTRUCTURA:
						printf("\nLOS ARBOLES TIENEN LA MISMA ESTRUCTURA");
					break;

					case IGUAL_DATOS:
						printf("\nLOS ARBOLES SOLO TIENEN LOS MISMOS DATOS");
					break;

				}
			break;

			case '6':
				auxIntPtr = crearEntero(myInputNumero("\nIndique numero a eliminar: "));
				free(eliminarDato(&arbolA, auxIntPtr));
			break;

			case '7':
				auxIntPtr = crearEntero(myInputNumero("\nIndique numero a eliminar: "));
				free(eliminarDato(&arbolB, auxIntPtr));
			break;

			case '8':
				printf("\nALTURA ARBOL A: [%d]",getAlturaArbol(&arbolA));
				printf("\nALTURA ARBOL B: [%d]",getAlturaArbol(&arbolB));
			break;

			case '9':
				printf("\nARBOL A ");
				equilibrarArbol(&arbolA);
				printf("\nARBOL B ");
				equilibrarArbol(&arbolB);
			break;

			case 'A':
				eliminarArbol(&arbolA);
				eliminarArbol(&arbolB);
				printf("\n\n FIN DE PROGRAMA\n");
			break;

			case 'B':{
						
			}		
			break;

			default:
				printf("\nOPERACION INCORRECTA");
			break;
		}
	}
	
	return 0;
}

char dispMenu(){
	printf("\n---MENU---");
	printf("\n[1] para insertar en Arbol A");
	printf("\n[2] para insertar en Arbol B");
	printf("\n[3] para imprimir  Arbol A");
	printf("\n[4] para imprimir  Arbol B");
	printf("\n[5] para comparar arboles");
	printf("\n[6] para remover dato en Arbol A");
	printf("\n[7] para remover dato en Arbol B");
	printf("\n[8] para imprimir las profundidades de los arboles");
	printf("\n[9] para equilibrar ambos arboles");
	printf("\n[A] para salir y eliminar arboles");
	return myInputChar("\nEscoje tu opcion: ");
}



char myInputChar(char *str){
	printf("%s",str);
	char opc;
	if(scanf("%c",&opc))
		printf(" ");
	while(getchar() != '\n');
	return opc;
}

int myInputNumero(char *str){
	printf("%s",str);
	int opc;
	if(scanf("%d",&opc))
		printf(" ");
	while(getchar() != '\n');
	return opc;
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

//no me deja compilar myprintf :(
/*
void myprintf(char* msg,char *formato,...)
{
	va_list args;
    va_start(args, formato);
	printf("\n %s ",msg);
	char *ptr = formato;
	while(*ptr!='\0')
	{
		switch(*ptr)
		{
			case 'd':
				printf("%d ",va_arg(args, int));
				break;
			case 'c':
				printf("%c ",va_arg(args, int));				
				break;
			case 'f':
				printf("%f ",va_arg(args, double));				
				break;
			case 'x':
				printf("%x ",va_arg(args, Arbol*));				
				break;
		}
		ptr++;
	}
	va_end(args);
}
*/