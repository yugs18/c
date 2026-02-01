/* random.c */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int our_random_function(int max) {
    int x;

    x = rand() % max + 1;
    return x;
}

int main() {
    int random;

    srand(getpid());

    random = our_random_function(5);
    printf("%d", random);

    random = our_random_function(10);
    printf("%d", random);

    return 0;
}