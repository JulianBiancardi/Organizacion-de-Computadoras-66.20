#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "base64.h"

int testDecode(char* input, char* expectedOutput);

int main() {
  printf("Start Testing Decode\n");
  int success = testDecode("RW4g", "Man");
  success = success & testDecode("dW4g", "e");
  success = success & testDecode("ZS4=", "e.");
  if (success)
    printf("Tests: OK\n");
  else
    printf("Tests: ERROR\n");
}

int testDecode(char* input, char* expectedOutput) {
  char actualOutput[3] = "";
  int decodeResult = decode64(input, actualOutput);
  int expectedEqual = strcmp(actualOutput, expectedOutput);
  printf(
      "Encode text was: '%s'. Expected decode is: '%s'. Actual decode result: "
      "'%s'\n",
      input, expectedOutput, actualOutput);
  return (!decodeResult) & (!expectedEqual);
}
