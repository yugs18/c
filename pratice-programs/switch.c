/* switch.c */
#include <stdio.h>

int main() {
    int x;

    printf("Choose between 1. apple, 2. banana, 3. cherry: ");
    scanf("%d", &x);

    switch(x) {
        case 1:
            printf("You choose apple.\n");
            break;
        case 2:
            printf("You choose banana.\n");
            break;
        case 3:
            printf("You choose cherry.\n");
            break;
        default:
            printf("Invalid choice.\n");
    }

    return 0;
}