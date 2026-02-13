/* arcfour.h */
#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include <errno.h>

#define MS                  500
#define export              __attribute__((visibility("default")))
#define rc4decrypt          rc4encrypt
#define rc4uninit(x)        free(x)
#define rc4whitewash(x, y)     for (x = 0; x < (MS * 1000000); x++) \
                                        (volatile uint8_t)rc4byte(y);

struct s_arcfour {
    int i, j, k;
    uint8_t s[256];
};
typedef struct s_arcfour Arcfour;

export Arcfour *rc4init(uint8_t *, uint16_t);
uint8_t rc4byte(Arcfour *);
export uint8_t *rc4encrypt(Arcfour *, uint8_t *, uint16_t);