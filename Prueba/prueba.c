#include <stdio.h>
#include <string.h> /* memset */
#include <ncurses.h> // Para dibujar
#include <math.h> // Para el sqrt y la pow, pow pow pow, what does the fox say?

/* NOTA: Para compilar este archivo: gcc -o test prueba.c -lncurses -lm */

int eow = 0; // EOW stands for End of the World

char a; // Almacén temporal de los caracteres obtenidos
char cad[50]; // Arreglo de paso para enviar a miArreglo
char miArreglo[99][99]; // Arreglo final para las cadenas obtenidas
int penDown = 1; // Estado de la "pluma"

char coordenadas[99][99]; // Espera... esto lo voy a ocupar en algún momento
char misCoordenadas[99][2][99]; // Nivel 1: número de par, Nivel 2: x ó y, Nivel 3: string de contenido.

void drawThis(float e1, float ye1, float e2, float ye2){
	float x1 = e1, y1 = ye1, x2 = e2, y2 = ye2;

	initscr(); // Inicializa la pantalla de dibujo

	int i; // FIX THIS: !!!
	float step;
	float yDiff = y2 - y1, xDiff = x2 - x1;

	if ( yDiff > xDiff ) {
		if ( (xDiff) != 0 ) {
			if ( sqrt(pow(yDiff,2)) > sqrt(pow(xDiff,2)) ) {
				step = (xDiff) / (yDiff);
			} else {
				step = (yDiff) / (xDiff);
			}
		} else {
			step = 0;
		}
	} else {
		if ( (yDiff) != 0 ) {
			if ( sqrt(pow(yDiff,2)) > sqrt(pow(xDiff,2)) ) {
				step = (xDiff) / (yDiff);
			} else {
				step = (yDiff) / (xDiff);
			}
		} else {
			step = 0;
		}
	}

	// Aquí dibuja de verdad :0
	if ( sqrt(pow(yDiff,2)) > sqrt(pow(xDiff,2)) ) {
		if ( y1 > y2 ) {
			for ( i = 0; i >= (yDiff); i-- ) {
				move(y1 + i,x1 + (step * i));
				addstr("o");
			}
		} else {
			for ( i = 0; i <= (yDiff); i++ ) {
				//printf("%f, %f, step: %f\n", y1 + i, x1 + (step * i), step);
				move(y1 + i,x1 + (step * i));
				addstr("o");
			}
		}
	} else {
		if ( x1 > x2 ) {
			for ( i = 0; i >= (xDiff); i-- ) {
				move(y1 + (step * i),x1 + i);
				addstr("o");
			}
		} else {
			for ( i = 0; i <= (xDiff); i++ ) {
				move(y1 + (step * i),x1 + i);
				addstr("o");
			}
		}
	}

	refresh(); // Actualiza el dibujo
	sleep(1); // Pausa el programa x segundos
	endwin(); // Cierra la pantalla de dibujo
}

int isOnlyNumber( char *sera ){ // Checa si la cadena completa son sólo números
	int l = strlen(sera);
	int m = 0;

	for ( m = 0; m < l; ++m ) {
		if ( !isdigit(sera[m]) ) {
			return 0;
		}
	}
	return 1;
}

int isInstruction( char *sera ){
	if ( strcmp(sera, "up") == 0 || strcmp(sera, "down") == 0 || strcmp(sera, "fin") == 0 ) {
		return 1;
	}
	return 0;
}

int i = 0; // Contador para letras obtenidas por getchar
int j = 0; // Contador para el almacenamiento de cad en miArreglo
int k = 0; // Contador para la posición de ingreso de las cadenas a 
void checaCaracter( char verifyMe ) {
	int goOn = 0;

	// Si el caracter no está vacío sigue jalando más y metiéndolos en cad
	if ( verifyMe != ' ' && verifyMe != '\n' && verifyMe != '\t' && verifyMe != '\r' && verifyMe != EOF ) {
		cad[i] = verifyMe;
		i++;
	} else if ( cad[0] != '\0' ) { // Al encontrar un caracter vacío 
		for (j = 0; j < i; ++j) // Recorre el arreglo cad
		{
			if ( isOnlyNumber( cad ) == 1 ) // Si cad es un número (de uno o varios dígitos)
			{
				miArreglo[k][j] = cad[j]; // Guarda en miArreglo el número en la posición k
				goOn = 1;
			} else if ( isInstruction( cad ) == 1 ) // Si es una instrucción
			{
				if ( strcmp(cad, "fin") == 0 ) // Si es fin
				{
					goOn = 0; // Detiene este ciclo
					eow = 1; // Finaliza el mundo y con esto el programa muere :0
				} else {
					miArreglo[k][j] = cad[j]; // Guarda en el arreglo la instrucción en la posición k
					goOn = 1;
				}
			}
		}

		if ( goOn == 1 ) // Si el ciclo terminó
		{
			k++; // Avanza en la posición de miArreglo
		}
		
		memset(cad, 0, sizeof cad); // Borra el arreglo temporal cad (cad es de cadena :3)
		i = 0; // Reinicia el contador de caracteres
	}
} // checaCaracter end

/**
/* La función para ver el futuro   \(ºoº)/   ~(º.º)~
*/
int futurePeerer(int theposition) { // Se fija si el siguiente elemento del arreglo es una coordenada
	if ( isdigit(miArreglo[theposition+1][0]) ) {
		return 1;
	}
	else {
		return 0;
	}
}

/**
/* Parser de coordenadas
*/
int coordParser() { 
	int runner = 0; // Para recorrer miArreglo
	int error = 0; // Errores (stray coordinates)

	printf("COORDINATE PARSER RESULTS:\n");

	while( miArreglo[runner][0] != '\0' ){ // NOTICEME: Recorrer un arreglo hasta que ya no tenga nada, nada de nada, NADA DE NADA
		if ( isdigit(miArreglo[runner][0]) ) {
			if ( futurePeerer(runner) == 1 ) // Si el siguiente elemento es una coordenada, le sigue
			{
				printf("Good (%s, %s) \n",miArreglo[runner],miArreglo[runner+1]);
				runner += 1;
			} else { // Si no, cuenta un error
				printf("================\nStray Coordinate\n================\n");
				error++;
			}
		}
		runner++;
	}
	return error;
} // coordParser end

void main(){

	while ( a != EOF && eow != 1 ) // Mientras a sea diferente al fin de archivo y eow no sea 1
	{
		a = getchar(); // Consigue un nuevo caracter
		checaCaracter( a ); // Comprueba el caracter
	}

	int forPrint = 0;
	int pairCount = 0;
	int coordCount = 0;
	printf("CLEAN ARRAY:\n");
	while( miArreglo[forPrint][0] != '\0' ){
		int l = 0;

		printf("%s, ", miArreglo[forPrint]);
		// Aquí estoy moviendo el arreglo limpio a mi super arreglo tridimensional
		// It's like I can touch it!!!
		if ( isdigit( miArreglo[forPrint][0] ) && pairCount == 0 ) {
			for ( l = 0; l <= strlen(miArreglo[forPrint]); l++ ) {
				misCoordenadas[coordCount][0][l] = miArreglo[forPrint][l];
			}
			pairCount++;
		} else if ( isdigit( miArreglo[forPrint][0] ) && pairCount == 1 ) {
			for ( l = 0; l < strlen(miArreglo[forPrint]); l++ ) {
				misCoordenadas[coordCount][1][l] = miArreglo[forPrint][l];
			}
			pairCount = 0;
			coordCount++;
		} else if ( !isdigit( miArreglo[forPrint][0] ) ) {
			for ( l = 0; l < strlen(miArreglo[forPrint]); l++ ) {
				misCoordenadas[coordCount][0][l] = miArreglo[forPrint][l];
			}
			coordCount++;
		}

		forPrint++;
	}
	printf("\n\n");

	//coordParser();

	if ( coordParser() != 0 ) {
		printf("\n=================\nERROR ERROR ERROR\n=================\n Please verify the instructions file for possible mistakes ;D\n\n");
	} else {
		printf("\nCLEAN INSTRUCTIONS:\n");

		int l = 0;
		while( misCoordenadas[l][0][0] != '\0' ) {
			printf("[%d]: %s", l, misCoordenadas[l][0]);
			if ( isdigit(misCoordenadas[l][0][0]) ) {
				printf(",%s\n", misCoordenadas[l][1]);
			} else {
				printf("\n");
			}
			l++;
		}

		printf("\nEXECUTING DRAWING TOOL...\n\n");

		int m = 1;
		int aFlag = 0;
		float angle;
		int xVal, yVal;
		while ( misCoordenadas[m][0][0] != '\0' ) {
			if ( isdigit(misCoordenadas[m][0][0]) && aFlag == 0  ) {
				int n = 1;
				while ( !isdigit(misCoordenadas[m-n][0][0]) ) {
					if ( m - n > 0 ) {
						n++;
					} else {
						aFlag = 1;
						break;
					}
				}
				if ( aFlag == 0 ) {
					if ( penDown == 1 ) {
						angle = atan( (float)(atoi(misCoordenadas[m-n][1]) - atoi(misCoordenadas[m][1])) / (float)(atoi(misCoordenadas[m-n][0]) - atoi(misCoordenadas[m][0])) ) * (180 / 3.14159265359);
						if ( sqrt(pow(angle,2)) < 30 ) {
							xVal = atoi(misCoordenadas[m][0]);
							yVal = atoi(misCoordenadas[m-n][1]);
						} else if ( sqrt(pow(angle,2)) > 60 && sqrt(pow(angle,2)) < 90 ) {
							xVal = atoi(misCoordenadas[m-n][0]);
							yVal = atoi(misCoordenadas[m][1]);
						} else {
							yVal = atoi(misCoordenadas[m][1]);
							xVal = atoi(misCoordenadas[m][0]);
						}
						printf("%d, %d\n", xVal, yVal );
						printf("%d,%d : %d,%d || %f\n", atoi(misCoordenadas[m-n][0]), atoi(misCoordenadas[m-n][1]), atoi(misCoordenadas[m][0]), atoi(misCoordenadas[m][1]), angle);
						drawThis( atoi(misCoordenadas[m-n][0]), atoi(misCoordenadas[m-n][1]), xVal, yVal );
					}
					m++;
				}
			} else {
				if ( m == 1 && aFlag == 1 ) {
					if ( strcmp(misCoordenadas[m-1][0], "up") == 0 ) {
						printf("Pen is up \n");
						penDown = 0;
					} else if ( strcmp(misCoordenadas[m-1][0], "down") == 0 ) {
						penDown = 1;
					}
				} else {
					if ( strcmp(misCoordenadas[m][0], "up") == 0 ) {
						printf("Pen is up \n");
						penDown = 0;
					} else if ( strcmp(misCoordenadas[m][0], "down") == 0 ) {
						penDown = 1;
					}
				}
				aFlag = 0;
				m++;
			}
		}

		printf("\nFIN DEL PROGRAMA\n");	

	}

} // main end