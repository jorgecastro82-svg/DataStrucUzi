#pragma once
#define MAX_SIZE_NAME 10
typedef struct{
    char name[MAX_SIZE_NAME];
    int npages;
}Archivo;

Archivo *crearArchivo();

int freeArchivo(Archivo *myFile);
int cmpArchivo(void *file1,void *file2);
int cmpArchivoByName(void *file1,void *file2);
void impArchivo(void *file); 