#ifndef FILE_READER_H
#define FILE_READER_H

#include <stdio.h>

typedef void (*callback_t)(char* line, size_t line_len, void* extra);

typedef struct file_reader {
  FILE* file;
} file_reader_t;

/* Initialize the file_writer, setting it by default to write to stdin.
 * Returns 0 on success, -1 otherwise.
 */
int file_reader_init(file_reader_t* self);

/* Receives a file_name and opens it. */
int file_reader_open(file_reader_t* self, char* file_name);

/* Reads the whole file line by line. Calls the callback for each line, passing
 * the extra.
 */
void file_reader_process(file_reader_t* self, callback_t callback, void* extra);

/* Destroys the file_reader_t */
void file_reader_destroy(file_reader_t* self);

#endif