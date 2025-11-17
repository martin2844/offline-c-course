#include <stdio.h>

int main() {
    int number, i;
    int is_prime = 1; // Assume number is prime

    printf("Prime Number Checker\n");
    printf("====================\n");
    printf("Enter a positive integer: ");
    scanf("%d", &number);

    if (number <= 1) {
        printf("%d is not a prime number.\n", number);
    } else if (number == 2) {
        printf("2 is the smallest prime number.\n");
    } else {
        // Check for factors from 2 to sqrt(number)
        for (i = 2; i * i <= number; i++) {
            if (number % i == 0) {
                is_prime = 0; // Number is not prime
                break;
            }
        }

        if (is_prime) {
            printf("%d is a prime number.\n", number);
        } else {
            printf("%d is not a prime number (divisible by %d).\n", number, i);
        }
    }

    return 0;
}