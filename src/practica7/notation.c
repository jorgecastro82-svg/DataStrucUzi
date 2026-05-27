#include "notation.h"

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

int precedencia(char opc){
	switch(opc){
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
			aux = (char*)popDato(&pila);
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