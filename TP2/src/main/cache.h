#ifndef CACHE_H
#define CACHE_H

#include <stdbool.h>
#include <stdio.h>

typedef struct cache {
  int miss_rate;
} cache_t;

void cache_init(cache_t* self, int ways, int cachesize, int blocksize);

unsigned int cache_find_set(cache_t* self, int address);

unsigned int cache_find_lru(cache_t* self, int setnum);

unsigned int cache_is_dirty(cache_t* self, int way, int setnum);

void cache_read_block(cache_t* self, int blocknum);

void cache_write_block(cache_t* self, int way, int setnum);

char cache_read_byte(cache_t* self, int address);

void cache_write_byte(cache_t* self, int address, char value);

int cache_get_miss_rate(cache_t* self);

void cache_uninit(cache_t* self);

#endif /* CACHE_H */