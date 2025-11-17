#include <stdio.h>

int main() {
    int number, original_number, digit, sum = 0;

    printf("Sum of Digits Calculator\n");
    printf("========================\n");
    printf("Enter a positive integer: ");
    scanf("%d", &number);

    // Handle negative numbers
    if (number < 0) {
        number = -number; // Make it positive
    }

    original_number = number;

    if (number == 0) {
        printf("Sum of digits of 0 = 0\n");
    } else {
        while (number > 0) {
            digit = number % 10;  // Get the last digit
            sum += digit;         // Add it to the sum
            number /= 10;         // Remove the last digit
        }

        printf("Sum of digits of %d = %d\n", original_number, sum);
    }

    return 0;
}