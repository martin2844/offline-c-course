#include "calculator.h"

// Addition function
float add(float a, float b) {
    return a + b;
}

// Subtraction function
float subtract(float a, float b) {
    return a - b;
}

// Multiplication function
float multiply(float a, float b) {
    return a * b;
}

// Division function with error handling
int divide(float a, float b, float *result) {
    if (b == 0.0f) {
        return 0; // Error: division by zero
    }

    *result = a / b;
    return 1; // Success
}