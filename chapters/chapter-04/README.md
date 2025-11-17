# Chapter 4: Functions

## Learning Objectives
By the end of this chapter, you will be able to:
- Understand what functions are and why they're important
- Declare and define functions
- Pass parameters to functions and return values
- Use function prototypes
- Understand variable scope and lifetime
- Implement recursive functions
- Organize code with modular programming

## Introduction to Functions

A function is a reusable block of code that performs a specific task. Functions help you:
- **Organize code** into logical units
- **Reuse code** without duplication
- **Test code** in isolation
- **Maintain and debug** more easily
- **Break complex problems** into smaller pieces

## Basic Function Syntax

### Function Definition
```c
return_type function_name(parameter_list) {
    // Function body
    // Statements
    return value; // Only if return_type is not void
}
```

### Simple Example
```c
#include <stdio.h>

// Function definition
void say_hello() {
    printf("Hello, World!\n");
}

int main() {
    // Function call
    say_hello();
    say_hello();  // Call it again!

    return 0;
}
```

## Functions with Parameters and Return Values

### Function with Parameters
```c
#include <stdio.h>

// Function that takes parameters but returns nothing
void print_number(int num) {
    printf("The number is: %d\n", num);
}

int main() {
    print_number(42);
    print_number(100);

    return 0;
}
```

### Function with Return Value
```c
#include <stdio.h>

// Function that takes parameters and returns a value
int add(int a, int b) {
    return a + b;
}

int main() {
    int result = add(5, 3);
    printf("5 + 3 = %d\n", result);

    printf("10 + 20 = %d\n", add(10, 20));

    return 0;
}
```

### Function with Multiple Parameters
```c
#include <stdio.h>

// Function that calculates the area of a rectangle
float calculate_rectangle_area(float length, float width) {
    return length * width;
}

// Function that finds the maximum of three numbers
int find_max(int a, int b, int c) {
    int max = a;

    if (b > max) {
        max = b;
    }
    if (c > max) {
        max = c;
    }

    return max;
}

int main() {
    float area = calculate_rectangle_area(5.5, 3.2);
    printf("Rectangle area: %.2f\n", area);

    int maximum = find_max(10, 25, 15);
    printf("Maximum of 10, 25, 15 is: %d\n", maximum);

    return 0;
}
```

## Function Prototypes

### Why Use Prototypes?
Function prototypes tell the compiler about a function before it's defined, allowing you to:
- Call functions before they're defined
- Catch type mismatches at compile time
- Organize code more flexibly

### Basic Prototype Syntax
```c
#include <stdio.h>

// Function prototypes (declarations)
int multiply(int a, int b);
void print_message(char message[]);
float calculate_average(int a, int b, int c);

int main() {
    int result = multiply(6, 7);
    printf("6 * 7 = %d\n", result);

    print_message("Hello from main!");

    float avg = calculate_average(80, 90, 85);
    printf("Average: %.2f\n", avg);

    return 0;
}

// Function definitions
int multiply(int a, int b) {
    return a * b;
}

void print_message(char message[]) {
    printf("Message: %s\n", message);
}

float calculate_average(int a, int b, int c) {
    return (float)(a + b + c) / 3.0f;
}
```

## Parameter Passing Methods

### Pass by Value (Default)
C passes parameters by value, meaning functions receive copies of the arguments.

```c
#include <stdio.h>

void modify_value(int x) {
    x = 100;  // This only changes the local copy
    printf("Inside function: x = %d\n", x);
}

int main() {
    int original = 10;
    printf("Before function call: original = %d\n", original);

    modify_value(original);

    printf("After function call: original = %d\n", original);
    // original is still 10 because it was passed by value

    return 0;
}
```

### Pass by Reference (Using Pointers)
We'll cover this in detail in Chapter 6, but here's a preview:

```c
#include <stdio.h>

void modify_value(int *x) {  // Pointer parameter
    *x = 100;  // Dereference to modify original value
    printf("Inside function: *x = %d\n", *x);
}

int main() {
    int original = 10;
    printf("Before function call: original = %d\n", original);

    modify_value(&original);  // Pass address of original

    printf("After function call: original = %d\n", original);
    // original is now 100 because we passed its address

    return 0;
}
```

## Variable Scope and Lifetime

### Local Variables
```c
#include <stdio.h>

void function1() {
    int local_var = 10;  // Local to function1
    printf("In function1: local_var = %d\n", local_var);
}

void function2() {
    int local_var = 20;  // Different variable, same name
    printf("In function2: local_var = %d\n", local_var);
}

int main() {
    int local_var = 30;  // Different variable, same name
    printf("In main: local_var = %d\n", local_var);

    function1();
    function2();

    printf("Back in main: local_var = %d\n", local_var);

    return 0;
}
```

### Global Variables
```c
#include <stdio.h>

int global_var = 100;  // Global variable

void show_global() {
    printf("In show_global: global_var = %d\n", global_var);
}

void modify_global() {
    global_var = 200;
    printf("In modify_global: global_var = %d\n", global_var);
}

int main() {
    printf("In main (initial): global_var = %d\n", global_var);

    show_global();
    modify_global();
    show_global();

    printf("In main (final): global_var = %d\n", global_var);

    return 0;
}
```

### Static Variables
```c
#include <stdio.h>

void counter_function() {
    static int counter = 0;  // Static variable - keeps its value
    counter++;
    printf("This function has been called %d time(s)\n", counter);
}

int main() {
    // Call the function multiple times
    for (int i = 0; i < 5; i++) {
        counter_function();
    }

    return 0;
}
```

## Useful Math Functions

### Using the Math Library
```c
#include <stdio.h>
#include <math.h>  // Required for math functions
// Note: Compile with -lm flag: clang program.c -o program -lm

int main() {
    double x = 16.0;
    double y = 2.0;

    printf("Square root of %.1f: %.2f\n", x, sqrt(x));
    printf("%.1f to the power of %.1f: %.2f\n", x, y, pow(x, y));
    printf("Sine of %.1f radians: %.2f\n", y, sin(y));
    printf("Cosine of %.1f radians: %.2f\n", y, cos(y));
    printf("Absolute value of -5: %.2f\n", fabs(-5.0));
    printf("Ceiling of 4.3: %.2f\n", ceil(4.3));
    printf("Floor of 4.7: %.2f\n", floor(4.7));

    return 0;
}
```

### Custom Math Functions
```c
#include <stdio.h>

// Function to calculate factorial
long factorial(int n) {
    if (n < 0) {
        return -1;  // Error: factorial of negative number
    }

    long result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

// Function to check if a number is prime
int is_prime(int n) {
    if (n <= 1) return 0;
    if (n == 2) return 1;
    if (n % 2 == 0) return 0;

    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return 0;
    }
    return 1;
}

// Function to calculate GCD (Greatest Common Divisor)
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    printf("5! = %ld\n", factorial(5));
    printf("10! = %ld\n", factorial(10));

    printf("17 is prime: %s\n", is_prime(17) ? "Yes" : "No");
    printf("15 is prime: %s\n", is_prime(15) ? "Yes" : "No");

    printf("GCD of 48 and 18: %d\n", gcd(48, 18));

    return 0;
}
```

## Recursive Functions

### Understanding Recursion
A recursive function calls itself to solve a problem by breaking it down into smaller, similar problems.

### Factorial Example
```c
#include <stdio.h>

// Iterative factorial
long factorial_iterative(int n) {
    long result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

// Recursive factorial
long factorial_recursive(int n) {
    // Base case
    if (n <= 1) {
        return 1;
    }

    // Recursive case
    return n * factorial_recursive(n - 1);
}

int main() {
    int num = 5;

    printf("Iterative factorial of %d: %ld\n", num, factorial_iterative(num));
    printf("Recursive factorial of %d: %ld\n", num, factorial_recursive(num));

    return 0;
}
```

### Fibonacci Sequence
```c
#include <stdio.h>

// Recursive Fibonacci (inefficient but simple to understand)
int fibonacci_recursive(int n) {
    if (n <= 1) {
        return n;
    }
    return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2);
}

// Iterative Fibonacci (more efficient)
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

int main() {
    printf("First 10 Fibonacci numbers:\n");
    for (int i = 0; i < 10; i++) {
        printf("%d ", fibonacci_iterative(i));
    }
    printf("\n");

    return 0;
}
```

## Function Organization

### Grouping Related Functions
```c
#include <stdio.h>

// Geometry calculation functions
float circle_area(float radius) {
    return 3.14159f * radius * radius;
}

float rectangle_area(float length, float width) {
    return length * width;
}

float triangle_area(float base, float height) {
    return 0.5f * base * height;
}

// Utility functions
void print_separator() {
    printf("================================\n");
}

void print_area_result(const char shape[], float area) {
    printf("%s area: %.2f\n", shape, area);
}

int main() {
    float radius = 5.0f, length = 10.0f, width = 6.0f;
    float base = 8.0f, height = 4.0f;

    print_separator();

    float ca = circle_area(radius);
    print_area_result("Circle", ca);

    float ra = rectangle_area(length, width);
    print_area_result("Rectangle", ra);

    float ta = triangle_area(base, height);
    print_area_result("Triangle", ta);

    print_separator();

    return 0;
}
```

## Advanced Function Concepts

### Function Pointers (Introduction)
We'll cover these in depth in Chapter 6, but here's a basic example:

```c
#include <stdio.h>

// Simple functions
int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }
int multiply(int a, int b) { return a * b; }

// Function that takes another function as parameter
int calculate(int a, int b, int (*operation)(int, int)) {
    return operation(a, b);
}

int main() {
    int x = 10, y = 5;

    printf("%d + %d = %d\n", x, y, calculate(x, y, add));
    printf("%d - %d = %d\n", x, y, calculate(x, y, subtract));
    printf("%d * %d = %d\n", x, y, calculate(x, y, multiply));

    return 0;
}
```

### Default Arguments (Workaround)
C doesn't support default arguments directly, but we can simulate them:

```c
#include <stdio.h>

// Simulate default arguments using overloading-like approach
void print_message(const char msg[]) {
    print_message_with_count(msg, 1);
}

void print_message_with_count(const char msg[], int count) {
    for (int i = 0; i < count; i++) {
        printf("%s\n", msg);
    }
}

int main() {
    print_message("Hello");  // Uses default count of 1
    print_message_with_count("Hi there", 3);  // Custom count

    return 0;
}
```

## Error Handling in Functions

### Returning Error Codes
```c
#include <stdio.h>

#define SUCCESS 0
#define ERROR_DIVIDE_BY_ZERO -1
#define ERROR_NEGATIVE_NUMBER -2

// Function that returns error codes
int divide(int a, int b, float *result) {
    if (b == 0) {
        return ERROR_DIVIDE_BY_ZERO;
    }
    if (a < 0 || b < 0) {
        return ERROR_NEGATIVE_NUMBER;
    }

    *result = (float)a / b;
    return SUCCESS;
}

int main() {
    int a = 10, b = 2;
    float result;
    int status = divide(a, b, &result);

    switch (status) {
        case SUCCESS:
            printf("%d / %d = %.2f\n", a, b, result);
            break;
        case ERROR_DIVIDE_BY_ZERO:
            printf("Error: Division by zero!\n");
            break;
        case ERROR_NEGATIVE_NUMBER:
            printf("Error: Negative numbers not allowed!\n");
            break;
        default:
            printf("Unknown error!\n");
            break;
    }

    return 0;
}
```

## Best Practices

### Function Design Principles
1. **Single Responsibility**: Each function should do one thing well
2. **Descriptive Names**: Use verbs and clear, descriptive names
3. **Consistent Naming**: Follow a consistent naming convention
4. **Limit Parameters**: Too many parameters indicate the function might be doing too much
5. **Validate Input**: Always validate function parameters
6. **Document Functions**: Use comments to explain purpose and parameters

### Example of Good Function Design
```c
#include <stdio.h>

/**
 * Calculates the compound interest
 * @param principal Initial amount of money
 * @param rate Annual interest rate (as decimal, e.g., 0.05 for 5%)
 * @param years Number of years
 * @param compounds_per_year Number of times interest is compounded per year
 * @return Final amount after compound interest
 */
float calculate_compound_interest(float principal, float rate,
                                 int years, int compounds_per_year) {
    // Input validation
    if (principal <= 0 || rate < 0 || years < 0 || compounds_per_year <= 0) {
        return -1.0f;  // Error value
    }

    // Compound interest formula: A = P(1 + r/n)^(nt)
    float amount = principal;
    float period_rate = rate / compounds_per_year;
    int total_periods = years * compounds_per_year;

    for (int i = 0; i < total_periods; i++) {
        amount *= (1.0f + period_rate);
    }

    return amount;
}

int main() {
    float principal = 1000.0f;
    float rate = 0.05f;  // 5%
    int years = 10;
    int compounds_per_year = 12;  // Monthly

    float final_amount = calculate_compound_interest(principal, rate,
                                                   years, compounds_per_year);

    if (final_amount > 0) {
        printf("Initial: $%.2f\n", principal);
        printf("Final amount after %d years: $%.2f\n", years, final_amount);
        printf("Interest earned: $%.2f\n", final_amount - principal);
    } else {
        printf("Error: Invalid input parameters!\n");
    }

    return 0;
}
```

## Common Errors and Solutions

### Error: "implicit declaration of function"
**Cause**: Function not declared before use
**Solution**: Add function prototype before first use

### Error: "conflicting types for function"
**Cause**: Function prototype doesn't match definition
**Solution**: Ensure parameter types and return types match exactly

### Error: "function returns address of local variable"
**Cause**: Returning pointer to local variable
**Solution**: Use static allocation or pass pointer as parameter

### Warning: "control reaches end of non-void function"
**Cause**: Function doesn't return value on all paths
**Solution**: Ensure all code paths return appropriate value

## Exercises

### Exercise 4.1: Temperature Conversion Functions
Create functions to convert between Celsius, Fahrenheit, and Kelvin.

### Exercise 4.2: Basic Calculator Functions
Create functions for addition, subtraction, multiplication, and division with proper error handling.

### Exercise 4.3: Number Properties Functions
Create functions to check if a number is even, odd, prime, or perfect.

### Exercise 4.4: String Utility Functions
Create functions to find string length, reverse a string, and check if a string is a palindrome.

### Exercise 4.5: Array Functions
Create functions to find minimum, maximum, and average of an integer array.

## Challenge Problems

### Challenge 4.1: Advanced Calculator
Create a calculator that uses function pointers to perform operations.

### Challenge 4.2: Recursive Tower of Hanoi
Implement the Tower of Hanoi problem using recursion.

### Challenge 4.3: Mathematical Expression Parser
Create a simple expression parser that can evaluate basic mathematical expressions.

## Quick Reference

### Function Declaration
```c
return_type function_name(parameter_type parameter_name, ...);
```

### Function Definition
```c
return_type function_name(parameter_type parameter_name, ...) {
    // Function body
    return value; // if return_type is not void
}
```

### Common Standard Library Functions
- `printf()`, `scanf()` - Input/output (stdio.h)
- `sqrt()`, `pow()`, `sin()`, `cos()` - Math functions (math.h)
- `strlen()`, `strcpy()`, `strcmp()` - String functions (string.h)
- `malloc()`, `free()` - Memory allocation (stdlib.h)

## Next Steps
Once you're comfortable with:
- Writing and calling functions
- Passing parameters and returning values
- Understanding scope and lifetime
- Using recursive functions
- Organizing code with modular programming

You're ready to move to **Chapter 5: Arrays and Strings**!

You're also ready for **Milestone 1: Calculator Project** which will combine everything you've learned so far!