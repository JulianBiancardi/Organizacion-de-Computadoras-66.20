#include <stdbool.h>

#include "args_parser.h"
#include "constants.h"
#include "file_reader.h"
#include "file_writer.h"

int main(int argc, char** argv) {
  char input_file[FILE_NAME_MAX_LEN] = NULL;
  char output_file[FILE_NAME_MAX_LEN] = NULL;
  bool decode;
  get_arguments(argc, argv, input_file, output_file, &decode);

  file_reader_t file_reader;
  file_reader_init(&file_reader, input_file);

  file_writer_t file_writer;
  file_writer_init(&file_writer, output_file);

  if (decode == true) {
    file_reader_process(&file_reader, encode_and_output, &file_writer);
  } else {
    file_reader_process(&file_reader, decode_and_output, &file_writer);
  }

  file_writer_destroy(&file_writer);
  file_reader_destroy(&file_reader);
  return NO_ERROR;
}

int encode_and_output(char* buffer, size_t buffer_len, void* extra) {}

int decode_and_output(char* buffer, size_t buffer_len, void* extra) {}