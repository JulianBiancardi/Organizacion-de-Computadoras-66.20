#include "file_reader.h"

#include <stdio.h>

#include "constants.h"

#define BUFFER_LEN 64

int file_reader_init(file_reader_t* self, char* file_name) {
  if (file_name == NULL) {
    self->file = stdin;
  } else {
    self->file = fopen(file_name, 'r');
  }
  return NO_ERROR;
}

int file_reader_process(file_reader_t* self, file_reader_callback_t callback,
                        void* context) {
  char buffer[BUFFER_LEN];
  while (!feof(self->file)) {
    size_t chars_read = fread(buffer, 1, BUFFER_LEN, self->file);
    if (callback(buffer, chars_read, context) == ERROR) {
      return ERROR;
    }
  }
}

void file_reader_destroy(file_reader_t* self) {
  if (self->file != stdin) {
    fclose(self->file);
  }
}