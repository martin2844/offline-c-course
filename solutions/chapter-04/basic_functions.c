#include <stdio.h>

// Simple function with no parameters and no return value
void say_hello() {
    printf("Hello, World!\n");
}

// Function with parameters but no return value
void greet_person(char name[]) {
    printf("Hello, %s!\n", name);
}

// Function with parameters and return value
int add_numbers(int a, int b) {
    return a + b;
}

// Function that returns a floating point value
float multiply(float a, float b) {
    return a * b;
}

int main() {
    // Test all our functions
    printf("Testing basic functions:\n");
    printf("========================\n");

    say_hello();
    greet_person("Alice");
    greet_person("Bob");

    int sum = add_numbers(10, 25);
    printf("10 + 25 = %d\n", sum);

    float product = multiply(3.5f, 2.0f);
    printf("3.5 * 2.0 = %.2f\n", product);

    return 0;
}