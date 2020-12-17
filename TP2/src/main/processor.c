#include "processor.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cache.h"

// TODO define function properly and choose better name
void static error();

void process(char* line, size_t line_len) {
  char* ptr = strchr(line, ' ');
  int chars_to_cmp = line_len;
  if (ptr != NULL) {
    chars_to_cmp = ptr - line;
  }

  if (strncmp(line, "init", chars_to_cmp) == 0) {
    init();
  } else if (strncmp(line, "MR", chars_to_cmp) == 0) {
    missrate();
  } else if (strncmp(line, "R", chars_to_cmp) == 0) {
    read(ptr);
  } else if (strncmp(line, "W", chars_to_cmp) == 0) {
    write(ptr);
  } else {
    error();
  }
}

void init() {
  cache_init();
  memory_init();
}

void read(char* instr) {
  int address = (int)strtol(instr, (char**)NULL, 10);
  unsigned char byte = cache_read_byte(address);
}
void write(char* instr) {
  char* next;
  int address = (int)strtol(instr, &next, 10);
  // Skip comma and space
  unsigned int value = (unsigned int)strtoul(next + 2, (char**)NULL, 10);
  cache_write_byte(address, value);
}

void missrate() { cache_get_miss_rate(NULL); }

void error() {}