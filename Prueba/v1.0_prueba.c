#include <stdio.h>
#include <string.h> /* memset */

int eow = 0; // EOW stands for End of the World

char a; // Almacén temporal de los caracteres obtenidos
char cad[50]; // Arreglo de paso para enviar a miArreglo
char miArreglo[99][99]; // Arreglo final para las cadenas obtenidas

char coordenadas[99][99]; // Espera... esto lo voy a ocupar en algún momento

int isOnlyNumber( char *sera ){ // Checa si la cadena completa son sólo números
	int l = strlen(sera);
	int m = 0;

	for ( m = 0; m < l; ++m )
	{
		if ( !isdigit(sera[m]) )
		{
			return 0;
		}
	}
	return 1;
}

int isInstruction( char *sera ){
	if ( strcmp(sera, "up") == 0 || strcmp(sera, "down") == 0 || strcmp(sera, "fin") == 0 )
	{
		return 1;
	}
	return 0;
}

int i = 0; // Contador para letras obtenidas por getchar
int j = 0; // Contador para el almacenamiento de cad en miArreglo
int k = 0; // Contador para la posición de ingreso de las cadenas a 
void checaCaracter( char verifyMe ){
	int goOn = 0;

	// Si el caracter no está vacío sigue jalando más y metiéndolos en cad
	if ( verifyMe != ' ' && verifyMe != '\n' && verifyMe != '\t' && verifyMe != '\r' && verifyMe != EOF )
	{
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
int futurePeerer(int theposition){ // Se fija si el siguiente elemento del arreglo es una coordenada
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
int coordParser(){ 
	char misCoordenadas[99][2][99]; // Nivel 1: número de par, Nivel 2: x ó y, Nivel 3: string de contenido.
	int runner = 0; // Para recorrer miArreglo
	int error = 0; // Errores (stray coordinates)

	while( miArreglo[runner][0] != '\0' ){ // NOTICEME: Recorrer un arreglo hasta que ya no tenga nada, nada de nada, NADA DE NADA
		if ( isdigit(miArreglo[runner][0]) )
		{
			if ( futurePeerer(runner) == 1 ) // Si el siguiente elemento es una coordenada, le sigue
			{
				printf("Good (%s, %s) \n",miArreglo[runner],miArreglo[runner+1]);
				runner += 1;
			} else { // Si no, cuenta un error
				printf("Stray Coordinate\n");
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
	printf("CLEAN ARRAY: ");
	while( miArreglo[forPrint][0] != '\0' ){
		printf("%s, ", miArreglo[forPrint]);
		forPrint++;
	}
	printf("\n\n");

	//coordParser();

	if ( coordParser() != 0 )
	{
		printf("\nERROR ERROR ERROR\n");
	}

} // main end