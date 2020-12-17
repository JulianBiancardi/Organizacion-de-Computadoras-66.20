#include "cache_tests.h"

#include "../main/cache.h"
#include "../main/memory.h"
#include "tests_setup.h"

int static cache_properties_test();
int static cache_creation_test();
int static cache_destruction_test();
int static cache_clean_test();
int static cache_find_set_test();
int static cache_read_miss_test();
int static cache_read_hit_test();
int static cache_read_miss_rate_test();
int static cache_tag_miss_test();
int static cache_way_filling_test();
int static cache_find_lru_test();
int static cache_lru_block_replacement_test();
int static cache_read_full_block_hit_test();
int static cache_write_read_test();
int static cache_write_full_block_hit_test();
int static cache_write_miss_test();
int static cache_write_hit_test();
int static cache_write_miss_rate_test();

void cache_tests() {
  begin_tests("CACHE");

  print_test("The cache gets its properties set correctly",
             cache_properties_test, NO_ERROR);
  print_test("The cache is initialized correctly", cache_creation_test,
             NO_ERROR);
  print_test("The cache is unitialized correctly", cache_destruction_test,
             NO_ERROR);
  print_test("The cache is initially fully clean", cache_clean_test, NO_ERROR);
  print_test("The cache finds a set from an address", cache_find_set_test,
             NO_ERROR);
  print_test("The cache misses when first reading a byte", cache_read_miss_test,
             NO_ERROR);
  print_test("The cache hits when rereading a byte", cache_read_hit_test,
             NO_ERROR);
  print_test("The cache correctly measures reading miss-rate",
             cache_read_miss_rate_test, NO_ERROR);
  print_test("The cache misses when set and offset are equal but not the tag",
             cache_tag_miss_test, NO_ERROR);
  print_test("The cache doesn't replace a block if another way is free",
             cache_way_filling_test, NO_ERROR);
  print_test("The cache finds the least recently used block correctly",
             cache_find_lru_test, NO_ERROR);
  print_test(
      "The cache replaces the least recently used block if the set is full",
      cache_lru_block_replacement_test, NO_ERROR);
  print_test("The cache hits all the block if it was loaded for reading",
             cache_read_full_block_hit_test, NO_ERROR);
  print_test("The cache reads the correct value after writing",
             cache_write_read_test, NO_ERROR);
  print_test("The cache misses when first writing a byte",
             cache_write_miss_test, NO_ERROR);
  print_test("The cache hits when rewriting a byte", cache_write_hit_test,
             NO_ERROR);
  print_test("The cache correctly measures writing miss-rate",
             cache_write_miss_rate_test, NO_ERROR);
  print_test("The cache hits all the block if it was allocated for writing",
             cache_write_full_block_hit_test, NO_ERROR);

  end_tests();
}

int static cache_properties_test() {
  cachesize = 8;
  blocksize = 4;
  ways = 2;

  if (cachesize != 8 || blocksize != 4 || ways != 2) {
    return ERROR;
  }

  return NO_ERROR;
}

int static cache_creation_test() {
  cache_init();
  return NO_ERROR;
}

int static cache_destruction_test() {
  cache_uninit();
  return NO_ERROR;
}

int static cache_clean_test() {
  cache_init();
  int result = NO_ERROR;

  for (int s = 0; s < 1024; s++) {
    for (int w = 0; w < 2; w++) {
      if (cache_is_dirty(w, s)) {
        result = ERROR;
      }
    }
  }

  cache_uninit();
  return result;
}

int static cache_find_set_test() {
  cache_init();
  int result = NO_ERROR;

  if (cache_find_set(0x1234) != 0x8d) {
    result = ERROR;
  }
  if (cache_find_set(0x4321) != 0xc8) {
    result = ERROR;
  }

  cache_uninit();
  return result;
}

int static cache_read_miss_test() {
  cache_init();
  memory_init();
  int result = NO_ERROR;

  cache_read_byte(0x1234);
  if (cache_hit()) {
    result = ERROR;
  }

  cache_read_byte(0x4321);
  if (cache_hit()) {
    result = ERROR;
  }

  cache_uninit();
  memory_uninit();
  return result;
}

int static cache_read_hit_test() {
  cache_init();
  memory_init();
  int result = NO_ERROR;

  cache_read_byte(0x1234);
  cache_read_byte(0x1234);
  if (!cache_hit()) {
    result = ERROR;
  }

  cache_read_byte(0x4321);
  cache_read_byte(0x4321);
  if (!cache_hit()) {
    result = ERROR;
  }

  cache_uninit();
  memory_uninit();
  return result;
}

int static cache_read_miss_rate_test() {
  cache_init();
  memory_init();
  int result = NO_ERROR;

  if (cache_get_miss_rate() != 0.0) {
    result = ERROR;
  }

  cache_read_byte(0x1234);
  if (cache_get_miss_rate() != 100.0) {
    result = ERROR;
  }

  cache_read_byte(0x1234);
  if (cache_get_miss_rate() != 50.0) {
    result = ERROR;
  }

  cache_read_byte(0x4321);
  // Check between a small range due to floats imperfection
  if (cache_get_miss_rate() > 66.666 * 1.001 ||
      cache_get_miss_rate() < 66.666 * 0.999) {
    result = ERROR;
  }

  cache_read_byte(0x4321);
  if (cache_get_miss_rate() != 50.0) {
    result = ERROR;
  }

  cache_uninit();
  memory_uninit();
  return result;
}

int static cache_tag_miss_test() {
  cache_init();
  memory_init();
  int result = NO_ERROR;

  cache_read_byte(0x4321);
  // Different tag, same set and offset
  cache_read_byte(0x5321);
  if (cache_hit()) {
    result = ERROR;
  }

  cache_uninit();
  memory_uninit();
  return result;
}

int static cache_way_filling_test() {
  cache_init();
  memory_init();
  int result = NO_ERROR;

  cache_read_byte(0x4321);
  cache_read_byte(0x5321);
  cache_read_byte(0x4321);
  if (!cache_hit()) {
    result = ERROR;
  }

  cache_uninit();
  memory_uninit();
  return result;
}

int static cache_find_lru_test() {
  cache_init();
  memory_init();
  int result = NO_ERROR;

  cache_read_byte(0x4321);
  cache_read_byte(0x5321);
  if (cache_find_lru(0xc8) != 0) {
    result = ERROR;
  }

  cache_read_byte(0x6321);
  if (cache_find_lru(0xc8) != 1) {
    result = ERROR;
  }

  cache_uninit();
  memory_uninit();
  return result;
}

int static cache_lru_block_replacement_test() {
  cache_init();
  memory_init();
  int result = NO_ERROR;

  cache_read_byte(0x4321);
  cache_read_byte(0x5321);
  cache_read_byte(0x6321);

  cache_read_byte(0x5321);
  if (!cache_hit()) {
    result = ERROR;
  }
  cache_read_byte(0x4321);
  if (cache_hit()) {
    result = ERROR;
  }

  cache_uninit();
  memory_uninit();
  return result;
}

int static cache_read_full_block_hit_test() {
  cache_init();
  memory_init();
  int result = NO_ERROR;

  // Loads 0x4320 to 0x4323
  cache_read_byte(0x4321);

  cache_read_byte(0x4320);
  if (!cache_hit()) {
    result = ERROR;
  }

  cache_read_byte(0x4322);
  if (!cache_hit()) {
    result = ERROR;
  }

  cache_read_byte(0x4323);
  if (!cache_hit()) {
    result = ERROR;
  }

  cache_uninit();
  memory_uninit();
  return result;
}

int static cache_write_read_test() {
  cache_init();
  memory_init();
  int result = NO_ERROR;

  cache_write_byte(0x4321, 0xff);
  if (cache_read_byte(0x4321) != 0xff) {
    result = ERROR;
  }

  cache_uninit();
  memory_uninit();
  return result;
}

int static cache_write_miss_test() {
  cache_init();
  memory_init();
  int result = NO_ERROR;

  cache_write_byte(0x4321, 0xff);
  if (cache_hit()) {
    result = ERROR;
  }

  cache_uninit();
  memory_uninit();
  return result;
}

int static cache_write_hit_test() {
  cache_init();
  memory_init();
  int result = NO_ERROR;

  cache_write_byte(0x4321, 0xff);
  cache_write_byte(0x4321, 0xf0);
  if (!cache_hit()) {
    result = ERROR;
  }

  cache_uninit();
  memory_uninit();
  return result;
}

int static cache_write_miss_rate_test() {
  cache_init();
  memory_init();
  int result = NO_ERROR;

  if (cache_get_miss_rate() != 0.0) {
    result = ERROR;
  }

  cache_write_byte(0x1234, 0x11);
  if (cache_get_miss_rate() != 100.0) {
    result = ERROR;
  }

  cache_write_byte(0x1234, 0x54);
  if (cache_get_miss_rate() != 50.0) {
    result = ERROR;
  }

  cache_write_byte(0x4321, 0xf1);
  // Check between a small range due to floats imperfection
  if (cache_get_miss_rate() > 66.666 * 1.001 ||
      cache_get_miss_rate() < 66.666 * 0.999) {
    result = ERROR;
  }

  cache_write_byte(0x4321, 0x94);
  if (cache_get_miss_rate() != 50.0) {
    result = ERROR;
  }

  cache_uninit();
  memory_uninit();
  return result;
}

int static cache_write_full_block_hit_test() {
  cache_init();
  memory_init();
  int result = NO_ERROR;

  // Loads 0x4320 to 0x4323
  cache_write_byte(0x4321, 0x11);

  cache_write_byte(0x4320, 0x43);
  if (!cache_hit()) {
    result = ERROR;
  }

  cache_write_byte(0x4322, 0x51);
  if (!cache_hit()) {
    result = ERROR;
  }

  cache_write_byte(0x4323, 0x89);
  if (!cache_hit()) {
    result = ERROR;
  }

  cache_uninit();
  memory_uninit();
  return result;
}