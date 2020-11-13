#include "mcm_tests.h"

#include <stdio.h>

#include "tests_setup.h"

#define NO_ERROR 0
#define ERROR -1

extern unsigned int mcm(unsigned int, unsigned int);

int static x5_y10_test();
int static x256_y192_test();
int static x1111_y1294_test();
int static x12_y20_test();
int static x205_y87_test();

void mcm_tests() {
  begin_tests("MCM TESTS");
  print_test("MCM entre 5 y 10 devuelve 10", x5_y10_test, NO_ERROR);
  print_test("MCM entre 256 y 192 devuelve ", x256_y192_test, NO_ERROR);
  print_test("MCM entre 1111 y 1294 devuelve ", x1111_y1294_test, NO_ERROR);
  print_test("MCM entre 12 y 20 devuelve ", x12_y20_test, NO_ERROR);
  print_test("MCM entre 205 y 87 devuelve ", x205_y87_test, NO_ERROR);
  end_tests();
}

int static x5_y10_test() {
  unsigned int x = 5;
  unsigned int y = 10;
  unsigned int result = mcm(x, y);
  if (result == 10) {
    return NO_ERROR;
  }
  return ERROR;
}

int static x256_y192_test() {
  unsigned int x = 256;
  unsigned int y = 192;
  unsigned int result = mcm(x, y);
  if (result == 768) {
    return NO_ERROR;
  }
  return ERROR;
}

int static x1111_y1294_test() {
  unsigned int x = 1111;
  unsigned int y = 1294;
  unsigned int result = mcm(x, y);
  if (result == 1437634) {
    return NO_ERROR;
  }
  return ERROR;
}

int static x12_y20_test() {
  unsigned int x = 12;
  unsigned int y = 20;
  unsigned int result = mcm(x, y);
  if (result == 60) {
    return NO_ERROR;
  }
  return ERROR;
}

int static x205_y87_test() {
  unsigned int x = 205;
  unsigned int y = 87;
  unsigned int result = mcm(x, y);
  if (result == 17835) {
    return NO_ERROR;
  }
  return ERROR;
}