
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

int verificarParentesis(char *cadena);
int myInputNumero(char *str);
void infixToPostfix(char *infix,char *postfix);
int precedencia(char opc);
//void remplazarUnariosInfix(char *infix);
//void unarioFalso(char *unario);


int main(void)
{
	char infix[64] = {0};
	char postfix[64] = {0};

	inputCadena("\nINGRESE OPERACION INFIX: ",infix,64);
	if(!verificarParentesis(infix)){
		printf("\nEl orden de los parentesis es incorrecto");
		return 0;
	}
	infixToPostfix(infix,postfix);
	printf("\nRESULTADO POSTFIX: %s",postfix);
	printf("\n");
	return 0;
}

void infixToPostfix(char *infix,char *postfix){
	if(!infix)
		return;

	int index = 0;
	char *aux = infix;
	Pila p = {NULL,0,-1,NULL,NULL};

	while(*aux != '\0'){
		switch(*aux){
			case '^':case '*':case '/':case '+':case '-'://caso operador
				if(pilaVacia(p) || (precedencia(*aux) > precedencia(*((char*)peekPila(p)))))
					pushDato(&p,aux++);

				//caso contrario
				else{
					while(!pilaVacia(p) && (precedencia(*aux) <= precedencia(*((char*)peekPila(p))))){
						postfix[index++] = *((char*)popDato(&p));
					}
					pushDato(&p,aux++);
				}
			break;
			
			case ')':
				++aux;
				while(!pilaVacia(p) && (*((char*)peekPila(p)) != '(')){
					postfix[index++] = *((char*)popDato(&p));
				}
				popDato(&p);
			break;
			

			case '(':	//caso parentesis de abertura
				pushDato(&p,aux++);
			break;

			default:	//caso operando
				postfix[index++] = *(aux++);
			break;
		}
	}
	while(!pilaVacia(p))
		postfix[index++] = *((char*)popDato(&p));

	postfix[index++] = '\0';
}

//X+B^A/C-(B+A)^Z*X


int precedencia(char opc){
	switch(opc){
			//case '~':case '&':	//caso unario, ~ es menos & es mas
			//	return 4;
			//break;

			case '^':
				return 3;
			break;

			case '*':case '/':
				return 2;
			break;

			case '+':case '-':
				return 1;
			break;

			case '(':
				return -1;
			break;

			case ')':
				return -1;
			break;

			default:
				return 0;
			break;
	}
}

int verificarParentesis(char *cadena)
{
	if(!cadena)
		return 0;

	Pila pila = {NULL,0,-1,NULL,NULL};	

	int i = 0;
	char* aux;
	//metida de los caracteres a la pila IGNORANDO ESPACIOS
	while(cadena[i] != '\0'){
		
		if(cadena[i] == '(' || cadena[i] == '[' || cadena[i] == '{' ){
			pushDato(&pila,cadena+i);
		}
		//caso se encuentra una cerrada
		else if(cadena[i] == ')' || cadena[i] == ']'|| cadena[i] == '}'){
			if(pilaVacia(pila))
				return 0;
			aux = popDato(&pila);
			if(cadena[i] == ')' && *aux != '(')
				return 0;
			else if(cadena[i] == ']' && *aux != '[')
				return 0;
			else if(cadena[i] == '}' && *aux != '{')
				return 0;
		}
		i++;
	}
	if(!pilaVacia(pila))
		return 0;
	return 1;	
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

/*
void remplazarUnariosInfix(char *infix){
	if(!infix)
		return;
	
	char *aux = infix;

	//caso inicial
	if(precedencia(*infix) == 1)
		unarioFalso(infix);

	while(*(++aux) != '\0'){

		//se checa si el siguiente es un parentesis
		if(precedencia(*(aux+1)) == -1)
			unarioFalso(aux);
		//solo se checa si el anterior fue un operador o un parentesis de tipo (
		else if(precedencia(*(aux-1)) && precedencia(*aux) != -1)
			unarioFalso(aux);
	}
}

void unarioFalso(char *unario){
	switch(*unario){//caso unario, ~ es menos & es mas
		case '+':
			*unario = '&';
		break;

		case '-':
			*unario = '~';		
		break;
	}
}
*/

/*
void infixtoPostfix(char *cadena, char *postfix)
{
	Pila pila = {NULL,0,-1,imprimirCaracter,free,compararOperadores};
	char *operador_cima;
	int j = 0;

	
	for(int i = 0; cadena[i] != '\0'; i++)
	{
		//SI EL CARACTER ACTUAL ES IGUAL A UN CARACTER DE APERTURA
		//LO AÑADIMOS A LA PILA
		if(cadena[i] == '(')
		{
			if(pilaVacia(pila))
			pushDato(&pila,&cadena[i]);
			else
			pushDato(&pila,&cadena[i]);
		}

		//SI EL CARACTER ACTUAL ES IGUAL A UN CARACTER DE CIERRE
		else if(cadena[i] == ')')
		{
				operador_cima = peekCima(pila);
				
				// MIENTRAS LA PILA NO ESTE VACIA Y EL OPERADOR DE LA CIMA SEA DISTINTO DEL CARACTER
				// DE APERTURA
				while(!pilaVacia(pila) && *operador_cima != '(')
				{
					operador_cima = popDato(&pila); // QUITAMOS EL OPERADOR DE LA PILA
					postfix[j] = *operador_cima; // LO AÑADIMOS A LA CADENA POSTFIX
					j++;
					operador_cima = peekCima(pila); //CONSULTAMOS NUEVAMENTE LA CIMA DE LA PILA
				}

				// SI LA PILA NO ESTA VACIA Y EL OPERADOR DE LA CIMA ES IGUAL AL CARACTER DE APERTURA
				if(!pilaVacia(pila) && *operador_cima == '(')
					popDato(&pila); // LO QUITAMOS DE LA PILA
		}
		
		
		else if(cadena[i] == '+' || cadena[i] == '-' || cadena[i] == '*' || cadena[i] == '/' || cadena[i] == '^')
		{
			if(pilaVacia(pila))
				pushDato(&pila,&cadena[i]);
				
	
			else
			{
				operador_cima = peekCima(pila);
				
				//SI EL OPERADOR ACTUAL ES MAYOR QUE EL DE LA PILA
				if(pila.comparar(&cadena[i],operador_cima) > 0)
				pushDato(&pila,&cadena[i]);
			
				//SI EL OPERADOR ACTUAL ES MENOR O IGUAL
				else
				{
					// MIENTRAS EL OPERADOR ACTUAL SEA MENOR O IGUAL QUE LA CIMA DE LA PILA
					// Y LA PILA NO ESTE VACIA
						while(!pilaVacia(pila) && pila.comparar(&cadena[i],operador_cima) <= 0)
						{
							operador_cima = popDato(&pila);
							postfix[j] = *operador_cima;
							operador_cima = peekCima(pila);
							j++;
						}
						
						pushDato(&pila,&cadena[i]);
						//operador_cima = peekCima(pila);
						//printf("Cima actual de la pila y fuera del while: %c",*operador_cima);
				}
				
			}
		
		}
		
		else
		{	
			postfix[j] = cadena[i];
			j++;
		}
		
	}
	
	// VACIAMOS EL RESTO DEL CONTENIDO DE LA PILA
	// AÑADIMOS LOS OPERADORES FALTANTES A LA CADENA POSTFIX
	while(!pilaVacia(pila))
	{
		operador_cima = popDato(&pila);
		postfix[j] = *operador_cima;
		j++;
	}
	
	postfix[j] = '\0';
	
	
	for(int i = 0; postfix[i] != '\0'; i++)
	{
		printf(" %c",postfix[i]);
	}
	
		
}
*/
