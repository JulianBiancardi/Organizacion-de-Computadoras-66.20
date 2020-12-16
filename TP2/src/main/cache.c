#include "cache.h"

/* La memoria a simular es una caché [1] asociativa por conjuntos, en que
se puedan pasar por parámetro el número de vı́as, la capacidad y el tamaño
de bloque. La polı́tica de reemplazo será LRU y la polı́tica de escrituraserá
WB/WA. Se asume que el espacio de direcciones es de 16 bits, y hay entonces una
memoria principal a simular con un tamaño de 64KB. Estas memorias pueden ser
implementadas como variables globales. Cada bloque de la memoria caché deberá
contar con su metadata, incluyendo el bit V , el bit D, el tag, y un campo que
permita implementar la polı́tica de LRU.*/

void cache_init(cache_t* self, int ways, int cachesize, int blocksize) {
  if (self == NULL) {
    // TODO RETURN AN ERROR
    return;
  }

  self->miss_rate = 0;
}

unsigned int cache_find_set(cache_t* self, int address);

unsigned int cache_find_lru(cache_t* self, int setnum);

unsigned int cache_is_dirty(cache_t* self, int way, int setnum);

void cache_read_block(cache_t* self, int blocknum);

void cache_write_block(cache_t* self, int way, int setnum);

char cache_read_byte(cache_t* self, int address);

void cache_write_byte(cache_t* self, int address, char value);

int cache_get_miss_rate(cache_t* self) { return self->miss_rate; }

void cache_uninit(cache_t* self);