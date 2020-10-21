
#include "encode.h"

#include <stdlib.h>

#define SUCCED 0
#define ERROR -1

#define SOURCE_LEN 3
#define OUTPUT_LEN 4

char _encodeValue(long value) {
  char encoding_table[64] =
      "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
  return encoding_table[value];
}

long generate_phrase(const char *source, size_t len) {
  long phrase = 0;
  // Encode letter by letter and shift. Then add to the phrase.
  for (size_t pos = 0; pos < SOURCE_LEN; pos++) {
    unsigned char octet = pos < len ? (unsigned char)source[pos] : 0;
    int shiftValue = (SOURCE_LEN - 1) - pos;
    phrase += octet << 8 * shiftValue;
  }
  return phrase;
}

int encode64(char *source, size_t source_len, char *buffer) {
  if (source == NULL || buffer == NULL) return ERROR;

  long phrase = generate_phrase(source, source_len);

  // Generate letter by letter from the phrase
  for (size_t pos = 0; pos < OUTPUT_LEN; pos++) {
    long value = phrase >> (SOURCE_LEN - pos) * 6 & 0x3F;
    buffer[pos] = _encodeValue(value);
  }

  for (size_t pos = source_len + 1; pos < OUTPUT_LEN; pos++) {
    buffer[pos] = '=';
  }

  return SUCCED;
}
