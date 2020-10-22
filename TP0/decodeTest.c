#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "base64.h"
#define TESTS 3

int testDecode(char* input, char* expectedOutput);

int main() {
	printf("Start Testing Decode\n");
	char* dataMap[TESTS][2] = {{"TWFu","Man"},
		{"ZQ==","e"},
		{"ZS4=","e."}};
	int success = 1;
	for (int i = 0; i < TESTS; i++)
		success = success & testDecode(dataMap[i][0], dataMap[i][1]);
	if (success)
		printf("Tests: OK\n");
	else
		printf("Tests: ERROR\n");
}


int testDecode(char* input, char* expectedOutput) {
  char actualOutput[3] = "";
  int decodeResult = (int) decode64(input, actualOutput);
  int expectedEqual = strcmp(actualOutput, expectedOutput);
  printf("Input text was: '%s'."
      " Expected text is: '%s'."
      " Actual text result: '%s'\n",
      input, expectedOutput, actualOutput);
  return (decodeResult != -1) && (!expectedEqual);
}
