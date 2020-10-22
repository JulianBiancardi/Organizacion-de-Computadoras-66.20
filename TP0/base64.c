
#include "base64.h"

#include <stdlib.h>

#include "constants.h"

#define ENCODE_MASK 0x3F
#define DECODE_MASK 0xFF

static char _encodeValue(long value);
static long _generate_phrase(const char *source, size_t len);
static long _decodeLetterAndShift(char letter, int shiftValue);
static int _decodeValueLetter(char letter);

static char _encodeValue(long value) {
  char encoding_table[64] =
      "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
  return encoding_table[value];
}

static long _generate_phrase(const char *source, size_t len) {
  long phrase = 0;
  // Encode letter by letter and shift. Then add to the phrase.
  for (size_t pos = 0; pos < DECODED_LEN; pos++) {
    unsigned char octet = pos < len ? (unsigned char)source[pos] : 0;
    int shiftValue = (DECODED_LEN - 1) - pos;
    phrase += octet << 8 * shiftValue;
  }
  return phrase;
}

static long _decodeLetterAndShift(char letter, int shiftValue) {
  if (letter == '=') return 0;
  int decodedLetter = _decodeValueLetter(letter);
  if (decodedLetter == ERROR) {
    return ERROR;
  }
  return (long)decodedLetter << 6 * shiftValue;
}

static int _decodeValueLetter(char letter) {
  int intLetter = (int)letter;
  if (intLetter >= (int)'A' && intLetter <= (int)'Z')
    return intLetter - (int)'A';
  if (intLetter >= (int)'a' && intLetter <= (int)'z')
    return intLetter - (int)'a' + 26;
  if (intLetter >= (int)'0' && intLetter <= (int)'9')
    return intLetter - (int)'0' + 52;
  switch (letter) {
    case '+':
      return 62;
    case '/':
      return 63;
    default:
      return ERROR;
  }
}

int encode64(char *source, size_t source_len, char *buffer) {
  if (source == NULL || buffer == NULL) return ERROR;

  long phrase = _generate_phrase(source, source_len);

  // Generate letter by letter from the phrase
  for (size_t pos = 0; pos < ENCODED_LEN; pos++) {
    long value = phrase >> (DECODED_LEN - pos) * 6 & ENCODE_MASK;
    buffer[pos] = _encodeValue(value);
  }

  for (size_t pos = source_len + 1; pos < ENCODED_LEN; pos++) {
    buffer[pos] = '=';
  }

  return NO_ERROR;
}

ssize_t decode64(char *source, char *buffer) {
  long phrase = 0;
  ssize_t chars_decoded = 0;
  // Decode letter by letter and shift. Then add to the phrase.
  for (size_t position = 0; position < ENCODED_LEN; position++) {
    long decodeValue = _decodeLetterAndShift(source[position], 3 - position);
    if (decodeValue == ERROR) { return ERROR;}
    phrase = phrase + decodeValue;
  }
  // Generate letter by letter from the phrase
  for (size_t position = 0; position < DECODED_LEN; position++) {
    long decodeLetter = phrase >> (2 - position) * 8 & DECODE_MASK;
    if (decodeLetter != 0) { chars_decoded++;}
    buffer[position] = decodeLetter;
  }
  return chars_decoded;
}
