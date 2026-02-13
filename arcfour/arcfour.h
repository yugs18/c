/* arcfour.h */
#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include <errno.h>

#define rc4decrypt(x, y) rc4encrypt(x, y)

struct s_arcfour {
    int i, j, k;
    uint8_t s[256];
};
typedef struct s_arcfour Arcfour;

Arcfour *rc4init(uint8_t *, uint16_t);
uint8_t rc4byte(void);
uint8_t *rc4encrypt(uint8_t *, uint16_t);