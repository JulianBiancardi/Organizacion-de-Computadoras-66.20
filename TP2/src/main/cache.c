#include "cache.h"

#include <math.h>
#include <stdlib.h>

#include "constantsTP2.h"
#include "memory.h"

#define KB 1024
#define ADDR_MEMORY_BITS 16  // 64KB MEMORY
#define HIT true
#define MISS false

unsigned int ways = 0;
unsigned int cachesize = 0;
unsigned int blocksize = 0;
bool cache_initialized = false;
cache_t cache;

//-------------------------------------------------------------
/* Private functions*/
static unsigned int _get_tag(int address) {
  return address >> (cache.bits_offset + cache.bits_set);
}

static unsigned int _get_offset(int address) {
  unsigned short aux = address << (cache.bits_tag + cache.bits_set);
  return aux >> (cache.bits_tag + cache.bits_set);
}

static unsigned int _get_memblock(unsigned int address) {
  return address >> cache.bits_offset;
}

static void _increment_date(int setnum, int way_avoid) {
  for (size_t way = 0; way < ways; way++) {
    if (way != way_avoid) {
      (cache.sets[setnum].blocks[way].date)++;
    }
  }
}
//-------------------------------------------------------------

//-------------------------------------------------------------
/* Public functions */
int cache_init() {
  cache.hits = 0;
  cache.misses = 0;
  cache.last_satuts = HIT;
  cache.setsnum = (cachesize * KB) / (blocksize * ways);
  cache.bits_offset = log2(blocksize);
  cache.bits_set = log2(cache.setsnum);
  cache.bits_tag = ADDR_MEMORY_BITS - (cache.bits_set + cache.bits_offset);

  // Number of sets in the cache
  cache.sets = (set_t*)malloc(sizeof(set_t) * cache.setsnum);
  if (cache.sets == NULL) {
    return ERROR;
  }

  for (size_t i = 0; i < cache.setsnum; i++) {
    cache.sets[i].blocks = (block_t*)malloc(sizeof(block_t) * ways);
    if (cache.sets[i].blocks == NULL) {
      return ERROR;
    }
    for (size_t j = 0; j < ways; j++) {
      cache.sets[i].blocks[j].data = calloc(blocksize, sizeof(unsigned char));
      if (cache.sets[i].blocks[j].data == NULL) {
        return ERROR;
      }
      cache.sets[i].blocks[j].valid = false;
      cache.sets[i].blocks[j].dirty = false;
      cache.sets[i].blocks[j].date = 0;
    }
  }

  cache_initialized = true;
  return NO_ERROR;
}

unsigned int cache_find_set(int address) {
  /* ADDRES = TAG + SET + OFFSET */
  /*Se asume que el espacio de direcciones es de 16 bits */
  unsigned short aux = (address << cache.bits_tag);
  return aux >> (cache.bits_tag + cache.bits_offset);
}

unsigned int cache_find_lru(int setnum) {
  unsigned int way = 0;
  unsigned int max = cache.sets[setnum].blocks[way].date;
  for (size_t j = 1; j < ways; j++) {
    if (cache.sets[setnum].blocks[j].date > max) {
      max = cache.sets[setnum].blocks[j].date;
      way = j;
    }
  }
  return way;
}

unsigned int cache_is_dirty(int way, int setnum) {
  return (cache.sets[setnum].blocks[way].dirty);
}

void cache_read_block(int blocknum) {
  unsigned int setnum = cache_find_set(blocknum << cache.bits_offset);
  unsigned int way = cache_find_lru(setnum);  // Find the lru block

  // Write the block with the memory data
  for (size_t i = 0; i < blocksize; i++) {
    cache.sets[setnum].blocks[way].data[i] =
        memory.data[blocknum * blocksize + i];
  }

  cache.sets[setnum].blocks[way].valid = true;
  cache.sets[setnum].blocks[way].dirty = false;
  cache.sets[setnum].blocks[way].tag = _get_tag(blocknum * blocksize);
}

void cache_write_block(int way, int setnum) {
  // Verify if the block is dirty and write the block in memory
  if (cache.sets[setnum].blocks[way].valid && cache_is_dirty(way, setnum)) {
    unsigned int tag = cache.sets[setnum].blocks[way].tag;
    unsigned int address = (tag << (cache.bits_set + cache.bits_offset)) +
                           (setnum << cache.bits_offset);
    for (size_t i = 0; i < blocksize; i++) {
      memory.data[address + i] = cache.sets[setnum].blocks[way].data[i];
    }
  }
}

unsigned char cache_read_byte(int address) {
  unsigned int tag = _get_tag(address);
  unsigned int setnum = cache_find_set(address);
  unsigned int offset = _get_offset(address);

  for (size_t i = 0; i < ways; i++) {
    if (cache.sets[setnum].blocks[i].valid &&
        cache.sets[setnum].blocks[i].tag == tag) {
      (cache.hits)++;
      cache.last_satuts = HIT;
      cache.sets[setnum].blocks[i].date = 0;
      _increment_date(setnum, i);
      return cache.sets[setnum].blocks[i].data[offset];
    }
  }
  // El dato no se encuentra en cache, cargo el bloque y devuelvo el dato.
  (cache.misses)++;
  cache.last_satuts = MISS;
  unsigned int way = cache_find_lru(setnum);  // Find the lru block
  cache_write_block(way,
                    setnum);  // Write the block in main memory if it is dirty
  cache_read_block(_get_memblock(address));
  cache.sets[setnum].blocks[way].date = 0;
  _increment_date(setnum, way);
  return cache.sets[setnum].blocks[way].data[offset];
}

void cache_write_byte(int address, unsigned char value) {
  unsigned int tag = _get_tag(address);
  unsigned int setnum = cache_find_set(address);
  unsigned int offset = _get_offset(address);

  for (size_t i = 0; i < ways; i++) {
    if (cache.sets[setnum].blocks[i].valid &&
        cache.sets[setnum].blocks[i].tag == tag) {
      (cache.hits)++;
      cache.last_satuts = HIT;
      cache.sets[setnum].blocks[i].data[offset] = value;
      cache.sets[setnum].blocks[i].dirty = true;
      cache.sets[setnum].blocks[i].date = 0;
      _increment_date(setnum, i);
      return;
    }
  }
  // El dato no se encuentra en cache,cargo el bloque y lo escribo.
  (cache.misses)++;
  cache.last_satuts = MISS;
  unsigned int way = cache_find_lru(setnum);  // Find the lru block
  cache_write_block(way,
                    setnum);  // Write the block in main memory if it is dirty
  cache_read_block(_get_memblock(address));

  cache.sets[setnum].blocks[way].data[offset] = value;
  cache.sets[setnum].blocks[way].dirty = true;
  cache.sets[setnum].blocks[way].date = 0;
  _increment_date(setnum, way);
  return;
}

float cache_get_miss_rate() {
  if ((cache.misses + cache.hits) == 0) {
    return 0;
  }
  return ((float)cache.misses / (cache.misses + cache.hits)) * 100.0;
}

bool cache_hit() { return cache.last_satuts; }

void cache_uninit() {
  for (size_t setnum = 0; setnum < cache.setsnum; setnum++) {
    for (size_t waynum = 0; waynum < ways; waynum++) {
      free(cache.sets[setnum].blocks[waynum].data);
    }
    free(cache.sets[setnum].blocks);
  }
  free(cache.sets);

  cache_initialized = false;
}
//-------------------------------------------------------------
