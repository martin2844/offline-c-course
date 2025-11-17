#include <stdio.h>

int main() {
    int number;

    printf("Number Classifier\n");
    printf("================\n");
    printf("Enter an integer: ");
    scanf("%d", &number);

    printf("\nAnalysis of %d:\n", number);

    // Positive, negative, or zero
    if (number > 0) {
        printf("- It's a positive number\n");
    } else if (number < 0) {
        printf("- It's a negative number\n");
    } else {
        printf("- It's zero\n");
    }

    // Even or odd (only meaningful for non-zero)
    if (number != 0) {
        if (number % 2 == 0) {
            printf("- It's an even number\n");
        } else {
            printf("- It's an odd number\n");
        }
    } else {
        printf("- Zero is neither even nor odd in this context\n");
    }

    // Additional classifications
    if (number > 0) {
        if (number == 1) {
            printf("- It's the multiplicative identity\n");
        } else if (number == 2) {
            printf("- It's the smallest prime number\n");
        } else if (number % 3 == 0 && number != 3) {
            printf("- It's divisible by 3\n");
        }
    }

    return 0;
}