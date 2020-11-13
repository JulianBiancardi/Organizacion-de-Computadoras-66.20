#include "mcd_tests.h"

#include <stdio.h>

#include "tests_setup.h"

#define NO_ERROR 0
#define ERROR -1

extern unsigned int mcd(unsigned int, unsigned int);

int static x5_y10_test();
int static x256_y192_test();
int static x1111_y1294_test();
int static x12_y20_test();
int static x205_y87_test();

void mcd_tests() {
  begin_tests("MCD TESTS");
  print_test("MCD entre 5 y 10 devuelve 5", x5_y10_test, NO_ERROR);
  print_test("MCD entre 256 y 192 devuelve ", x256_y192_test, NO_ERROR);
  print_test("MCD entre 1111 y 1294 devuelve ", x1111_y1294_test, NO_ERROR);
  print_test("MCD entre 12 y 20 devuelve ", x12_y20_test, NO_ERROR);
  print_test("MCD entre 205 y 87 devuelve ", x205_y87_test, NO_ERROR);
  end_tests();
}

int static x5_y10_test() {
  unsigned int x = 5;
  unsigned int y = 10;
  unsigned int result = mcd(x, y);
  if (result == 5) {
    return NO_ERROR;
  }
  return ERROR;
}

int static x256_y192_test() {
  unsigned int x = 256;
  unsigned int y = 192;
  unsigned int result = mcd(x, y);
  if (result == 64) {
    return NO_ERROR;
  }
  return ERROR;
}

int static x1111_y1294_test() {
  unsigned int x = 1111;
  unsigned int y = 1294;
  unsigned int result = mcd(x, y);
  if (result == 1) {
    return NO_ERROR;
  }
  return ERROR;
}

int static x12_y20_test() {
  unsigned int x = 12;
  unsigned int y = 20;
  unsigned int result = mcd(x, y);
  if (result == 4) {
    return NO_ERROR;
  }
  return ERROR;
}

int static x205_y87_test() {
  unsigned int x = 205;
  unsigned int y = 87;
  unsigned int result = mcd(x, y);
  if (result == 1) {
    return NO_ERROR;
  }
  return ERROR;
}