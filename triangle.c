/* triangle.c */
#include <stdio.h>

int area_triangle(int base, int height) {
    return (base * height) / 2;
}

int main() {
    int b, h, a;

    printf("Base: ");
    fflush(stdout);
    scanf("%d", &b);

    printf("Height: ");
    fflush(stdout);
    scanf("%d", &h);

    a = area_triangle(b, h);
    printf("Area: %d\n", a);

    return 0;
}