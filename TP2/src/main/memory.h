#ifndef MEMORY_H
#define MEMORY_H

typedef struct memory {
  unsigned char* data;
} memory_t;

extern memory_t memory;

int memory_init();

#endif