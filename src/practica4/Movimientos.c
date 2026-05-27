#include "Laberinto.h"


Movimientos movimientosPosibles(Laberinto lab,Coordenada punto)
{
	Movimientos movimientos = {0,0,0,0};
    //caso la posicion en la que esta es literal el B
    if( lab[punto.x][punto.y] == 'B'){
        movimientos.up = 3; //caso 3 significa que no ponga nada y se salga para no quitar el B
        return movimientos;
    }
	//ARRIBA
    if( lab[punto.x-1][punto.y] == 'B')
		movimientos.up = 2;
	//ABAJO
	if( lab[punto.x+1][punto.y] == 'B')
		movimientos.down = 2;
	//DERECHA
	if( lab[punto.x][punto.y+1] == 'B')
		movimientos.right = 2;
	//IZQUIERDA
	if( lab[punto.x][punto.y-1] == 'B')
		movimientos.left = 2;

    if(movimientos.up == 2 || movimientos.down == 2 || movimientos.right == 2 || movimientos.left == 2){
            return movimientos;
    }

	if( lab[punto.x-1][punto.y] == '*')
		movimientos.up = 1;
	//ABAJO
	if( lab[punto.x+1][punto.y] == '*')
		movimientos.down = 1;
	//DERECHA
	if( lab[punto.x][punto.y+1] == '*')
		movimientos.right = 1;
	//IZQUIERDA
	if( lab[punto.x][punto.y-1] == '*')
		movimientos.left = 1;
	return movimientos;	
}

 
void imprimirMovimientos(Movimientos movimientos)
{	
	printf("\n");
	//ARRIBA
	if( movimientos.up == 1)
		printf(" ARRIBA");
	//ABAJO
	if( movimientos.down == 1)
		printf(" ABAJO");
	//DERECHA
	if( movimientos.right == 1)
		printf(" DERECHA");
	//IZQUIERDA
	if( movimientos.left == 1)
		printf(" IZQUIERDA");
	
}


int bloqueado(Movimientos mov)
{
	return mov.up == 0 && mov.up == mov.down && mov.up==mov.left && mov.up==mov.right;
}