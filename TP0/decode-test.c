#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include "decode.h"

void testDecode(char* input, char* expectedOutput);

int main(){
	printf("Testing");
	testDecode("TWFu", "Man");
	testDecode("QZ==", "e");
}

void testDecode(char* input, char* expectedOutput){
	char actualOutput[3];
	int sucess = decode(input, actualOutput);
	printf("Encode text was: '%s'. Expected decode is: '%s'. Actual decode result: '%s'\n",input, expectedOutput, actualOutput);
	//assert(actualOutput == expectedOutput);
	assert(sucess == 0);
}
