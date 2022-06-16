#include "box_sha.h"

extern char *box_sha256(const char *string) {

    unsigned char *digest = calloc(SHA256_DIGEST_LENGTH + 1, sizeof(unsigned char));

    /*
    for ( int i = 0; i < 32; i++) {
        printf("%02x ", digest[i]);
    }
    printf("\n");
    */
    
    return SHA256(string, strlen(string), digest);
}
