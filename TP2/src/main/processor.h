#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <stddef.h>

void process(char* line, size_t line_len);

void init();
void read(char* address);
void write(char* address);
void missrate();

#endif
