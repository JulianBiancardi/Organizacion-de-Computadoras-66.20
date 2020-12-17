#ifndef FILE_WRITER_H
#define FILE_WRITER_H

#include <stdio.h>

typedef struct file_writer {
  FILE* file;
} file_writer_t;

/* Initialize the file_writer, setting it by default to write to stdout.
 * Returns 0 on success, -1 otherwise.
 */
int file_writer_init(file_writer_t* self);

/* Receives a file_name and opens it. */
int file_writer_open(file_writer_t* self, const char* file_name);

/* Writes into a file given a stream and a stream_len.
 * Returns the amount of bytes written.
 */
size_t file_writer_write(file_writer_t* self, const char* stream,
                         size_t stream_len);

/* Writes into a file given a formatted string */
size_t file_writer_print(file_writer_t* self, const char* format, ...);

/* Destroys the file_writer_t */
void file_writer_destroy(file_writer_t* self);

#endif