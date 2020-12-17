#include <stdio.h>

#include "../main/cache.h"

int main(int args, char** argv) {
  cache_init();

  unsigned int set = cache_find_set(0x0000);

  printf("%i", set);

  return 0;
}
