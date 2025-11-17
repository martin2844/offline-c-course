# Chapter 2: Variables and Data Types

## Learning Objectives
By the end of this chapter, you will be able to:
- Understand and use different data types in C
- Declare and initialize variables
- Use constants and the `const` keyword
- Perform type casting
- Understand variable scope
- Use the sizeof operator

## Introduction to Variables

A variable is a named storage location in memory that holds a value. In C, you must declare variables before using them.

### Variable Declaration Syntax
```c
data_type variable_name;
data_type variable_name = initial_value;
```

## Basic Data Types

### Integer Types
```c
#include <stdio.h>

int main() {
    // Basic integers
    int age = 25;           // Usually 4 bytes
    short small_num = 100;  // Usually 2 bytes
    long large_num = 1000000L;  // Usually 8 bytes on modern systems
    long long very_large = 9000000000LL;  // At least 8 bytes

    // Unsigned integers (only non-negative values)
    unsigned int positive = 42;
    unsigned short small_positive = 10;
    unsigned long large_positive = 1000000UL;

    printf("Age: %d\n", age);
    printf("Small number: %d\n", small_num);
    printf("Large number: %ld\n", large_num);
    printf("Very large: %lld\n", very_large);
    printf("Positive: %u\n", positive);

    return 0;
}
```

### Floating-Point Types
```c
#include <stdio.h>

int main() {
    float price = 19.99f;         // 4 bytes, single precision
    double precise = 3.1415926535; // 8 bytes, double precision
    long double very_precise = 1.23456789012345L; // Extended precision

    printf("Price: %.2f\n", price);
    printf("Precise: %.10f\n", precise);
    printf("Very precise: %.15Lf\n", very_precise);

    return 0;
}
```

### Character Type
```c
#include <stdio.h>

int main() {
    char grade = 'A';           // Single character
    char initial = 'M';         // Another single character

    printf("Grade: %c\n", grade);
    printf("Initial: %c\n", initial);
    printf("ASCII value of '%c': %d\n", grade, grade);

    return 0;
}
```

## Data Type Ranges and Sizes

### Checking Data Type Sizes
```c
#include <stdio.h>

int main() {
    printf("Data Type Sizes (in bytes):\n");
    printf("char: %zu byte(s)\n", sizeof(char));
    printf("short: %zu byte(s)\n", sizeof(short));
    printf("int: %zu byte(s)\n", sizeof(int));
    printf("long: %zu byte(s)\n", sizeof(long));
    printf("long long: %zu byte(s)\n", sizeof(long long));
    printf("float: %zu byte(s)\n", sizeof(float));
    printf("double: %zu byte(s)\n", sizeof(double));
    printf("long double: %zu byte(s)\n", sizeof(long double));

    return 0;
}
```

### Common Data Type Ranges (on most modern systems)
| Type | Size | Range |
|------|------|-------|
| `char` | 1 byte | -128 to 127 or 0 to 255 |
| `unsigned char` | 1 byte | 0 to 255 |
| `short` | 2 bytes | -32,768 to 32,767 |
| `unsigned short` | 2 bytes | 0 to 65,535 |
| `int` | 4 bytes | -2,147,483,648 to 2,147,483,647 |
| `unsigned int` | 4 bytes | 0 to 4,294,967,295 |
| `long` | 8 bytes | -9,223,372,036,854,775,808 to 9,223,372,036,854,775,807 |
| `float` | 4 bytes | ±3.4e±38 (7 digits) |
| `double` | 8 bytes | ±1.7e±308 (15 digits) |

## Variable Initialization

### Different Initialization Methods
```c
#include <stdio.h>

int main() {
    // Method 1: Declaration and initialization
    int count = 10;

    // Method 2: Declaration first, initialization later
    int total;
    total = 100;

    // Method 3: Multiple declarations and initializations
    int x = 5, y = 10, z = 15;

    // Method 4: Declaration with default value (uninitialized)
    int uninitialized_var;  // Contains garbage value!

    printf("Count: %d\n", count);
    printf("Total: %d\n", total);
    printf("x: %d, y: %d, z: %d\n", x, y, z);
    printf("Uninitialized (garbage): %d\n", uninitialized_var);  // Dangerous!

    return 0;
}
```

## Constants

### Using `#define`
```c
#include <stdio.h>

#define PI 3.14159
#define MAX_STUDENTS 100
#define COMPANY_NAME "Tech Corp"

int main() {
    float radius = 5.0;
    float area = PI * radius * radius;

    printf("Company: %s\n", COMPANY_NAME);
    printf("Max students: %d\n", MAX_STUDENTS);
    printf("Area of circle: %.2f\n", area);

    return 0;
}
```

### Using `const` Keyword
```c
#include <stdio.h>

int main() {
    const int MAX_SCORE = 100;
    const float TAX_RATE = 0.08f;
    const char WELCOME[] = "Welcome to our program";

    int score = 85;
    float tax = score * TAX_RATE;

    printf("Score: %d/%d\n", score, MAX_SCORE);
    printf("Tax: $%.2f\n", tax);
    printf("%s\n", WELCOME);

    // MAX_SCORE = 200;  // Error: cannot modify const variable

    return 0;
}
```

## Type Casting

### Implicit Type Casting (Automatic)
```c
#include <stdio.h>

int main() {
    int int_value = 5;
    float float_value = 2.5f;
    double result;

    // int is promoted to float, then result is promoted to double
    result = int_value + float_value;
    printf("Result: %f\n", result);

    // float is truncated to int
    int truncated = float_value + 1;  // 2.5 + 1 = 3.5 → truncated to 3
    printf("Truncated: %d\n", truncated);

    return 0;
}
```

### Explicit Type Casting
```c
#include <stdio.h>

int main() {
    int a = 5, b = 2;

    // Without casting: integer division
    int result1 = a / b;  // 5 / 2 = 2 (integer division)
    printf("Integer division: %d\n", result1);

    // With casting: floating-point division
    float result2 = (float)a / b;  // 5.0 / 2 = 2.5
    printf("Floating-point division: %.1f\n", result2);

    // Another way
    float result3 = a / (float)b;  // 5 / 2.0 = 2.5
    printf("Floating-point division: %.1f\n", result3);

    return 0;
}
```

## Variable Scope

### Local vs Global Variables
```c
#include <stdio.h>

// Global variable - accessible throughout the program
int global_var = 100;

void function1() {
    // Local variable - only accessible within function1
    int local_var = 10;
    printf("In function1 - global_var: %d, local_var: %d\n", global_var, local_var);
}

void function2() {
    // Different local variable with same name
    int local_var = 20;
    global_var = 200;  // Can modify global variable

    printf("In function2 - global_var: %d, local_var: %d\n", global_var, local_var);
}

int main() {
    int local_var = 30;  // Another local variable

    printf("In main - global_var: %d, local_var: %d\n", global_var, local_var);

    function1();
    function2();

    printf("Back in main - global_var: %d, local_var: %d\n", global_var, local_var);

    return 0;
}
```

### Block Scope
```c
#include <stdio.h>

int main() {
    int outer_var = 10;

    printf("Outside block: outer_var = %d\n", outer_var);

    {
        int inner_var = 20;
        int outer_var = 30;  // Shadows the outer outer_var

        printf("Inside block: outer_var = %d, inner_var = %d\n", outer_var, inner_var);
    }

    // inner_var is not accessible here
    printf("Outside block: outer_var = %d\n", outer_var);

    return 0;
}
```

## Input and Output with Variables

### Using `scanf()` for Input
```c
#include <stdio.h>

int main() {
    int age;
    float height;
    char initial;

    printf("Enter your age: ");
    scanf("%d", &age);

    printf("Enter your height (in feet): ");
    scanf("%f", &height);

    printf("Enter your initial: ");
    scanf(" %c", &initial);  // Note the space before %c

    printf("Hello %c., you are %d years old and %.1f feet tall.\n",
           initial, age, height);

    return 0;
}
```

### Important `scanf()` Notes
- Always use `&` before variable names (except for arrays/strings)
- For characters, use `" %c"` to skip whitespace
- Always check the return value of `scanf()` in real programs

## Best Practices

1. **Initialize variables** when you declare them
2. **Use meaningful variable names** (`age` instead of `a`, `user_count` instead of `uc`)
3. **Choose appropriate data types** (don't use `int` for everything)
4. **Use constants** for values that don't change
5. **Be careful with type casting** to avoid data loss
6. **Minimize global variables** to avoid naming conflicts

## Common Errors and Solutions

### Error: "use of undeclared identifier"
**Cause**: Variable not declared or out of scope
**Solution**: Declare the variable before use, check scope

### Error: "division by zero"
**Cause**: Dividing by zero in your calculations
**Solution**: Check for zero before dividing

### Error: "format specifies type 'int' but the argument has type 'float'"
**Cause**: Mismatch between format specifier and variable type
**Solution**: Use correct format specifier (`%d` for int, `%f` for float)

### Warning: "variable 'x' is uninitialized"
**Cause**: Using variable before giving it a value
**Solution**: Initialize variable when declaring

## Exercises

### Exercise 2.1: Variable Declaration
Create a program that declares variables of different types and prints their values.

### Exercise 2.2: Size Calculator
Create a program that shows the size of all basic data types on your system.

### Exercise 2.3: Temperature Converter
Create a program that converts Celsius to Fahrenheit using the formula:
`F = (C * 9/5) + 32`

### Exercise 2.4: Circle Calculator
Create a program that calculates the area and circumference of a circle given its radius.

### Exercise 2.5: Variable Scope Demonstration
Create a program that demonstrates the difference between local and global variables.

## Challenge Problems

### Challenge 2.1: Data Type Explorer
Create a program that demonstrates the limits of each data type by finding the maximum and minimum values.

### Challenge 2.2: Simple Calculator
Create a program that takes two numbers and performs all basic arithmetic operations, demonstrating type casting.

## Quick Reference

### Format Specifiers for `printf()` and `scanf()`
| Specifier | Type | Example |
|-----------|------|---------|
| `%d` | int | `printf("%d", age);` |
| `%ld` | long | `printf("%ld", large_num);` |
| `%lld` | long long | `printf("%lld", very_large);` |
| `%u` | unsigned int | `printf("%u", positive);` |
| `%f` | float/double | `printf("%.2f", price);` |
| `%c` | char | `printf("%c", initial);` |
| `%s` | string | `printf("%s", name);` |
| `%p` | pointer | `printf("%p", &variable);` |
| `%zu` | size_t | `printf("%zu", sizeof(int));` |

### Type Casting Priority (highest to lowest)
1. Parentheses `()`
2. Unary operators (type casting `()`, `+`, `-`, `!`, `~`)
3. Multiplicative `*`, `/`, `%`
4. Additive `+`, `-`
5. Relational `<`, `<=`, `>`, `>=`
6. Equality `==`, `!=`
7. Logical AND `&&`
8. Logical OR `||`
9. Assignment `=`, `+=`, `-=`, `*=`, `/=`, `%=`

## Next Steps
Once you're comfortable with:
- Using different data types appropriately
- Declaring and initializing variables
- Understanding variable scope
- Performing type casting
- Getting user input

You're ready to move to **Chapter 3: Control Flow**!