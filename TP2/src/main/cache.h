#ifndef CACHE_H
#define CACHE_H

#include <stdbool.h>
#include <stdio.h>

#define MAIN_MEMORY_SIZE 65536
/* La memoria a simular es una caché [1] asociativa por conjuntos, en que
se puedan pasar por parámetro el número de vı́as, la capacidad y el tamaño
de bloque. La polı́tica de reemplazo será LRU y la polı́tica de escritura será
WB/WA. Se asume que el espacio de direcciones es de 16 bits, y hay entonces una
memoria principal a simular con un tamaño de 64KB. Estas memorias pueden ser
implementadas como variables globales. Cada bloque de la memoria caché deberá
contar con su metadata, incluyendo el bit V , el bit D, el tag, y un campo que
permita implementar la polı́tica de LRU.*/

struct main_memory {
  unsigned char data[MAIN_MEMORY_SIZE];
} main_memory;

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
  unsigned int missses;
  unsigned int last_status;
  unsigned int last_block;
} cache_t;

/* Initializes the cache */
void cache_init(cache_t* self);  // TODO REMOVE THIS PARAMETERS

/* Receives an address and returns the set which maps to that address. */
unsigned int cache_find_set(cache_t* self, int address);

/* Receives a set number and returns the number of the block least recently
 * used. */
unsigned int cache_find_lru(cache_t* self, int setnum);

/* Receives a set number and a way and returns whether the block is dirty. */
unsigned int cache_is_dirty(cache_t* self, int way, int setnum);

/* Receives a block address and reads it from memory into the cache. */
void cache_read_block(cache_t* self, int blocknum);

/* Receives a set number and a way and writes it into memory. */
void cache_write_block(cache_t* self, int way, int setnum);

/* Receives an address and returns the byte. */
unsigned char cache_read_byte(cache_t* self, int address);

/* Receives an address and a byte, which gets written into the address. */
void cache_write_byte(cache_t* self, int address, unsigned char value);

/* Returns the miss rate from the cache. */
int cache_get_miss_rate(cache_t* self);

/* Destroys the cache, releasing all of its resources. */
void cache_uninit(cache_t* self);

#endif /* CACHE_H */