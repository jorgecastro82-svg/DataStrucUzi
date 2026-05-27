#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include <time.h>
#include <iostring.h>
#include <arbol.h>
#include <pila.h>
#include <math.h>
#include "notation.h"

int* crearEntero(int);
int compararEntero(void*,void*);
void imprimirEntero(void*);
int myInputNumero(char *str);
char myInputChar(char *str);
void imprimirChar(void *a);
char dispMenu();
NodoA *postfixToTree(char *postfix);
float *myInputFloat(char *str);
void llenarArregloVariables(NodoA *raiz,float *var[56]);
int asciiToIndex(void *aa);
float calculoArregloVariables(NodoA *raiz,float *var[56]);
float treeToValue(Arbol *a);

int main(void)
{
	char infix[64] = {0};
	char postfix[64] = {0};

	Arbol arbol = {NULL,0,imprimirChar,NULL,NULL};
	while(true){
		switch(dispMenu()){

			case '0': //caso captura de expresion infix y convertirla a postfix y generar arbol
				eliminarArbol(&arbol);
				do{
					inputCadena("\nINGRESE OPERACION INFIX: ",infix,64);
				}while(!verificarParentesis(infix));
				infixToPostfix(infix,postfix);
				printf("\nRESULTADO POSTFIX: %s",postfix);
				printf("\n");
				//dado cadena postfix convertir a arbol de expresion
				arbol.raiz = postfixToTree(postfix);
			break;

			case '1'://dado cadena postfix convertir a arbol de expresion e imprimirlo
				if(arbol.raiz)
					imprimirArbol(arbol);
				else
					printf("\nARBOL VACIOOO");
			break;

			case '2'://hacer funcion de calculacion dado arbol de expresion
				if(!arbol.raiz)
					printf("\nARBOL VACIOOO");
				else
					printf("\nEl valor obtenido es: %f",treeToValue(&arbol));
					
			break;

			case '3'://caso salir 
				printf("\nSaliendo de programa");
				eliminarArbol(&arbol);
				printf("\n");
				return 0;
			break;

			default:
				printf("\nOperacion Incorrecta");
			break;
		}
	}
	return 0;
}

NodoA *postfixToTree(char *postfix){
	if(!postfix)
		return NULL;
	
	char *aux = postfix;
	Pila p = {NULL,0,-1,NULL,NULL};

	while(*aux != '\0'){
		switch(*aux){
			case '^':case '*':case '/':case '+':case '-':{//caso operador
				NodoA *nodoAux = crearNodoA(aux);
				nodoAux->dch = popDato(&p);
				nodoAux->izq = popDato(&p);
				pushDato(&p,nodoAux);
			}
			break;
			

			default:	//caso operando
				pushDato(&p,crearNodoA(aux));
			break;
		}
		aux++;
	}
	//solo queda la raiz en la pila
	return popDato(&p);
}

float treeToValue(Arbol *a){

	//arreglo de 56 punteros flotantes a nulo
	//56 por que solo puede haber max 56 vars(abecedario)
	float *variables[56] = {0},res = 0; 
	
	//se preguntan los valores
	llenarArregloVariables(a->raiz,variables);
	res = calculoArregloVariables(a->raiz,variables);
	//free variables
	for(int i = 0; i < 56;i++)
		free(variables[i]);

	return res;
}

void llenarArregloVariables(NodoA *raiz,float *var[56]){
	if(!raiz)
		return;
	int index = asciiToIndex(raiz->dato);

	llenarArregloVariables(raiz->izq,var);
	if(index != -1 && !var[index]){
		printf("\nDame el valor para la variable: %c:",*((char*)raiz->dato));
		var[index] = myInputFloat(" ");
	}
	llenarArregloVariables(raiz->dch,var);
}


float calculoArregloVariables(NodoA *raiz,float *var[56]){
	char opcion = '~'; //caso raiz es nula
	int index = -1;
	if(raiz){
		opcion = *((char*)raiz->dato);
		index = asciiToIndex(raiz->dato);
	}
	switch(opcion){
		case '+':
			return calculoArregloVariables(raiz->izq,var) + calculoArregloVariables(raiz->dch,var);
		break;

		case '-':
			return calculoArregloVariables(raiz->izq,var) - calculoArregloVariables(raiz->dch,var);
		break;

		case '*':
			return calculoArregloVariables(raiz->izq,var) * calculoArregloVariables(raiz->dch,var);
		break;

		case '/':
			return calculoArregloVariables(raiz->izq,var) / calculoArregloVariables(raiz->dch,var);
		break;

		case '^':
			return (float)pow(calculoArregloVariables(raiz->izq,var),calculoArregloVariables(raiz->dch,var));
		break;

		case '~'://caso nulo
			return 0;
		break;

		default:
			return *(var[index]);
		break; 
	}
	

	llenarArregloVariables(raiz->izq,var);
	if(index != -1 && !var[index]){
		printf("\nDame el valor para la variable: %c",*((char*)raiz->dato));
		var[index] = myInputFloat(" ");
	}
	llenarArregloVariables(raiz->dch,var);
}


int asciiToIndex(void *aa){
	char a = *((char*)aa);
	if(a >= 'a' && a <= 'z')
		return a - 'a';
	else if(a >= 'A' && a <= 'Z')
		return a - 'A' + 16;
	else
		return -1;
}

char dispMenu(){
	printf("\n---MENU---");
	printf("\n[0] Capturar expresion");
	printf("\n[1] Imprimir Arbol de Expresion");
	printf("\n[2] Evaluar Expresion");
	printf("\n[3] Terminar Programa");
	return myInputChar("\nIngrese su seleccion: ");
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

float *myInputFloat(char *str){
	printf("%s",str);
	float *opc = malloc(sizeof(float));
	if(scanf("%f",opc))
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

void imprimirChar(void *a)
{
	char *aa=a;
	printf("%c",*aa);
}
