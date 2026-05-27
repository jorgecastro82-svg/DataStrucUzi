#include <stdio.h>
#include <iostring.h>
#include <pila.h>


#define MAX 100

int palindromo(char *cadena);
int verificarParentesis(char *cadena);
int compCadenas( void *a,void *b);
char mayusculA(char caracter);

int main(void)
{
	char *cadena = NULL;
	
	inputCadenaDinamica("\n Captura cadena: ",&cadena,MAX);
	printf(" Es palindromo: %s", palindromo(cadena) ? "SI" : "NO");
	
	inputCadenaDinamica("\n\n Captura expresion: ",&cadena,MAX);
	printf(" Parentesis correctos : %s", verificarParentesis(cadena) ? "SI" : "NO");
	
	free(cadena);
	printf("\n\n FIN DE PROGRAMA");
	return 0;
}



int palindromo(char *cadena)
{
	Pila pila = {NULL,0,-1,NULL,NULL};
	int i = 0;

	//metida de los caracteres a la pila IGNORANDO ESPACIOS
	while(cadena[i] != '\0'){
		if(cadena[i] != ' '){
			pushDato(&pila,cadena+i);
		}
		i++;
	}

	i = 0;
	//sacada y comparacion de los caracteres con la cadena
	while(cadena[i] != '\0'){
		if(cadena[i] != ' '){
			if(compCadenas(cadena + i,popDato(&pila)) != 0)
				return 0;
		}
		i++;
	}
	return 1;
}

int verificarParentesis(char *cadena)
{
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

int compCadenas( void *a,void *b)
{
	char *cadA,*cadB;
	cadA = a;
	cadB = b;
	return mayusculA(*cadA) - mayusculA(*cadB);
}


char mayusculA(char caracter)
{
	if( caracter>='a' && caracter<='z')
		return caracter-32;
	return caracter;
}

