#include <stdlib.h>

#include "args_parser.h"
#include "cache.h"
#include "constantsTP2.h"
#include "file_reader.h"
#include "processor.h"

int main(int argc, char** argv) {
  file_reader_t file_reader;
  if (get_arguments(argc, argv, &file_reader, &cachesize, &ways, &blocksize) !=
      NO_ERROR) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

void process_and_output(char* line, size_t line_len, void* extra) {
  processor_t* extra = (processor_t*)extra;
  process(line, line_len);
}