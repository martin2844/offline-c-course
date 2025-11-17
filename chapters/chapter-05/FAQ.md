# Chapters 4-6: Functions, Arrays, Strings, and Pointers - FAQ

## Functions

### Q: What's the difference between function declaration and definition?
A:
- **Declaration**: `int add(int a, int b);` (prototype, tells compiler about function)
- **Definition**: `int add(int a, int b) { return a + b; }` (actual implementation)

### Q: Why do I need function prototypes?
A: Prototypes allow you to:
- Use functions before they're defined
- Enable compiler to check parameter types
- Provide better error messages
- Organize code more flexibly

### Q: What's the difference between `void func()` and `void func(void)`?
A: In C:
- `void func()` means function takes unspecified parameters
- `void func(void)` means function takes no parameters
Always use `void` for no parameters to avoid confusion.

### Q: Can a function return multiple values?
A: Not directly, but you can:
- Use pointers: `void get_values(int *a, int *b)`
- Return a structure: `Point get_coordinates()`
- Use global variables (generally discouraged)

### Q: What does `static` mean for a function?
A: `static` limits the function's visibility to the current file only (internal linkage).

### Q: What's the difference between `return` and `exit`?
A: `return` exits from the current function only. `exit()` terminates the entire program immediately.

### Q: How many parameters can a function have?
A: Practically limited by available stack space, but generally keep it under 6-8 for readability. Consider using structures if you need many parameters.

### Q: Can I have functions with the same name?
A: No, C doesn't support function overloading. Each function must have a unique name.

### Q: What is a recursive function?
A: A function that calls itself. Must have a base case to prevent infinite recursion.

### Q: Are function parameters passed by value or reference?
A: C always passes parameters by value. To modify parameters, pass pointers (simulates pass-by-reference).

## Arrays

### Q: What's the difference between `int arr[5]` and `int *arr`?
A: `int arr[5]` declares an array of 5 integers (fixed size). `int *arr` declares a pointer to integer (can point to array or single integer).

### Q: Why does `sizeof(array)` give different results inside and outside functions?
A: Inside functions, arrays decay to pointers, so `sizeof(array)` gives pointer size (usually 8 bytes). Outside functions, it gives the full array size.

### Q: Can I return an array from a function?
A: Not directly. Alternatives:
- Return pointer to static array: `int* func() { static int arr[5]; return arr; }`
- Return dynamically allocated array: `int* func() { return malloc(5 * sizeof(int)); }`
- Pass array as parameter and modify it

### Q: What's the difference between `char str[]` and `char *str`?
A: `char str[]` creates an array (modifiable). `char *str` creates a pointer (might point to string literal).

### Q: How do I find the size of an array?
A: Use `sizeof(array) / sizeof(array[0])`. Works only for arrays, not pointers.

### Q: Can I change the size of an array after it's declared?
A: No, arrays have fixed size. Use dynamic allocation (`malloc`, `realloc`) for variable-size arrays.

### Q: What is array bounds checking?
A: C does NOT automatically check array bounds. Accessing `arr[10]` when array size is 10 is undefined behavior.

### Q: What's the difference between `arr[0]` and `0[arr]`?
A: They're identical! Both access the first element. `arr[i]` is equivalent to `*(arr + i)`, and `i[arr]` is equivalent to `*(i + arr)`.

### Q: How do I initialize a multidimensional array?
A: `int matrix[3][3] = {{1,2,3},{4,5,6},{7,8,9}};`

### Q: Can I have variable-length arrays?
A: Yes, in C99 and later: `int arr[size];` where size is a variable. These are allocated on stack.

## Strings

### Q: What's the difference between `'a'` and `"a"`?
A: `'a'` is a character (type: char). `"a"` is a string containing 'a' and null terminator (type: char[2]).

### Q: Why do strings need null terminator `\0`?
A: `\0` marks the end of string. Without it, functions won't know where the string ends.

### Q: How do I determine string length?
A: Use `strlen()` from `<string.h>`. It counts characters until it finds `\0`.

### Q: What's the difference between `strcpy` and `strncpy`?
A: `strcpy` copies string without length check (dangerous). `strncpy` copies up to n characters (safer).

### Q: Why do I get "buffer overflow" errors with strings?
A: You're writing past the end of character array. Always ensure destination has enough space + null terminator.

### Q: What's the difference between `char *s` and `char s[]`?
A:
- `char *s` - pointer to char (can point to any string)
- `char s[]` - array of char (fixed size, contains string)

### Q: How do I compare strings?
A: Use `strcmp()`, not `==`: `if (strcmp(str1, str2) == 0)`.

### Q: Can I modify string literals?
A: No! String literals are read-only. `char *s = "hello"; s[0] = 'H';` is undefined behavior.

### Q: What's the safest way to copy strings?
A: Use `strncpy` or `snprintf` with explicit size checking:
```c
strncpy(dest, src, dest_size - 1);
dest[dest_size - 1] = '\0';
```

### Q: How do I concatenate strings?
A: Use `strcat()` or `strncat()`. Ensure destination has enough space.

## Pointers

### Q: What is a pointer?
A: A variable that stores a memory address. `int *p;` declares a pointer to integer.

### Q: What's the difference between `*p` and `p`?
A: `p` is the pointer (address). `*p` is the value at that address (dereferencing).

### Q: What's the difference between `&` and `*`?
A: `&` is "address of" operator. `*` is "dereference" operator:
```c
int x = 5;
int *p = &x;  // p points to x
int y = *p;   // y gets value of x (5)
```

### Q: What does `NULL` mean for pointers?
A: `NULL` is a special value indicating pointer points to nothing. Always initialize pointers to `NULL`.

### Q: Can I use pointer arithmetic on any pointer?
A: Only on pointers to array elements or allocated memory. The result is defined only within the array bounds.

### Q: What's the difference between `int *p, q;` and `int *p, *q;`?
A: `int *p, q;` declares `p` as pointer and `q` as integer. `int *p, *q;` declares both as pointers.

### Q: What is a dangling pointer?
A: Pointer that points to freed or invalid memory. Accessing it causes undefined behavior.

### Q: How do I allocate memory for pointers?
A: Use `malloc()`: `int *p = malloc(sizeof(int) * 10);` Always check return value and free with `free()`.

### Q: What's the difference between `malloc` and `calloc`?
A: `malloc` allocates uninitialized memory. `calloc` allocates zero-initialized memory.

### Q: Should I check `malloc` return value?
A: YES! Always check for `NULL` return indicating allocation failure.

### Q: What's the difference between stack and heap allocation?
A:
- Stack: Automatic, limited size, fast allocation/deallocation
- Heap: Manual, larger size, slower, requires `malloc`/`free`

### Q: What is a pointer to pointer?
A: Pointer that points to another pointer: `int **pp;` Used for dynamic arrays and function parameters.

### Q: Can I cast any pointer type to any other?
A: Yes, but it's dangerous. Cast only when you know what you're doing. Use `void*` for generic pointers.

### Q: What's the difference between `void*` and `char*`?
A: `void*` is generic pointer (no type). `char*` is pointer to character (often used for bytes).

## Common Mistakes

### Q: Why does my program crash when I use pointers?
A: Common causes:
- Dereferencing `NULL` pointer
- Dangling pointer (freed memory)
- Accessing invalid memory
- Pointer arithmetic errors

### Q: Why does my array size seem wrong after passing to function?
A: Arrays decay to pointers in function parameters. Use `sizeof(array)/sizeof(array[0])` in caller, pass size separately.

### Q: Why does my string manipulation not work?
A: Common causes:
- Forgetting null terminator
- Buffer overflow
- Using assignment instead of `strcpy`
- Modifying string literals

### Q: Why does `malloc` not give me the memory I requested?
A: Check return value for `NULL`. System might be out of memory or requested size too large.

### Q: Why does `free` crash my program?
A: Common causes:
- Freeing pointer twice
- Freeing non-heap pointer
- Freeing `NULL` pointer (safe, but pointless)
- Pointer arithmetic made original pointer invalid

## Best Practices

### Q: Should I use `malloc` or stack allocation?
A: Use stack allocation for small, fixed-size arrays. Use `malloc` for:
- Large arrays
- Variable-size arrays
- Data that must outlive current function

### Q: How should I name pointers?
A: Common conventions:
```c
int *ptr_to_int;      // Clear and descriptive
int *p, *q;          // Both pointers
int *p, q;           // Avoid - ambiguous
int buffer[SIZE];    // Arrays are often not named with _ptr
```

### Q: Should I always initialize pointers?
A: YES! Initialize to `NULL` or a valid address immediately.

### Q: How should I handle memory allocation errors?
A: Always check return values and handle gracefully:
```c
int *p = malloc(size * sizeof(int));
if (p == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(EXIT_FAILURE);
}
```

---

## 💡 Pro Tips

### Pointers
1. **Always initialize pointers** to NULL or valid addresses
2. **Check malloc return values** for NULL
3. **Free all allocated memory** to prevent leaks
4. **Set pointers to NULL after freeing** to catch use-after-free
5. **Be careful with pointer arithmetic** - stay within bounds

### Arrays
1. **Use sizeof() to determine array size** when possible
2. **Remember arrays decay to pointers** in function calls
3. **Be aware of array bounds** - C doesn't check for you
4. **Prevent buffer overflows** in string operations
5. **Use const** for arrays that shouldn't be modified

### Strings
1. **Always allocate space for null terminator**: `char str[SIZE+1]`
2. **Use safe string functions**: `strncpy`, `snprintf`
3. **Never modify string literals**
4. **Check string lengths** before operations
5. **Use strcmp() for comparisons**, not `==`

### Functions
1. **Keep functions small and focused** (one purpose)
2. **Use descriptive function names**
3. **Limit parameter count** (consider structures)
4. **Document function contracts** (preconditions, postconditions)
5. **Use const** for parameters that aren't modified