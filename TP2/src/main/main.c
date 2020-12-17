#include <stdlib.h>

#include "args_parser.h"
#include "cache.h"
#include "constantsTP2.h"
#include "file_reader.h"
#include "file_writer.h"
#include "memory.h"
#include "processor.h"

int main(int argc, char** argv) {
  file_reader_t file_reader;
  file_writer_t file_writer;
  file_reader_init(&file_reader);
  file_writer_init(&file_writer);

  if (get_arguments(argc, argv, &file_reader, &file_writer, &cachesize, &ways,
                    &blocksize) != NO_ERROR) {
    file_writer_destroy(&file_writer);
    file_reader_destroy(&file_reader);
    return EXIT_FAILURE;
  }

  cache_init();
  memory_init();

  file_reader_process(&file_reader, (callback_t)process_and_output,
                      &file_writer);

  cache_uninit();
  memory_uninit();

  file_writer_destroy(&file_writer);
  file_reader_destroy(&file_reader);
  return EXIT_SUCCESS;
}