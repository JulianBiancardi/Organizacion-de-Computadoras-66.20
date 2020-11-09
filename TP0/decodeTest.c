#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "./src/main/base64.h"
#define TESTS 3
#define NEGATIVE_TESTS 4

int testDecode(char* input, char* expectedOutput);
int testErrorCases(char* input);

int main() {
  printf("Start Testing Decode\n");
  char* dataMap[TESTS][2] = {{"TWFu", "Man"}, {"ZQ==", "e"}, {"ZS4=", "e."}};
  char* errorCases[NEGATIVE_TESTS] = {"ab", "!|°'", "ABC", "[¿.)"};
  int success = 1;
  for (int i = 0; i < TESTS; i++)
    success = success && testDecode(dataMap[i][0], dataMap[i][1]);
  for (int i = 0; i < NEGATIVE_TESTS; i++)
    success = success && testErrorCases(errorCases[i]);
  if (success)
    printf("Tests: OK\n");
  else
    printf("Tests: ERROR\n");
}

int testDecode(char* input, char* expectedOutput) {
  char actualOutput[3] = "";
  int decodeResult = (int)decode64(input, actualOutput);
  int expectedEqual = strcmp(actualOutput, expectedOutput);
  printf(
      "Input text was: '%s'."
      " Expected text is: '%s'."
      " Actual text result: '%s'\n",
      input, expectedOutput, actualOutput);
  return (decodeResult != -1) && (!expectedEqual);
}

int testErrorCases(char* input) {
  char buffer[3] = "";
  int decodeResult = (int)decode64(input, buffer);
  printf("Input text was: '%s'. Expected result is -1. Actual result is '%d'\n",
         input, decodeResult);
  return decodeResult == -1;
}