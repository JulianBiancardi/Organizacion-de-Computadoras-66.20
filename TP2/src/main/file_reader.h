#ifndef FILE_READER_H
#define FILE_READER_H

#include <stdio.h>

typedef void (*callback_t)(char* line, size_t line_len, void* extra);

typedef struct file_reader {
  FILE* file;
} file_reader_t;

int file_reader_init(file_reader_t* file_reader, char* file_name);

void file_reader_process(file_reader_t* file_reader, callback_t callback,
                         void* extra);

void file_reader_uninit(file_reader_t* file_reader);

#endif