#ifndef FILE_READER_H
#define FILE_READER_H

#include <stdio.h>

typedef int (*file_reader_callback_t)(char* buffer, size_t* buffer_len,
                                      void* context);

typedef struct file_reader {
  FILE* file;
} file_reader_t;

/* Given a file_reader_t pointer and a file name, initialize the file_reader.
 * Returns 0 on success, -1 otherwise
 */
int file_reader_init(file_reader_t* self, char* file_name);

int file_reader_process(file_reader_t* self, file_reader_callback_t callback,
                        void* context);

/* Destroys a file_reader_t */
void file_reader_destroy(file_reader_t* self);

#endif