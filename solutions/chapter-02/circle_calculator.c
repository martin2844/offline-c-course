#include <stdio.h>

#define PI 3.14159f

int main() {
    float radius, area, circumference;

    printf("Circle Calculator\n");
    printf("=================\n");
    printf("Enter the radius of the circle: ");
    scanf("%f", &radius);

    // Calculate area: π * r²
    area = PI * radius * radius;

    // Calculate circumference: 2 * π * r
    circumference = 2.0f * PI * radius;

    printf("\nResults for a circle with radius %.2f:\n", radius);
    printf("Area: %.4f square units\n", area);
    printf("Circumference: %.4f units\n", circumference);

    return 0;
}