#include <stdio.h>
#include <string.h> /* memset */
#include <ncurses.h> // Para dibujar

int eow = 0; // EOW stands for End of the World

char a; // Almacén temporal de los caracteres obtenidos
char cad[50]; // Arreglo de paso para enviar a miArreglo
char miArreglo[99][99]; // Arreglo final para las cadenas obtenidas

char coordenadas[99][99]; // Espera... esto lo voy a ocupar en algún momento
char misCoordenadas[99][2][99]; // Nivel 1: número de par, Nivel 2: x ó y, Nivel 3: string de contenido.

void drawThis(float e1, float ye1, float e2, float ye2){
	float x1 = e1, y1 = ye1, x2 = e2, y2 = ye2;

	initscr(); // Inicializa la pantalla de dibujo
	
	// Este bloque puede ser innecesario
	move(y1,x1); // Al parecer move(Y[filas],X[columnas]); Dafuq
	addstr("o");
	move(y2,x2);
	addstr("o");
	// ---------------------------------

	int i;
	float step = (y2 - y1) / (x2-x1); // Calcula el step, siento que aquí falta algo
	
	// Aquí dibuja de verdad :0
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

	refresh(); // Actualiza el dibujo
	sleep(3); // Pausa el programa x segundos
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
			printf("%s", misCoordenadas[l][0]);
			if ( isdigit(misCoordenadas[l][0][0]) ) {
				printf(",%s\n", misCoordenadas[l][1]);
			} else {
				printf("\n");
			}
			l++;
		}

		printf("\nEXECUTING DRAWING TOOL...\n\n");

		int m = 0;
		while( misCoordenadas[m][0][0] != '\0' ) {
			if ( ( misCoordenadas[m-1][0][0] != '\0' || isdigit(misCoordenadas[m-1][0][0]) ) && isdigit(misCoordenadas[m][0][0]) ) {
				drawThis( atoi(misCoordenadas[m-1][0]), atoi(misCoordenadas[m-1][1]), atoi(misCoordenadas[m][0]), atoi(misCoordenadas[m][1]) );
				m += 2;
			}
			if ( isdigit(misCoordenadas[m][0][0]) ) {
				
			} else {
				printf("\n");
				m++;
			}
		}		

	}

} // main end