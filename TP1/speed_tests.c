
#include "speed_tests.h"

#include <time.h>

#include "tests_setup.h"

int static single_mcm_test();
int static single_mcd_test();
int static mcm_64_test();
int static mcd_64_test();
int static mcm_1024_test();
int static mcd_1024_test();
int static mcm_65536_test();
int static mcd_65536_test();
int static mcm_4194304_test();
int static mcd_4194304_test();

void speed_tests() {
  begin_tests("SPEED_TESTS");

  benchmark_test("1 MCM average time", single_mcm_test);
  benchmark_test("1 MCD average time", single_mcd_test);
  benchmark_test("64 MCM time", mcm_64_test);
  benchmark_test("64 MCD time", mcd_64_test);
  benchmark_test("1024 MCM time", mcm_1024_test);
  benchmark_test("1024 MCD time", mcd_1024_test);
  benchmark_test("65536 MCM time", mcd_65536_test);
  benchmark_test("65536 MCD time", mcd_65536_test);
  benchmark_test("4194304 MCD time", mcd_4194304_test);
  benchmark_test("4194304 MCD time", mcd_4194304_test);

  for (int i = 0; i < 2, 147, 483, 647; i += 50) {
  }

  end_tests();
}

int static single_mcm_test() {
  clock_t start = clock();
  for (int i = 0; i < 1048575; i++) {
  }
}
int static single_mcd_test();
int static mcm_64_test();
int static mcd_64_test();
int static mcm_1024_test();
int static mcd_1024_test();
int static mcm_65536_test();
int static mcd_65536_test();
int static mcm_4194304_test();
int static mcd_4194304_test();