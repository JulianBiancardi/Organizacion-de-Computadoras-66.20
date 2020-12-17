#include "cache.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "constantsTP2.h"

#define KB 1024
#define HIT 1
#define MISS 0

/* Private functions*/
void memory_init(memory_t* memory) {
  memory->data = malloc(MAIN_MEMORY_SIZE);
  memset(memory->data, 0, MAIN_MEMORY_SIZE);
}

static unsigned int _get_tag(int address) {
  unsigned int bit_offset = log2(blocksize);
  unsigned int bit_set = log2(cache.setsnum);
  unsigned int bit_tag = 16 - (bit_set + bit_offset);  // TODO 16 IS CONSTANT

  unsigned int tag = (address >> (bit_offset + bit_set)) & bit_tag;

  return tag;
}

static unsigned int _get_offset(int address) {
  unsigned int bit_offset = log2(blocksize);
  unsigned int offset = address & bit_offset;

  return offset;
}

static unsigned int _get_memblock(unsigned int address) {
  unsigned int bit_offset = log2(blocksize);
  return address >> bit_offset;
}

static void _read_tocache(unsigned int blocknum, unsigned int way,
                          unsigned int setnum) {
  block_t current_block = cache.sets[setnum].blocks[way];
  if (current_block.valid && current_block.dirty) {
    cache_write_block(way, setnum);  // Write the block in memory
  }

  for (size_t i = 0; i < blocksize; i++) {
    current_block.data[i] = cache.memory->data[blocknum * blocksize + i];
  }

  // current_block.numero = ++cache.ultimoBloque;
  current_block.dirty = false;
  current_block.valid = true;
  current_block.tag = _get_tag(blocknum * blocksize);
}
//-------------------------------------------------------------

//-------------------------------------------------------------
/* Public functions */
void cache_init() {
  cache.setsnum = (cachesize * KB) / (blocksize * ways);
  cache.hits = 0;
  cache.misses = 0;
  cache.last_satuts = HIT;

  // Number of sets in the cache
  cache.sets = (set_t*)malloc(sizeof(set_t) * cache.setsnum);
  if (cache.sets == NULL) {
    return ERROR;
  }

  // TODO VERIFY THE NULL POINTER
  for (size_t i = 0; i < cache.setsnum; i++) {
    cache.sets[i].blocks = (block_t*)malloc(sizeof(block_t) * ways);
    for (size_t j = 0; j < ways; j++) {
      cache.sets[i].blocks[j].data = calloc(blocksize, sizeof(unsigned char));
      cache.sets[i].blocks[j].valid = false;
      cache.sets[i].blocks[j].dirty = false;
      cache.sets[i].blocks[j].date = 0;
    }
  }

  cache.memory = malloc(sizeof(memory_t*));
  memory_init(cache.memory);
}

unsigned int cache_find_set(int address) {
  /* ADDRES = TAG + SET + OFFSET */
  /*Se asume que el espacio de direcciones es de 16 bits */

  int bit_offset = log2(blocksize);
  int bit_set = log2(cache.setsnum);
  int bit_tag = 16 - (bit_set + bit_offset);  // TODO 16 IS CONSTANT

  unsigned int set = ((address << bit_tag) >> (bit_offset + bit_tag)) & bit_set;

  return set;
}

unsigned int cache_find_lru(int setnum) {
  if (setnum < 0 || setnum > cache.setsnum) {
    return (unsigned int)ERROR;
  }
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
  int bit_offset = log2(blocksize);
  unsigned int setnum = cache_find_set(blocknum << bit_offset);
  unsigned int way = cache_find_lru(setnum);  // Find the lru block

  // Verify if the block is dirty and write the block in memory
  if (cache.sets[setnum].blocks[way].valid && cache_is_dirty(way, setnum)) {
    cache_write_block(way, setnum);
  }

  // Write the block with the memory data
  for (size_t i = 0; i < blocksize; i++) {
    cache.sets[setnum].blocks[way].data[i] =
        cache.memory->data[blocknum * blocksize + i];
  }

  // current_block.numero = ++cache.ultimoBloque; //TODO
  cache.sets[setnum].blocks[way].dirty = false;
  cache.sets[setnum].blocks[way].valid = true;
  cache.sets[setnum].blocks[way].tag = _get_tag(blocknum * blocksize);
}

void cache_write_block(int way, int setnum) {
  unsigned int tag = cache.sets[setnum].blocks[way].tag;

  int bit_offset = log2(blocksize);
  int bit_set = log2(cache.setsnum);

  unsigned int address =
      (tag << (bit_set + bit_offset)) + (setnum << bit_offset);
  for (size_t i = 0; i < blocksize; i++) {
    cache.memory->data[address + i] = cache.sets[setnum].blocks[way].data[i];
  }
}

unsigned char cache_read_byte(int address) {
  unsigned int setnum = cache_find_set(address);
  unsigned int tag = _get_tag(address);
  unsigned int offset = _get_offset(address);
  for (size_t i = 0; i < ways; i++) {
    if (cache.sets[setnum].blocks[i].valid &&
        cache.sets[setnum].blocks[i].tag == tag) {
      (cache.hits)++;
      cache.last_satuts = HIT;
      return cache.sets[setnum].blocks[i].data[offset];
    }
  }
  // El dato no se encuentra en cache => cargo el bloque y devuelvo el dato.
  (cache.misses)++;
  cache.last_satuts = MISS;
  unsigned int way = cache_find_lru(setnum);
  cache_read_block(get_memblock(address));  // TODO Simply use get_memblock?
  //_read_tocache(self, , way, setnum);
  return cache.sets[setnum].blocks[way].data[offset];
}

void cache_write_byte(int address, unsigned char value) {
  unsigned int setnum = cache_find_set(address);
  unsigned int tag = _get_tag(address);
  unsigned int offset = _get_offset(address);
  for (size_t i = 0; i < ways; i++) {
    if (cache.sets[setnum].blocks[i].valid &&
        cache.sets[setnum].blocks[i].tag == tag) {
      (cache.hits)++;
      cache.last_satuts = HIT;
      cache.sets[setnum].blocks[i].data[offset] = value;
      return;
    }
  }
  // El dato no se encuentra en cache => cargo el bloque y lo escribo.
  (cache.misses)++;
  cache.last_satuts = MISS;
  unsigned int way = cache_find_lru(setnum);  // Find the lru block
  cache_read_block(get_memblock(address));    // TODO Simply use get_memblock?
  cache.sets[setnum].blocks[way].dirty = true;
  cache.sets[setnum].blocks[way].data[offset] = value;
  return;
}

float cache_get_miss_rate() {
  if ((cache.misses + cache.misses) == 0) {
    return 0;
  }
  return (cache.misses / (cache.misses + cache.hits)) * 100;
}

bool hit() { return cache.last_satuts; }

void cache_uninit() {
  for (size_t setnum = 0; setnum < cache.setsnum; setnum++) {
    for (size_t waynum = 0; waynum < ways; waynum++) {
      free(cache.sets[setnum].blocks[waynum].data);
    }
    free(cache.sets[setnum].blocks);
  }
  free(cache.sets);
}
//-------------------------------------------------------------
