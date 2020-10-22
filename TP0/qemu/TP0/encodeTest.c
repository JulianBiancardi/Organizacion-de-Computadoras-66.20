#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "base64.h"

void testEncode(char* input, char* expectedOutput, size_t source_len);

int main() {
  printf("Testing");
  testEncode("Man", "TWFu", 3);
  testEncode("e.", "ZS4=", 2);
  testEncode("e", "ZQ==", 1);
  testEncode("su", "c3U=", 2);
  testEncode("s", "cw==", 1);
}

void testEncode(char* input, char* expectedOutput, size_t source_len) {
  char actualOutput[4];
  int sucess = encode64(input, source_len, actualOutput);
  printf(
      "Encode text was: '%s'. Expected encode is: '%s'. Actual decode result: "
      "'%s'\n",
      input, expectedOutput, actualOutput);
  // assert(actualOutput == expectedOutput);
}