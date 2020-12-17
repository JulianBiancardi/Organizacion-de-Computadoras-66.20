#define _POSIX_C_SOURCE 200809L

#include "file_reader.h"

#define BUF_SIZE 64

int file_reader_init(file_reader_t* file_reader, char* file_name) {
  file_reader->file = fopen(file_name, "w+");
}

void file_reader_process(file_reader_t* file_reader, callback_t callback,
                         void* extra) {
  // Dynamic memory since getline might allocate according to documentation
  char line = malloc(sizeof(char) * BUF_SIZE);
  size_t line_len = BUF_SIZE;

  while (!feof(file_reader->file)) {
    size_t chars_read = getline(&line, &line_len, file_reader->file);
    callback(line, line_len, extra);
  }

  free(line);
}

void file_reader_uninit(file_reader_t* file_reader) {
  fclose(file_reader->file);
}