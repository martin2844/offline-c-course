#include <stdio.h>

// Function prototypes
int is_even(int num);
int is_odd(int num);
int is_prime(int num);
int is_perfect(int num);
int sum_of_divisors(int num);

int main() {
    int numbers[] = {6, 7, 28, 15, 2, 496, 1};
    int size = sizeof(numbers) / sizeof(numbers[0]);

    printf("Number Properties Analyzer\n");
    printf("==========================\n");

    for (int i = 0; i < size; i++) {
        int num = numbers[i];
        printf("\nNumber: %d\n", num);
        printf("  Even: %s\n", is_even(num) ? "Yes" : "No");
        printf("  Odd: %s\n", is_odd(num) ? "Yes" : "No");
        printf("  Prime: %s\n", is_prime(num) ? "Yes" : "No");
        printf("  Perfect: %s\n", is_perfect(num) ? "Yes" : "No");
    }

    return 0;
}

// Check if a number is even
int is_even(int num) {
    return num % 2 == 0;
}

// Check if a number is odd
int is_odd(int num) {
    return num % 2 != 0;
}

// Check if a number is prime
int is_prime(int num) {
    if (num <= 1) return 0;
    if (num == 2) return 1;
    if (num % 2 == 0) return 0;

    for (int i = 3; i * i <= num; i += 2) {
        if (num % i == 0) {
            return 0;
        }
    }
    return 1;
}

// Check if a number is perfect (equal to sum of its proper divisors)
int is_perfect(int num) {
    if (num <= 1) return 0;

    return sum_of_divisors(num) == num;
}

// Calculate sum of proper divisors (excluding the number itself)
int sum_of_divisors(int num) {
    int sum = 1; // 1 is always a divisor (for num > 1)

    if (num == 1) return 0;

    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            sum += i;
            if (i != num / i && num / i != num) {
                sum += num / i;
            }
        }
    }

    return sum;
}