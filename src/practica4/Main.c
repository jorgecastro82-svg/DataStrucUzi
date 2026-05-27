#include <stdio.h>
#include <stdlib.h>
#include <pila.h>
#include "Laberinto.h"

void resolverLab(unsigned char **lab,Coordenada punto);


int main(void)
{
    Laberinto lab = crear_laberinto();
	Coordenada *punto;
	//Movimientos mov;
	Coordenada origen = {18,1};
	Coordenada destino = {17,0};
	setOrigen(lab,origen);
	setDestino(lab,destino);
	imprimirLab(lab);
	Pila pila = {NULL,0,-1,imprimirCoordenada,free};
	//PUSH INICIAL DEL ORIGEN
	punto = crearCoordenada(origen.x,origen.y);
	pushDato(&pila,punto);
	
	//CICLO
	/*
	while( !pilaVacia(pila))
	{
		punto = peekPila(pila);
		mov = movimientosPosibles(lab,*punto);		
		//REGRESAR
		
		if(bloqueado(mov))
		{
			free( popDato(&pila) );
		}
		
		//MOVERTE
	}
	*/
    resolverLab(lab,origen);
	

	imprimirLab(lab);
	liberarLaberinto(lab);
    printf("\n\n FIN DE PROGRAMA\n\n");
    return 0;
}

void resolverLab(unsigned char **lab,Coordenada punto){
    Coordenada *cordDinamic = crearCoordenada(punto.x,punto.y);
    Pila pila = {NULL,0,-1,NULL,NULL};
    pushDato(&pila,cordDinamic);
    Movimientos mov;

    while(!pilaVacia(pila)){
        cordDinamic = peekDato(&pila); //peekDato(&pila);
        mov = movimientosPosibles(lab,*cordDinamic);
	    imprimirMovimientos(mov);

	    printf("\n");

        //caso en la misma posicion se encontro B
        if( mov.up == 3)
	    {
            break;
        }
	    //ARRIBA CASO GANADOR
	    else if( mov.up == 2)
	    {
		    lab[cordDinamic->x][cordDinamic->y] = '.';
            pushDato(&pila,crearCoordenada(cordDinamic->x-1,cordDinamic->y));
            break;
        }
	    //ABAJO CASO GANADOR
	    else if( mov.down == 2)
	    {
		    lab[cordDinamic->x][cordDinamic->y] = '.';
            pushDato(&pila,crearCoordenada(cordDinamic->x+1,cordDinamic->y));            
            break;
        }
	    //DERECHA CASO GANADOR
	    else if( mov.right == 2)
	    {
		    lab[cordDinamic->x][cordDinamic->y] = '.';
            pushDato(&pila,crearCoordenada(cordDinamic->x,cordDinamic->y+1));
            break;
        }
	    //IZQUIERDA CASO GANADOR
	    else if( mov.left == 2)
	    {
		    lab[cordDinamic->x][cordDinamic->y] = '.';
            pushDato(&pila,crearCoordenada(cordDinamic->x,cordDinamic->y-1));
            break;
        }
        //ARRIBA
	    else if( mov.up == 1)
	    {
            if(!(lab[cordDinamic->x][cordDinamic->y] == 'A'))
		        lab[cordDinamic->x][cordDinamic->y] = '.';
            pushDato(&pila,crearCoordenada(cordDinamic->x-1,cordDinamic->y));
        }
	    //ABAJO
	    else if( mov.down == 1)
	    {
            if(!(lab[cordDinamic->x][cordDinamic->y] == 'A'))
		        lab[cordDinamic->x][cordDinamic->y] = '.';
            pushDato(&pila,crearCoordenada(cordDinamic->x+1,cordDinamic->y));
        }
	    //DERECHA
	    else if( mov.right == 1)
	    {
            if(!(lab[cordDinamic->x][cordDinamic->y] == 'A'))
		        lab[cordDinamic->x][cordDinamic->y] = '.';
            pushDato(&pila,crearCoordenada(cordDinamic->x,cordDinamic->y+1));
        }
	    //IZQUIERDA
	    else if( mov.left == 1)
	    {
            if(!(lab[cordDinamic->x][cordDinamic->y] == 'A'))
		        lab[cordDinamic->x][cordDinamic->y] = '.';
            pushDato(&pila,crearCoordenada(cordDinamic->x,cordDinamic->y-1));
        }
        else{
            lab[cordDinamic->x][cordDinamic->y] = 'O';
            //liberacion por que tiene memoria dinamica la cordenada
            free(popDato(&pila));
        }
        imprimirLab(lab);
    }
    //caso mazos imposibles
    if(!(mov.up + mov.down + mov.right + mov.left)){
        printf("NO HAY SOLUCION!!!!!!!");
    }
	printf("\n");
	imprimirLab(lab);

    //caso de que ya se salio del loop del laberinto y la pila todavia contiene cosas
    while(!pilaVacia(pila))
        free(popDato(&pila));
}