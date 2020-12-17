#include "memory.h"

#include <stddef.h>

#include "constantsTP2.h"

void memory_init() {
  memory.data = malloc(MAIN_MEMORY_SIZE);
  if (malloc == NULL) {
    return ERROR;
  }

  memset(memory.data, 0, MAIN_MEMORY_SIZE);
  return NO_ERROR;
}