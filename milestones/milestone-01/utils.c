#include "calculator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Get float input with validation
int get_float_input(float *value, const char *prompt) {
    char buffer[100];
    char *endptr;

    while (1) {
        printf("%s", prompt);
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            return 0; // Input error
        }

        // Remove trailing newline
        buffer[strcspn(buffer, "\n")] = '\0';

        // Convert string to float
        *value = strtof(buffer, &endptr);

        // Check if conversion was successful
        if (endptr == buffer) {
            printf("Invalid input. Please enter a number.\n");
        } else {
            return 1; // Success
        }
    }
}

// Get integer input with validation
int get_int_input(int *value, const char *prompt) {
    char buffer[100];
    char *endptr;

    while (1) {
        printf("%s", prompt);
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            return 0; // Input error
        }

        // Remove trailing newline
        buffer[strcspn(buffer, "\n")] = '\0';

        // Convert string to integer
        *value = strtol(buffer, &endptr, 10);

        // Check if conversion was successful
        if (endptr == buffer) {
            printf("Invalid input. Please enter an integer.\n");
        } else {
            return 1; // Success
        }
    }
}

// Clear input buffer
void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Menu display functions
void display_main_menu(void) {
    printf("\nMain Menu\n");
    printf("=========\n");
    printf("1. Basic Operations (+, -, *, /)\n");
    printf("2. Advanced Operations (^, √, !)\n");
    printf("3. Number Theory (GCD, LCM, Prime)\n");
    printf("4. Unit Conversions\n");
    printf("5. Memory Functions\n");
    printf("6. Show Current Memory\n");
    printf("0. Exit\n");
}

void display_basic_ops_menu(void) {
    printf("\nBasic Operations\n");
    printf("================\n");
    printf("1. Addition (+)\n");
    printf("2. Subtraction (-)\n");
    printf("3. Multiplication (*)\n");
    printf("4. Division (/)\n");
    printf("0. Return to main menu\n");
}

void display_advanced_ops_menu(void) {
    printf("\nAdvanced Operations\n");
    printf("===================\n");
    printf("1. Power (x^y)\n");
    printf("2. Square Root (√x)\n");
    printf("3. Factorial (x!)\n");
    printf("0. Return to main menu\n");
}

void display_conversion_menu(void) {
    printf("\nUnit Conversions\n");
    printf("=================\n");
    printf("1. Celsius to Fahrenheit\n");
    printf("2. Fahrenheit to Celsius\n");
    printf("3. Inches to Centimeters\n");
    printf("4. Pounds to Kilograms\n");
    printf("0. Return to main menu\n");
}