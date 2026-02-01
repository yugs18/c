/* numbers.c */
#include <stdio.h>

int main() {
    int x, y;

    printf("Please input a number: ");
    scanf("%d", &x);

    printf("Please input a number: ");
    scanf("%d", &y);

    int result = x + y;
    printf("The sum of %d and %d is %d\n", x, y, result);

    return 0;
}