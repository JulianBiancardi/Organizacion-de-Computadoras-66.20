#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#include "args_parser.h"
#include "constantsTP1.h"
#include "euclides.h"

#define ARGV_M 4
#define ARGV_N 5

int main(int argc, char** argv) {
  FILE* output;
  char output_file[FILE_NAME_MAX_LEN];
  unsigned int x;
  unsigned int y;
  bool mcm_bool;
  bool mcd_bool;
  if (get_arguments(argc, argv, &output, &x, &y, &mcm_bool, &mcd_bool) !=
      NO_ERROR) {
    return 0;
  }

  if (mcd_bool) {
    unsigned int result = mcd(x, y);
    fprintf(output, "%u\n", result);
  }
  if (mcm_bool) {
    unsigned int result = mcm(x, y);
    fprintf(output, "%u\n", result);
  }
  return NO_ERROR;
}