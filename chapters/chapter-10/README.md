# Chapter 10: Advanced Topics

## Learning Objectives
By the end of this chapter, you will be able to:
- Understand and use bitwise operations
- Work with the C preprocessor and macros
- Handle command-line arguments
- Implement multiple file programs
- Use advanced error handling techniques
- Apply performance optimization strategies
- Understand C standards and portability

## Bitwise Operations

Bitwise operations work directly on binary representations of numbers. They're essential for:
- **Low-level programming** and hardware interaction
- **Performance optimization** in critical code
- **Data compression** and encoding algorithms
- **Flag management** and bit masks
- **Graphics and game development**

### Basic Bitwise Operations
```c
#include <stdio.h>

void demonstrate_bitwise_ops() {
    int a = 12;  // Binary: 1100
    int b = 10;  // Binary: 1010

    printf("Bitwise Operations Demo\n");
    printf("=======================\n");
    printf("a = %d (binary: ", a);
    for (int i = 7; i >= 0; i--) {
        printf("%d", (a >> i) & 1);
    }
    printf(")\n");

    printf("b = %d (binary: ", b);
    for (int i = 7; i >= 0; i--) {
        printf("%d", (b >> i) & 1);
    }
    printf(")\n\n");

    printf("Bitwise AND (&): a & b = %d\n", a & b);    // 1000 = 8
    printf("Bitwise OR (|): a | b = %d\n", a | b);    // 1110 = 14
    printf("Bitwise XOR (^): a ^ b = %d\n", a ^ b);    // 0110 = 6
    printf("Bitwise NOT (~): ~a = %d\n", ~a);          // One's complement
    printf("Left Shift (<<): a << 2 = %d\n", a << 2); // 110000 = 48
    printf("Right Shift (>>): a >> 2 = %d\n", a >> 2); // 0011 = 3
}

int main() {
    demonstrate_bitwise_ops();
    return 0;
}
```

### Practical Bit Manipulation
```c
#include <stdio.h>

// Flag management example
#define FLAG_READ   0b0001  // 1
#define FLAG_WRITE  0b0010  // 2
#define FLAG_EXEC   0b0100  // 4
#define FLAG_HIDDEN 0b1000  // 8

void set_flag(int *permissions, int flag) {
    *permissions |= flag;
}

void clear_flag(int *permissions, int flag) {
    *permissions &= ~flag;
}

int check_flag(int permissions, int flag) {
    return (permissions & flag) != 0;
}

void toggle_flag(int *permissions, int flag) {
    *permissions ^= flag;
}

// Common bit manipulation functions
int count_set_bits(int num) {
    int count = 0;
    while (num) {
        count += num & 1;
        num >>= 1;
    }
    return count;
}

int reverse_bits(int num) {
    int reversed = 0;
    for (int i = 0; i < 32; i++) {
        reversed = (reversed << 1) | (num & 1);
        num >>= 1;
    }
    return reversed;
}

int find_lowest_set_bit(int num) {
    if (num == 0) return -1;

    int position = 0;
    while ((num & 1) == 0) {
        num >>= 1;
        position++;
    }
    return position;
}

int main() {
    printf("Advanced Bit Manipulation\n");
    printf("========================\n");

    // Flag management
    int permissions = 0;
    printf("Initial permissions: %d\n", permissions);

    set_flag(&permissions, FLAG_READ);
    printf("After setting READ: %d\n", permissions);

    set_flag(&permissions, FLAG_WRITE);
    printf("After setting WRITE: %d\n", permissions);

    set_flag(&permissions, FLAG_EXEC);
    printf("After setting EXEC: %d\n", permissions);

    printf("Has WRITE permission: %s\n",
           check_flag(permissions, FLAG_WRITE) ? "Yes" : "No");

    toggle_flag(&permissions, FLAG_READ);
    printf("After toggling READ: %d\n", permissions);

    clear_flag(&permissions, FLAG_WRITE);
    printf("After clearing WRITE: %d\n", permissions);

    // Bit counting and manipulation
    int test_num = 29;  // Binary: 11101
    printf("\nNumber: %d\n", test_num);
    printf("Set bits: %d\n", count_set_bits(test_num));
    printf("Lowest set bit position: %d\n", find_lowest_set_bit(test_num));
    printf("Reversed bits: %d\n", reverse_bits(test_num));

    return 0;
}
```

## The C Preprocessor

The C preprocessor processes directives before compilation. It enables:
- **Macros** for code generation
- **Conditional compilation** for platform-specific code
- **File inclusion** for modular programming
- **Constant definitions** and symbolic constants

### Macro Definitions
```c
#include <stdio.h>

// Simple macro
#define PI 3.14159f

// Function-like macro
#define SQUARE(x) ((x) * (x))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

// Stringification macro
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

// Token pasting macro
#define CONCAT(a, b) a##b

// Conditional macro
#ifdef DEBUG
#define DEBUG_PRINT(fmt, ...) printf("[DEBUG] " fmt "\n", ##__VA_ARGS__)
#else
#define DEBUG_PRINT(fmt, ...)
#endif

// Multi-line macro
#define PRINT_INFO(name, age, salary) \
    printf("Name: %s\n", name); \
    printf("Age: %d\n", age); \
    printf("Salary: $%.2f\n", salary);

// Macro with do-while for safety
#define SAFE_SWAP(a, b, type) \
    do { \
        type temp = a; \
        a = b; \
        b = temp; \
    } while(0)

int main() {
    printf("C Preprocessor Demo\n");
    printf("===================\n");

    // Simple macro usage
    printf("PI = %f\n", PI);

    // Function-like macros
    int x = 5, y = 8;
    printf("SQUARE(%d) = %d\n", x, SQUARE(x));
    printf("MAX(%d, %d) = %d\n", x, y, MAX(x, y));

    // Stringification
    printf("Variable name: %s\n", TOSTRING(x));

    // Token pasting
    int CONCAT(var, 1) = 100;
    int CONCAT(var, 2) = 200;
    printf("var1 = %d, var2 = %d\n", var1, var2);

    // Conditional compilation
    #ifdef DEBUG
        printf("Debug mode is enabled\n");
    #endif

    DEBUG_PRINT("This is a debug message: %d", 42);

    // Multi-line macro
    PRINT_INFO("John Doe", 30, 75000.00);

    // Safe macro usage
    SAFE_SWAP(x, y, int);
    printf("After swap: x = %d, y = %d\n", x, y);

    return 0;
}
```

### Conditional Compilation
```c
#include <stdio.h>

// Platform detection
#if defined(_WIN32) || defined(_WIN64)
    #define PLATFORM "Windows"
#elif defined(__linux__)
    #define PLATFORM "Linux"
#elif defined(__APPLE__)
    #define PLATFORM "macOS"
#else
    #define PLATFORM "Unknown"
#endif

// Feature flags
#define ENABLE_ADVANCED_FEATURES 1
#define USE_FAST_ALGORITHM 1

int main() {
    printf("Conditional Compilation Demo\n");
    printf("=============================\n");

    printf("Platform: %s\n", PLATFORM);

    // Compile-time conditionals
    #if ENABLE_ADVANCED_FEATURES
        printf("Advanced features are enabled\n");

        #if USE_FAST_ALGORITHM
            printf("Using fast algorithm\n");
        #else
            printf("Using standard algorithm\n");
        #endif
    #else
        printf("Advanced features are disabled\n");
    #endif

    // Compiler detection
    #if defined(__clang__)
        printf("Compiler: Clang\n");
    #elif defined(__GNUC__)
        printf("Compiler: GCC\n");
    #elif defined(_MSC_VER)
        printf("Compiler: MSVC\n");
    #endif

    // Architecture detection
    #if defined(__x86_64__) || defined(_M_X64)
        printf("Architecture: x64\n");
    #elif defined(__i386__) || defined(_M_IX86)
        printf("Architecture: x86\n");
    #elif defined(__arm__) || defined(_M_ARM)
        printf("Architecture: ARM\n");
    #endif

    return 0;
}
```

## Command-Line Arguments

Command-line arguments allow your programs to accept input from the command line.

### Basic Argument Processing
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_usage(const char *program_name) {
    printf("Usage: %s [options]\n", program_name);
    printf("Options:\n");
    printf("  -h, --help     Show this help message\n");
    printf("  -v, --verbose  Enable verbose output\n");
    printf("  -o <file>      Output file\n");
    printf("  -n <number>    Number to process\n");
}

int main(int argc, char *argv[]) {
    int verbose = 0;
    char *output_file = NULL;
    int number = 0;
    int has_number = 0;

    printf("Command Line Arguments Demo\n");
    printf("============================\n");

    printf("Program name: %s\n", argv[0]);
    printf("Number of arguments: %d\n", argc - 1);

    if (argc < 2) {
        print_usage(argv[0]);
        return 1;
    }

    // Process arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            print_usage(argv[0]);
            return 0;
        }
        else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--verbose") == 0) {
            verbose = 1;
        }
        else if (strcmp(argv[i], "-o") == 0) {
            if (i + 1 < argc) {
                output_file = argv[++i];
            } else {
                printf("Error: -o requires a filename\n");
                return 1;
            }
        }
        else if (strcmp(argv[i], "-n") == 0) {
            if (i + 1 < argc) {
                number = atoi(argv[++i]);
                has_number = 1;
            } else {
                printf("Error: -n requires a number\n");
                return 1;
            }
        }
        else {
            printf("Unknown argument: %s\n", argv[i]);
            print_usage(argv[0]);
            return 1;
        }
    }

    // Display results
    printf("\nProcessed arguments:\n");
    printf("Verbose mode: %s\n", verbose ? "enabled" : "disabled");
    printf("Output file: %s\n", output_file ? output_file : "none");
    printf("Number: %s\n", has_number ? "specified" : "not specified");
    if (has_number) {
        printf("Number value: %d\n", number);
    }

    return 0;
}
```

### Advanced Argument Parser
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char name;
    char *long_name;
    int has_arg;
    char *description;
} Option;

typedef struct {
    char *output_file;
    int input_count;
    char **input_files;
    int verbose;
    int show_help;
    int show_version;
    int number;
    char *mode;
} Config;

Option options[] = {
    {'h', "help", 0, "Show help message"},
    {'v', "verbose", 0, "Enable verbose output"},
    {'o', "output", 1, "Output file"},
    {'n', "number", 1, "Number to process"},
    {'m', "mode", 1, "Processing mode"},
    {'V', "version", 0, "Show version"},
    {0, NULL, 0, NULL}
};

void print_help(const char *program_name) {
    printf("Usage: %s [options] [files...]\n\n", program_name);
    printf("Options:\n");

    for (int i = 0; options[i].name != 0; i++) {
        if (options[i].has_arg) {
            printf("  -%c <%s>, --%s <%s>\n",
                   options[i].name, options[i].long_name,
                   options[i].long_name, options[i].long_name);
        } else {
            printf("  -%c, --%s\n", options[i].name, options[i].long_name);
        }
        printf("      %s\n", options[i].description);
    }
}

void print_version() {
    printf("Advanced Argument Parser v1.0\n");
    printf("Built with C compiler\n");
}

void init_config(Config *config) {
    config->output_file = NULL;
    config->input_count = 0;
    config->input_files = NULL;
    config->verbose = 0;
    config->show_help = 0;
    config->show_version = 0;
    config->number = 0;
    config->mode = NULL;
}

void free_config(Config *config) {
    if (config->input_files) {
        free(config->input_files);
    }
    if (config->output_file) {
        free(config->output_file);
    }
    if (config->mode) {
        free(config->mode);
    }
}

int parse_arguments(int argc, char *argv[], Config *config) {
    int file_count = 0;

    // Count input files
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] != '-') {
            file_count++;
        }
    }

    // Allocate memory for input files
    if (file_count > 0) {
        config->input_files = (char**)malloc(file_count * sizeof(char*));
    }

    file_count = 0;

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            // Long option (--option)
            if (argv[i][1] == '-') {
                char *option = argv[i] + 2;
                char *arg = NULL;

                // Check if option has argument
                char *equals = strchr(option, '=');
                if (equals) {
                    *equals = '\0';
                    arg = equals + 1;
                } else if (i + 1 < argc && argv[i + 1][0] != '-') {
                    arg = argv[++i];
                }

                // Process long options
                if (strcmp(option, "help") == 0) {
                    config->show_help = 1;
                } else if (strcmp(option, "verbose") == 0) {
                    config->verbose = 1;
                } else if (strcmp(option, "version") == 0) {
                    config->show_version = 1;
                } else if (strcmp(option, "output") == 0) {
                    config->output_file = arg ? strdup(arg) : NULL;
                } else if (strcmp(option, "number") == 0) {
                    config->number = arg ? atoi(arg) : 0;
                } else if (strcmp(option, "mode") == 0) {
                    config->mode = arg ? strdup(arg) : NULL;
                }
            }
            // Short options (-o or -abc)
            else {
                for (int j = 1; argv[i][j]; j++) {
                    char opt = argv[i][j];

                    switch (opt) {
                        case 'h':
                            config->show_help = 1;
                            break;
                        case 'v':
                            config->verbose = 1;
                            break;
                        case 'V':
                            config->show_version = 1;
                            break;
                        case 'o':
                        case 'n':
                        case 'm':
                            // These options require arguments
                            if (argv[i][j + 1] != '\0') {
                                // Argument is attached to option
                                char *arg = argv[i] + j + 1;
                                if (opt == 'o') {
                                    config->output_file = strdup(arg);
                                } else if (opt == 'n') {
                                    config->number = atoi(arg);
                                } else if (opt == 'm') {
                                    config->mode = strdup(arg);
                                }
                                j += strlen(arg); // Skip to end of string
                            } else {
                                // Argument is next token
                                if (i + 1 < argc) {
                                    i++;
                                    if (opt == 'o') {
                                        config->output_file = strdup(argv[i]);
                                    } else if (opt == 'n') {
                                        config->number = atoi(argv[i]);
                                    } else if (opt == 'm') {
                                        config->mode = strdup(argv[i]);
                                    }
                                }
                            }
                            break;
                        default:
                            printf("Unknown option: -%c\n", opt);
                            return 0;
                    }
                }
            }
        } else {
            // Input file
            config->input_files[file_count++] = argv[i];
        }
    }

    config->input_count = file_count;
    return 1;
}

int main(int argc, char *argv[]) {
    Config config;

    printf("Advanced Argument Parser\n");
    printf("=======================\n");

    init_config(&config);

    if (!parse_arguments(argc, argv, &config)) {
        free_config(&config);
        return 1;
    }

    // Handle special options
    if (config.show_help) {
        print_help(argv[0]);
        free_config(&config);
        return 0;
    }

    if (config.show_version) {
        print_version();
        free_config(&config);
        return 0;
    }

    // Display configuration
    printf("Configuration:\n");
    printf("  Verbose: %s\n", config.verbose ? "yes" : "no");
    printf("  Output file: %s\n", config.output_file ? config.output_file : "stdout");
    printf("  Number: %d\n", config.number);
    printf("  Mode: %s\n", config.mode ? config.mode : "default");
    printf("  Input files: %d\n", config.input_count);

    for (int i = 0; i < config.input_count; i++) {
        printf("    %s\n", config.input_files[i]);
    }

    free_config(&config);
    return 0;
}
```

## Multi-File Programs

Organizing code across multiple files improves maintainability and modularity.

### Header File Example
```c
// calculator.h
#ifndef CALCULATOR_H
#define CALCULATOR_H

// Function declarations
int add(int a, int b);
int subtract(int a, int b);
int multiply(int a, int b);
int divide(int a, int b, int *result);

// Constants
#define CALC_VERSION "1.0.0"
#define MAX_OPERATIONS 1000

#endif
```

### Implementation File
```c
// calculator.c
#include "calculator.h"
#include <stdio.h>

int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

int multiply(int a, int b) {
    return a * b;
}

int divide(int a, int b, int *result) {
    if (b == 0) {
        return 0; // Error
    }
    *result = a / b;
    return 1; // Success
}
```

### Main Program
```c
// main.c
#include <stdio.h>
#include "calculator.h"

int main() {
    printf("Calculator %s\n", CALC_VERSION);
    printf("==================\n");

    int a = 20, b = 5;
    int result;

    printf("%d + %d = %d\n", a, b, add(a, b));
    printf("%d - %d = %d\n", a, b, subtract(a, b));
    printf("%d * %d = %d\n", a, b, multiply(a, b));

    if (divide(a, b, &result)) {
        printf("%d / %d = %d\n", a, b, result);
    } else {
        printf("Division by zero!\n");
    }

    return 0;
}
```

## Advanced Error Handling

### Error Codes and Messages
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

// Error codes
typedef enum {
    SUCCESS = 0,
    ERROR_INVALID_INPUT = -1,
    ERROR_MEMORY_ALLOC = -2,
    ERROR_FILE_NOT_FOUND = -3,
    ERROR_PERMISSION_DENIED = -4,
    ERROR_NETWORK_ERROR = -5,
    ERROR_TIMEOUT = -6
} ErrorCode;

// Error message table
const char* error_messages[] = {
    "Success",
    "Invalid input provided",
    "Memory allocation failed",
    "File not found",
    "Permission denied",
    "Network error occurred",
    "Operation timed out"
};

// Error handling context
typedef struct {
    ErrorCode code;
    char message[256];
    char file[64];
    int line;
    char function[64];
} ErrorContext;

// Set error context
#define SET_ERROR(ctx, err_code, msg) \
    do { \
        (ctx)->code = (err_code); \
        strncpy((ctx)->message, (msg), sizeof((ctx)->message) - 1); \
        strncpy((ctx)->file, __FILE__, sizeof((ctx)->file) - 1); \
        (ctx)->line = __LINE__; \
        strncpy((ctx)->function, __func__, sizeof((ctx)->function) - 1); \
    } while(0)

// Print error context
void print_error(const ErrorContext *error) {
    if (error->code != SUCCESS) {
        fprintf(stderr, "ERROR [%d]: %s\n", error->code, error->message);
        fprintf(stderr, "  Function: %s\n", error->function);
        fprintf(stderr, "  File: %s:%d\n", error->file, error->line);
        if (errno != 0) {
            fprintf(stderr, "  System: %s\n", strerror(errno));
        }
    }
}

// Example functions with error handling
int process_data(int *data, int size, ErrorContext *error) {
    if (!data || size <= 0) {
        SET_ERROR(error, ERROR_INVALID_INPUT, "Invalid data or size");
        return ERROR_INVALID_INPUT;
    }

    // Simulate memory allocation
    int *processed = (int*)malloc(size * sizeof(int));
    if (!processed) {
        SET_ERROR(error, ERROR_MEMORY_ALLOC, "Failed to allocate memory");
        return ERROR_MEMORY_ALLOC;
    }

    // Process data (simple multiplication by 2)
    for (int i = 0; i < size; i++) {
        processed[i] = data[i] * 2;
    }

    // Copy back to original array
    memcpy(data, processed, size * sizeof(int));
    free(processed);

    return SUCCESS;
}

int read_file(const char *filename, ErrorContext *error) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        SET_ERROR(error, ERROR_FILE_NOT_FOUND, "Cannot open file");
        return ERROR_FILE_NOT_FOUND;
    }

    // Simulate file processing
    printf("Processing file: %s\n", filename);

    fclose(file);
    return SUCCESS;
}

int main() {
    ErrorContext error = {SUCCESS, "", "", 0, ""};
    int data[] = {1, 2, 3, 4, 5};
    int size = sizeof(data) / sizeof(data[0]);

    printf("Advanced Error Handling\n");
    printf("=======================\n");

    // Test successful operation
    printf("Test 1: Successful data processing\n");
    int result = process_data(data, size, &error);
    if (result == SUCCESS) {
        printf("Data processed successfully\n");
    } else {
        print_error(&error);
    }

    // Test error case
    printf("\nTest 2: Invalid input\n");
    result = process_data(NULL, size, &error);
    if (result != SUCCESS) {
        print_error(&error);
    }

    // Test file error
    printf("\nTest 3: File not found\n");
    result = read_file("nonexistent.txt", &error);
    if (result != SUCCESS) {
        print_error(&error);
    }

    // Test successful file operation
    printf("\nTest 4: File exists\n");
    result = read_file(__FILE__, &error);
    if (result == SUCCESS) {
        printf("File processed successfully\n");
    } else {
        print_error(&error);
    }

    return 0;
}
```

## Performance Optimization

### Profiling and Optimization Techniques
```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Function to measure execution time
#define BENCHMARK(func, iterations, ...) \
    do { \
        clock_t start = clock(); \
        for (int i = 0; i < (iterations); i++) { \
            func(__VA_ARGS__); \
        } \
        clock_t end = clock(); \
        double time_spent = ((double)(end - start)) / CLOCKS_PER_SEC; \
        printf("Benchmark: %s - %d iterations: %.6f seconds\n", \
               #func, iterations, time_spent); \
    } while(0)

// Inefficient string concatenation
void inefficient_concat(char *result, const char **strings, int count) {
    strcpy(result, "");
    for (int i = 0; i < count; i++) {
        strcat(result, strings[i]);
    }
}

// Efficient string concatenation (pre-calculate length)
void efficient_concat(char *result, const char **strings, int count) {
    // Calculate total length first
    int total_length = 1; // +1 for null terminator
    for (int i = 0; i < count; i++) {
        total_length += strlen(strings[i]);
    }

    // Copy directly without repeated scanning
    char *ptr = result;
    for (int i = 0; i < count; i++) {
        int len = strlen(strings[i]);
        memcpy(ptr, strings[i], len);
        ptr += len;
    }
    *ptr = '\0';
}

// Matrix multiplication optimization
void matrix_multiply_basic(float *a, float *b, float *c, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            c[i * n + j] = 0;
            for (int k = 0; k < n; k++) {
                c[i * n + j] += a[i * n + k] * b[k * n + j];
            }
        }
    }
}

// Optimized matrix multiplication (loop order changed)
void matrix_multiply_optimized(float *a, float *b, float *c, int n) {
    // Initialize result matrix
    memset(c, 0, n * n * sizeof(float));

    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            float a_ik = a[i * n + k];
            for (int j = 0; j < n; j++) {
                c[i * n + j] += a_ik * b[k * n + j];
            }
        }
    }
}

// Cache-friendly array processing
void process_cache_friendly(int *array, int size) {
    const int BLOCK_SIZE = 64; // Optimized for cache lines

    for (int i = 0; i < size; i += BLOCK_SIZE) {
        int end = (i + BLOCK_SIZE < size) ? i + BLOCK_SIZE : size;
        for (int j = i; j < end; j++) {
            // Process in small chunks that fit in cache
            array[j] = array[j] * 2 + 1;
        }
    }
}

int main() {
    printf("Performance Optimization Demo\n");
    printf("=============================\n");

    // String concatenation benchmark
    const char *strings[] = {
        "Hello, ", "World! ", "This ", "is ", "a ", "performance ",
        "test ", "with ", "multiple ", "strings."
    };
    int string_count = sizeof(strings) / sizeof(strings[0]);
    int total_length = 0;
    for (int i = 0; i < string_count; i++) {
        total_length += strlen(strings[i]);
    }

    char result1[total_length + 1];
    char result2[total_length + 1];

    const int iterations = 100000;

    printf("\nString concatenation benchmarks:\n");
    BENCHMARK(inefficient_concat, iterations, result1, strings, string_count);
    BENCHMARK(efficient_concat, iterations, result2, strings, string_count);

    // Matrix multiplication benchmark
    const int matrix_size = 100;
    const int matrix_iterations = 100;

    float *a = (float*)malloc(matrix_size * matrix_size * sizeof(float));
    float *b = (float*)malloc(matrix_size * matrix_size * sizeof(float));
    float *c1 = (float*)malloc(matrix_size * matrix_size * sizeof(float));
    float *c2 = (float*)malloc(matrix_size * matrix_size * sizeof(float));

    // Initialize matrices
    for (int i = 0; i < matrix_size * matrix_size; i++) {
        a[i] = (float)(i % 10);
        b[i] = (float)((i * 3) % 10);
    }

    printf("\nMatrix multiplication benchmarks (%dx%d):\n",
           matrix_size, matrix_size);
    BENCHMARK(matrix_multiply_basic, matrix_iterations, a, b, c1, matrix_size);
    BENCHMARK(matrix_multiply_optimized, matrix_iterations, a, b, c2, matrix_size);

    // Cache-friendly processing
    int array_size = 1000000;
    int *array = (int*)malloc(array_size * sizeof(int));
    for (int i = 0; i < array_size; i++) {
        array[i] = i;
    }

    printf("\nArray processing benchmarks (1M elements):\n");
    BENCHMARK(process_cache_friendly, 1000, array, array_size);

    // Cleanup
    free(a);
    free(b);
    free(c1);
    free(c2);
    free(array);

    printf("\nOptimization Techniques:\n");
    printf("1. Minimize memory allocations\n");
    printf("2. Optimize loop order for cache locality\n");
    printf("3. Use block processing for large datasets\n");
    printf("4. Avoid redundant calculations\n");
    printf("5. Choose appropriate data structures\n");
    printf("6. Use compiler optimizations (-O2, -O3)\n");

    return 0;
}
```

## C Standards and Portability

### C Standards Overview
```c
#include <stdio.h>
#include <stdlib.h>

// Feature detection
#if defined(__STDC_VERSION__)
    #if __STDC_VERSION__ >= 201112L
        #define C_STANDARD "C11"
    #elif __STDC_VERSION__ >= 199901L
        #define C_STANDARD "C99"
    #elif __STDC_VERSION__ >= 199409L
        #define C_STANDARD "C94"
    #else
        #define C_STANDARD "C89/C90"
    #endif
#else
    #define C_STANDARD "Pre-C89"
#endif

// Compiler-specific features
#if defined(__clang__)
    #define COMPILER "Clang"
#elif defined(__GNUC__)
    #define COMPILER "GCC"
#elif defined(_MSC_VER)
    #define COMPILER "MSVC"
#else
    #define COMPILER "Unknown"
#endif

// Portable integer types (C99)
#include <stdint.h>
#include <inttypes.h>

void demonstrate_portability() {
    printf("C Standards and Portability\n");
    printf("===========================\n");
    printf("C Standard: %s\n", C_STANDARD);
    printf("Compiler: %s\n", COMPILER);

    // Portable integer types
    printf("\nPortable integer types:\n");
    printf("int8_t: %zu bytes\n", sizeof(int8_t));
    printf("int16_t: %zu bytes\n", sizeof(int16_t));
    printf("int32_t: %zu bytes\n", sizeof(int32_t));
    printf("int64_t: %zu bytes\n", sizeof(int64_t));

    // Size and endianness
    printf("\nSystem properties:\n");
    printf("Size of int*: %zu bytes\n", sizeof(void*));
    printf("Size of long: %zu bytes\n", sizeof(long));

    // Check endianness
    unsigned int test = 0x12345678;
    if (*(unsigned char*)&test == 0x78) {
        printf("Endianness: Little Endian\n");
    } else {
        printf("Endianness: Big Endian\n");
    }

    // Time_t size
    printf("Size of time_t: %zu bytes\n", sizeof(time_t));
}

int main() {
    demonstrate_portability();

    printf("\nPortability Guidelines:\n");
    printf("1. Use standard integer types (int32_t, etc.)\n");
    printf("2. Avoid implementation-defined behavior\n");
    printf("3. Use feature detection for conditional compilation\n");
    printf("4. Test on multiple platforms\n");
    printf("5. Follow coding standards (MISRA, CERT, etc.)\n");
    printf("6. Use static analysis tools\n");

    return 0;
}
```

## Best Practices

### Code Quality
1. **Use meaningful variable and function names**
2. **Add appropriate comments** without over-commenting
3. **Follow consistent coding style**
4. **Validate all inputs** and handle errors
5. **Write modular, reusable functions**

### Performance
1. **Profile before optimizing** - measure actual bottlenecks
2. **Choose appropriate algorithms** for the problem size
3. **Minimize memory allocations** in hot paths
4. **Consider cache locality** in data structures
5. **Use compiler optimizations** appropriately

### Portability
1. **Avoid platform-specific code** when possible
2. **Use standard library functions** consistently
3. **Test on multiple compilers and platforms**
4. **Be aware of endianness** and data type sizes
5. **Use feature detection** rather than compiler checks

## Common Pitfalls

### Macro Issues
- **Side effects** in macro parameters
- **Operator precedence** problems
- **Multiple evaluation** of arguments
- **Debugging difficulties**

### Bitwise Operation Errors
- **Signed vs unsigned** confusion
- **Endianness assumptions**
- **Operator precedence** issues
- **Undefined behavior** with shifts

### Preprocessor Problems
- **Macro name collisions**
- **Include guard issues**
- **Circular dependencies**
- **Conditional compilation complexity**

## Exercises

### Exercise 10.1: Bit Manipulation Library
Create functions for common bit manipulation operations.

### Exercise 10.2: Configuration Parser
Build a configuration file parser using macros.

### Exercise 10.3: Cross-Platform Utilities
Write utilities that work on different operating systems.

### Exercise 10.4: Performance Profiler
Create a simple performance profiling library.

### Exercise 10.5: Error Handling Framework
Implement a comprehensive error handling system.

## Challenge Problems

### Challenge 10.1: Custom Allocator
Build a memory allocator with fragmentation handling.

### Challenge 10.2: Bitset Implementation
Create a bitset data structure with efficient operations.

### Challenge 10.3: Portable File System
Write cross-platform file system utilities.

## Quick Reference

### Bitwise Operators
- **AND (`&`)**: Bitwise AND
- **OR (`|`)**: Bitwise OR
- **XOR (`^`)**: Bitwise exclusive OR
- **NOT (`~`)**: Bitwise NOT
- **Left Shift (`<<`)**: Shift left
- **Right Shift (`>>`)**: Shift right

### Preprocessor Directives
- **`#define`**: Define macro or constant
- **`#include`**: Include file
- **`#ifdef/#ifndef`**: Conditional compilation
- **`#if/#elif/#else/#endif`**: Conditional compilation
- **`#pragma`**: Compiler-specific directives

### Standard Includes
- **`<stdio.h>`**: Standard I/O
- **`<stdlib.h>`: Standard library
- **`<string.h>`: String manipulation
- **`<stdint.h>`: Standard integer types
- **`<stdbool.h>`: Boolean type (C99+)

## 🎯 Chapter Summary

### Key Concepts Covered
1. **Bitwise Operations**: Understanding and applying bit manipulation techniques
2. **Preprocessor Directives**: Macros, conditional compilation, and include guards
3. **Command-Line Arguments**: Processing and validating program arguments
4. **Multi-File Programs**: Organizing code across multiple source files
5. **Error Handling Strategies**: Comprehensive error management approaches

### Skills Developed
- Bit manipulation and optimization techniques
- Macro programming and preprocessor usage
- Professional program organization and structure
- Advanced error handling and debugging techniques
- Cross-platform compatibility considerations

### Real-World Applications
- System programming and optimization
- Configuration management systems
- Cross-platform utility development
- Performance-critical applications
- Professional software development practices

---

## 🚀 What's Next?

You've completed the **Core Concepts Phase** of the course! Chapters 1-10 have given you a solid foundation in C programming.

**Upcoming Advanced Chapters:**
- **Chapters 11-13**: Advanced data structures, algorithms, and system programming
- **Chapters 14-16**: Professional development tools, performance optimization, and modern C
- **Chapters 17-20**: Specialized topics like security, graphics, parallel computing, and testing

**Your Next Major Milestone:**
📝 **Final Project: DevTools Utility Suite** (after completing Chapters 11-13)

Keep building on this strong foundation - the most exciting parts are yet to come! ✨