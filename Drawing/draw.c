#include <ncurses.h>
#include <stdio.h>

void main(){

	float x1, y1, x2, y2;
	//sscanf(destino?,"%d",&algo); -> para pasar a int las coordenadas

	printf("Give me X1:\n");
	scanf("%f",&x1);

	printf("Give me Y1:\n");
	scanf("%f",&y1);

	printf("Give me X2:\n");
	scanf("%f",&x2);

	printf("Give me Y2:\n");
	scanf("%f",&y2);

	initscr(); // Inicializa la pantalla de dibujo

	move(y1,x1); // Al parecer move(Y[filas],X[columnas]); Dafuq
	
	addstr("o");

	move(y2,x2);

	addstr("o");

	int i;
	float step = (y2 - y1) / (x2-x1);
	
	if ( x1 > x2 )
	{
		for ( i = 0; i >= (x2 - x1); i-- ) {
			move(y1 + (step * i),x1 + i);
			addstr("o");
		}
	} else {
		for ( i = 0; i <= (x2 - x1); i++ ) {
			move(y1 + (step * i),x1 + i);
			addstr("o");
		}
	}

	refresh(); // Actualiza el dibujo

	sleep(3); // Pausa el programa x segundos

	endwin(); // Cierra la pantalla de dibujo

}