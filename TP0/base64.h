#ifndef __BASE64_H__
#define __BASE64_H__

#include <stddef.h>

/*	Encode from ASCII to base 64.*/
int encode64(char* source, size_t source_len, char* buffer);

/*  Decode from base64 to ASCII.*/
int decode64(char* source, char* buffer);

#endif  // __BASE64_H__
