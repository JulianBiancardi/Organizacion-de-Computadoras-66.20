#include "file_writer.h"

#include <stdarg.h>
#include <string.h>
#include <sys/types.h>

#include "constantsTP2.h"

int file_writer_init(file_writer_t* self) {
  self->file = stdout;
  return NO_ERROR;
}

int file_writer_open(file_writer_t* self, const char* file_name) {
  if (self->file != stdout) {
    fclose(self->file);
  }

  if (strcmp(file_name, "stdout") == 0) {
    self->file = stdout;
  } else {
    self->file = fopen(file_name, "w");
  }

  return NO_ERROR;
}

size_t file_writer_write(file_writer_t* self, const char* stream,
                         size_t stream_len) {
  return fwrite(stream, 1, stream_len, self->file);
}

size_t file_writer_print(file_writer_t* self, const char* format, ...) {
  va_list args;
  va_start(args, format);
  size_t chars = vfprintf(self->file, format, args);
  va_end(args);
  return chars;
}

void file_writer_destroy(file_writer_t* self) {
  if (self->file != stdout) {
    fclose(self->file);
  }
}