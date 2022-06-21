#include "box_sha.h"

extern unsigned char *box_sha256(const char *string) {

    unsigned char *digest = calloc(SHA256_DIGEST_LENGTH + 1, sizeof(unsigned char));

    SHA256(string, strlen(string), digest);

    return digest; 
}

extern char *box_hex(const unsigned char* bytes, int len) {

    char *hex = calloc(len*2 + 1, sizeof(char));

    for (int i = 0; i < len; i++) {
         sprintf(&hex[i*2], "%02x", bytes[i]);
    }

    return hex;
}
