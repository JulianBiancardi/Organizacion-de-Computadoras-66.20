#ifndef FILE_WRITER_H
#define FILE_WRITER_H

#include <stdio.h>

typedef struct file_writer {
  FILE* file;
} file_writer_t;

/* Given a file_reader_t pointer and a file name, initialize the file_reader.
 * Returns 0 on success, -1 otherwise
 */
int file_writer_init(file_writer_t* self);

/* Receives a file_name and opens it. */
int file_writer_open(file_writer_t* self, char* file_name);

/* Writes into a file given a stream and a stream_len.
 * Returns the amount of bytes written.
 */
size_t file_writer_write(file_writer_t* self, char* stream, size_t stream_len);

/* Destroys a file_writer_t */
void file_writer_destroy(file_writer_t* self);

#endif