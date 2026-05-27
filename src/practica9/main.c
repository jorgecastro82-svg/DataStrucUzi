#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include<ctype.h>
#include<arbol.h>

#include <iostring.h>
#include <HashQ.h>
#include "Libro.h"

int dispMenu();
int folding_isbn(void *data);
int folding_titulo(void *data);
int folding_autor(void *data);
int folding_fecha(void *data);
int cmp_isbn(void *a, void *b);
int cmp_titulo(void *a, void *b);
int cmp_autor (void *a, void *b);
int cmp_fecha (void *a, void *b);

int main(void)
{

	HashQTable htISBN,htTitulo,htAutor,htFecha;
	Acervo acervo = obtener_libros();
	unsigned int tam = (acervo.cantidad*100/45) + 1;
    htISBN = initHashTable(tam,folding_isbn,cmp_isbn,imprimirLibro);
    htTitulo = initHashTable(tam,folding_titulo,cmp_titulo,imprimirLibro);
    htAutor = initHashTable(tam,folding_autor,cmp_autor,imprimirLibro);
    htFecha = initHashTable(tam,folding_fecha,cmp_fecha,imprimirLibro);
 
    for(int i = 0; i < acervo.cantidad; i++){
        fn_insertKey(&htISBN,&acervo.libros[i]);
        fn_insertKey(&htTitulo,&acervo.libros[i]);
        fn_insertKey(&htAutor,&acervo.libros[i]);
        fn_insertKey(&htFecha,&acervo.libros[i]);
    }

	bool flag = true;

	while(flag){
		switch(dispMenu()){
			case 1:{
				char str[MAX_ISBN+1]; //por alguna razon sospecho que del caracter nulo, se ocupa un espacio mayor
    			inputCadena("\nISBN a buscar: ", str, sizeof(str));
    			Libro auxLibro = {0};
				strcpy(auxLibro.isbn,str);
    			Libro *res = fn_searchKey(&htISBN, &auxLibro);
    			if(res) 
					imprimirLibro(res);
    			else
					printf("\nLibro no encontrado");
			}	
			break;

			case 2:{ //Buscar por Titulo
				int op;
			    printf("\n---Menu Titulo---");
			    printf("\n[1] Buscar por titulo");
			    printf("\n[2] Buscar por rango de iniciales");
			    inputEntero("\nOpcion: ", &op);
			    if(op == 1){
					char str[MAX_ISBN+1]; 
    				inputCadena("\nTitulo a buscar: ", str, sizeof(str));
    				Libro auxLibro = {0};
					strcpy(auxLibro.titulo,str);
    				Libro *res = fn_searchKey(&htTitulo, &auxLibro);
    				if(res) 
						imprimirLibro(res); 
    				else
						printf("\nLibro no encontrado");
				}
			    else if(op == 2){
					char inf, sup;
    				inputChar("\nLimite inferior: ", &inf);
    				inputChar("\nLimite superior: ", &sup);

    				inf = toupper(inf);
    				sup = toupper(sup);
    				if(inf > sup){ //caso de que ponga el inferior a una letra mayor que la superior se intercambian
						char t = inf;
						inf = sup;
						sup = t; 
					}

					Arbol arbol = {NULL,0,imprimirLibroSaltoLinea,cmp_titulo,NULL};
    				for(int i = 0; i < htTitulo.len; i++){
    				    void *ranura = htTitulo.table[i];
    				    if(ranura && ranura != &htTitulo){
    				        Libro *l = ranura;
    				        char inicial = toupper(l->titulo[0]);
    				        if(inicial >= inf && inicial <= sup)
								insertarArbol(&arbol, l);
    				    }
    				}
    				if(!arbol.raiz)
						printf("\nNo se encontraron libros en ese rango");
    				
					imprimirOrden(arbol, ORDEN);
    				eliminarArbol(&arbol);
				}
			    else
					printf("\nOpcion incorrecta");
			}
			break;

			case 3:{ //Buscar por Autor
				int op;
				printf("\n---Menu Autor---");
				printf("\n[1] Buscar por autor");
				printf("\n[2] Buscar por rango de iniciales");
				inputEntero("\nOpcion: ", &op);
				if(op == 1){
				    char str[MAX_AUTOR+1];
    				inputCadena("\nAutor a buscar: ", str, sizeof(str));
    				Arbol arbol = {NULL, 0, imprimirLibroSaltoLinea, cmp_fecha, NULL}; //se muestran los libros de ese autor y por fecha
    				for(int i = 0; i < htAutor.len; i++){
    				    void *ranura = htAutor.table[i];
    				    if(ranura && ranura != &htAutor){
    				        Libro *l = ranura;
    				        if(strcmp(l->autor, str) == 0)
    				            insertarArbol(&arbol, l);
    				    }
    				}
    				if(!arbol.raiz)
    				    printf("\nAutor no encontrado");
    				else
    				    imprimirOrden(arbol, ORDEN);
				
    				eliminarArbol(&arbol);
				}
				else if(op == 2){
				    char inf, sup;
				    inputChar("\nLimite inferior: ", &inf);
				    inputChar("\nLimite superior: ", &sup);
				    inf = toupper(inf);
				    sup = toupper(sup);
				    if(inf > sup){
				        char t = inf;
				        inf = sup;
				        sup = t;
				    }
				    Arbol arbol = {NULL, 0, imprimirLibroSaltoLinea, cmp_autor, NULL};
				    for(int i = 0; i < htAutor.len; i++){
				        void *ranura = htAutor.table[i];
				        if(ranura && ranura != &htAutor){
				            Libro *l = ranura;
				            char inicial = toupper(l->autor[0]);
				            if(inicial >= inf && inicial <= sup)
				                insertarArbol(&arbol, l);
				        }
				    }
				    if(!arbol.raiz)
				        printf("\nNo se encontraron autores en ese rango");
				
				    imprimirOrden(arbol, ORDEN);
				    eliminarArbol(&arbol);
				}
				else
				    printf("\nOpcion incorrecta");
			}
			break;

			case 4:{ //Buscar por Fecha
				int op;
			    printf("\n---Menu Fecha---");
			    printf("\n[1] Buscar por anio");
			    printf("\n[2] Buscar por rango de anios");
			    inputEntero("\nOpcion: ", &op);
			    if(op == 1){
			        int anio;
			        inputEntero("\nAnio a buscar: ", &anio);
			        Arbol arbol = {NULL, 0, imprimirLibroSaltoLinea, cmp_titulo, NULL}; //se ordena por titulo pero se muestran por fecha
			        for(int i = 0; i < htFecha.len; i++){
			            void *ranura = htFecha.table[i];
			            if(ranura && ranura != &htFecha){
			                Libro *l = ranura;
			                if(l->fecha == anio)
			                    insertarArbol(&arbol, l);
			            }
			        }
			        if(!arbol.raiz)
			            printf("\nNo se encontraron libros de ese anio");
			        else
			            imprimirOrden(arbol, ORDEN);
				
			        eliminarArbol(&arbol);
			    }
			    else if(op == 2){
			        int inf, sup;
			        inputEntero("\nAnio inferior: ", &inf);
			        inputEntero("\nAnio superior: ", &sup);
			        if(inf > sup){
			            int t = inf;
			            inf = sup;
			            sup = t;
			        }
			        Arbol arbol = {NULL, 0, imprimirLibroSaltoLinea, cmp_fecha, NULL};
			        for(int i = 0; i < htFecha.len; i++){
			            void *ranura = htFecha.table[i];
			            if(ranura && ranura != &htFecha){
			                Libro *l = ranura;
			                if(l->fecha >= inf && l->fecha <= sup)
			                    insertarArbol(&arbol, l);
			            }
			        }
			        if(!arbol.raiz)
			            printf("\nNo se encontraron libros en ese rango");
			        else
			            imprimirOrden(arbol, ORDEN);
				
			        eliminarArbol(&arbol);
			    }
			    else
			        printf("\nOpcion incorrecta");
			}
			break;

			case 5:{ //Eliminar libro dado su ISBN
				char str[MAX_ISBN+1];
			    inputCadena("\nISBN a eliminar: ", str, sizeof(str));
			    Libro auxLibro = {0};
			    strcpy(auxLibro.isbn,str);
						
			    Libro *res = fn_searchKey(&htISBN, &auxLibro);
			    if(!res){
			        printf("\nLibro no encontrado");
			        break;
			    }
			    printf("\nEliminando:\n");
			    imprimirLibro(res);
				
				fn_deleteKey(&htISBN,res);
				remap(&htISBN);

				//se tiene que eliminar dado su ISBN en todas las tablas
				//por que pueden haber libros con mismo autor, mismo titulo
				//misma fecha, pero la unica diferencia es el ISBN
				fn_comparar cmpOriginal;

				cmpOriginal = htTitulo.comparar;
				htTitulo.comparar = htISBN.comparar;
				fn_deleteKey(&htTitulo, res);
				htTitulo.comparar = cmpOriginal;
				remap(&htTitulo);
							
				cmpOriginal = htAutor.comparar;
				htAutor.comparar = htISBN.comparar;
				fn_deleteKey(&htAutor, res);
				htAutor.comparar = cmpOriginal;
				remap(&htAutor);
							
				cmpOriginal = htFecha.comparar;
				htFecha.comparar = htISBN.comparar;
				fn_deleteKey(&htFecha, res);
				htFecha.comparar = cmpOriginal;
				remap(&htFecha);
			    
			    printf("\nLibro eliminado del acervo");
			}
			break;

			case 6: //Terminar Programa
				flag = false;
			break;

			default://caso incorrecto
				printf("\nOPCION INCORRECTA");
			break;
		}
	}


	printf("\n\n FIN DE PROGRAMA\n");
	return 0;
}


int folding(void *data)
{
	char *cadena = data;
	int key = 0,sector = 1,sumatoria=0;
	for(int i = 0; cadena[i]!='\0'; i++)
	{
		//abc de
		sumatoria += cadena[i];
		if( i!=0 && (i+1)%3 == 0)
		{
			key+= sector*sumatoria;
			sumatoria = 0;
			sector++;
		}
	}	
	key+= sector*sumatoria;
	return key;
	
}

void imprimir(void *data)
{	
	char *cadena = data;
	printf("%s",cadena);
}
 
int dispMenu(){
	int opc;
	printf("\n---MENU---");
	printf("\n[1] Buscar por ISBN");
	printf("\n[2] Buscar por Titulo");
	printf("\n[3] Buscar por Autor");
	printf("\n[4] Buscar por Fecha");
	printf("\n[5] Eliminar libro dado su ISBN");
	printf("\n[6] Terminar Programa");
	inputEntero("\nIngrese su opcion: ",&opc);
	return opc;
}

//sectores de 3 ponderados
int folding_isbn(void *data){
    Libro *l = data;
    char *s = l->isbn;
    int key = 0, sector = 1, suma = 0, cnt = 0;
    for(int i = 0; s[i] != '\0'; i++){
        suma += s[i] - '0';
        cnt++;
        if(cnt == 3){
			key += sector * suma;
			suma = 0;
			cnt = 0;
			sector++;
		} 
    }
    if(cnt) 
		key += sector * suma;
    return key;
}
 
//sectores de 4 ponderados
int folding_titulo(void *data){
    Libro *l = data;
    char *s = l->titulo;
    int key = 0, sector = 1, suma = 0;
    for(int i = 0; s[i] != '\0'; i++){
        suma += toupper(s[i]);
        if((i+1) % 4 == 0){
			key += sector * suma;
			suma = 0;
			sector++;
		}
    }
    key += sector * suma;
    return key;
}
 
//sectores de 4 ponderados
int folding_autor(void *data){
    Libro *l = data;
    char *s = l->autor;
    int key = 0, sector = 1, suma = 0;
    for(int i = 0; s[i] != '\0'; i++){
        suma += toupper(s[i]);
        if((i+1) % 4 == 0){
			key += sector * suma; 
			suma = 0;
			sector++;
		}
    }
    key += sector * suma;
    return key;
}
 
//la fecha como entero
int folding_fecha(void *data){
    Libro *l = data;
    return l->fecha;
}

int cmp_isbn(void *a, void *b){
	return strcmp(((Libro*)a)->isbn,((Libro*)b)->isbn);
}

int cmp_titulo(void *a, void *b){
	return strcmp(((Libro*)a)->titulo,((Libro*)b)->titulo);
}

int cmp_autor(void *a, void *b){
	return strcmp(((Libro*)a)->autor,((Libro*)b)->autor); 
}

int cmp_fecha(void *a, void *b){
    int d = ((Libro*)a)->fecha - ((Libro*)b)->fecha;
    if(d != 0)
		return d;
    return strcmp(((Libro*)a)->titulo,((Libro*)b)->titulo);
}

int cmp_autor_and_fecha(void *a, void *b){
	return strcmp(((Libro*)a)->autor,((Libro*)b)->autor); 
}