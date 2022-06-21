#ifndef BOX_SHA_H
#define BOX_SHA_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>

extern unsigned char *box_sha256(const char *string);

extern char *box_hex(const unsigned char* bytes, int len);

#endif
