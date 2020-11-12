#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#include "args_parser.h"
#include "constantsTP1.h"

extern unsigned int mcd(unsigned int, unsigned int);
extern unsigned int mcm(unsigned int, unsigned int);

int main(int argc, char** argv) {
  FILE* output;
  unsigned int x, y;
  bool mcm_bool, mcd_bool;
  if (get_arguments(argc, argv, &output, &x, &y, &mcm_bool, &mcd_bool) !=
      NO_ERROR) {
    return 0;
  }

  if (mcd_bool) {
    unsigned int result = mcd(x, y);
    fprintf(output, "MCD: %u\n", result);
  }
  if (mcm_bool) {
    unsigned int result = mcm(x, y);
    fprintf(output, "mcm: %u\n", result);
  }
  return NO_ERROR;
}