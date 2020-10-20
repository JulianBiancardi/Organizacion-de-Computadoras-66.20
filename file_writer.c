#include "file_writer.h"

#include "constants.h"

int file_writer_init(file_writer_t* self, char* file_name) {
  if (file_name == NULL) {
    self->file = stdout;
  } else {
    self->file = fopen(file_name, 'w');
  }
  return NO_ERROR;
}

void file_writer_destroy(file_writer_t* self) {
  if (self->file != stdout) {
    fclose(self->file);
  }
}