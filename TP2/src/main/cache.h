#ifndef CACHE_H
#define CACHE_H

#include <stdbool.h>
#include <stdio.h>

typedef struct block {
  unsigned int date;
  bool valid;
  bool dirty;
  unsigned char tag;
  unsigned char* data;
} block_t;

typedef struct set {
  block_t* blocks;
} set_t;

typedef struct cache {
  set_t* sets;
  unsigned int hits;
  unsigned int misses;
  bool last_satuts;
  unsigned int setsnum;
  unsigned int bits_tag;
  unsigned int bits_set;
  unsigned int bits_offset;
} cache_t;

extern unsigned int ways;
extern unsigned int cachesize;
extern unsigned int blocksize;
extern bool cache_initialized;
extern cache_t cache;

/* Initializes the cache */
int cache_init();

/* Receives an address and returns the set which maps to that address. */
unsigned int cache_find_set(int address);

/* Receives a set number and returns the number of the block least recently
 * used. */
unsigned int cache_find_lru(int setnum);

/* Receives a set number and a way and returns whether the block is dirty. */
unsigned int cache_is_dirty(int way, int setnum);

/* Receives a block address and reads it from memory into the cache. */
void cache_read_block(int blocknum);

/* Receives a set number and a way and writes it into memory. */
void cache_write_block(int way, int setnum);

/* Receives an address and returns the byte. */
unsigned char cache_read_byte(int address);

/* Receives an address and a byte, which gets written into the address. */
void cache_write_byte(int address, unsigned char value);

/* Returns the miss rate from the cache. */
float cache_get_miss_rate();

/* Returns if the last operation was hit or miss*/
bool cache_hit();

/* Destroys the cache, releasing all of its resources. */
void cache_uninit();

#endif /* CACHE_H */