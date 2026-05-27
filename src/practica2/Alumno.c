#include "Alumno.h"

Alumno* crearAlumno(void)
{
	Alumno *nuevo = calloc(1,sizeof(Alumno));
	inputEnteroSinSigno("\n Matricula: ",&nuevo->matricula);
	inputCadena(" Nombre: ",nuevo->nombre,LEN);
	inputEntero(" Semetres: ",&nuevo->semestre);
	inputFloat(" Promedio: ",&nuevo->promedio);
	return nuevo;	
}

void imprimirAlumno(void *dato)
{
	Alumno *alumno = dato;
	printf("\n %-7u | ",alumno->matricula);
	printf("%-40s | ",alumno->nombre);
	printf("%-2d | ",alumno->semestre);
	printf("%.2f  ",alumno->promedio);
}
//comparar
// NEGATIVO si datoA < datoB
// CERO si datoA == datoB
// POSITIVO si datoA > datoB
int compararMatricula(void *datoA,void *datoB)
{
	Alumno *alumA = datoA,*alumB = datoB;
	return alumA->matricula - alumB->matricula;	
}
int compararNombre(void *datoA,void *datoB)
{
	Alumno *alumA = datoA,*alumB = datoB;
	return strcmp(alumA->nombre,alumB->nombre);	
}
int compararSemestre(void *datoA,void *datoB)
{
	Alumno *alumA = datoA,*alumB = datoB;
	return alumA->semestre - alumB->semestre;	
	
}
int compararPromedio(void *datoA,void *datoB)
{
	Alumno *alumA = datoA,*alumB = datoB;
	if( alumA->promedio < alumB->promedio) return -1;
	else if( alumA->promedio > alumB->promedio) return 1;
	else return 0;
}
int compararAlumno(void *datoA,void *datoB)
{
	return 0;
}

//funciones parar comparar mediante input, ya que las funciones de comparar comparan
//un dato alumno con otro dato alumno
// y queremos hacer que compare un dato con un alumno
//se omite la de matricula por que funciona
//se descubrio que funciona solo por que su apuntador 
//y el apuntador a la estructura apuntan a lo mismo
//solo por que es el primer miembro, solo por eso sirve
int compararNombreInput(void *input, void *dato)
{
    char *nombreInput = input;
    Alumno *alum = dato;
    return strcmp(nombreInput, alum->nombre);
}

int compararSemestreInput(void *input, void *dato)
{
    int *semestreInput = input;
    Alumno *alum = dato;

    return *semestreInput - alum->semestre;
}

int compararPromedioInput(void *input, void *dato)
{
    float *promedioInput = input;
    Alumno *alum = dato;

    return *promedioInput - alum->promedio;
}


