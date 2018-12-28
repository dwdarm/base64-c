/* Fajar Dwi Darmanto (fajardwidarm@gmail.com) */

#ifndef BASE64_H
#define BASE64_H

#include <stdlib.h>
#include <string.h>

size_t base64_encode (const unsigned char *in, char *out, size_t szi);
size_t base64_decode (const char *in, unsigned char *out, size_t szi);

#endif
