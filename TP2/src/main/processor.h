#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <stddef.h>

#include "file_writer.h"

void process_and_output(char* line, size_t line_len,
                        file_writer_t* file_writer);

void init();
void read(char* address);
void write(char* address);
void missrate();

#endif
