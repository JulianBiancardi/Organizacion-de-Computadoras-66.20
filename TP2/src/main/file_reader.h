#include <stdio.h>

typedef struct file_reader {
  FILE* file;
} file_reader_t;

int file_reader_init(file_reader_t* file_reader, char* file_name);