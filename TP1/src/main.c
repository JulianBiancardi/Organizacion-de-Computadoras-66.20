#include <stdbool.h>
#include <stddef.h>
#include <unistd.h>

#include "args_parser.h"
#include "constantsTP1.h"
#include "file_writer.h"

#define ARGV_M 4
#define ARGV_N 5

int main(int argc, char** argv) {
  char output_file[FILE_NAME_MAX_LEN] = "stdout";
  bool divisor;
  unsigned int m = argv[ARGV_M];
  unsigned int n = argv[ARGV_N];
  if (m < RANGE_MIN || m > RANGE_MAX) {
    return ERROR;
  }
  if (n < RANGE_MIN || n > RANGE_MAX) {
    return ERROR;
  }
  get_arguments(argc, argv, output_file, &divisor);

  file_writer_t file_writer;
  file_writer_init(&file_writer, output_file);

  unsigned int result;
  if (divisor == true) {
    result = mcd(m, n);
  } else {
    result = mcm(m, n);
  }

  file_writer_write(&file_writer, result, );
  file_writer_destroy(&file_writer);

  return NO_ERROR;
}
