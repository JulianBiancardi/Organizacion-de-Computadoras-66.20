#ifndef MEMORY_H
#define MEMORY_H

#define MAIN_MEMORY_SIZE 65536

typedef struct memory {
  unsigned char* data;
} memory_t;

extern memory_t memory;

int memory_init();

#endif