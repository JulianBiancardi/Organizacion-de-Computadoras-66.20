#ifndef PROCESSOR_H
#define PROCESSOR_H

typedef struct processor {
  int FIXME_TODO_DELETE;
} processor_t;

void process(char* line, size_t line_len);

void init();
void read(char* address);
void write(char* address);
void missrate();

#endif
