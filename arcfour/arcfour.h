/* ============================================================
 * arcfour.h
 * ------------------------------------------------------------
 * Header file for a simple RC4 (Arcfour) implementation.
 *
 * This file defines:
 *   - constants and macros
 *   - RC4 state structure
 *   - public API function prototypes
 *
 * RC4 is a stream cipher:
 *   encryption and decryption are the same operation.
 * ============================================================
 */

/*
 * Enable GNU-specific extensions before any system headers.
 * Needed for features like assert_perror().
 */
#define _GNU_SOURCE


/* ---------------- Standard Library Includes ---------------- */

#include <stdio.h>      /* printf(), perror() */
#include <unistd.h>     /* POSIX functions */
#include <stdlib.h>     /* malloc(), free(), exit() */
#include <string.h>     /* strlen(), memcpy() */
#include <stdint.h>     /* fixed-width integer types */
#include <assert.h>     /* assert(), assert_perror() */
#include <errno.h>      /* errno */


/* ---------------- Configuration Constants ---------------- */

/*
 * MS:
 * Used by rc4whitewash() macro.
 *
 * Represents the number of milliseconds of keystream
 * to discard (roughly). RC4’s early output bytes are
 * statistically biased, so many implementations discard
 * an initial portion ("RC4-drop").
 */
#define MS 500


/* ---------------- Utility Macros ---------------- */

/*
 * export:
 * Makes symbols visible outside shared libraries (.so).
 *
 * Useful when building this code as a shared object.
 */
#define export __attribute__((visibility("default")))


/*
 * RC4 is symmetric:
 *   encrypt == decrypt
 *
 * This macro aliases decryption directly to encryption.
 *
 * Example:
 *   rc4decrypt(state, data, len)
 * becomes:
 *   rc4encrypt(state, data, len)
 */
#define rc4decrypt rc4encrypt


/*
 * Free RC4 context memory.
 *
 * Wrapper macro for readability.
 */
#define rc4uninit(x) free(x)


/*
 * rc4whitewash(x, y)
 * ------------------
 * Discards early RC4 keystream bytes to reduce known
 * statistical biases (RC4-drop).
 *
 * Parameters:
 *   x → loop counter variable
 *   y → pointer to Arcfour state
 *
 * This repeatedly generates bytes and ignores them.
 *
 * NOTE:
 * - Implemented as a macro for speed.
 * - (volatile uint8_t) prevents compiler optimization
 *   from removing the calls.
 *
 * WARNING:
 * - Macro uses its argument variable directly.
 * - Ensure x is declared before calling.
 */
#define rc4whitewash(x, y) \
    for (x = 0; x < (MS * 1000000); x++) \
        (volatile uint8_t)rc4byte(y);


/* ---------------- RC4 State Structure ---------------- */

/*
 * Internal RC4 state.
 *
 * Members:
 *   i, j : indices used by the PRGA
 *   k    : last generated keystream byte (optional storage)
 *   s[256] : permutation array (core RC4 state)
 *
 * The S-box is continuously shuffled during encryption.
 */
struct s_arcfour {
    int i, j, k;
    uint8_t s[256];
};

/* Type alias for cleaner API usage */
typedef struct s_arcfour Arcfour;


/* ---------------- Public API ---------------- */

/*
 * rc4init()
 * ---------
 * Initializes RC4 state using a key.
 *
 * Parameters:
 *   key  → pointer to key bytes
 *   len  → key size in bytes
 *
 * Returns:
 *   Pointer to initialized Arcfour state.
 */
export Arcfour *rc4init(uint8_t *, uint16_t);


/*
 * rc4byte()
 * ---------
 * Generates a single byte of RC4 keystream.
 *
 * This performs one PRGA step.
 */
uint8_t rc4byte(Arcfour *);


/*
 * rc4encrypt()
 * ------------
 * Encrypts or decrypts data using RC4.
 *
 * Parameters:
 *   state     → initialized RC4 context
 *   input     → data buffer
 *   size      → number of bytes
 *
 * Returns:
 *   Newly allocated output buffer.
 *
 * NOTE:
 * Since RC4 is symmetric:
 *   calling this function on ciphertext
 *   produces plaintext.
 */
export uint8_t *rc4encrypt(Arcfour *, uint8_t *, uint16_t);
