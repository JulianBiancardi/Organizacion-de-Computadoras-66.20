#include "memory.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "constantsTP2.h"

#define MAIN_MEMORY_SIZE 65536

memory_t memory;

int memory_init() {
  memory.data = malloc(MAIN_MEMORY_SIZE);
  if (memory.data == NULL) {
    return ERROR;
  }

  memset(memory.data, 0, MAIN_MEMORY_SIZE);
  return NO_ERROR;
}

void memory_uninit() {
  if (memory.data != NULL) {
    free(memory.data);
  }
}