#include <stdio.h>
#include "Alumno.h"
#include <listadoble.h>
#include <iostring.h>
#include <stdbool.h>

//prototipos de funciones
int dispMenu();
int dispMenuOrdenamiento();
int dispMenuBusquedaPorMiembro();
int dispMenuImprimir();

int main()
{
	ListaD lista = {NULL,NULL,0,imprimirAlumno,compararMatricula,free};
	Alumno *aux = NULL;
	int (*auxComp)(void*,void*);
	int auxEntero;
	char auxNombre[LEN];
	float auxFloat;
	unsigned int auxSinSigno;
	NodoD *auxNodoD = NULL;
	while(true){
		switch(dispMenu()){
			//Se capturan los datos del alumno (las matrículas deben ser únicas)
			// y se inserta en la lista enlazada.
			case 1:
				//primero de todo se cambia la funcion miembro comparar de la lista a matricula
				// y se guarda auxiliar de la funcion anterior que se tuvo en comparar
				auxComp = lista.comparar;
				lista.comparar = compararMatricula;
				//creacion de alumno
				aux = crearAlumno();
				//caso de que su matricula ya esta en la lista
				//como retorna una estructura resultado que sus miembros se inicializan en NULL
				//en caso de que enco no sea NULL entrara a este if
				if(buscarDatoD(lista,&aux->matricula)){
					printf("\nNo puedes aniadir dos alumnos con misma matricula");
					free(aux);
					lista.comparar = auxComp;
				}
				//caso contrario entonces no esta y si se puede aniadir, y se regresa
				//a la funcion anterior de comparar
				else{
					lista.comparar = auxComp;
					insertEnOrdenD(&lista,aux);
				}

			break;

			//Se muestran en pantalla los alumnos en la lista enlazada, de acuerdo a su orden.
			case 2:
				
				//impresion de que es cada cosa
				if(!lista.inicio){
					printf("\nESTA VACIA NO PUEDES IMPIMIR NADA");
					break;
				}

				switch(dispMenuImprimir()){
					case 1:
						imprimirListaDIF(lista);
					break;

					case 2:
						imprimirListaDFI(lista);
					break;

					default:
						printf("\nOPCION INCORRECTA, NO SE IMPRIMIO NADA");
					break;
				}
			break;

			//Se cambia el orden de los datos según la selección de algunos de los miembros de la estructura Alumno 
			//(matrícula, nombre, semestres, promedio). 
			//Se requiere una lista auxiliar para realizar esta operación.
			case 3:
				if(!lista.inicio){
					printf("\nESTA VACIA NO PUEDES REORDENAR NADA");
					break;
				}

				switch(dispMenuOrdenamiento()){
					case 1:
						reordenarD(&lista,compararMatricula);
					break;

					case 2:
						reordenarD(&lista,compararNombre);
					break;

					case 3:
						reordenarD(&lista,compararSemestre);
					break;

					case 4:
						reordenarD(&lista,compararPromedio);
					break;

					default:
						printf("\nOPCION INCORRECTA, NO SE CAMBIO NADA");
					break;
				}
				
			break;
 
			//Se captura el criterio de búsqueda de acuerdo a un miembro de la estructura Alumno 
			//(matrícula, nombre, semestres, promedio). Es necesario cambiar la función de comparación. 
			//Se muestra en pantalla los datos del alumno en caso de encontrarlo
			case 4:
				if(!lista.inicio){
					printf("\nESTA VACIA NO PUEDES BUSCAR NADA");
					break;
				}
				//guardado de la funcion de comparacion anterior ya que solo se usara diferente comparacion
				//para realizar la busqueda
				auxComp = lista.comparar;

				//seleccion de ordenamiento para busqueda
				switch(dispMenuBusquedaPorMiembro()){
					case 1:
						lista.comparar = compararMatricula;
						//pedida de matricula
						do{
						}while(!inputEnteroSinSigno("\nIngrese matricula del alumno a buscar: ",&auxSinSigno));
						auxNodoD = buscarDatoD(lista,&auxSinSigno);
					break;

					case 2:
						lista.comparar = compararNombreInput;
						//pedida de nombre
						do{
						}while(!inputCadena("\nIngrese nombre del alumno a buscar: ",auxNombre,LEN));
						auxNodoD = buscarDatoD(lista,auxNombre);
					break;

					case 3:
						lista.comparar = compararSemestreInput;
						//pedida de semestsre, va retornar el primero que encuentre con ese semestre
						do{
						}while(!inputEntero("\nIngrese semestre del alumno a buscar: ",&auxEntero));
						auxNodoD = buscarDatoD(lista,&auxEntero);
					break;

					case 4:
						lista.comparar = compararPromedioInput;
						//pedida de semestsre, va retornar el primero que encuentre con ese semestre
						do{
						}while(!inputFloat("\nIngrese promedio del alumno a buscar: ",&auxFloat));
						auxNodoD = buscarDatoD(lista,&auxFloat);
					break;

					default:
						printf("\nOPCION INCORRECTA, REGRESANDO A MENU");
					break;
				}
				//caso de ser encontrado
				if(auxNodoD && auxNodoD->dato){
					imprimirAlumno(auxNodoD->dato);
				}
				else{
					printf("\nLos datos enviados no pertenecen a ningun alumno");
				}
				//regresar a la funcion de comparacion anterior
				lista.comparar = auxComp;
			break;

			//Se captura la matrícula del alumno a eliminar y se extrae de la lista
			case 5:
				if(!lista.inicio){
					printf("\nESTA VACIA NO PUEDES ELIMINAR NADA");
					break;
				}

				//auxiliar para funcion de comparacion
				auxComp = lista.comparar;
				lista.comparar = compararMatricula;
				
				//pedida de matricula
				do{
				}while(!inputEnteroSinSigno("\nIngrese matricula del alumno a eliminar: ",&auxSinSigno));
				borrarDatoD(&lista,&auxSinSigno);
				
				lista.comparar = auxComp;
			break;

			//salida del programa
			case 6:
				printf("\nSaliendo del programa");
				return 0;
			break;

			//caso operacion incorrecta
			default:
				printf("\nOPERACION INCORRECTA");
			break;
		}
	}

	return 0;
}

int dispMenu(){
	int numRetornar;
	do{
		printf("\n---MENU---");
		printf("\n[1] para registrar Alumno");
		printf("\n[2] para desplegar alumnos");
		printf("\n[3] para Reordenar");
		printf("\n[4] para buscar alumno");
		printf("\n[5] para borrar alumno");
		printf("\n[6] para salir del programa");
	}while(!inputEntero("\nIngrese su seleccion: ",&numRetornar));
	return numRetornar;
}

int dispMenuOrdenamiento(){
	int numRetornar;
	do{
		printf("\n---MENU DE ORDENADO DE LISTA---");
		printf("\n[1] para ordenar por matricula");
		printf("\n[2] para ordenar por nombre");
		printf("\n[3] para ordenar por semestre");
		printf("\n[4] para ordenar por promedio");
	}while(!inputEntero("\nIngrese su seleccion: ",&numRetornar));
	return numRetornar;
}

int dispMenuBusquedaPorMiembro(){
	int numRetornar;
	do{
		printf("\n---MENU DE BUSQUEDA POR MIEMBRO	---");
		printf("\n[1] para buscar por matricula");
		printf("\n[2] para buscar por nombre");
		printf("\n[3] para buscar por semestre");
		printf("\n[4] para buscar por promedio");
	}while(!inputEntero("\nIngrese su seleccion: ",&numRetornar));
	return numRetornar;
}



int dispMenuImprimir(){
	int numRetornar;
	do{
		printf("\n---MENU DE IMPRESION DE LISTA---");
		printf("\n[1] para imprimir ascendente");
		printf("\n[2] para imprimir descendente");
	}while(!inputEntero("\nIngrese su seleccion: ",&numRetornar));
	return numRetornar;
}