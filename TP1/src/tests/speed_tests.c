
#include "speed_tests.h"

#include <stdlib.h>
#include <time.h>

#include "tests_setup.h"

double static mcm_time_test();
double static mcd_time_test();

extern unsigned int mcm(unsigned int, unsigned int);
extern unsigned int mcd(unsigned int, unsigned int);

#define SAMPLE_SIZE 1073741824  // 2 ^ 30 - 1

void speed_tests() {
  begin_tests("SPEED_TESTS");

  benchmark_test("Ejecuciones de MCM", SAMPLE_SIZE, mcm_time_test);
  benchmark_test("Ejecuciones de MCD", SAMPLE_SIZE, mcd_time_test);

  end_tests();
}

double static mcm_time_test() {
  unsigned int numbers[1024];
  for (int i = 0; i < 1024; i++) {
    numbers[i] = rand();
  }

  clock_t start = clock();
  for (int i = 0; i < SAMPLE_SIZE; i++) {
    unsigned int index = rand();
    index %= 1023;
    mcm(numbers[index], numbers[index]);
  }
  clock_t end = clock();

  return (double)(end - start) / CLOCKS_PER_SEC;
}

double static mcd_time_test() {
  unsigned int numbers[1024];
  for (int i = 0; i < 1024; i++) {
    numbers[i] = rand();
  }

  clock_t start = clock();
  for (int i = 0; i < SAMPLE_SIZE; i++) {  // 2^25 - 1
    unsigned int index = rand();
    index %= 1023;
    mcd(numbers[index], numbers[index]);
  }
  clock_t end = clock();

  return (double)(end - start) / CLOCKS_PER_SEC;
}