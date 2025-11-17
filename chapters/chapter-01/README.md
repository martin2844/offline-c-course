# Chapter 1: Getting Started with C

## Learning Objectives
By the end of this chapter, you will be able to:
- Understand what C is and why it's important
- Write, compile, and run your first C program
- Understand the basic structure of a C program
- Use comments and basic formatting
- Handle compilation errors

## What is C?

C is a powerful, general-purpose programming language created by Dennis Ritchie at Bell Labs in 1972. It's known for:
- **Efficiency**: Runs close to the hardware
- **Portability**: Runs on virtually every platform
- **Influence**: Inspired many other languages (C++, Java, Python, etc.)
- **Systems programming**: Used for operating systems, embedded systems, and performance-critical applications

### Why Learn C?
- Deep understanding of how computers work
- Better memory management skills
- Foundation for learning other languages
- Essential for systems programming and embedded development

## Your First C Program

Let's start with the classic "Hello, World!" program.

### The Code
Create a file called `hello.c`:

```c
#include <stdio.h>

int main() {
    printf("Hello, World!\n");
    return 0;
}
```

### Breaking It Down

**Line 1: `#include <stdio.h>`**
- `#include` is a preprocessor directive
- `stdio.h` stands for "Standard Input/Output"
- Gives us access to functions like `printf()`

**Line 3: `int main()`**
- Every C program has a `main()` function
- This is where program execution begins
- `int` means the function returns an integer

**Line 4: `{`**
- Opens the function body
- Code goes between `{` and `}`

**Line 5: `printf("Hello, World!\n");`**
- `printf()` prints text to the console
- `\n` creates a new line
- `;` ends the statement

**Line 6: `return 0;`**
- Returns 0 to indicate successful execution
- Non-zero values typically indicate errors

**Line 7: `}`**
- Closes the function body

## Compiling and Running

### Basic Compilation
```bash
clang hello.c -o hello
```
- `clang` is the compiler
- `hello.c` is your source file
- `-o hello` specifies the output executable name

### Running the Program
```bash
./hello
```
Output:
```
Hello, World!
```

### Compilation with Warnings (Recommended)
```bash
clang -Wall -Wextra -g hello.c -o hello
```
- `-Wall`: Enable most warnings
- `-Wextra`: Enable additional warnings
- `-g`: Include debug information

## Understanding the Compilation Process

1. **Preprocessing**: Handles `#include` directives
2. **Compilation**: Converts C code to assembly
3. **Assembly**: Converts assembly to machine code
4. **Linking**: Connects libraries and creates executable

## Comments

Comments explain your code and are ignored by the compiler.

### Single-line Comments
```c
// This is a single-line comment
int age = 25; // Declare age variable
```

### Multi-line Comments
```c
/*
 * This is a multi-line comment
 * It can span multiple lines
 * Useful for detailed explanations
 */
```

## Basic Program Structure

```c
#include <stdio.h>  // Include standard library

// Global variables (optional)
int global_variable = 100;

// Function declaration (optional)
void my_function();

int main() {
    // Local variables
    int local_variable = 50;

    // Function calls
    printf("Global: %d, Local: %d\n", global_variable, local_variable);
    my_function();

    return 0;  // Success
}

// Function definition
void my_function() {
    printf("This is my function!\n");
}
```

## Common Compilation Errors and Solutions

### Error: "implicit declaration of function 'printf'"
**Cause**: Missing `#include <stdio.h>`
**Solution**: Add `#include <stdio.h>` at the top

### Error: "syntax error near unexpected token '}'"
**Cause**: Missing semicolon or mismatched braces
**Solution**: Check all statements end with `;` and braces match

### Error: "undefined reference to 'main'"
**Cause**: No `main()` function
**Solution**: Ensure you have `int main() { }` in your code

### Error: "Permission denied"
**Cause**: Can't create output file
**Solution**: Check directory permissions or choose different output name

## Exercises

### Exercise 1.1: Personal Greeting
Create a program that prints your name and a welcome message.

**Expected Output:**
```
Welcome to C Programming, [Your Name]!
Let's start learning!
```

### Exercise 1.2: Program Information
Create a program that prints information about the program.

**Expected Output:**
```
=== Program Information ===
Name: My First C Program
Version: 1.0
Author: [Your Name]
Purpose: Learning C programming
==========================
```

### Exercise 1.3: ASCII Art
Create a program that prints simple ASCII art.

**Expected Output:**
```
   *   *
  * * * *
 *  ***  *
*         *
```

### Exercise 1.4: Comment Practice
Take Exercise 1.1 and add appropriate comments explaining each part of the program.

### Exercise 1.5: Compilation Practice
Create a file with deliberate errors and practice identifying and fixing them:
1. Missing semicolon
2. Missing include
3. Mismatched braces
4. Misspelled function name

## Challenge Problems

### Challenge 1.1: Multi-Language Greeting
Create a program that prints greetings in 3 different languages.

### Challenge 1.2: Program Banner
Create a program that prints a detailed banner for your C course journey.

## Best Practices

1. **Always use warning flags** when compiling: `clang -Wall -Wextra`
2. **Add meaningful comments** to explain complex logic
3. **Use consistent indentation** (4 spaces is common)
4. **Choose descriptive variable names**
5. **Compile frequently** to catch errors early
6. **Keep programs simple** when learning

## Quick Reference

### Common Include Files
- `#include <stdio.h>` - Standard input/output
- `#include <stdlib.h>` - Standard library functions
- `#include <string.h>` - String manipulation
- `#include <math.h>` - Mathematical functions

### Useful Compiler Flags
- `-Wall` - Enable most warnings
- `-Wextra` - Enable extra warnings
- `-g` - Include debug information
- `-O2` - Optimize for speed
- `-std=c99` - Use C99 standard

### Basic printf() Format Specifiers
- `%d` - Integer
- `%f` - Float
- `%c` - Character
- `%s` - String
- `%p` - Pointer address

## Next Steps
Once you're comfortable with:
- Writing basic C programs
- Compiling and running code
- Understanding program structure
- Fixing simple compilation errors

You're ready to move to **Chapter 2: Variables and Data Types**!