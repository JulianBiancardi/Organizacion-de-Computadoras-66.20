#ifndef FILE_READER_H
#define FILE_READER_H

#include <stdio.h>

typedef void (*callback_t)(char* line, size_t line_len, void* extra);

typedef struct file_reader {
  FILE* file;
} file_reader_t;

int file_reader_init(file_reader_t* self);

int file_reader_open(file_reader_t* self, char* file_name);

void file_reader_process(file_reader_t* self, callback_t callback, void* extra);

void file_reader_destroy(file_reader_t* self);

#endif