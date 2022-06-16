#ifndef BOX_SHA_H
#define BOX_SHA_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>

extern char *box_sha256(const char *string);

#endif
