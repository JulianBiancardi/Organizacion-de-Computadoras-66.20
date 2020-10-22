#ifndef __BASE64_H__
#define __BASE64_H__

#include <stddef.h>
#include <sys/types.h>

/*	Encode from ASCII to base 64.*/
int encode64(char* source, size_t source_len, char* buffer);

/*  Decode from base64 to ASCII.*/
ssize_t decode64(char* source, char* buffer);

#endif  // __BASE64_H__
