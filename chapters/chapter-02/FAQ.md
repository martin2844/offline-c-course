# Chapter 2: Variables and Data Types - FAQ

## Data Types

### Q: What's the difference between `int`, `float`, and `double`?
A:
- `int`: Stores whole numbers (e.g., 42, -17)
- `float`: Single-precision floating-point numbers (e.g., 3.14, -0.001)
- `double`: Double-precision floating-point numbers (more precise than float)

### Q: When should I use `float` vs `double`?
A: Use `double` by default - it's the standard on modern systems and provides better precision. Only use `float` when:
- You need to save memory in large arrays
- You're working with systems that require single precision
- Memory is extremely limited

### Q: What's the range of different integer types?
A: On most modern systems:
- `char`: -128 to 127 (or 0 to 255 if unsigned)
- `short`: -32,768 to 32,767
- `int`: -2,147,483,648 to 2,147,483,647
- `long`: Usually same as `int` or larger
- `long long`: -9,223,372,036,854,775,808 to 9,223,372,036,854,775,807

### Q: What does `unsigned` mean?
A: `unsigned` means the variable can only store non-negative values. This doubles the positive range but removes negative values. Example: `unsigned int` ranges from 0 to 4,294,967,295 instead of -2,147,483,648 to 2,147,483,647.

### Q: Should I use `char` for numbers or strings?
A: `char` can store either:
- A single character: `char letter = 'A';`
- A small integer: `char number = 42;`
For strings, use `char*` (pointer to char) or `char[]` (array of char).

### Q: What's the difference between `char` and `unsigned char`?
A: `char` can be signed (-128 to 127) or unsigned (0 to 255) depending on the compiler. `unsigned char` is always 0 to 255. Use `unsigned char` for raw byte data.

## Variables

### Q: Why do variables need to be declared before use?
A: The compiler needs to know the type and name of each variable to allocate memory and perform type checking. This prevents errors and enables optimizations.

### Q: What's the difference between declaration and initialization?
A:
- **Declaration**: `int x;` (allocates memory, value is undefined)
- **Initialization**: `int x = 5;` (allocates memory and sets initial value)

### Q: Why do uninitialized variables have "garbage" values?
A: When you declare a variable without initializing it, the memory contains whatever bits were there before. This is called "garbage" because it's unpredictable.

### Q: Should I always initialize variables?
A: YES! Always initialize variables to avoid undefined behavior. Common practice:
```c
int x = 0;           // Initialize to 0
double y = 0.0;      // Initialize to 0.0
char c = '\0';       // Initialize to null character
```

### Q: What's the difference between `const` and `#define`?
A:
- `const int MAX = 100;` - Type-safe variable, debuggable, respects scope
- `#define MAX 100` - Simple text replacement, no type checking, global scope

Prefer `const` in most cases.

## Type Casting

### Q: What is type casting?
A: Type casting converts a value from one type to another. Example: `double result = (double)numerator / denominator;`

### Q: Why does `5 / 2` give me 2 instead of 2.5?
A: Integer division truncates the decimal part. To get floating-point division:
```c
double result = 5.0 / 2.0;     // or
double result = (double)5 / 2;   // or
double result = 5 / (double)2;
```

### Q: What's implicit vs explicit type casting?
A:
- **Implicit**: Automatic conversion by compiler: `double d = 5;`
- **Explicit**: Manual conversion: `int i = (int)d;`

### Q: What happens when I cast a `double` to `int`?
A: The decimal part is truncated (not rounded). `int x = (int)3.99; // x = 3`

### Q: Is type casting safe?
A: It can be dangerous if the target type can't hold the value. Example: `char c = 300;` will cause overflow. Always check ranges when casting.

## Constants

### Q: What's the purpose of the `const` keyword?
A: `const` creates variables that cannot be modified after initialization. Benefits:
- Prevents accidental modification
- Allows compiler optimizations
- Makes code clearer (signifies intent)

### Q: Can `const` variables be used in array sizes?
A: In C99 and later, yes for variable-length arrays. But for compile-time constants, use `#define` or `enum`.

### Q: What's a literal vs a constant?
A:
- **Literal**: The actual value written in code: `int x = 42;` (42 is literal)
- **Constant**: A named variable that can't change: `const int MAX = 42;`

## Sizeof and Type Sizes

### Q: Why is `sizeof(char)` always 1?
A: By definition, `sizeof(char)` is exactly 1 byte in C. All other type sizes are relative to this.

### Q: Are integer sizes the same on all computers?
A: No! Integer sizes can vary by platform:
- `int` might be 16, 32, or 64 bits
- Always use `sizeof()` or `int32_t`, `int64_t` from `<stdint.h>` for specific sizes

### Q: What's the difference between `sizeof(int)` and `sizeof(int*)`?
A: `sizeof(int)` is the size of an integer (usually 4 bytes). `sizeof(int*)` is the size of a pointer to integer (usually 8 bytes on 64-bit systems).

### Q: Why use `size_t` instead of `int` for sizes?
A: `size_t` is guaranteed to be large enough to hold the size of any object. It's unsigned and the return type of `sizeof()`. Use it for array sizes, loop counters, etc.

## Common Mistakes

### Q: Why do I get "format specifier" warnings?
A: You're using the wrong format specifier in `printf`. Common matches:
```c
printf("%d", int_var);     // %d for int
printf("%f", float_var);   // %f for float
printf("%lf", double_var); // %lf for double
printf("%c", char_var);    // %c for char
printf("%s", string_var);  // %s for string (char*)
```

### Q: What does "integer overflow" mean?
A: When you store a value larger than the type can hold. Example: `char c = 300;` will wrap around to a different value.

### Q: Why does my program behave strangely with large numbers?
A: Check for integer overflow. Use larger types (`long long`) or check ranges before operations.

### Q: What's the difference between `'\n'` and `"\n"`?
A: `'\n'` is a character literal (type: char). `"\n"` is a string literal containing a newline (type: char[]).

## Best Practices

### Q: Should I use `#define` or `const` for constants?
A: Prefer `const` because:
- It's type-safe
- It respects scope
- It appears in debugger
- It follows the same rules as regular variables

### Q: How should I name my variables?
A: Good naming conventions:
```c
int user_age;        // snake_case (common in C)
int isValid;         // Clear boolean naming
int MAX_USERS;       // Constants in UPPER_CASE
float calculate_tax(); // Verbs for functions, nouns for variables
```

### Q: Should I always initialize variables to zero?
A: Yes, it's good practice. It prevents undefined behavior and makes debugging easier.

### Q: When should I use different integer types?
A: General guidelines:
```c
char c;              // Characters, small numbers (0-255)
short s;             // Small integers, save memory
int i;               // General purpose integer
long l;             // Large integers
long long ll;       // Very large integers
size_t sz;           // Sizes, counts, indices
```

## Troubleshooting

### Q: Why does my floating-point calculation give wrong results?
A: Floating-point arithmetic has precision limitations. Use `double` instead of `float`, and be aware that `0.1 + 0.2 != 0.3` exactly due to binary representation.

### Q: What does "signed/unsigned mismatch" warning mean?
A: You're comparing or assigning between signed and unsigned values, which can cause unexpected results. Use consistent signedness or cast explicitly.

### Q: Why do I get "undeclared identifier" errors?
A: The variable name is misspelled, not declared, or out of scope. Check spelling and declaration location.

---

## 💡 Pro Tips

1. **Always include `<stdint.h>` for fixed-size integers**: `int32_t`, `uint64_t`
2. **Use `sizeof()` instead of hardcoding sizes**: `int arr[10]; for(int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++)`
3. **Initialize all variables**: Prevents undefined behavior
4. **Use appropriate types**: Don't use `int` for everything
5. **Be careful with signed/unsigned mixing**: Can cause subtle bugs
6. **Prefer `double` over `float`**: Modern systems handle it well
7. **Use meaningful variable names**: `user_count` is better than `uc`
8. **Check for integer overflow**: Especially in calculations involving multiplication