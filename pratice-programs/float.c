/* float.c */
#include <stdio.h>

int main() {
    // area = π * r^2
    float radius, pi = 3.14, area;

    printf("Enter the radius of the circle: ");
    scanf("%f", &radius);

    area = pi * radius * radius;
    printf("The area of the circle with radius %.2f is %.2f\n", radius, area);

    // area = height * base / 2
    float height, base, triangle_area;

    printf("Enter the height and base of the triangle: ");
    scanf("%f %f", &height, &base);

    triangle_area = (height * base) / 2;
    printf("The area of the triangle with height %.2f and base %.2f is %.2f\n", height, base, triangle_area);

    return 0;
}