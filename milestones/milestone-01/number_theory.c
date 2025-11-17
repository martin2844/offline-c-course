#include "calculator.h"

// Greatest Common Divisor using Euclidean algorithm
int gcd(int a, int b) {
    a = (a < 0) ? -a : a; // Absolute value
    b = (b < 0) ? -b : b; // Absolute value

    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }

    return a;
}

// Least Common Multiple
int lcm(int a, int b) {
    if (a == 0 || b == 0) {
        return 0;
    }

    return (a / gcd(a, b)) * b;
}

// Prime number check
int is_prime(int number) {
    if (number <= 1) {
        return 0; // Not prime
    }

    if (number == 2) {
        return 1; // Prime
    }

    if (number % 2 == 0) {
        return 0; // Not prime
    }

    for (int i = 3; i * i <= number; i += 2) {
        if (number % i == 0) {
            return 0; // Not prime
        }
    }

    return 1; // Prime
}