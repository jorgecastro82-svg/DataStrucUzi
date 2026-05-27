#include "listadoble.h"


void insertarFinalD(ListaD *lista,void *dato)
{
	NodoD *nuevo = crearNodoD(dato);
	//LISTA VACIA
	if(!lista->inicio)
	{
		lista->inicio = lista->fin = nuevo;
	}
	//LISTA NO VACIA
	else
	{
		lista->fin->sig = nuevo;
		nuevo->ant = lista->fin;
		lista->fin = nuevo;
	}
	lista->cant++;
}

void imprimirListaDIF(ListaD lista)
{
	printf("\n [%d] LISTA:",lista.cant);
	if(!lista.inicio)
	{
		printf("VACIA");
		return;
	}
	for(NodoD *aux = lista.inicio; aux!=NULL;  aux=aux->sig )
	{
		printf("\n");
		lista.imprimir( aux->dato);
	}	
}

void imprimirListaDFI(ListaD lista)
{
	printf("\n [%d] LISTA:",lista.cant);
	if(!lista.inicio)
	{
		printf("VACIA");
		return;
	}
	for(NodoD *aux = lista.fin; aux!=NULL;  aux=aux->ant )
	{
		printf("\n");
		lista.imprimir( aux->dato);
	}
	 
}



void borrarInicioD(ListaD *lista)
{
	NodoD *aux;
	if(!lista->inicio)
		return;	
	aux = lista->inicio;
	//UNICO NODO
	if( lista->inicio == lista->fin)
	{
		lista->inicio = lista->fin = NULL;
	}	
	//MINIMO 2
	else
	{
		lista->inicio = aux->sig;
		lista->inicio->ant = NULL;
		
	}
	//if(lista->liberar) si quito esto no me da seg fault
		//lista->liberar( aux->dato);
	free(aux);	
	lista->cant--;	
}

void borrarListaD(ListaD *lista)
{
	while(lista->inicio)
	{
		borrarInicioD(lista);
	}	
}

//NO IMPLEMENTADAS ANTES DE HACER PULL
ListaD inicializarListaD(void);	//no se que se especifico ene sta funcion :((

//BUSCAR
NodoD* buscarDatoD(ListaD lista,void *dato){
	for(NodoD *aux = lista.inicio;aux != NULL;aux = aux->sig){
		if(!lista.comparar(aux->dato,dato)){
			return aux;
		}
	}
	return NULL;
}
NodoD* buscarDatoEspecificoD(ListaD lista,void *dato,int (*comparar)(void*,void*));
//INSERTAR
void insertEnOrdenD(ListaD *lista,void *dato){
	NodoD *nuevo = crearNodoD(dato);
	//LISTA VACIA?
	if ( !lista->inicio)
	{	
		lista->inicio = lista->fin = nuevo;
	}	
	//LISTA YA TIENE ALGO
	else
	{
		for (NodoD *aux = lista->inicio; aux!= NULL ;aux = aux->sig)
		{
			
			if( lista->comparar( nuevo->dato , aux->dato  ) < 0)
			{
				//REEMPLAZAR INICIO
				if(aux == lista->inicio)
				{
					nuevo->sig = aux;
    				nuevo->ant = NULL;
    				aux->ant = nuevo;
    				lista->inicio = nuevo;
				}
				//INSERTAR EN MEDIO DE NODOS
				else
				{
					nuevo->ant = aux->ant;
					nuevo->sig = aux;
					aux->ant->sig = nuevo;
					aux->ant = nuevo;
				}
				break;
			}
			else if ( aux == lista->fin)
			{
				aux->sig = nuevo;
				nuevo->ant = aux;
				nuevo->sig = NULL;
				lista->fin = nuevo;
				break;
			}						
		}			
	}	
	lista->cant++;
}
void insertarInicioD(ListaD*,void*);
int insertarEnD( ListaD * lista, void *dato,int index);
//ELIMINAR
int borrarEnD( ListaD *lista, int index);

void borrarFinD(ListaD *lista){
    if(!lista->inicio)
        return;
    else if(lista->inicio == lista->fin){
        free(lista->inicio);
        lista->inicio = lista->fin = NULL;
        lista->cant--;
    }
    else{
        NodoD *aux = lista->fin;
        lista->fin = aux->ant;
        lista->fin->sig = NULL;
        free(aux);
        lista->cant--;
    }
}

void borrarDatoD(ListaD *lista,void *dato){
	NodoD *res = buscarDatoD(*lista,dato);
	if(res)
	{
		if( res== lista->inicio)
			borrarInicioD(lista);
		else if (res == lista->fin)
			borrarFinD(lista);
		else
		{
			res->ant->sig = res->sig;
			res->sig->ant = res->ant;
			if(lista->liberar) lista->liberar(res->dato);
			free(res);
			lista->cant--;
		}
	}
}

void reordenarD(ListaD *lista, int (*comparar)(void*,void*)){
    ListaD aux = {NULL, NULL, 0, lista->imprimir, comparar, lista->liberar};
    NodoD *sig;

    for(NodoD *n = lista->inicio; n != NULL; n = sig){
        sig = n->sig;
        n->ant = n->sig = NULL;
        insertEnOrdenD(&aux, n->dato);
    }

    lista->inicio = aux.inicio;
    lista->fin    = aux.fin;
    lista->cant   = aux.cant;
}