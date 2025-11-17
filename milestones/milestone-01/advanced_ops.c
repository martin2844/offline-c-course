#include "calculator.h"
#include <math.h>

// Power function (base^exponent)
float power(float base, float exponent) {
    return powf(base, exponent);
}

// Square root function with error handling
int square_root(float number, float *result) {
    if (number < 0.0f) {
        return 0; // Error: square root of negative number
    }

    *result = sqrtf(number);
    return 1; // Success
}

// Factorial function
long factorial(int number) {
    if (number < 0) {
        return -1; // Error: factorial of negative number
    }

    if (number == 0 || number == 1) {
        return 1;
    }

    long result = 1;
    for (int i = 2; i <= number; i++) {
        result *= i;

        // Check for overflow
        if (result < 0) {
            return -1; // Error: overflow
        }
    }

    return result;
}