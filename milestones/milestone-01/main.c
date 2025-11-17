#include <stdio.h>
#include <stdlib.h>
#include "calculator.h"

// Global memory variable
static float memory = 0.0f;

int main() {
    int choice, subchoice;
    float result, a, b;
    int int_a, int_b;

    printf("========================================\n");
    printf("     ADVANCED CALCULATOR v1.0\n");
    printf("========================================\n");
    printf("Your comprehensive calculation tool!\n\n");

    do {
        display_main_menu();

        if (!get_int_input(&choice, "Enter your choice (0-6): ")) {
            printf("Invalid input. Please enter a number.\n");
            continue;
        }

        switch (choice) {
            case 0:
                printf("Thank you for using Advanced Calculator!\n");
                break;

            case 1: // Basic Operations
                display_basic_ops_menu();
                if (get_int_input(&subchoice, "Choose operation (1-4, 0 to return): ")) {
                    if (subchoice >= 1 && subchoice <= 4) {
                        if (get_float_input(&a, "Enter first number: ") &&
                            get_float_input(&b, "Enter second number: ")) {

                            switch (subchoice) {
                                case 1:
                                    result = add(a, b);
                                    printf("%.2f + %.2f = %.2f\n", a, b, result);
                                    break;
                                case 2:
                                    result = subtract(a, b);
                                    printf("%.2f - %.2f = %.2f\n", a, b, result);
                                    break;
                                case 3:
                                    result = multiply(a, b);
                                    printf("%.2f * %.2f = %.2f\n", a, b, result);
                                    break;
                                case 4:
                                    if (divide(a, b, &result)) {
                                        printf("%.2f / %.2f = %.2f\n", a, b, result);
                                    } else {
                                        printf("Error: Division by zero!\n");
                                    }
                                    break;
                            }
                        }
                    }
                }
                break;

            case 2: // Advanced Operations
                printf("\nAdvanced Operations:\n");
                printf("1. Power (x^y)\n");
                printf("2. Square Root\n");
                printf("3. Factorial\n");
                printf("0. Return to main menu\n");

                if (get_int_input(&subchoice, "Choose operation (1-3, 0 to return): ")) {
                    switch (subchoice) {
                        case 1:
                            if (get_float_input(&a, "Enter base: ") &&
                                get_float_input(&b, "Enter exponent: ")) {
                                result = power(a, b);
                                printf("%.2f ^ %.2f = %.2f\n", a, b, result);
                            }
                            break;
                        case 2:
                            if (get_float_input(&a, "Enter number: ")) {
                                if (square_root(a, &result)) {
                                    printf("√%.2f = %.2f\n", a, result);
                                } else {
                                    printf("Error: Cannot calculate square root of negative number!\n");
                                }
                            }
                            break;
                        case 3:
                            if (get_int_input(&int_a, "Enter non-negative integer: ")) {
                                if (int_a >= 0) {
                                    result = factorial(int_a);
                                    if (result >= 0) {
                                        printf("%d! = %.0f\n", int_a, result);
                                    } else {
                                        printf("Error: Factorial too large!\n");
                                    }
                                } else {
                                    printf("Error: Factorial of negative number not defined!\n");
                                }
                            }
                            break;
                    }
                }
                break;

            case 3: // Number Theory
                printf("\nNumber Theory Operations:\n");
                printf("1. Greatest Common Divisor (GCD)\n");
                printf("2. Least Common Multiple (LCM)\n");
                printf("3. Prime Number Check\n");
                printf("0. Return to main menu\n");

                if (get_int_input(&subchoice, "Choose operation (1-3, 0 to return): ")) {
                    switch (subchoice) {
                        case 1:
                            if (get_int_input(&int_a, "Enter first integer: ") &&
                                get_int_input(&int_b, "Enter second integer: ")) {
                                result = gcd(int_a, int_b);
                                printf("GCD(%d, %d) = %.0f\n", int_a, int_b, result);
                            }
                            break;
                        case 2:
                            if (get_int_input(&int_a, "Enter first integer: ") &&
                                get_int_input(&int_b, "Enter second integer: ")) {
                                result = lcm(int_a, int_b);
                                printf("LCM(%d, %d) = %.0f\n", int_a, int_b, result);
                            }
                            break;
                        case 3:
                            if (get_int_input(&int_a, "Enter integer to check: ")) {
                                if (is_prime(int_a)) {
                                    printf("%d is a prime number.\n", int_a);
                                } else {
                                    printf("%d is not a prime number.\n", int_a);
                                }
                            }
                            break;
                    }
                }
                break;

            case 4: // Unit Conversions
                display_conversion_menu();
                if (get_int_input(&subchoice, "Choose conversion (1-4, 0 to return): ")) {
                    switch (subchoice) {
                        case 1:
                            if (get_float_input(&a, "Enter temperature in Celsius: ")) {
                                result = celsius_to_fahrenheit(a);
                                printf("%.2f°C = %.2f°F\n", a, result);
                            }
                            break;
                        case 2:
                            if (get_float_input(&a, "Enter temperature in Fahrenheit: ")) {
                                result = fahrenheit_to_celsius(a);
                                printf("%.2f°F = %.2f°C\n", a, result);
                            }
                            break;
                        case 3:
                            if (get_float_input(&a, "Enter length in inches: ")) {
                                result = inches_to_cm(a);
                                printf("%.2f inches = %.2f cm\n", a, result);
                            }
                            break;
                        case 4:
                            if (get_float_input(&a, "Enter weight in pounds: ")) {
                                result = pounds_to_kg(a);
                                printf("%.2f pounds = %.2f kg\n", a, result);
                            }
                            break;
                    }
                }
                break;

            case 5: // Memory Functions
                printf("\nMemory Operations:\n");
                printf("Current memory: %.4f\n", recall_memory());
                printf("1. Store value in memory\n");
                printf("2. Recall value from memory\n");
                printf("3. Clear memory\n");
                printf("0. Return to main menu\n");

                if (get_int_input(&subchoice, "Choose operation (1-3, 0 to return): ")) {
                    switch (subchoice) {
                        case 1:
                            if (get_float_input(&a, "Enter value to store: ")) {
                                store_memory(a);
                                printf("Stored %.4f in memory.\n", a);
                            }
                            break;
                        case 2:
                            printf("Memory value: %.4f\n", recall_memory());
                            break;
                        case 3:
                            clear_memory();
                            printf("Memory cleared.\n");
                            break;
                    }
                }
                break;

            case 6: // Show current memory
                printf("Current memory value: %.4f\n", recall_memory());
                break;

            default:
                printf("Invalid choice! Please enter a number between 0 and 6.\n");
                break;
        }

        if (choice != 0) {
            printf("\nPress Enter to continue...");
            clear_input_buffer();
            getchar();
            printf("\n");
        }

    } while (choice != 0);

    return 0;
}

// Memory operations implementation
void store_memory(float value) {
    memory = value;
}

float recall_memory(void) {
    return memory;
}

void clear_memory(void) {
    memory = 0.0f;
}