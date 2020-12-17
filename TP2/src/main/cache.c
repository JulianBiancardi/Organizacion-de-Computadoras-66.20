#include "cache.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "constantsTP2.h"

#define KB 1024

/* Private functions*/

void memory_init(memory_t* memory) {
  memory->data = malloc(MAIN_MEMORY_SIZE);
  memset(memory->data, 0, MAIN_MEMORY_SIZE);
}

static unsigned int _get_tag(cache_t* self, int address) {
  int bit_offset = log2(blocksize);
  int bit_set = log2(self->setsnum);
  int bit_tag = 16 - (bit_set + bit_offset);  // TODO 16 IS CONSTANT

  unsigned int tag = (address >> (bit_offset + bit_set)) & bit_tag;

  return tag;
}

static unsigned int _get_offset(cache_t* self, int address) {
  int bit_offset = log2(blocksize);
  unsigned int offset = address & bit_offset;

  return offset;
}

static unsigned int _get_memblock(cache_t* self, unsigned int address) {
  int bit_offset = log2(blocksize);
  return address >> bit_offset;
}

static void _write_tomem(cache_t* self, unsigned int way, unsigned int setnum) {
  unsigned int tag = self->sets[setnum].blocks[way].tag;

  int bit_offset = log2(blocksize);
  int bit_set = log2(self->setsnum);

  unsigned int address =
      (tag << (bit_set + bit_offset)) + (setnum << bit_offset);
  for (size_t i = 0; i < blocksize; i++) {
    self->memory->data[address + i] = self->sets[setnum].blocks[way].data[i];
  }
}

static void _read_tocache(cache_t* self, unsigned int blocknum,
                          unsigned int way, unsigned int setnum) {
  block_t current_block = self->sets[setnum].blocks[way];
  if (current_block.valid && current_block.dirty) {
    _write_tomem(self, way, setnum);  // Write the block in memory
  }

  for (size_t i = 0; i < blocksize; i++) {
    current_block.data[i] = self->memory->data[blocknum * blocksize + i];
  }

  // current_block.numero = ++cache.ultimoBloque;
  current_block.dirty = false;
  current_block.valid = true;
  current_block.tag = _get_tag(self, blocknum * blocksize);
}

//-------------------------------------------------------------

//-------------------------------------------------------------
/* Public functions */
int cache_init(cache_t* self) {
  if (self == NULL) {
    return ERROR;
  }
  self->setsnum = (cachesize * KB) / (blocksize * ways);
  self->hits = 0;
  self->missses = 0;

  // Number of sets in the cache
  self->sets = (set_t*)malloc(sizeof(set_t) * self->setsnum);
  if (self->sets == NULL) {
  }

  // TODO VERIFY THE NULL POINTER
  for (size_t i = 0; i < self->setsnum; i++) {
    self->sets[i].blocks = (block_t*)malloc(sizeof(block_t) * ways);
    for (size_t j = 0; j < ways; j++) {
      self->sets[i].blocks[j].data = calloc(blocksize, sizeof(unsigned char));
      self->sets[i].blocks[j].valid = false;
      self->sets[i].blocks[j].dirty = false;
    }
  }

  self->memory = malloc(sizeof(memory_t*));
  memory_init(self->memory);
}

unsigned int cache_find_set(cache_t* self, int address) {
  /* ADDRES = TAG + SET + OFFSET */
  /*Se asume que el espacio de direcciones es de 16 bits */

  int bit_offset = log2(blocksize);
  int bit_set = log2(self->setsnum);
  int bit_tag = 16 - (bit_set + bit_offset);  // TODO 16 IS CONSTANT

  unsigned int set = ((address << bit_tag) >> (bit_offset + bit_tag)) & bit_set;

  return set;
}

unsigned int cache_find_lru(cache_t* self, int setnum) {
  if (setnum < 0 || setnum > self->setsnum) {
    return (unsigned int)ERROR;
  }
  unsigned int way = 0;
  unsigned int max = self->sets[setnum].blocks[way].date;
  for (size_t j = 1; j < ways; j++) {
    if (self->sets[setnum].blocks[j].date > max) {
      max = self->sets[setnum].blocks[j].date;
      way = j;
    }
  }
  return way;
}

unsigned int cache_is_dirty(cache_t* self, int way, int setnum) {
  if (setnum < 0 || setnum > self->setsnum) {
    return (unsigned int)ERROR;
  }
  if (way < 0 || way > ways) {
    return (unsigned int)ERROR;
  }
  return self->sets[setnum].blocks[way].dirty;
}

void cache_read_block(cache_t* self, int blocknum) {}

void cache_write_block(cache_t* self, int way, int setnum) {}

unsigned char cache_read_byte(cache_t* self, int address) {
  unsigned int setnum = cache_find_set(self, address);
  unsigned int tag = _get_tag(self, address);
  unsigned int offset = _get_offset(self, address);
  for (size_t i = 0; i < ways; i++) {
    block_t current_block = self->sets[setnum].blocks[i];
    if (current_block.valid && current_block.tag == tag) {
      (self->hits)++;
      return current_block.data[offset];
    }
  }
  // El dato no se encuentra en cache => cargo el bloque y devuelvo el dato.
  (self->missses)++;

  unsigned int way = cache_find_lru(self, setnum);
  _read_tocache(self, _get_memblock(self, address), way, setnum);
  return self->sets[setnum].blocks[way].data[offset];
}

void cache_write_byte(cache_t* self, int address, unsigned char value) {
  unsigned int setnum = cache_find_set(self, address);
  unsigned int tag = _get_tag(self, address);
  unsigned int offset = _get_offset(self, address);
  for (size_t i = 0; i < ways; i++) {
    block_t current_block = self->sets[setnum].blocks[i];
    if (current_block.valid && current_block.tag == tag) {
      (self->hits)++;
      current_block.data[offset] = value;
      return;
    }
  }
  // El dato no se encuentra en cache => cargo el bloque y lo escribo.
  (self->missses)++;

  unsigned int way = cache_find_lru(self, setnum);
  _read_tocache(self, _get_memblock(self, address), way, setnum);
  self->sets[setnum].blocks[way].dirty = true;
  self->sets[setnum].blocks[way].data[offset] = value;
  return;
}

float cache_get_miss_rate(cache_t* self) {
  if ((self->missses + self->missses) == 0) {
    return 0;
  }
  return (self->missses / (self->missses + self->hits)) * 100;
}

void cache_uninit(cache_t* self) {}
//-------------------------------------------------------------
