#ifndef MEMORY_H
#define MEMORY_H

#include <stdbool.h>

typedef struct memory {
  unsigned char* data;
} memory_t;

extern bool memory_initialized;
extern memory_t memory;

/* Initializes the memory */
int memory_init();

/* Destroys the memory, releasing all of its resources. */
void memory_uninit();

#endif