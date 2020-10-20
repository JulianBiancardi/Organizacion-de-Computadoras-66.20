#include <stdio.h>
#include <stdint.h>
#include "decode.h"
#define ERROR -1
#define MASK 0xFF

static long decodeLetterAndShift(char letter, int shiftValue);
static int decodeValueLetter(char letter);

int decode(char* source, char* buffer){
	long phrase = 0;
	// Decode letter by letter and shift. Then add to the phrase.
	for (int position = 0; position < 4; position ++){
		long decodeValue = decodeLetterAndShift(source[position], 3 - position);
		if (decodeValue == ERROR)
			return ERROR;
		phrase = phrase + decodeValue;
	}
	// Generate letter by letter from the phrase
	for (int position = 0; position < 3; position ++){
		long decodeLetter = phrase >> (2 - position) * 8 & MASK;
		buffer[position] = decodeLetter;
	}
	return 0;
}

static long decodeLetterAndShift(char letter, int shiftValue){
	if(letter == '=')
		return 0;
	int decodedLetter = decodeValueLetter(letter);
	if (decodedLetter == ERROR){
		printf("Error decoding letter: '%c'\n",letter);
		return ERROR;
	}
	return (long) decodedLetter << 6 * shiftValue;
}
	
static int decodeValueLetter(char letter){
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

