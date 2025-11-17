#include <stdio.h>

// Function prototypes
float add(float a, float b);
float subtract(float a, float b);
float multiply(float a, float b);
int divide(float a, float b, float *result);

int main() {
    float x = 15.0f, y = 3.0f;
    float result;

    printf("Calculator Functions Demo\n");
    printf("=========================\n");

    printf("Numbers: %.1f and %.1f\n", x, y);

    printf("%.1f + %.1f = %.1f\n", x, y, add(x, y));
    printf("%.1f - %.1f = %.1f\n", x, y, subtract(x, y));
    printf("%.1f * %.1f = %.1f\n", x, y, multiply(x, y));

    int status = divide(x, y, &result);
    if (status == 0) {
        printf("%.1f / %.1f = %.1f\n", x, y, result);
    } else {
        printf("Error: Division by zero!\n");
    }

    // Test division by zero
    status = divide(x, 0.0f, &result);
    if (status != 0) {
        printf("Division by zero properly handled!\n");
    }

    return 0;
}

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
        return -1; // Error code for division by zero
    }

    *result = a / b;
    return 0; // Success
}