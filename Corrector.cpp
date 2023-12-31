/*****************************************************************************************************************
UNIVERSIDAD NACIONAL AUTONOMA DE MEXICO
FACULTAD DE ESTUDIOS SUPERIORES - ARAGON -

Computadoras y programacion.
Calder�n Almanza Marvin Daniel 321307491

Quiso decir : Programa principal de la aplicacion de la distancia de Levenstein.

* *****************************************************************************************************************/


#include "stdafx.h"
#include <ctype.h>
#include <string.h>
#include "corrector.h"
#define DEPURAR 0

//Funciones publicas del proyecto
/*****************************************************************************************************************
	DICCIONARIO: Esta funcion crea el diccionario completo
	char *	szNombre				:	Nombre del archivo de donde se sacaran las palabras del diccionario
	char	szPalabras[][TAMTOKEN]	:	Arreglo con las palabras completas del diccionario
	int		iEstadisticas[]			:	Arreglo con el numero de veces que aparecen las palabras en el diccionario
	int &	iNumElementos			:	Numero de elementos en el diccionario
******************************************************************************************************************/
void	Diccionario(char* szNombre, char szPalabras[][TAMTOKEN], int iEstadisticas[], int& iNumElementos)
{
	FILE* fpDicc;
	char linea[80000];
	char palabraDetectada[TAMTOKEN];
	int i;
	int indicePD;
	char apoyo[TAMTOKEN];
	iNumElementos = 0;
	// abrir el achivo
	if (DEPURAR == 1)
		printf("%s", szNombre);

	fopen_s(&fpDicc, szNombre, "r");

	if (fpDicc != NULL)
	{
		indicePD = 0;
		while (!feof(fpDicc))
		{
			fgets(linea, sizeof(linea), fpDicc);

			for (i = 0; i < strlen(linea); i++)
			{
				if (linea[i] == ' ' || linea[i] == '.' || linea[i] == ':' || linea[i] == ',' || linea[i] == '-' || linea[i] == ';' || linea[i] == '\n')
				{
					if (linea[i + 1] != ' ')
					{
						palabraDetectada[indicePD] = '\0';
						strcpy_s(szPalabras[iNumElementos], TAMTOKEN, palabraDetectada);
						iEstadisticas[iNumElementos] = 1;
						indicePD = 0;
						iNumElementos++;
					}
				}
				else
				{
					if (linea[i] != '(' && linea[i] != ')' && linea[i] != ',' && linea[i] != '.' && linea[i] != ';' && linea[i] != ':' && linea[i] != ' ' && linea[i] != '\'' && linea[i] != '-' && linea[i + 1] != '-')
					{
						palabraDetectada[indicePD] = tolower(linea[i]);
						indicePD++;
					}
				}
			}
			// burbujazo
			int capas, comp, o, h;
			//palabras repetidas
			for (i = 0; i < iNumElementos - 1; i++) {
				for (o = i + 1; o < iNumElementos;) {
					if (strcmp(szPalabras[i], szPalabras[o]) == 0) {
						iEstadisticas[i] = iEstadisticas[i] + 1;
						// Eliminar elemento duplicado
						for (h = o; h < iNumElementos - 1; h++) {
							strcpy_s(szPalabras[h], TAMTOKEN, szPalabras[h + 1]);
						}
						(iNumElementos)--;
					}
					else {
						o++;
					}
				}
			}
			for (capas = 0; capas < iNumElementos - 1; capas++) {
				for (comp = 0; comp < iNumElementos - 1; comp++) {
					if (strcmp(szPalabras[comp], szPalabras[comp + 1]) > 0) {

						strcpy_s(apoyo, TAMTOKEN, szPalabras[comp]);
						strcpy_s(szPalabras[comp], TAMTOKEN, szPalabras[comp + 1]);
						strcpy_s(szPalabras[comp + 1], TAMTOKEN, apoyo);
					}
				}
			}
		}
		fclose(fpDicc);
	}
	printf("\nNumPalabras: %i\n", iNumElementos);
}



/*****************************************************************************************************************
	ListaCandidatas: Esta funcion recupera desde el diccionario las palabras validas y su peso
	Regresa las palabras ordenadas por su peso
	char	szPalabrasSugeridas[][TAMTOKEN],	//Lista de palabras clonadas
	int		iNumSugeridas,						//Lista de palabras clonadas
	char	szPalabras[][TAMTOKEN],				//Lista de palabras del diccionario
	int		iEstadisticas[],					//Lista de las frecuencias de las palabras
	int		iNumElementos,						//Numero de elementos en el diccionario
	char	szListaFinal[][TAMTOKEN],			//Lista final de palabras a sugerir
	int		iPeso[],							//Peso de las palabras en la lista final
	int &	iNumLista)							//Numero de elementos en la szListaFinal
******************************************************************************************************************/
void	ListaCandidatas		(
	char	szPalabrasSugeridas[][TAMTOKEN],	//Lista de palabras clonadas
	int		iNumSugeridas,						//Lista de palabras clonadas
	char	szPalabras[][TAMTOKEN],				//Lista de palabras del diccionario
	int		iEstadisticas[],					//Lista de las frecuencias de las palabras
	int		iNumElementos,						//Numero de elementos en el diccionario
	char	szListaFinal[][TAMTOKEN],			//Lista final de palabras a sugerir
	int		iPeso[],							//Peso de las palabras en la lista final
	int &	iNumLista)							//Numero de elementos en la szListaFinal
{

	//Sustituya estas lineas por su c digo
	strcpy(szListaFinal[0], szPalabrasSugeridas[ 0] ); //la palabra candidata
	iPeso[0] = iEstadisticas[0];			// el peso de la palabra candidata
	
	iNumLista = 1;							//Una sola palabra candidata
}

/*****************************************************************************************************************
	ClonaPalabras: toma una palabra y obtiene todas las combinaciones y permutaciones requeridas por el metodo
	char *	szPalabraLeida,						// Palabra a clonar
	char	szPalabrasSugeridas[][TAMTOKEN], 	//Lista de palabras clonadas
	int &	iNumSugeridas)						//Numero de elementos en la lista
******************************************************************************************************************/
void	ClonaPalabras(
	char* szPalabraLeida,						// Palabra a clonar
	char szPalabrasSugeridas[][TAMTOKEN], 	//Lista de palabras clonadas
	int& iNumSugeridas)						//Numero de elementos en la lista
{
	int i;
	char clona[50][TAMTOKEN];
	char ayuda[50];
	char palabra[50];
	// Almacenar la palabra original en la posici�n 0 del arreglo de palabras sugeridas
	strcpy_s(szPalabrasSugeridas[0], szPalabraLeida);

	// Eliminar una letra a la vez y almacenar las sugerencias en el arreglo
	int longitud = strlen(szPalabraLeida);

	strcpy_s(palabra, TAMTOKEN, szPalabraLeida);

	strcpy_s(szPalabrasSugeridas[0], TAMTOKEN, szPalabraLeida);

	for (int i = 1; i < longitud + 1; i++) {
		int indice = 0;

		// Iteramos sobre cada posici�n en la palabra
		for (int j = 0; j < longitud; j++) {
			// Saltamos el car�cter en la posici�n actual
			if (i != j) {
				clona[i + 1][indice++] = palabra[j];
			}
		}
		clona[i][indice] = '\0';  // Agregamos el car�cter nulo al final
	}
	//for (int l = 1; l < 100; l++)
	//{
		/*for (i = 0; i < longitud; i++)
		{
			ayuda[i]=szPalabraLeida[i + 1];
		}


		strcpy_s(clona[1][TAMTOKEN],TAMTOKEN, ayuda);
	//}*/



	// Transponer pares de caracteres y almacenar las nuevas sugerencias
	for (int i = 0; i < longitud - 1; i++) {
		// Copiar la palabra original
		strcpy_s(szPalabraLeida, TAMTOKEN, szPalabrasSugeridas[0]);

		// Intercambiar caracteres en posici�n i e i+1 sin usar void swap
		szPalabraLeida[i] ^= szPalabraLeida[i + 1];
		szPalabraLeida[i + 1] ^= szPalabraLeida[i];
		szPalabraLeida[i] ^= szPalabraLeida[i + 1];

		// Almacenar la palabra modificada en el arreglo de palabras sugeridas
		strcpy_s(szPalabrasSugeridas[longitud + i + 1], TAMTOKEN, szPalabraLeida);
	}


	printf("Palabras Sugeridas:\n");
	for (int i = 0; i <= longitud + longitud - 1; i++) {
		printf("%s\n", szPalabrasSugeridas[i]);

		strcpy_s(szPalabrasSugeridas[0], TAMTOKEN, szPalabraLeida); //lo que sea que se capture, es sugerencia
		iNumSugeridas = 1;							//Una sola palabra sugerida
	}
}
