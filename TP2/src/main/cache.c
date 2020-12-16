#include "cache.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>

#define KB 1024

/* Private functions*/

void memory_init(memory_t* memory) {
  memory->data = malloc(MAIN_MEMORY_SIZE);
  memset(memory->data, 0, MAIN_MEMORY_SIZE);
}

static unsigned int _get_tag(int address) {
  int number_sets = (cachesize * KB) / (blocksize * ways);
  int bit_offset = log2(256);
  int bit_set = log2(4);
  int bit_tag = 16 - (bit_set + bit_offset);  // TODO 16 IS CONSTANT

  unsigned int tag = (address >> (bit_offset + bit_set)) & bit_tag;

  return tag;
}

static unsigned int _get_offset(int address) {
  int number_sets = (cachesize * KB) / (blocksize * ways);
  int bit_offset = log2(256);

  unsigned int offset = address & bit_offset;

  return offset;
}

/*
static void _read_tocache(cache_t* self, unsigned int blocknum,
                          unsigned int way, unsigned int set) {
  block_t current_block = self->sets[set].blocks[way];
  if (current_block.valid && current_block.dirty) {
    write_tomem(way, set);  // Escribo el bloque en memoria.
  }

  for (size_t i = 0; i < blocksize; i++) {
    current_block.data[i] = main_memory.data[blocknum * blocksize + i];
  }

  // current_block.numero = ++cache.ultimoBloque;
  current_block.dirty = false;
  current_block.valid = true;
  current_block.tag = _get_tag(blocknum * blocksize);
}*/

/* Public functions */
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

  self->memory = malloc(sizeof(memory_t*));
  memory_init(self->memory);
}

unsigned int cache_find_set(cache_t* self, int address) {
  /* ADDRES = TAG + SET + OFFSET */
  /*Se asume que el espacio de direcciones es de 16 bits */

  int number_sets = (cachesize * KB) / (blocksize * ways);
  int bit_offset = log2(blocksize);
  int bit_set = log2(number_sets);
  int bit_tag = 16 - (bit_set + bit_offset);  // TODO 16 IS CONSTANT

  unsigned int set = ((address << bit_tag) >> (bit_offset + bit_tag)) & bit_set;

  return set;
}

unsigned int cache_find_lru(cache_t* self, int setnum) {
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
  return self->sets[setnum].blocks[way].dirty;
}

void cache_read_block(cache_t* self, int blocknum) {}

void cache_write_block(cache_t* self, int way, int setnum) {
  int number_sets = (cachesize * KB) / (blocksize * ways);
  if (way > ways || setnum > number_sets) {
    return;
  }
  // First obtain the data
  unsigned char* data = self->sets[setnum].blocks[way].data;
}

/*unsigned char cache_read_byte(cache_t* self, int address) {
  unsigned int set = cache_find_set(self, address);
  unsigned int tag = _get_tag(address);
  unsigned int offset = _get_offset(address);
  for (size_t i = 0; i < ways; i++) {
    block_t current_block = self->sets[set].blocks[i];
    if (current_block.valid && current_block.tag == tag) {
      (self->hits)++;
      return current_block.data[offset];
    }
  }
  // El dato no se encuentra en cache => cargo el bloque y devuelvo el dato.
  (self->missses)++;

  unsigned int way = select_oldest(self, set);
  _read_tocache(get_memblock(address), way, set);
  return self->sets[set].blocks[way].data[offset];
}*/

void cache_write_byte(cache_t* self, int address, unsigned char value) {
  unsigned int set = cache_find_set(self, address);
  unsigned int tag = _get_tag(address);
  unsigned int offset = _get_offset(address);
  for (size_t i = 0; i < ways; i++) {
    block_t current_block = self->sets[set].blocks[i];
    if (current_block.valid && current_block.tag == tag) {
      (self->hits)++;
      current_block.data[offset] = value;
      return;
    }
  }
  // El dato no se encuentra en cache => cargo el bloque y lo escribo.
  (self->missses)++;
  /*TODO
  unsigned int way = select_oldest(conjunto);
  read_tocache(get_memblock(address), way, conjunto);
  cache.conjuntos[conjunto].vias[way].dirty = true;
  cache.conjuntos[conjunto].vias[way].data[offset] = value;*/
  return;
}

int cache_get_miss_rate(cache_t* self) {
  if ((self->missses + self->missses) == 0) {
    return 0;
  }
  return (self->missses / (self->missses + self->hits));
}

void cache_uninit(cache_t* self) {}
