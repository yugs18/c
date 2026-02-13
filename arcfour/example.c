/* ============================================================
 * example.c
 * ------------------------------------------------------------
 * Example program demonstrating how to use the RC4 library.
 *
 * Flow:
 *   1. Define key and plaintext
 *   2. Initialize RC4 state
 *   3. Encrypt plaintext
 *   4. Reinitialize RC4 with same key
 *   5. Decrypt ciphertext
 *
 * NOTE:
 * RC4 is symmetric, so encryption and decryption use
 * the SAME function.
 * ============================================================
 */

#include "arcfour.h"

/*
 * Convenience macro:
 * Immediately flush stderr output.
 * Useful when debugging to force text to appear.
 */
#define F fflush(stderr)

int main(void);


/* ------------------------------------------------------------
 * printbin()
 * ------------------------------------------------------------
 * Prints raw binary bytes as hexadecimal text.
 *
 * Example:
 *   input bytes: 74 6f 6d
 *   output:      746f 6d
 *
 * Parameters:
 *   input → pointer to bytes
 *   size  → number of bytes
 * ------------------------------------------------------------
 */
void printbin(uint8_t *input, const uint16_t size) {
    uint16_t i;
    uint8_t *p;

    /* Ensure size is valid */
    assert(size > 0);

    /* Iterate through all bytes */
    for (i = size, p = input; i; i--, p++) {

        /* Add space every 2 bytes for readability */
        if (!(i % 2))
            printf(" ");

        /* Print one byte as 2-digit hex */
        printf("%.02x", *p);
    }

    printf("\n");
    return;
}


/* ------------------------------------------------------------
 * main()
 * ------------------------------------------------------------
 * Demonstrates RC4 encryption and decryption.
 * ------------------------------------------------------------
 */
int main() {

    /* Pointer to RC4 internal state */
    Arcfour *rc4;

    /* Key size and text size (in bytes) */
    uint16_t skey, stext;

    /* key and plaintext (normal text strings) */
    char *key, *from;

    /* Encrypted and decrypted data (binary buffers) */
    uint8_t *encrypted;
    uint8_t *decrypted;


    /* ------------------ Input Data ------------------ */

    /*
     * Encryption key.
     * RC4 accepts arbitrary byte sequences.
     */
    key = "tomatoes";
    skey = strlen(key);

    /*
     * Plaintext message to encrypt.
     */
    from = "Shall I compare thee to a summer's day?";
    stext = strlen(from);


    /* ---------------- Encryption Phase ---------------- */

    printf("Initializing encryption...\n"); F;

    /*
     * Initialize RC4 state using the key.
     * This runs the Key Scheduling Algorithm (KSA).
     */
    rc4 = rc4init((uint8_t *)key, skey);

    printf("done\n");

    /*
     * Show original plaintext.
     */
    printf("'%s'\n ->", from);

    /*
     * Encrypt plaintext:
     *
     * ciphertext[i] = plaintext[i] XOR keystream[i]
     */
    encrypted = rc4encrypt(rc4, (uint8_t *)from, stext);

    /* Print encrypted binary data in hex form */
    printbin(encrypted, stext);

    /* RC4 state no longer needed */
    rc4uninit(rc4);


    /* ---------------- Decryption Phase ---------------- */

    printf("Initializing decryption...\n"); F;

    /*
     * IMPORTANT:
     * RC4 must start from the SAME initial state
     * for successful decryption.
     */
    rc4 = rc4init((uint8_t *)key, skey);

    printf("done\n");

    /*
     * Decrypt:
     *
     * ciphertext XOR keystream = plaintext
     *
     * rc4decrypt is just an alias for rc4encrypt.
     */
    decrypted = rc4decrypt(rc4, encrypted, stext);

    /* Print recovered plaintext */
    printf("    -> '%s'\n", decrypted);


    /* ---------------- Cleanup ---------------- */

    /* Free RC4 state */
    rc4uninit(rc4);

    /* Free dynamically allocated buffers */
    free(encrypted);
    free(decrypted);

    return 0;
}
