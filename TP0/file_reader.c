#include "file_reader.h"

#include <stdio.h>
#include <string.h>

#include "constants.h"

// Must be a multiple of both 3 and 4 to avoid mistakes during translation
#define BUFFER_LEN 12 

int file_reader_init(file_reader_t* self, char* file_name) {
  if (strcmp(file_name, "stdin") == 0) {
    self->file = stdin;
  } else {
    self->file = fopen(file_name, "r");
  }
  return NO_ERROR;
}

int file_reader_process(file_reader_t* self, file_reader_callback_t callback,
                        void* context) {
  char buffer[BUFFER_LEN];
  while (!feof(self->file)) {
    size_t chars_read = fread(buffer, sizeof(char), BUFFER_LEN, self->file);
    if (callback(buffer, chars_read, context) == ERROR) {
      return ERROR;
    }
  }
  return NO_ERROR;
}

void file_reader_destroy(file_reader_t* self) {
  if (self->file != stdin) {
    fclose(self->file);
  }
}