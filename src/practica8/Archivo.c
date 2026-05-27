#include "Archivo.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostring.h>

Archivo *crearArchivo(){
    Archivo *myFile = calloc(1,sizeof(Archivo));
    if(myFile){
        myFile->npages = rand() % 100 + 1;
        //Creacion de nombre random
        int nameLength = rand() % MAX_SIZE_NAME;
        for(int i = 0;i <= nameLength;i++)
            myFile->name[i] = 'a' + rand() % ('z' - 'a');
        myFile->name[nameLength + 1] = '\0';
    }
    return myFile;
} 

//al final esto ni se ocupa, con solo hacer free(myFile)
int freeArchivo(Archivo *myFile){
    free(myFile);
    return 1;
}

int cmpArchivo(void *file1,void *file2){
    Archivo *f1 = file1;
    Archivo *f2 = file2;
    return f1->npages - f2->npages;
}

void impArchivo(void *file){
    Archivo *myFile = file;
    printf("[%2d] %s",myFile->npages,myFile->name);
}

int cmpArchivoByName(void *file1,void *file2){
    Archivo *f1 = file1;
    Archivo *f2 = file2;
    return strcmpIC(f1->name,f2->name);
}