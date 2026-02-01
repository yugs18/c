/* while.c */
#include <stdio.h>

int main() {
    int x;
    
    while(1) {
        printf("Enter a number (0 to exit): ");
        scanf("%d", &x);
        if (x == 0) {
            break;
        }
        printf("You entered: %d\n", x);
    }

    return 0;
}