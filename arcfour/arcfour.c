/* arcfour.c */
#include "arcfour.h"

/*
 * rc4init()
 * ----------
 * Initializes the RC4 state using the given key.
 *
 * This performs the RC4 Key Scheduling Algorithm (KSA):
 *   1. Initialize the permutation array S[0..255]
 *   2. Shuffle S using the key bytes
 *
 * Returns:
 *   Pointer to initialized Arcfour structure.
 */
export Arcfour *rc4init(uint8_t *key, uint16_t size) {
    int x;
    uint8_t temp1, temp2;
    Arcfour *p;
    uint32_t n;   /* NOTE: currently uninitialized before rc4whitewash */

    /* Allocate memory for RC4 state */
    p = malloc(sizeof(struct s_arcfour));
    if (p == NULL) {
        assert_perror(errno);   /* Better: perror + exit */
    }

    /*
     * Optional zeroing of S-box.
     * (Not strictly needed because it is overwritten below.)
     */
    for (x = 0; x < 256; x++) {
        p->s[x] = 0;
    }

    /* Initialize indexes used during encryption */
    p->i = p->j = p->k = 0;
    temp1 = temp2 = 0;

    /* ---------------------------------------------------
     * STEP 1: Initialize permutation array
     *
     * S becomes:
     *   [0, 1, 2, 3, ... 255]
     * ---------------------------------------------------
     */
    for (p->i = 0; p->i < 256; p->i++) {
        p->s[p->i] = p->i;
    }

    /* ---------------------------------------------------
     * STEP 2: RC4 Key Scheduling Algorithm (KSA)
     *
     * j = (j + S[i] + key[i mod keylen]) mod 256
     * swap(S[i], S[j])
     *
     * This mixes key bytes into the permutation.
     * ---------------------------------------------------
     */
    for (p->i = 0; p->i < 256; p->i++) {

        /* Select key byte cyclically */
        temp1 = p->i % size;

        /* Update j index */
        temp2 = p->j + p->s[p->i] + key[temp1];
        p->j = temp2 % 256;

        /* Swap S[i] and S[j] */
        temp1 = p->s[p->i];
        temp2 = p->s[p->j];
        p->s[p->i] = temp2;
        p->s[p->j] = temp1;
    }

    /*
     * Reset indices for PRGA (encryption phase)
     */
    p->i = p->j = 0;

    /*
     * Optional "RC4-drop" / whitewashing step.
     * Usually used to discard early biased keystream bytes.
     *
     * WARNING:
     * - n is currently uninitialized (BUG).
     * - set a value before use (e.g., n = 768).
     */
    rc4whitewash(n, p);

    return p;
}


/*
 * rc4byte()
 * ----------
 * Generates ONE byte of RC4 keystream.
 *
 * This implements the PRGA
 * (Pseudo-Random Generation Algorithm).
 */
uint8_t rc4byte(Arcfour *p) {
    uint16_t temp1, temp2;

    /* i = (i + 1) mod 256 */
    p->i = (p->i + 1) % 256;

    /* j = (j + S[i]) mod 256 */
    p->j = (p->j + p->s[p->i]) % 256;

    /* Swap S[i] and S[j] */
    temp1 = p->s[p->i];
    temp2 = p->s[p->j];
    p->s[p->i] = temp2;
    p->s[p->j] = temp1;

    /*
     * Output byte:
     * K = S[(S[i] + S[j]) mod 256]
     */
    temp1 = (p->s[p->i] + p->s[p->j]) % 256;
    p->k = p->s[temp1];

    return p->k;
}


/*
 * rc4encrypt()
 * ------------
 * Encrypts (or decrypts) a buffer using RC4.
 *
 * RC4 is symmetric:
 *   ciphertext = plaintext XOR keystream
 *   plaintext  = ciphertext XOR keystream
 */
export uint8_t *rc4encrypt(Arcfour *p, uint8_t *cleartext, uint16_t size) {
    uint8_t *ciphertext;
    int x;

    /* Allocate output buffer (+1 for optional '\0') */
    ciphertext = malloc(size + 1);
    if (!ciphertext) {
        assert_perror(errno);   /* Better: perror + exit */
    }

    /*
     * XOR each byte with generated keystream byte.
     */
    for (x = 0; x < size; x++) {
        ciphertext[x] = cleartext[x] ^ rc4byte(p);
    }

    /*
     * Null-termination (useful only if data is text).
     * RC4 output is binary, so this is optional.
     */
    ciphertext[size] = '\0';

    return ciphertext;
}
