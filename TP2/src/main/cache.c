#include "cache.h"

#include <stdlib.h>

#define KB 1024

void cache_init(cache_t* self, int ways, int cachesize, int blocksize) {
  if (self == NULL) {
    // TODO RETURN AN ERROR
    return;
  }
  self->hits = 0;
  self->missses = 0;

  // Number of sets in the cache
  int number_sets = (cachesize * KB) / (blocksize * ways);
  self->sets = (set_t*)malloc(sizeof(set_t) * number_sets);

  for (size_t i = 0; i < number_sets; i++) {
    self->sets[i].blocks = (block_t*)malloc(sizeof(block_t) * ways);
    for (size_t j = 0; j < ways; j++) {
      self->sets[i].blocks[j].data = malloc(sizeof(unsigned char) * blocksize);
    }
  }
}

unsigned int cache_find_set(cache_t* self, int address);

unsigned int cache_find_lru(cache_t* self, int setnum);

unsigned int cache_is_dirty(cache_t* self, int way, int setnum);

void cache_read_block(cache_t* self, int blocknum);

void cache_write_block(cache_t* self, int way, int setnum);

char cache_read_byte(cache_t* self, int address);

void cache_write_byte(cache_t* self, int address, char value);

int cache_get_miss_rate(cache_t* self) {
  if ((self->missses + self->missses) == 0) {
    return 0;
  }
  return (self->missses / (self->missses + self->hits));
}

void cache_uninit(cache_t* self);