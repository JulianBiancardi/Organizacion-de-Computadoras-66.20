#include <stdio.h>

#include "../main/cache.h"

int main(int args, char** argv) {
  cache_t cache;
  cache_init(&cache);

  unsigned int set = cache_find_set(&cache, 0x0000);

  printf("%i", set);

  return 0;
}