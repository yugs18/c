/* if.c */
#include <stdio.h>

int main() {
    int velocity;

    printf("How fast you are driving in km/h?\n");
    scanf("%d", &velocity);

    if (velocity > 120) {
        printf("You are speeding! Slow down!\n");
    } else if (velocity < 40) {
        printf("You are driving too slow! Speed up!\n");
    } else {
        printf("You are driving at a safe speed.\n");
    }

    return 0;
}