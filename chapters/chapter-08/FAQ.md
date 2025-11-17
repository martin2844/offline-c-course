# Chapters 7-10: Structures, File I/O, Memory Management, Advanced Topics - FAQ

## Structures and Unions (Chapter 7)

### Q: What's the difference between `struct` and `class`?
A: C doesn't have classes. `struct` in C is similar to classes in other languages but without methods or inheritance. It groups related data together.

### Q: What's the difference between `struct` and `union`?
A: `struct` allocates space for all members. `union` allocates space for the largest member only - all members share the same memory.

### Q: When should I use `typedef` with structures?
A: Always for better readability:
```c
// Without typedef
struct Point p;

// With typedef
typedef struct Point Point;
Point p;  // Cleaner
```

### Q: What is structure padding?
A: Compilers add padding bytes between structure members to optimize memory access. This increases size but improves performance.

### Q: How can I eliminate structure padding?
A: Use `#pragma pack(1)` but be aware it may cause performance issues and portability problems.

### Q: Can structures contain pointers to themselves?
A: Yes, but you must use `struct` name:
```c
typedef struct Node {
    int data;
    struct Node *next;  // Forward reference needed
} Node;
```

### Q: What's the difference between `.` and `->` operators?
A: `.` accesses members of structure variables: `point.x`. `->` accesses members via pointer: `point->x`.

### Q: Can I copy structures with `=`?
A: Yes, you can assign structures: `struct1 = struct2;` This does shallow copy (pointers are copied, not pointed-to data).

### Q: How do I pass structures to functions efficiently?
A: Pass pointers to avoid copying large structures: `void process(struct Point *p)`.

### Q: What are bit fields in structures?
A: Bit fields allow you to specify exact number of bits for members:
```c
struct Flags {
    unsigned int is_enabled : 1;
    unsigned int priority : 3;
};
```

## File I/O (Chapter 8)

### Q: What's the difference between text and binary files?
A: Text files contain human-readable characters. Binary files contain raw bytes. Text files may have different line endings on different systems.

### Q: Why do I need to close files?
A: Flushes buffers, releases system resources, prevents data loss, and closes file handles.

### Q: What happens if I forget to close a file?
A: Operating system closes files when program exits, but it's bad practice. May cause data loss or resource leaks in long-running programs.

### Q: What's the difference between `FILE*` and file descriptors?
A: `FILE*` is C standard library abstraction. File descriptors are low-level OS handles (`int`). `FILE*` uses file descriptors internally.

### Q: When should I use binary vs text mode?
A:
- Text mode: Human-readable files, simple text processing
- Binary mode: Images, executable files, network protocols, precise control

### Q: What does `EOF` mean?
A: End of File marker. `feof()` checks if you've reached end of file.

### Q: Why does my file reading loop process the last line twice?
A: Common pattern with `feof()`:
```c
// Wrong - processes last line twice
while (!feof(fp)) {
    fgets(buffer, sizeof(buffer), fp);
    process(buffer);
}

// Correct
while (fgets(buffer, sizeof(buffer), fp) != NULL) {
    process(buffer);
}
```

### Q: What's the difference between `fprintf` and `printf`?
A: `fprintf` writes to specified file. `printf` writes to standard output.

### Q: Can I read and write the same file simultaneously?
A: Yes, but carefully. Use `"r+"`, `"w+"`, or `"a+"` modes. Be aware of file pointer position.

### Q: What is buffering?
A: C uses buffering to improve I/O performance. Writes may not go to disk immediately. Use `fflush()` to force immediate write.

### Q: How do I check if a file exists?
A: Try to open it: `if (fopen("file.txt", "r") != NULL)`.

### Q: What are the different file opening modes?
A:
- `"r"`: Read (file must exist)
- `"w"`: Write (creates or truncates file)
- `"a"`: Append (creates or adds to end)
- `"r+"`: Read and write (file must exist)
- `"w+"`: Read and write (creates or truncates)
- `"a+"`: Read and append (creates or adds to end)
- Add `b` for binary: `"rb"`, `"wb"`, etc.

## Memory Management (Chapter 9)

### Q: What's the difference between stack and heap allocation?
A:
- Stack: Automatic, limited size, fast, automatically managed
- Heap: Manual, larger size, slower, requires malloc/free

### Q: Why is `malloc` returning `NULL`?
A: System out of memory or requested size too large. Always check return value.

### Q: What's the difference between `malloc` and `calloc`?
A: `malloc` allocates uninitialized memory. `calloc` allocates zero-initialized memory.

### Q: When should I use `realloc`?
A: When you need to resize previously allocated memory. It may move the memory block.

### Q: What is a memory leak?
A: Memory allocated with `malloc` but never freed with `free`. Causes program to use increasing memory over time.

### Q: How can I detect memory leaks?
A: Use tools like Valgrind, AddressSanitizer, or implement custom tracking.

### Q: What's a dangling pointer?
A: Pointer that points to freed or invalid memory. Accessing it causes undefined behavior.

### Q: Should I always check `malloc` return value?
A: YES! Always check for `NULL` before using allocated memory.

### Q: What happens if I free memory twice?
A: Undefined behavior - may crash program or corrupt heap. Always set pointer to NULL after freeing.

### Q: Can I free a NULL pointer?
A: Yes, it's safe but does nothing.

### Q: How do I prevent memory leaks?
A:
- Match every malloc with free
- Free memory before function returns
- Use tools to detect leaks
- Consider RAII-style patterns

### Q: What's the difference between `free` and `delete`?
A: `free` is for C memory allocation. `delete` is C++ operator. Don't mix them.

### Q: Should I initialize dynamically allocated memory?
A: Yes, use `calloc` for zero initialization or manually initialize after `malloc`.

## Advanced Topics (Chapter 10)

### Q: What are bitwise operations used for?
A:
- Flags and bit masks
- Fast multiplication/division by powers of 2
- Hardware programming
- Cryptography
- Compression algorithms

### Q: What's the difference between `&` and `&&`?
A: `&` is bitwise AND. `&&` is logical AND.

### Q: What are bit fields?
A: way to specify exact number of bits for structure members:
```c
struct Flags {
    unsigned int flag1 : 1;
    unsigned int flag2 : 3;
};
```

### Q: What's the difference between `<<` and `>>`?
A: `<<` is left shift (multiply by 2^shift). `>>` is right shift (divide by 2^shift).

### Q: What are preprocessor directives?
A: Instructions processed before compilation: `#include`, `#define`, `#ifdef`, etc.

### Q: Should I use `#define` or `const`?
A: Prefer `const` for type safety and debugging. Use `#define` only when necessary.

### Q: What is macro expansion?
A: Preprocessor replaces macros with their definition before compilation:
```c
#define MAX(a, b) ((a) > (b) ? (a) : (b))
```

### Q: How do command-line arguments work?
A: `main` can receive arguments: `int main(int argc, char *argv[])`
- `argc`: number of arguments
- `argv`: array of argument strings

### Q: What's the difference between `argc` and `argv`?
A: `argc` is integer count. `argv[0]` is program name, `argv[1]` is first argument.

### Q: How do I handle multiple source files?
A:
- Split code into `.c` files
- Put declarations in `.h` files
- Use `#include` to include headers
- Compile multiple files together

### Q: What is object file vs source file?
A: Source file (`.c`) is human-readable code. Object file (`.o`) is compiled machine code.

### Q: How do I create a static library?
A: Compile with `-c`, then use `ar` to create `.a` file.

### Q: What is the difference between static and shared libraries?
A: Static libraries linked at compile time (`.a`). Shared libraries linked at runtime (`.so`, `.dylib`, `.dll`).

### Q: What are assertions?
A: Runtime checks that abort program if condition fails:
```c
#include <assert.h>
assert(ptr != NULL);
```

### Q: Should assertions be used in production code?
A: Yes, but consider `NDEBUG` macro. Compile with `-DNDEBUG` to disable assertions in production.

## Common Mistakes

### Q: Why does my structure size seem wrong?
A: Structure padding adds bytes. Use `pragma pack` or reorder members to minimize padding.

### Q: Why can't I assign structures with `=`?
A: You can! But it does shallow copy only. Pointers inside are copied, not pointed-to data.

### Q: Why does my file reading loop stop early?
A: Check for `feof()` correctly. Use `fgets()` return value instead.

### Q: Why does my program crash when I use pointers?
A: Common causes:
- Dereferencing NULL pointer
- Array bounds errors
- Freeing memory then using it
- Pointer arithmetic errors

### Q: Why does my bitwise code give wrong results?
A: Check operator precedence, use parentheses, ensure correct width of operands.

### Q: Why doesn't my macro work as expected?
A: Common issues:
- Missing parentheses in macro definition
- Side effects with multiple evaluation
- Stringification issues

## Best Practices

### Q: How should I structure large C programs?
A:
- Organize code into logical modules
- Use header files for declarations
- Keep functions small and focused
- Use meaningful variable names
- Add comprehensive comments

### Q: Should I use global variables?
A: Generally avoid global variables. Use them sparingly for configuration or shared state.

### Q: How should I handle errors in C?
A:
- Return error codes from functions
- Use assertions for programming errors
- Check return values
- Provide meaningful error messages

### Q: Should I use `goto`?
A: Generally avoid, but acceptable for:
- Error cleanup in functions
- Breaking out of nested loops
- State machine implementations

### Q: How should I name my variables and functions?
A: Use descriptive names, consistent conventions:
```c
int calculate_average(int *scores, int count);
const int MAX_STUDENTS;
```

---

## 💡 Pro Tips

### Structures
1. **Use typedef** for cleaner syntax: `typedef struct Point Point;`
2. **Group related data** logically
3. **Be aware of structure padding** for serialization
4. **Pass pointers** to avoid copying large structures
5. **Initialize all structure members**

### File I/O
1. **Always check file open results** for NULL
2. **Close files** when done
3. **Use appropriate file modes** for your needs
4. **Handle EOF correctly** in reading loops
5. **Flush buffers** when immediate write needed
6. **Use binary mode** for non-text data

### Memory Management
1. **Always initialize pointers** to NULL
2. **Check malloc return** for NULL
3. **Match every malloc with free**
4. **Set pointer to NULL after free**
5. **Prefer stack allocation** when possible
6. **Use valgrind** to detect memory errors

### Advanced Topics
1. **Prefer const over #define** for constants
2. **Use parentheses** in macro definitions
3. **Be careful with operator precedence** in bitwise operations
4. **Document command-line interfaces**
5. **Use assertions** for debugging and contracts
6. **Consider cross-platform compatibility**