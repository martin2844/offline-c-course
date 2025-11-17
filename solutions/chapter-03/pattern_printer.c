#include <stdio.h>

int main() {
    int size, i, j;

    printf("Pattern Printer\n");
    printf("===============\n");
    printf("Enter the size of patterns (1-10): ");
    scanf("%d", &size);

    if (size < 1 || size > 10) {
        printf("Invalid size! Using size 5 instead.\n");
        size = 5;
    }

    // Right triangle
    printf("\n1. Right Triangle:\n");
    for (i = 1; i <= size; i++) {
        for (j = 1; j <= i; j++) {
            printf("* ");
        }
        printf("\n");
    }

    // Inverted right triangle
    printf("\n2. Inverted Right Triangle:\n");
    for (i = size; i >= 1; i--) {
        for (j = 1; j <= i; j++) {
            printf("* ");
        }
        printf("\n");
    }

    // Square
    printf("\n3. Square:\n");
    for (i = 1; i <= size; i++) {
        for (j = 1; j <= size; j++) {
            printf("* ");
        }
        printf("\n");
    }

    // Number pyramid
    printf("\n4. Number Pyramid:\n");
    for (i = 1; i <= size; i++) {
        // Print spaces
        for (j = 1; j <= size - i; j++) {
            printf("  ");
        }
        // Print numbers
        for (j = 1; j <= i; j++) {
            printf("%d ", j);
        }
        printf("\n");
    }

    // Diamond pattern (for odd sizes)
    if (size % 2 == 1) {
        printf("\n5. Diamond Pattern:\n");
        // Upper half
        for (i = 1; i <= size; i += 2) {
            for (j = 1; j <= (size - i) / 2; j++) {
                printf(" ");
            }
            for (j = 1; j <= i; j++) {
                printf("*");
            }
            printf("\n");
        }
        // Lower half
        for (i = size - 2; i >= 1; i -= 2) {
            for (j = 1; j <= (size - i) / 2; j++) {
                printf(" ");
            }
            for (j = 1; j <= i; j++) {
                printf("*");
            }
            printf("\n");
        }
    }

    return 0;
}