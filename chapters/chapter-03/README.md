# Chapter 3: Control Flow

## Learning Objectives
By the end of this chapter, you will be able to:
- Use conditional statements (if, else if, else)
- Understand and apply logical operators
- Use switch statements for multiple conditions
- Implement different types of loops (for, while, do-while)
- Use break and continue statements
- Understand operator precedence

## Conditional Statements

### if Statement
The simplest form of conditional execution.

```c
#include <stdio.h>

int main() {
    int age = 18;

    if (age >= 18) {
        printf("You are eligible to vote!\n");
    }

    return 0;
}
```

### if-else Statement
Execute one block if condition is true, another if false.

```c
#include <stdio.h>

int main() {
    int temperature = 25;

    if (temperature > 30) {
        printf("It's hot outside!\n");
    } else {
        printf("It's not too hot.\n");
    }

    return 0;
}
```

### if-else if-else Chain
Handle multiple conditions in sequence.

```c
#include <stdio.h>

int main() {
    int score = 85;

    printf("Your grade: ");
    if (score >= 90) {
        printf("A\n");
    } else if (score >= 80) {
        printf("B\n");
    } else if (score >= 70) {
        printf("C\n");
    } else if (score >= 60) {
        printf("D\n");
    } else {
        printf("F\n");
    }

    return 0;
}
```

## Logical Operators

### AND, OR, NOT Operators
```c
#include <stdio.h>

int main() {
    int age = 25;
    int has_license = 1; // 1 = true, 0 = false

    // AND operator (&&)
    if (age >= 18 && has_license) {
        printf("You can drive a car.\n");
    }

    // OR operator (||)
    int is_student = 1;
    int is_senior = 0;
    if (is_student || is_senior) {
        printf("You qualify for a discount.\n");
    }

    // NOT operator (!)
    int is_raining = 0;
    if (!is_raining) {
        printf("It's not raining. Good weather for a walk!\n");
    }

    // Complex conditions
    int temperature = 22;
    int humidity = 40;
    if (temperature >= 20 && temperature <= 25 && humidity >= 30 && humidity <= 50) {
        printf("Perfect weather conditions!\n");
    }

    return 0;
}
```

## Relational Operators

### Comparison Operators
```c
#include <stdio.h>

int main() {
    int a = 10, b = 20;

    printf("Relational Operators:\n");
    printf("%d == %d: %d\n", a, b, a == b);  // Equal
    printf("%d != %d: %d\n", a, b, a != b);  // Not equal
    printf("%d < %d: %d\n", a, b, a < b);    // Less than
    printf("%d > %d: %d\n", a, b, a > b);    // Greater than
    printf("%d <= %d: %d\n", a, b, a <= b);  // Less than or equal
    printf("%d >= %d: %d\n", a, b, a >= b);  // Greater than or equal

    return 0;
}
```

## Switch Statement

### Basic Switch
Useful when comparing a variable against multiple constant values.

```c
#include <stdio.h>

int main() {
    int day = 3;

    printf("Day %d is ", day);
    switch (day) {
        case 1:
            printf("Monday");
            break;
        case 2:
            printf("Tuesday");
            break;
        case 3:
            printf("Wednesday");
            break;
        case 4:
            printf("Thursday");
            break;
        case 5:
            printf("Friday");
            break;
        case 6:
            printf("Saturday");
            break;
        case 7:
            printf("Sunday");
            break;
        default:
            printf("Invalid day");
            break;
    }
    printf("\n");

    return 0;
}
```

### Switch with Fall-through
Multiple cases sharing the same code.

```c
#include <stdio.h>

int main() {
    int month = 4;

    printf("Month %d is in ", month);
    switch (month) {
        case 12:
        case 1:
        case 2:
            printf("Winter");
            break;
        case 3:
        case 4:
        case 5:
            printf("Spring");
            break;
        case 6:
        case 7:
        case 8:
            printf("Summer");
            break;
        case 9:
        case 10:
        case 11:
            printf("Fall");
            break;
        default:
            printf("Invalid month");
            break;
    }
    printf("\n");

    return 0;
}
```

## Loops

### for Loop
Best when you know how many iterations you need.

```c
#include <stdio.h>

int main() {
    printf("Counting with for loop:\n");
    for (int i = 1; i <= 5; i++) {
        printf("Count: %d\n", i);
    }

    printf("\nCounting backwards:\n");
    for (int i = 10; i >= 1; i--) {
        printf("%d ", i);
    }
    printf("\n");

    printf("\nMultiples of 3:\n");
    for (int i = 3; i <= 30; i += 3) {
        printf("%d ", i);
    }
    printf("\n");

    return 0;
}
```

### while Loop
Best when you don't know how many iterations you need.

```c
#include <stdio.h>

int main() {
    int count = 1;

    printf("Counting with while loop:\n");
    while (count <= 5) {
        printf("Count: %d\n", count);
        count++;
    }

    printf("\nUser input example:\n");
    int number;
    printf("Enter positive numbers (0 or negative to stop):\n");

    int sum = 0;
    while (1) { // Infinite loop
        scanf("%d", &number);
        if (number <= 0) {
            break; // Exit the loop
        }
        sum += number;
        printf("Current sum: %d\n", sum);
    }
    printf("Final sum: %d\n", sum);

    return 0;
}
```

### do-while Loop
Similar to while loop, but always executes at least once.

```c
#include <stdio.h>

int main() {
    int number;

    printf("do-while loop example:\n");
    do {
        printf("Enter a positive number (0 to quit): ");
        scanf("%d", &number);
        if (number > 0) {
            printf("You entered: %d\n", number);
        }
    } while (number > 0);

    printf("Program ended.\n");
    return 0;
}
```

## Loop Control Statements

### break Statement
Exits the current loop immediately.

```c
#include <stdio.h>

int main() {
    printf("Finding first multiple of 7 greater than 50:\n");
    for (int i = 51; ; i++) {
        if (i % 7 == 0) {
            printf("Found: %d\n", i);
            break;
        }
    }

    printf("\nSearching in array:\n");
    int numbers[] = {10, 25, 30, 45, 50, 65, 80};
    int target = 50;
    int found = 0;

    for (int i = 0; i < 7; i++) {
        if (numbers[i] == target) {
            printf("Found %d at index %d\n", target, i);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("%d not found in the array\n", target);
    }

    return 0;
}
```

### continue Statement
Skips the rest of the current iteration and continues with the next.

```c
#include <stdio.h>

int main() {
    printf("Printing odd numbers (skipping evens):\n");
    for (int i = 1; i <= 10; i++) {
        if (i % 2 == 0) {
            continue; // Skip even numbers
        }
        printf("%d ", i);
    }
    printf("\n");

    printf("\nProcessing positive numbers only:\n");
    int data[] = {15, -3, 8, -1, 12, -7, 20};
    for (int i = 0; i < 7; i++) {
        if (data[i] < 0) {
            printf("Skipping negative number: %d\n", data[i]);
            continue;
        }
        printf("Processing positive number: %d\n", data[i]);
    }

    return 0;
}
```

## Nested Loops and Conditional Statements

### Nested if Statements
```c
#include <stdio.h>

int main() {
    int age = 25;
    int has_license = 1;
    int has_car = 1;

    if (age >= 18) {
        printf("You are old enough to drive.\n");
        if (has_license) {
            printf("You have a license.\n");
            if (has_car) {
                printf("You can drive your car!\n");
            } else {
                printf("You can drive but need a car.\n");
            }
        } else {
            printf("You need to get a license first.\n");
        }
    } else {
        printf("You are too young to drive.\n");
    }

    return 0;
}
```

### Nested Loops
```c
#include <stdio.h>

int main() {
    printf("Multiplication table:\n");
    for (int i = 1; i <= 5; i++) {
        for (int j = 1; j <= 5; j++) {
            printf("%3d ", i * j);
        }
        printf("\n");
    }

    printf("\nRight triangle pattern:\n");
    for (int i = 1; i <= 5; i++) {
        for (int j = 1; j <= i; j++) {
            printf("* ");
        }
        printf("\n");
    }

    return 0;
}
```

## Operator Precedence

### Understanding Priority
Operators are evaluated in a specific order:

```c
#include <stdio.h>

int main() {
    int result;

    // High precedence: * and / before + and -
    result = 2 + 3 * 4;      // 2 + (3 * 4) = 14
    printf("2 + 3 * 4 = %d\n", result);

    // Use parentheses to change order
    result = (2 + 3) * 4;    // (2 + 3) * 4 = 20
    printf("(2 + 3) * 4 = %d\n", result);

    // Relational operators vs logical operators
    int age = 25;
    int score = 85;
    if (age > 18 && score > 80) {
        printf("Age > 18 AND score > 80: True\n");
    }

    // Complex expression with precedence
    int a = 5, b = 10, c = 3;
    result = a + b * c;       // 5 + (10 * 3) = 35
    printf("5 + 10 * 3 = %d\n", result);

    // Precedence table (high to low):
    // 1. () [] -> . ++ --
    // 2. * / %
    // 3. + -
    // 4. < <= > >=
    // 5. == !=
    // 6. &&
    // 7. ||
    // 8. = += -= *= /= %=

    return 0;
}
```

## Common Patterns

### Input Validation
```c
#include <stdio.h>

int main() {
    int age;

    do {
        printf("Enter your age (1-120): ");
        scanf("%d", &age);

        if (age < 1 || age > 120) {
            printf("Invalid age! Please try again.\n");
        }
    } while (age < 1 || age > 120);

    printf("Valid age entered: %d\n", age);
    return 0;
}
```

### Menu System
```c
#include <stdio.h>

int main() {
    int choice;
    float num1, num2;

    do {
        printf("\nSimple Calculator Menu:\n");
        printf("1. Addition\n");
        printf("2. Subtraction\n");
        printf("3. Multiplication\n");
        printf("4. Division\n");
        printf("5. Exit\n");
        printf("Enter your choice (1-5): ");
        scanf("%d", &choice);

        if (choice >= 1 && choice <= 4) {
            printf("Enter two numbers: ");
            scanf("%f %f", &num1, &num2);
        }

        switch (choice) {
            case 1:
                printf("%.2f + %.2f = %.2f\n", num1, num2, num1 + num2);
                break;
            case 2:
                printf("%.2f - %.2f = %.2f\n", num1, num2, num1 - num2);
                break;
            case 3:
                printf("%.2f * %.2f = %.2f\n", num1, num2, num1 * num2);
                break;
            case 4:
                if (num2 != 0) {
                    printf("%.2f / %.2f = %.2f\n", num1, num2, num1 / num2);
                } else {
                    printf("Error: Division by zero!\n");
                }
                break;
            case 5:
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
                break;
        }
    } while (choice != 5);

    return 0;
}
```

## Best Practices

1. **Use meaningful condition names**: Consider boolean variables for clarity
2. **Keep conditions simple**: Break complex conditions into multiple lines
3. **Use switch for constants**: Use switch instead of long if-else chains
4. **Avoid infinite loops**: Always have a clear exit condition
5. **Use appropriate loop types**:
   - `for` for known iterations
   - `while` for unknown iterations
   - `do-while` for at least one execution
6. **Indent consistently**: Use proper indentation for nested structures

## Common Errors and Solutions

### Error: "dangling else"
**Problem**: else associates with the nearest if
**Solution**: Use braces to clarify association

```c
// Wrong
if (condition1)
    if (condition2)
        statement1;
else
    statement2; // This else goes with if (condition2)

// Right
if (condition1) {
    if (condition2) {
        statement1;
    } else {
        statement2;
    }
}
```

### Error: Infinite loop
**Problem**: Loop condition never becomes false
**Solution**: Ensure loop variable changes appropriately

### Error: Off-by-one error
**Problem**: Using <= when you meant <, or vice versa
**Solution**: Test loop boundaries carefully

## Exercises

### Exercise 3.1: Number Classification
Create a program that classifies a number as positive, negative, or zero, and whether it's even or odd.

### Exercise 3.2: Grade Calculator
Create a program that takes a score (0-100) and assigns a letter grade (A-F) with appropriate messages.

### Exercise 3.3: Prime Number Checker
Create a program that determines if a number is prime.

### Exercise 3.4: Sum of Digits
Create a program that calculates the sum of digits of a given number.

### Exercise 3.5: Simple Menu System
Create a text-based menu with at least 5 options and input validation.

## Challenge Problems

### Challenge 3.1: Number Guessing Game
Create a number guessing game where the user tries to guess a random number (use a fixed number for offline practice).

### Challenge 3.2: Pattern Printer
Create a program that prints various patterns (triangles, diamonds, etc.) using nested loops.

### Challenge 3.3: Simple ATM Simulation
Create a program that simulates basic ATM operations with PIN validation.

## Quick Reference

### Conditional Operators
| Operator | Description | Example |
|----------|-------------|---------|
| `==` | Equal to | `x == y` |
| `!=` | Not equal to | `x != y` |
| `>` | Greater than | `x > y` |
| `<` | Less than | `x < y` |
| `>=` | Greater than or equal | `x >= y` |
| `<=` | Less than or equal | `x <= y` |
| `&&` | Logical AND | `x > 0 && y > 0` |
| `||` | Logical OR | `x > 0 || y > 0` |
| `!` | Logical NOT | `!(x == 0)` |

### Loop Structures
- **for loop**: `for (initialization; condition; increment)`
- **while loop**: `while (condition)`
- **do-while loop**: `do { } while (condition)`
- **break**: Exit loop immediately
- **continue**: Skip current iteration

## Next Steps
Once you're comfortable with:
- Using conditional statements appropriately
- Implementing different types of loops
- Understanding operator precedence
- Creating nested control structures
- Handling user input validation

You're ready to move to **Chapter 4: Functions**!