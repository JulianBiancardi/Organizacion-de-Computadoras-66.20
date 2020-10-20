#include <stdio.h>
#include <stdint.h>
#define RBUFFER 1024
#define ERROR -1
#define MASK 0xFF

int decode(char* inputFilePath, char* outputFilePath);
int decodeValueLetter(char letter);
long decodeLetterAndShift(char letter, int multiplier);

int main(){
	decode("input.txt", "output.txt");
}

int decode(char* inputFilePath, char* outputFilePath){
	FILE* inputFile = fopen(inputFilePath, "r");
	if (!inputFile){
		printf("No se pudo abrir el archivo codificado");
		return ERROR;
	}
	FILE* outputFile = fopen(outputFilePath, "w");
	if (!outputFile){
		printf("No se pudo abrir el archivo codificado");
		fclose(inputFile);
		return ERROR;
	}
	// Lectura del archivo. El codificado es una sola linea. 
	char data[RBUFFER];
	int readSuccess = fscanf(inputFile, "%[^\n]\n",data);
	if (!readSuccess){
		printf("Error reading file");
		fclose(inputFile);
		fclose(outputFile);
		return ERROR;
	}
	
	int position = 0;
	while(data[position] != EOF && data[position] !=  '\n'){
		/* Se toman 4 letras codificadas y se las ordena para armar
		el binario con el cual se debe decodificar */
		long first = decodeLetterAndShift(data[position], 3);
		long second = decodeLetterAndShift(data[position + 1], 2);
		long third = decodeLetterAndShift(data[position + 2], 1);
		long fourth = decodeLetterAndShift(data[position + 3], 0);
		if (first == ERROR || second == ERROR || third == ERROR || fourth == ERROR)
			return ERROR;
		// La frase binaria es el resultado de la suma de las 4 letras decodificadas.
		long binaryPhrase = first + second + third + fourth;
		// Ahora obtengo las 3 letras decodificadas. (Limpio con mascara binara de 8 bits en 1)
		first = binaryPhrase >> 2*8 & MASK;
		second = binaryPhrase >> 1*8 & MASK;
		third = binaryPhrase & MASK;
		// Guardo siempre y cuando el caracter no sea null.
		if(first)
			fputc((char) first, outputFile);
		if(second)
			fputc((char) second, outputFile);
		if(third)
			fputc((char) third, outputFile);
		position = position + 4;
		printf("Data in position (%d) is: %c\n",position, data[position]);
	};
	
	fclose(inputFile);
	fclose(outputFile);
	return 0;
}


long decodeLetterAndShift(char letter, int shiftValue){
	if(letter == '=')
		return 0;
	int decodedLetter = decodeValueLetter(letter);
	if (decodedLetter == ERROR){
		printf("Error decoding letter: '%c'\n",letter);
		return ERROR;
	}
	return (long) decodedLetter << 6 * shiftValue;
}
	

int decodeValueLetter(char letter){
	int intLetter = (int) letter;
	if (intLetter >= (int) 'A' && intLetter <= (int) 'Z')
		return intLetter - (int) 'A';
	if (intLetter >= (int) 'a' && intLetter <= (int) 'z')
		return intLetter - (int) 'a' + 26;
	if (intLetter >= (int) '0' && intLetter <= (int) '9')
		return intLetter - (int) '0' + 52;
	switch (letter){
		case '+': 	return 62;
		case '/':	return 63;
		default: 	return ERROR;
	}
}

