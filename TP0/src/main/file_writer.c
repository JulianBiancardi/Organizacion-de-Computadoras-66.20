#include "file_writer.h"

#include <string.h>
#include "constants.h"

int file_writer_init(file_writer_t* self, char* file_name) {
  if (strcmp(file_name, "stdout") == 0) {
    self->file = stdout;
  } else {
    self->file = fopen(file_name, "w");
  }
  return NO_ERROR;
}

size_t file_writer_write(file_writer_t* self, char* stream, size_t stream_len) {
  return fwrite(stream, 1, stream_len, self->file);
}

void file_writer_destroy(file_writer_t* self) {
  if (self->file != stdout) {
    fclose(self->file);
  }
}