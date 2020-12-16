#include "cache.h"

#include <math.h>
#include <stdlib.h>

#define KB 1024

// TODO MOVE THIS
static unsigned int ways = 4;
static unsigned int cachesize = 4;
static unsigned int blocksize = 256;

void cache_init(cache_t* self) {
  if (self == NULL) {
    // TODO RETURN AN ERROR
    return;
  }
  self->hits = 0;
  self->missses = 0;

  // Number of sets in the cache
  int number_sets = (cachesize * KB) / (blocksize * ways);
  self->sets = (set_t*)malloc(sizeof(set_t) * number_sets);

  // TODO VERIFY THE NULL POINTER
  for (size_t i = 0; i < number_sets; i++) {
    self->sets[i].blocks = (block_t*)malloc(sizeof(block_t) * ways);
    for (size_t j = 0; j < ways; j++) {
      self->sets[i].blocks[j].data = calloc(blocksize, sizeof(unsigned char));
      self->sets[i].blocks[j].valid = false;
      self->sets[i].blocks[j].dirty = false;
    }
  }
}

unsigned int cache_find_set(cache_t* self, int address) {
  /* ADDRES = LABEL + SET + OFFSET */
  /* 000000  00  00000000  */
  /*
  Se asume que el espacio de direcciones es de 16 bits
  */
  int number_sets = (cachesize * KB) / (blocksize * ways);
  int bit_offset = log2(256);
  int bit_set = log2(4);
  int bit_label = 16 - (bit_set + bit_offset);  // TODO 16 IS CONSTANT

  unsigned int set =
      ((address << bit_label) >> (bit_offset + bit_label)) & bit_set;

  return set;
}

unsigned int cache_find_lru(cache_t* self, int setnum);

unsigned int cache_is_dirty(cache_t* self, int way, int setnum) {
  return self->sets[setnum].blocks[way].dirty;
}

void cache_read_block(cache_t* self, int blocknum);

void cache_write_block(cache_t* self, int way, int setnum) {
  int number_sets = (cachesize * KB) / (blocksize * ways);
  if (way > ways || setnum > number_sets) {
    return;
  }
  // First obtain the data
  unsigned char* data = self->sets[setnum].blocks[way].data;
}

unsigned char cache_read_byte(cache_t* self, int address);

void cache_write_byte(cache_t* self, int address, unsigned char value);

int cache_get_miss_rate(cache_t* self) {
  if ((self->missses + self->missses) == 0) {
    return 0;
  }
  return (self->missses / (self->missses + self->hits));
}

void cache_uninit(cache_t* self);