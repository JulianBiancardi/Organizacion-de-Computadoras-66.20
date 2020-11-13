#include "tests_setup.h"

#include <stdio.h>
#include <string.h>

#define ERROR_RED "\x1b[31m"
#define CORRECT_GREEN "\x1b[32m"
#define RESET_FONT "\x1b[0m"
#define BOLD_FONT "\x1b[1m"

#define DIV_LEN 80

void print_test(char* message, int (*func)(), int expected_value) {
  int test_result = func();
  char message_result[100];
  if (test_result != expected_value) {
    sprintf(message_result,
            "%s: %sERROR%s\n\tExpected value: %d\n\tInstead got: %d\n", message,
            ERROR_RED, RESET_FONT, expected_value, test_result);
  } else {
    sprintf(message_result, "%s: %sOK%s\n", message, CORRECT_GREEN, RESET_FONT);
  }
  printf(message_result);
}

void benchmark_test(char* message, unsigned int sample_size, double (*func)()) {
  printf("%s%u%s %s: %s%f s%s\n", BOLD_FONT, sample_size, RESET_FONT, message,
         BOLD_FONT, func(), RESET_FONT);
}

void begin_tests(char* module_tested) {
  size_t module_len = strlen(module_tested);
  for (int i = 0; i < DIV_LEN; i++) {
    printf("=");
  }
  printf("\n");

  for (size_t i = 1; i < (DIV_LEN - module_len) / 2; i++) {
    printf(" ");
  }
  printf("%s%s%s", BOLD_FONT, module_tested, RESET_FONT);
  for (size_t i = 1; i < (DIV_LEN - module_len) / 2; i++) {
    printf(" ");
  }
  printf("\n\n");
}

void end_tests() { printf("\n"); }