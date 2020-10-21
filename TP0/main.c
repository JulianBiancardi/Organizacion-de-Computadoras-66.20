#include <stdbool.h>
#include <stddef.h>

#include "args_parser.h"
#include "constants.h"
#include "file_reader.h"
#include "file_writer.h"

int static encode_and_output(char* source, size_t source_len, void* extra);
int static decode_and_output(char* source, size_t source_len, void* extra);

int main(int argc, char** argv) {
  char input_file[FILE_NAME_MAX_LEN] = "stdin";
  char output_file[FILE_NAME_MAX_LEN] = "stdout";
  bool decode;
  get_arguments(argc, argv, input_file, output_file, &decode);

  file_reader_t file_reader;
  file_reader_init(&file_reader, input_file);

  file_writer_t file_writer;
  file_writer_init(&file_writer, output_file);

  int result;
  if (decode == true) {
    result = file_reader_process(&file_reader, decode_and_output, &file_writer);
  } else {
    result = file_reader_process(&file_reader, encode_and_output, &file_writer);
  }

  file_writer_destroy(&file_writer);
  file_reader_destroy(&file_reader);
  return NO_ERROR;
}

#include "base64.h"

int static min(int a, int b) {
  return a < b ? a : b;
}

int encode_and_output(char* source, size_t source_len, void* extra) {
  file_writer_t* file_writer = (file_writer_t*)extra;
  char encoded_text[ENCODED_LEN];

  int ptr = 0;
  for (ptr; ptr < source_len; ptr += 3) {
    // Move the head of the pointer, encode up to 3 bytes
    if (encode64(source+ptr, min(source_len - ptr, DECODED_LEN), encoded_text) == ERROR) {
      return ERROR;
    }
    file_writer_write(file_writer, encoded_text, ENCODED_LEN);
  }

  return NO_ERROR;
}

int decode_and_output(char* source, size_t source_len, void* extra) {
  file_writer_t *file_writer = (file_writer_t*)extra;
  char decoded_text[DECODED_LEN];

  int ptr = 0;
  for (ptr; ptr < source_len; ptr += 3) {
    // Move the head of the pointer, decode 4 bytes
    if (decode64(source+ptr, decoded_text) == ERROR) {
      return ERROR;
    }
    file_writer_write(file_writer, decoded_text, DECODED_LEN);
  }

  return NO_ERROR;
}