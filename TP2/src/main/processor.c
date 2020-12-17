#include "processor.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cache.h"
#include "memory.h"

#define HIT "hit\n"
#define MISS "miss\n"

// TODO define function properly and choose better name
void static error();

void process_and_output(char* instr, size_t instr_len,
                        file_writer_t* file_writer) {
  char* ptr = strchr(instr, ' ');
  int chars_to_cmp = instr_len - 1;
  if (ptr != NULL) {
    chars_to_cmp = ptr - instr;
  }

  if (strncmp(instr, "init", chars_to_cmp) == 0) {
    init();
  } else if (strncmp(instr, "MR", chars_to_cmp) == 0) {
    missrate(file_writer);
  } else if (strncmp(instr, "R", chars_to_cmp) == 0) {
    read(ptr, file_writer);
  } else if (strncmp(instr, "W", chars_to_cmp) == 0) {
    write(ptr, file_writer);
  } else {
    error(instr, instr_len, file_writer);
  }
}

void init() {
  cache_init();
  memory_init();
}

void read(char* instr, file_writer_t* file_writer) {
  int address = (int)strtol(instr, (char**)NULL, 10);
  unsigned char byte = cache_read_byte(address);
  char* message = cache_hit() ? HIT : MISS;
  file_writer_write(file_writer, message, strlen(message));
}
void write(char* instr, file_writer_t* file_writer) {
  char* next;
  int address = (int)strtol(instr, &next, 10);
  // Skip comma and space
  unsigned int value = (unsigned int)strtoul(next + 2, (char**)NULL, 10);
  cache_write_byte(address, value);

  char* message = cache_hit() ? HIT : MISS;
  file_writer_write(file_writer, message, strlen(message));
}

void missrate(file_writer_t* file_writer) {
  file_writer_print(file_writer, "MISS-RATE: %.1f %%\n", cache_get_miss_rate());
}

void error(char* instr, size_t instr_len, file_writer_t* file_writer) {
  file_writer_print(file_writer, "Invalid Instruction: %s\n", instr);
}