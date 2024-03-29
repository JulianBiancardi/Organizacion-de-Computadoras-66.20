#define _POSIX_C_SOURCE 200809L

#include "file_reader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "constantsTP2.h"

#define BUF_SIZE 64

int file_reader_init(file_reader_t* self) {
  self->file = stdin;
  return NO_ERROR;
}

int file_reader_open(file_reader_t* self, char* file_name) {
  if (self->file != stdin) {
    fclose(self->file);
  }

  if (strcmp(file_name, "stdin") == 0) {
    self->file = stdin;
  } else {
    if (access(file_name, F_OK) != 0) {
      return ERROR;
    }
    self->file = fopen(file_name, "r");
  }
  return NO_ERROR;
}

void file_reader_process(file_reader_t* self, callback_t callback,
                         void* extra) {
  char* line = NULL;
  size_t line_len = 0;

  while (!feof(self->file)) {
    ssize_t chars_read = getline(&line, &line_len, self->file);
    if (chars_read < 0) {
      break;
    }
    callback(line, chars_read, extra);
  }

  free(line);
}

void file_reader_destroy(file_reader_t* self) {
  if (self->file != stdin) {
    fclose(self->file);
  }
}