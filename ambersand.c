/* ambersand.c */
#include <stdio.h>

void addition(int a, int b, int *target) {
    *target = a + b;

    return;
}

int main() {
    int x, y, answer;

    x = 5, y = 15;

    addition(x, y, &answer);
    printf("The sum of %d and %d is %d\n", x, y, answer);

    return 0;
}