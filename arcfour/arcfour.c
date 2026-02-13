/* arcfour.c */
#include "arcfour.h"

Arcfour *rc4init(uint8_t *key, uint16_t size) {
    int x;
    uint8_t temp1, temp2;
    Arcfour *p;

    p = malloc(sizeof(struct s_arcfour));
    if (p == NULL) {
        assert_perror(errno);
    }

    for (x = 0; x < 256; x++) {
        p -> s[x] = 0;
    }
    p -> i = p -> j = p -> k = 0;
    temp1 = temp2 = 0;

    for(p -> i = 0; p -> i < 256; p -> i++) {
        p -> s[p -> i] = p -> i;
    }

    for(p -> i = 0; p -> i < 256; p -> i++) {
        temp1 = p -> i % size;
        temp2 = p -> j + p -> s[p -> i] + key[temp1];
        p -> j = temp2 % 256;

        temp1 = p -> s[p -> i];
        temp2 = p -> s[p -> j];
        p -> s[p -> i] = temp2;
        p -> s[p -> j] = temp1;
    }

    p -> i = p -> j = 0;

    return p;
}