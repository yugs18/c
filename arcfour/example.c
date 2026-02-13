/* example.c */
#include "arcfour.h"

#define F fflush(stderr)

int main(void);

void printbin(uint8_t *input, const uint16_t size) {
    uint16_t i;
    uint8_t *p;

    assert(size > 0);

    for (i = size, p = input; i; i--, p++) {
        if (!(i % 2))
            printf(" ");
        printf("%.02x", *p);
    }

    printf("\n");

    return;
}

int main() {
    Arcfour *rc4;
    uint16_t skey, stext;
    char *key, *from;
    uint8_t *encrypted;
    uint8_t *decrypted;

    key = "tomatoes";
    skey = strlen(key);
    from = "Shall I compare thee to a summer's day?";
    stext = strlen(from);

    printf("Initializing encryption...\n"); F;
    rc4 = rc4init((uint8_t *)key ,skey);
    printf("done\n");

    printf("'%s'\n ->", from);
    encrypted = rc4encrypt(rc4, (uint8_t *)from, stext);
    printbin(encrypted, stext);

    rc4uninit(rc4);

    printf("Initializing decryption...\n"); F;
    rc4 = rc4init((uint8_t *)key ,skey);
    printf("done\n");

    decrypted = rc4decrypt(rc4, encrypted, stext);
    printf("    -> '%s'\n", decrypted);

    rc4uninit(rc4);
    free(encrypted);
    free(decrypted);

    return 0;
}