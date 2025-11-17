#include <stdio.h>

// Function prototypes
long factorial_recursive(int n);
long factorial_iterative(int n);
int fibonacci_recursive(int n);
int fibonacci_iterative(int n);
int gcd_recursive(int a, int b);

int main() {
    int num = 5;

    printf("Recursion Demonstration\n");
    printf("=======================\n");

    // Factorial examples
    printf("\nFactorial of %d:\n", num);
    printf("Recursive: %ld\n", factorial_recursive(num));
    printf("Iterative: %ld\n", factorial_iterative(num));

    // Fibonacci examples
    printf("\nFirst 10 Fibonacci numbers:\n");
    printf("Recursive: ");
    for (int i = 0; i < 10; i++) {
        printf("%d ", fibonacci_recursive(i));
    }
    printf("\n");

    printf("Iterative: ");
    for (int i = 0; i < 10; i++) {
        printf("%d ", fibonacci_iterative(i));
    }
    printf("\n");

    // GCD example
    int a = 48, b = 18;
    printf("\nGCD of %d and %d: %d\n", a, b, gcd_recursive(a, b));

    return 0;
}

// Recursive factorial function
long factorial_recursive(int n) {
    if (n <= 1) {
        return 1;
    }
    return n * factorial_recursive(n - 1);
}

// Iterative factorial function
long factorial_iterative(int n) {
    long result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

// Recursive Fibonacci function
int fibonacci_recursive(int n) {
    if (n <= 1) {
        return n;
    }
    return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2);
}

// Iterative Fibonacci function
int fibonacci_iterative(int n) {
    if (n <= 1) return n;

    int prev = 0, curr = 1;
    for (int i = 2; i <= n; i++) {
        int next = prev + curr;
        prev = curr;
        curr = next;
    }
    return curr;
}

// Recursive GCD function using Euclidean algorithm
int gcd_recursive(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd_recursive(b, a % b);
}