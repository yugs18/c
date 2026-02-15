/* getnextline challenge */

#include <stdio.h>   // printf
#include <stdlib.h>  // malloc, free
#include <unistd.h>  // read

/* Maximum size for one returned line */
#define BUFSIZE 2048

/* Function prototypes */
char *zero(char *);
char *gnl(void);
int main(void);

/*
 * zero()
 * ------
 * Fills the allocated buffer with '\0' bytes.
 * This guarantees:
 *   - the string starts empty
 *   - safe printing with %s
 */
char *zero(char *p)
{
   unsigned int n;

   /* Set every byte in buffer to zero */
   for (n = 0; n < BUFSIZE; n++)
      p[n] = 0;

   /* Redundant (already zero), but explicit */
   *p = '\0';

   return p;
}

/*
 * gnl()
 * -----
 * Simplified get-next-line implementation.
 *
 * Behaviour:
 *   - Reads from stdin (fd = 0)
 *   - Reads one character at a time
 *   - Stops at newline, EOF, or full buffer
 *   - Returns a malloc'ed string
 *
 * IMPORTANT:
 *   - Caller must free() the returned pointer.
 */
char *gnl()
{
   unsigned int n;   // number of characters stored
   char *p;          // moving pointer (write position)
   char *s;          // start of allocated string
   int r;            // return value of read()

   n = 0;

   /* Allocate buffer for one line */
   s = p = malloc(BUFSIZE);
   if (!s)
      return NULL;   // allocation failed

   /* Initialize buffer with zeros */
   zero(s);

   /* Infinite loop: keep reading until line end */
   while (1)
   {
      /*
       * Read ONE byte from stdin into current position.
       * fd = 0 means standard input.
       */
      r = read(0, p, 1);

      /*
       * r < 1 means:
       *   - EOF (0)
       *   - error (-1)
       */
      if (r < 1)
      {
         /* No characters read at all -> return NULL */
         if (n < 1)
            return 0;
         else
            /* Return partial line at EOF */
            return s;
      }
      /* Prevent writing past buffer end */
      else if (n > (BUFSIZE - 2))
         return s;

      /*
       * Examine the character just read.
       */
      switch (*p)
      {
      case 0:
      case '\n':
         /*
          * End of line.
          * Replace newline with '\0'
          * so result becomes valid C string.
          */
         *p = 0;
         return s;
         break;

      case '\r':
         /*
          * Handle carriage return (Windows line endings).
          */
         *p = 0;
         break;

      default:
         /*
          * Normal character:
          * move forward for next write.
          */
         p++;
         n++;
      }
   }

   /* Safety return (never normally reached) */
   return (n < 1) ? 0 : s;
}

/*
 * main()
 * ------
 * Demonstration:
 *   - Reads two lines from stdin
 *   - Prints them
 *   - Frees allocated memory
 */
int main()
{
   char *p1, *p2;

   /* Read first line */
   p1 = gnl();

   /* Read second line */
   p2 = gnl();

   /* Print lines wrapped in quotes */
   printf("'%s'\n"
          "'%s'\n",
          p1, p2);

   /* Free memory returned by gnl() */
   free(p2);
   free(p1);

   return 0;
}
