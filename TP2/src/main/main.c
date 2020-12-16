#include <stdlib.h>

#include "args_parser.h"
#include "cache.h"
#include "constantsTP2.h"

extern unsigned int mcd(unsigned int, unsigned int);
extern unsigned int mcm(unsigned int, unsigned int);

int main(int argc, char** argv) {
  FILE* output;
  unsigned int x, y;
  bool mcm_bool, mcd_bool;
  if (get_arguments(argc, argv, &cachesize, &ways, &blocksize) != NO_ERROR) {
    return EXIT_FAILURE;
  }

  if (mcd_bool) {
    unsigned int result = mcd(x, y);
    fprintf(output, "MCD: %u\n", result);
  }

  if (mcm_bool) {
    unsigned int result = mcm(x, y);
    fprintf(output, "mcm: %u\n", result);
  }
  return EXIT_SUCCESS;
}