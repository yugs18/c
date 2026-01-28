/* pointer.c */
#include <stdio.h>
#include <string.h>

int main() {
    char str[32];
    char *p;

    strncpy(str, "I am yeah!!", 31);
    p = str; // point to the first character of str

    // p = p + 1; // move pointer to the second character

    printf("%c\n", *p);
    return 0;
}