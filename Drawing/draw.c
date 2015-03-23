#include <ncurses.h>
#include <stdio.h>
#include <math.h>

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


	int i;
	float step;
	if ( sqrt(pow(y2 - y1,2)) > sqrt(pow(x2 - x1,2)) ) {
		if ( (x2 - x1) != 0 ) {
			step = (y2 - y1) / (x2 - x1);
		} else {
			step = 0;
		}
	} else {
		if ( (y2-y1) != 0 ) {
			step = (x2 - x1) / (y2-y1);
		} else {
			step = 0;
		}
	}
	
	initscr(); // Inicializa la pantalla de dibujo

	if ( sqrt(pow(y2 - y1,2)) > sqrt(pow(x2 - x1,2)) ) {
		if ( y1 > y2 ) {
			for ( i = 0; i >= (y2 - y1); i-- ) {
				move(y1 + i,x1 + (step * i));
				addstr("o");
			}
		} else {
			for ( i = 0; i <= (y2 - y1); i++ ) {
				move(y1 + i,x1 + (step * i));
				addstr("o");
			}
		}
	} else {
		if ( x1 > x2 ) {
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
	}

	refresh(); // Actualiza el dibujo

	sleep(3); // Pausa el programa x segundos

	endwin(); // Cierra la pantalla de dibujo

}