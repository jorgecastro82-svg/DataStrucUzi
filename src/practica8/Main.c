
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <arbol.h>
#include <time.h>
#include <iostring.h>
#include <heap.h>
#include "Archivo.h"

int* crearEntero(int);
int compararEntero(void*,void*);
void imprimirEntero(void*);
int dispMenu();
void swap(void **a, void **b);
int findIndexOfArchive(char* archName,Heap *h);

int main(void)
{
	Heap heap = crearHeap(HEAP_MIN,cmpArchivo,impArchivo);
	srand(time(NULL));
	//Arbol para impresiones
	Arbol arbAux = {0};
	void *archivoAux = NULL;

	while(true){

		//IMPLEMENTAR QUE SIEMPRE SE IMPRIMEN LOS PRIMERO 5 ARCHIVOS
		imprimirHeapFirstFive(heap);
		switch(dispMenu()){
			case 0://Cambiar Prioridad
				heap.tipo = (heap.tipo == HEAP_MAX) ? HEAP_MIN : HEAP_MAX;
				heapify(&heap);
				imprimirHeap(heap);
				printf("\n");
				arbAux = heapToTree(&heap,impArchivo,cmpArchivo);
				imprimirArbol(arbAux);
				eliminarArbol(&arbAux);
			break;

			case 1://imprimir cola de prioridad
				imprimirHeap(heap);
				printf("\n");
				arbAux = heapToTree(&heap,impArchivo,cmpArchivo);
				imprimirArbol(arbAux);
				eliminarArbol(&arbAux);
			break;

			case 2://agregar archivo
				insertarHeap(&heap, crearArchivo());
			break;

			case 3://procesar/imprimir archivo
				archivoAux = eliminarHeap(&heap);
				printf("\n Archivo procesado: ");
				if(!archivoAux){
					printf("\nNo hay archivos todavia");
				}
				else{
					impArchivo(archivoAux);
					free(archivoAux);
					archivoAux = NULL;
				}
			break;

			case 4://eliminar archivo (solo falta esto, se ocupa preguntar si se tiene que respetar cola de prioridad, o si se recorre cono arreglo		)
			{
				if(!heap.cantidad){
					printf("No hay nada que eliminar, esta vacio el heap\n");
					break;
				}
				
				//impresion de heap
				imprimirHeap(heap);
				printf("\n");

				//Pedida de nombre del archivo para eliminar
				char cadena[10] = {0};
				inputCadena("Deme el nombre del archivo a eliminar: ",cadena,10);
				
				//impresion del arbol modo grafico del heap
				arbAux = heapToTree(&heap,impArchivo,cmpArchivo);
				imprimirArbol(arbAux);
				eliminarArbol(&arbAux);

				//caso no se encontro el archivo que mandaron a eliminar
				int indexToSwap = findIndexOfArchive(cadena,&heap);
				if(indexToSwap == -1){
					printf("\nNo se encontro un archivo con ese nombre\n");
					break;
				}
				//lo que se hace es cambiarlo con la posicion inicial y se hace heapify despues
				swap(heap.datos + indexToSwap,heap.datos);
				void *dato = eliminarHeap(&heap);
				printf("\n Archivo procesado: ");
				impArchivo(dato);
				free(dato);
			}
			break;

			case 5://eliminar todos los archivos
				while(heap.cantidad)
				{
					void *dato = eliminarHeap(&heap);
					printf("\n Dato eliminado: ");
					impArchivo(dato);
					free(dato);
				}
			break;

			case 6://terminar programa
				while(heap.cantidad)
				{
					void *dato = eliminarHeap(&heap);
					free(dato);
				}
				printf("\n\n FIN DE PROGRAMA\n");
				return 0;
			break;

			default://caso incorrecto
				printf("\nOPCION INCORRECTA");
			break;
		}
	}
	
}

void swap(void **a, void **b){
	void* temp = *a;
	*a = *b;
	*b = temp;
	return;
}

int findIndexOfArchive(char* archName,Heap *h){
	if(!h || !h->datos)
		return -1;
	Archivo aux = {0};
	strcpy(aux.name,archName);
	for(int i = 0; i < h->cantidad;i++){
		if(cmpArchivoByName(&aux,h->datos[i]) == 0)
			return i;
	}
	return -1;
}
int dispMenu(){
	int opc;
	printf("\n---MENU---");
	printf("\n[0] Cambiar Prioridad");
	printf("\n[1] Mostrar Cola de Prioridad");
	printf("\n[2] Agregar Archivo");
	printf("\n[3] Procesar/Imprimir Archivo");
	printf("\n[4] Eliminar Archivo");
	printf("\n[5] Eliminar Todos Los Archivos");
	printf("\n[6] Terminar Programa");
	inputEntero("\nDeme su opcion: ",&opc);
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