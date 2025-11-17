# Chapter 15: Performance Optimization

## Learning Objectives
By the end of this chapter, you will be able to:
- Profile C programs to identify performance bottlenecks
- Apply optimization techniques at algorithm and code level
- Understand memory access patterns and cache optimization
- Implement compiler optimizations and build flags
- Use parallel programming techniques for performance gains

## Introduction to Performance Optimization

Performance optimization is the process of modifying software to make it use fewer resources (CPU, memory, I/O, etc.) or to execute more quickly. In C programming, optimization can significantly improve program efficiency.

### The Performance Optimization Mindset

Performance optimization is both an art and a science. It requires understanding:
- **How computers actually work** (hardware, memory hierarchy, CPU pipelines)
- **How your code executes** (compilation, linking, runtime behavior)
- **Where bottlenecks occur** (CPU, memory, I/O, network)
- **How to measure improvement** (profiling, benchmarking)

**Golden Rule of Optimization**: **Don't optimize prematurely!**

```c
// WRONG: Premature optimization
void complex_optimization() {
    // Complex code that's hard to read
    // But might be faster... maybe?
}

// RIGHT: Clear, correct code first
void clear_code() {
    // Simple, readable implementation
    // Optimize only if performance is actually a problem
}
```

**Donald Knuth's famous quote**: "Premature optimization is the root of all evil."

### Understanding Modern Computer Architecture

To optimize effectively, you must understand how modern computers work:

```
CPU Registers
    ↓ (1 cycle)
L1 Cache (32KB)      - Fastest, smallest
    ↓ (3-4 cycles)
L2 Cache (256KB-1MB)  - Fast, medium
    ↓ (10-20 cycles)
L3 Cache (8MB-32MB)   - Slower, larger
    ↓ (30-100 cycles)
Main Memory (GBs)     - Slow, largest
    ↓ (100-1000 cycles)
SSD Storage            - Much slower
    ↓ (10,000+ cycles)
Hard Drive             - Extremely slow
```

**Performance Implications:**
- **Cache Hits**: L1 cache access is ~100x faster than main memory
- **Cache Misses**: Can stall CPU for hundreds of cycles
- **Spatial Locality**: Accessing nearby memory is faster
- **Temporal Locality**: Recently accessed memory is faster to re-access

### The Optimization Process

**1. Measure First (Profile)**
```c
// Don't guess where the bottleneck is
// Measure actual performance
```

**2. Identify Bottlenecks**
- Find the 20% of code causing 80% of performance issues
- Focus on high-impact optimizations

**3. Optimize Systematically**
- Algorithmic improvements (Big O changes)
- Data structure changes
- Implementation details
- Low-level optimizations

**4. Measure Results**
- Verify optimization actually helped
- Ensure no regressions elsewhere
- Document performance gains

### Types of Performance Optimizations

#### Algorithmic Optimizations
Changing the fundamental approach:
- **O(n²) → O(n log n)**: Sorting algorithms
- **O(n) → O(1)**: Hash tables vs. linear search
- **Recursive → Iterative**: Eliminate function call overhead

#### Data Structure Optimizations
Choosing better data structures:
- **Arrays vs. Linked Lists**: Cache performance
- **Trees vs. Hash Tables**: Search pattern optimization
- **Memory Layout**: Structure packing and alignment

#### Implementation Optimizations
Improving how algorithms are implemented:
- **Loop Unrolling**: Reduce loop overhead
- **Branch Prediction**: Help CPU guess execution path
- **Vectorization**: Use SIMD instructions

#### Compiler Optimizations
Helping the compiler generate better code:
- **Optimization Flags**: -O1, -O2, -O3, -Os
- **Target Architecture**: -march=native
- **Link-Time Optimization**: -flto

#### Memory Optimizations
Improving memory access patterns:
- **Cache-Friendly Algorithms**: Access memory sequentially
- **Memory Pooling**: Reduce allocation overhead
- **Data-Oriented Design**: Structure data for optimal access

### Why Performance Optimization Matters

1. **Resource Efficiency**: Better use of available hardware resources
   - **Cost Savings**: Do more with less expensive hardware
   - **Energy Efficiency**: Reduced power consumption
   - **Environmental Impact**: Lower carbon footprint

2. **User Experience**: Faster response times and smoother operation
   - **Perceived Performance**: Users notice latency above 100ms
   - **Interactive Applications**: UI responsiveness is critical
   - **Real-time Systems**: Deadlines must be met reliably

3. **Scalability**: Handle larger data sets and more users
   - **Big Data**: Process terabytes efficiently
   - **Web Services**: Serve thousands of concurrent users
   - **Scientific Computing**: Complex simulations require optimization

4. **Cost Savings**: Reduced hardware requirements and energy consumption
   - **Cloud Computing**: Pay for compute time, optimization saves money
   - **Mobile Devices**: Battery life is precious
   - **Embedded Systems**: Limited hardware resources

### The Performance Pyramid

Not all optimizations are equal. Prioritize based on impact:

```
High Impact
┌─────────────────────────────────────┐
│ Algorithmic Improvements             │
│ - Better Big O complexity           │
│ - Different data structures         │
│ - Problem-specific optimizations     │
└─────────────────────────────────────┘
Medium Impact
┌─────────────────────────────────────┐
│ Implementation Improvements          │
│ - Loop optimizations                │
│ - Memory access patterns            │
│ - Compiler optimizations            │
└─────────────────────────────────────┘
Low Impact
┌─────────────────────────────────────┐
│ Micro-optimizations                 │
│ - Bit manipulation                  │
│ - Inline assembly                   │
│ - Register variables                │
└─────────────────────────────────────┘
```

**Example**: Optimizing a search function:
```c
// Level 1: Algorithmic (High Impact)
// O(n) linear search → O(log n) binary search

// Level 2: Implementation (Medium Impact)
// Better loop structure, reduced function calls

// Level 3: Micro-optimizations (Low Impact)
// Bit tricks, register hints, specific CPU instructions
```

### Performance Measurement Fundamentals

You can't optimize what you can't measure:

#### Wall Clock Time
```c
#include <time.h>

clock_t start = clock();
// ... code to measure ...
clock_t end = clock();
double cpu_time = ((double)(end - start)) / CLOCKS_PER_SEC;
```

#### High-Resolution Timing
```c
#include <sys/time.h>

struct timeval start, end;
gettimeofday(&start, NULL);
// ... code to measure ...
gettimeofday(&end, NULL);

double elapsed = (end.tv_sec - start.tv_sec) +
                 (end.tv_usec - start.tv_usec) / 1000000.0;
```

#### Memory Usage
```c
#include <sys/resource.h>

struct rusage usage;
getrusage(RUSAGE_SELF, &usage);
long memory_kb = usage.ru_maxrss;  // Peak memory usage in KB
```

### Common Performance Bottlenecks

#### CPU Bound
- **Tight loops**: Doing too much work per iteration
- **Inefficient algorithms**: Poor Big O complexity
- **Branch misprediction**: CPU can't guess execution path

#### Memory Bound
- **Cache misses**: Poor memory access patterns
- **Memory allocations**: Too many malloc/free calls
- **Pointer chasing**: Poor cache locality

#### I/O Bound
- **Blocking operations**: Waiting for disk or network
- **Inefficient file access**: Too many small reads/writes
- **Buffering issues**: Not using optimal buffer sizes

#### Algorithmic Issues
- **Nested loops**: O(n²) or worse complexity
- **Redundant work**: Computing the same values repeatedly
- **Poor data structures**: Wrong tool for the problem

### When to Optimize

**Good times to optimize:**
- **After profiling shows a bottleneck**
- **Before scaling to production**
- **When user experience is affected**
- **When hardware costs are significant**

**Bad times to optimize:**
- **Before code is working correctly**
- **Based on intuition rather than measurement**
- **For micro-benchmarks that don't reflect real usage**
- **When readability suffers significantly**

This foundation prepares you to understand the practical optimization techniques that follow, where you'll learn to apply these concepts to real C programs.

## Profiling and Analysis

### Using gprof for Profiling

```c
// profiling_example.c - Example program for profiling
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Function with different performance characteristics
void slow_function(int n) {
    volatile long sum = 0;
    for (int i = 0; i < n * 1000; i++) {
        sum += i;
    }
}

void fast_function(int n) {
    volatile long sum = n * (n - 1) * 1000 / 2;
    // This line prevents optimization of the entire function
    sum = sum;
}

void memory_intensive_function(int size) {
    int* array = malloc(size * sizeof(int));
    if (!array) return;

    // Initialize array
    for (int i = 0; i < size; i++) {
        array[i] = rand();
    }

    // Sort array (inefficient algorithm)
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }

    free(array);
}

void cpu_intensive_function(int iterations) {
    double result = 0.0;
    for (int i = 0; i < iterations; i++) {
        result += sin(i) * cos(i);
        result = sqrt(fabs(result));
    }
}

void io_intensive_function(int operations) {
    FILE* file = fopen("/tmp/temp_io_test.dat", "w");
    if (!file) return;

    for (int i = 0; i < operations; i++) {
        fprintf(file, "Data line %d with some content to write\n", i);
        fflush(file); // Force write to disk
    }

    fclose(file);
    unlink("/tmp/temp_io_test.dat");
}

void recursive_function(int depth) {
    if (depth <= 0) return;
    recursive_function(depth - 1);
    recursive_function(depth - 1);
}

int main() {
    printf("Performance Profiling Example\n");
    printf("============================\n");

    srand(time(NULL));

    // Run different functions to profile
    printf("Running slow function...\n");
    slow_function(10000);

    printf("Running fast function...\n");
    fast_function(10000);

    printf("Running memory-intensive function...\n");
    memory_intensive_function(1000);

    printf("Running CPU-intensive function...\n");
    cpu_intensive_function(100000);

    printf("Running I/O-intensive function...\n");
    io_intensive_function(1000);

    printf("Running recursive function...\n");
    recursive_function(15);

    printf("All functions completed.\n");
    return 0;
}
```

### Profiling Commands

```bash
# Compile with profiling support
gcc -pg -O0 -g -o profiling_example profiling_example.c -lm

# Run the program to generate profiling data
./profiling_example

# Analyze profiling data
gprof profiling_example gmon.out > analysis.txt

# View the analysis
less analysis.txt

# Generate a call graph (requires graphviz)
gprof -b profiling_example gmon.out | gprof2dot | dot -Tpng -o callgraph.png
```

### Custom Profiling Tools

```c
// custom_profiler.h - Simple profiling infrastructure
#ifndef CUSTOM_PROFILER_H
#define CUSTOM_PROFILER_H

#include <stdio.h>
#include <time.h>
#include <string.h>

#define MAX_PROFILED_FUNCTIONS 100

typedef struct {
    char name[64];
    double total_time;
    long call_count;
    double min_time;
    double max_time;
    clock_t start_time;
    int active;
} ProfileEntry;

typedef struct {
    ProfileEntry entries[MAX_PROFILED_FUNCTIONS];
    int count;
    FILE* log_file;
} Profiler;

extern Profiler g_profiler;

// Profiling macros
#define PROFILE_INIT() \
    profiler_init(&g_profiler);

#define PROFILE_CLEANUP() \
    profiler_cleanup(&g_profiler);

#define PROFILE_START(name) \
    profiler_start(&g_profiler, name);

#define PROFILE_END(name) \
    profiler_end(&g_profiler, name);

#define PROFILE_FUNCTION() \
    static const char* __func_name__ = __func__; \
    PROFILE_START(__func_name__); \
    // Function code here

#define PROFILE_FUNCTION_END() \
    PROFILE_END(__func_name__);

// Function declarations
void profiler_init(Profiler* profiler);
void profiler_cleanup(Profiler* profiler);
void profiler_start(Profiler* profiler, const char* name);
void profiler_end(Profiler* profiler, const char* name);
void profiler_report(Profiler* profiler);

#endif // CUSTOM_PROFILER_H
```

```c
// custom_profiler.c - Custom profiler implementation
#include "custom_profiler.h"

Profiler g_profiler;

void profiler_init(Profiler* profiler) {
    memset(profiler, 0, sizeof(Profiler));
    profiler->log_file = fopen("profile.log", "w");
    if (profiler->log_file) {
        fprintf(profiler->log_file, "Function,Call Count,Total Time,Avg Time,Min Time,Max Time\n");
    }
}

void profiler_cleanup(Profiler* profiler) {
    profiler_report(profiler);
    if (profiler->log_file) {
        fclose(profiler->log_file);
    }
}

static ProfileEntry* find_or_create_entry(Profiler* profiler, const char* name) {
    for (int i = 0; i < profiler->count; i++) {
        if (strcmp(profiler->entries[i].name, name) == 0) {
            return &profiler->entries[i];
        }
    }

    if (profiler->count < MAX_PROFILED_FUNCTIONS) {
        ProfileEntry* entry = &profiler->entries[profiler->count++];
        strncpy(entry->name, name, sizeof(entry->name) - 1);
        entry->name[sizeof(entry->name) - 1] = '\0';
        entry->total_time = 0.0;
        entry->call_count = 0;
        entry->min_time = 1e9;
        entry->max_time = 0.0;
        entry->active = 0;
        return entry;
    }

    return NULL;
}

void profiler_start(Profiler* profiler, const char* name) {
    ProfileEntry* entry = find_or_create_entry(profiler, name);
    if (entry && !entry->active) {
        entry->start_time = clock();
        entry->active = 1;
    }
}

void profiler_end(Profiler* profiler, const char* name) {
    ProfileEntry* entry = find_or_create_entry(profiler, name);
    if (entry && entry->active) {
        clock_t end_time = clock();
        double elapsed = ((double)(end_time - entry->start_time)) / CLOCKS_PER_SEC;

        entry->total_time += elapsed;
        entry->call_count++;
        entry->min_time = (elapsed < entry->min_time) ? elapsed : entry->min_time;
        entry->max_time = (elapsed > entry->max_time) ? elapsed : entry->max_time;
        entry->active = 0;
    }
}

void profiler_report(Profiler* profiler) {
    printf("\n=== Performance Profile Report ===\n");
    printf("%-30s %10s %12s %12s %12s %12s\n",
           "Function", "Calls", "Total(s)", "Avg(s)", "Min(s)", "Max(s)");
    printf("%-30s %10s %12s %12s %12s %12s\n",
           "--------", "-----", "--------", "------", "------", "------");

    // Sort by total time
    for (int i = 0; i < profiler->count - 1; i++) {
        for (int j = 0; j < profiler->count - i - 1; j++) {
            if (profiler->entries[j].total_time < profiler->entries[j + 1].total_time) {
                ProfileEntry temp = profiler->entries[j];
                profiler->entries[j] = profiler->entries[j + 1];
                profiler->entries[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < profiler->count; i++) {
        ProfileEntry* entry = &profiler->entries[i];
        if (entry->call_count > 0) {
            double avg_time = entry->total_time / entry->call_count;
            printf("%-30s %10ld %12.6f %12.6f %12.6f %12.6f\n",
                   entry->name, entry->call_count, entry->total_time,
                   avg_time, entry->min_time, entry->max_time);

            // Write to log file
            if (profiler->log_file) {
                fprintf(profiler->log_file, "%s,%ld,%.6f,%.6f,%.6f,%.6f\n",
                        entry->name, entry->call_count, entry->total_time,
                        avg_time, entry->min_time, entry->max_time);
            }
        }
    }
    printf("\nTotal functions profiled: %d\n", profiler->count);
}
```

## Algorithmic Optimization

### Algorithm Comparison and Optimization

```c
// algorithm_optimization.c - Compare different algorithm approaches
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "custom_profiler.h"

// O(n²) naive approach for finding duplicates
int find_duplicates_naive(int* array, int size) {
    PROFILE_FUNCTION();
    int duplicates = 0;

    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (array[i] == array[j]) {
                duplicates++;
                break;
            }
        }
    }

    PROFILE_FUNCTION_END();
    return duplicates;
}

// O(n log n) optimized approach using sorting
int compare_ints(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int find_duplicates_optimized(int* array, int size) {
    PROFILE_FUNCTION();
    int duplicates = 0;

    // Sort first - O(n log n)
    qsort(array, size, sizeof(int), compare_ints);

    // Count duplicates - O(n)
    for (int i = 1; i < size; i++) {
        if (array[i] == array[i - 1]) {
            duplicates++;
            // Skip all additional duplicates
            while (i + 1 < size && array[i + 1] == array[i]) {
                i++;
            }
        }
    }

    PROFILE_FUNCTION_END();
    return duplicates;
}

// O(n) approach using hash table (simplified)
#define HASH_SIZE 10007

typedef struct HashNode {
    int value;
    int count;
    struct HashNode* next;
} HashNode;

unsigned int hash_function(int value) {
    return (unsigned int)value % HASH_SIZE;
}

int find_duplicates_hash(int* array, int size) {
    PROFILE_FUNCTION();

    HashNode* hash_table[HASH_SIZE] = {NULL};
    int duplicates = 0;

    // Build hash table and count occurrences
    for (int i = 0; i < size; i++) {
        unsigned int index = hash_function(array[i]);
        HashNode* current = hash_table[index];
        HashNode* prev = NULL;

        // Search for existing value
        while (current != NULL) {
            if (current->value == array[i]) {
                current->count++;
                if (current->count == 2) {
                    duplicates++; // Count each duplicate only once
                }
                break;
            }
            prev = current;
            current = current->next;
        }

        // Add new value if not found
        if (current == NULL) {
            HashNode* new_node = malloc(sizeof(HashNode));
            new_node->value = array[i];
            new_node->count = 1;
            new_node->next = hash_table[index];
            hash_table[index] = new_node;
        }
    }

    // Clean up hash table
    for (int i = 0; i < HASH_SIZE; i++) {
        HashNode* current = hash_table[i];
        while (current != NULL) {
            HashNode* temp = current;
            current = current->next;
            free(temp);
        }
    }

    PROFILE_FUNCTION_END();
    return duplicates;
}

// String searching algorithms
int naive_string_search(const char* text, const char* pattern) {
    PROFILE_FUNCTION();

    int text_len = strlen(text);
    int pattern_len = strlen(pattern);
    int matches = 0;

    for (int i = 0; i <= text_len - pattern_len; i++) {
        int j;
        for (j = 0; j < pattern_len; j++) {
            if (text[i + j] != pattern[j]) {
                break;
            }
        }
        if (j == pattern_len) {
            matches++;
        }
    }

    PROFILE_FUNCTION_END();
    return matches;
}

// KMP string search algorithm
void compute_lps_array(const char* pattern, int* lps) {
    int len = strlen(pattern);
    int i = 1, j = 0;
    lps[0] = 0;

    while (i < len) {
        if (pattern[i] == pattern[j]) {
            j++;
            lps[i] = j;
            i++;
        } else {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

int kmp_string_search(const char* text, const char* pattern) {
    PROFILE_FUNCTION();

    int text_len = strlen(text);
    int pattern_len = strlen(pattern);
    int matches = 0;

    if (pattern_len == 0) return 0;

    int* lps = malloc(pattern_len * sizeof(int));
    compute_lps_array(pattern, lps);

    int i = 0, j = 0; // i for text, j for pattern

    while (i < text_len) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == pattern_len) {
            matches++;
            j = lps[j - 1];
        } else if (i < text_len && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }

    free(lps);
    PROFILE_FUNCTION_END();
    return matches;
}

// Test data generation
void generate_random_array(int* array, int size, int max_value) {
    for (int i = 0; i < size; i++) {
        array[i] = rand() % max_value;
    }
}

void generate_string_data(char* text, int size) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ";
    int charset_size = sizeof(charset) - 1;

    for (int i = 0; i < size - 1; i++) {
        text[i] = charset[rand() % charset_size];
    }
    text[size - 1] = '\0';
}

void benchmark_algorithms() {
    printf("=== Algorithm Performance Benchmark ===\n\n");

    srand(time(NULL));

    // Test duplicate finding algorithms
    printf("1. Duplicate Finding Algorithms:\n");
    int sizes[] = {100, 1000, 5000, 10000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    for (int i = 0; i < num_sizes; i++) {
        int size = sizes[i];
        printf("Testing with array size: %d\n", size);

        int* test_array = malloc(size * sizeof(int));
        int* array1 = malloc(size * sizeof(int));
        int* array2 = malloc(size * sizeof(int));
        int* array3 = malloc(size * sizeof(int));

        generate_random_array(test_array, size, size / 2);

        // Copy arrays for different algorithms
        memcpy(array1, test_array, size * sizeof(int));
        memcpy(array2, test_array, size * sizeof(int));
        memcpy(array3, test_array, size * sizeof(int));

        printf("  Naive approach (O(n²)): %d duplicates\n",
               find_duplicates_naive(array1, size));

        printf("  Optimized approach (O(n log n)): %d duplicates\n",
               find_duplicates_optimized(array2, size));

        printf("  Hash approach (O(n)): %d duplicates\n",
               find_duplicates_hash(array3, size));

        free(test_array);
        free(array1);
        free(array2);
        free(array3);
        printf("\n");
    }

    // Test string searching algorithms
    printf("2. String Searching Algorithms:\n");
    const char* long_text = "The quick brown fox jumps over the lazy dog. "
                           "The quick brown fox jumps over the lazy dog. "
                           "The quick brown fox jumps over the lazy dog.";
    const char* pattern = "quick";

    printf("Text length: %zu\n", strlen(long_text));
    printf("Pattern: '%s'\n\n", pattern);

    printf("  Naive search: %d matches\n", naive_string_search(long_text, pattern));
    printf("  KMP search: %d matches\n", kmp_string_search(long_text, pattern));
}

int main() {
    PROFILE_INIT();

    benchmark_algorithms();

    PROFILE_CLEANUP();

    return 0;
}
```

## Memory Access Optimization

### Cache-Friendly Programming

```c
// memory_optimization.c - Memory access pattern optimization
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define ARRAY_SIZE 10000
#define ROWS 1000
#define COLS 1000

// Cache-inefficient matrix multiplication
void matrix_multiply_bad(int a[ROWS][COLS], int b[COLS][ROWS], int result[ROWS][ROWS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < ROWS; j++) {
            result[i][j] = 0;
            for (int k = 0; k < COLS; k++) {
                result[i][j] += a[i][k] * b[k][j]; // Poor cache locality
            }
        }
    }
}

// Cache-efficient matrix multiplication
void matrix_multiply_good(int a[ROWS][COLS], int b[COLS][ROWS], int result[ROWS][ROWS]) {
    // Initialize result matrix
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < ROWS; j++) {
            result[i][j] = 0;
        }
    }

    // Cache-friendly multiplication order
    for (int i = 0; i < ROWS; i++) {
        for (int k = 0; k < COLS; k++) {
            int temp = a[i][k];
            for (int j = 0; j < ROWS; j++) {
                result[i][j] += temp * b[k][j]; // Better cache locality
            }
        }
    }
}

// Block-based matrix multiplication for even better cache performance
#define BLOCK_SIZE 64

void matrix_multiply_blocked(int a[ROWS][COLS], int b[COLS][ROWS], int result[ROWS][ROWS]) {
    // Initialize result matrix
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < ROWS; j++) {
            result[i][j] = 0;
        }
    }

    // Blocked multiplication
    for (int i = 0; i < ROWS; i += BLOCK_SIZE) {
        for (int j = 0; j < ROWS; j += BLOCK_SIZE) {
            for (int k = 0; k < COLS; k += BLOCK_SIZE) {
                // Multiply sub-blocks
                for (int ii = i; ii < i + BLOCK_SIZE && ii < ROWS; ii++) {
                    for (int jj = j; jj < j + BLOCK_SIZE && jj < ROWS; jj++) {
                        for (int kk = k; kk < k + BLOCK_SIZE && kk < COLS; kk++) {
                            result[ii][jj] += a[ii][kk] * b[kk][jj];
                        }
                    }
                }
            }
        }
    }
}

// Array traversal patterns
void row_major_traversal(int matrix[ROWS][COLS]) {
    printf("Row-major traversal (cache-friendly):\n");
    clock_t start = clock();

    volatile long sum = 0;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            sum += matrix[i][j];
        }
    }

    clock_t end = clock();
    double time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("  Time: %.6f seconds\n", time);
    printf("  Sum: %ld\n", sum);
}

void column_major_traversal(int matrix[ROWS][COLS]) {
    printf("Column-major traversal (cache-unfriendly):\n");
    clock_t start = clock();

    volatile long sum = 0;
    for (int j = 0; j < COLS; j++) {
        for (int i = 0; i < ROWS; i++) {
            sum += matrix[i][j];
        }
    }

    clock_t end = clock();
    double time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("  Time: %.6f seconds\n", time);
    printf("  Sum: %ld\n", sum);
}

// Memory alignment optimization
typedef struct {
    char c;        // 1 byte
    double d;      // 8 bytes - may cause padding
    int i;         // 4 bytes
    char s[10];    // 10 bytes
} UnoptimizedStruct;

typedef struct {
    double d;      // 8 bytes - largest member first
    char s[10];    // 10 bytes
    int i;         // 4 bytes
    char c;        // 1 byte
    // Total: 23 bytes + 1 byte padding = 24 bytes
} OptimizedStruct;

// Packed structure (no padding)
#pragma pack(push, 1)
typedef struct {
    char c;
    double d;
    int i;
    char s[10];
} PackedStruct;
#pragma pack(pop)

void memory_layout_demo() {
    printf("=== Memory Layout Optimization ===\n\n");

    printf("Structure sizes:\n");
    printf("  UnoptimizedStruct: %zu bytes\n", sizeof(UnoptimizedStruct));
    printf("  OptimizedStruct: %zu bytes\n", sizeof(OptimizedStruct));
    printf("  PackedStruct: %zu bytes\n", sizeof(PackedStruct));

    printf("\nMemory alignment:\n");
    printf("  Alignment of double: %zu\n", __alignof__(double));
    printf("  Alignment of int: %zu\n", __alignof__(int));
    printf("  Alignment of char: %zu\n", __alignof__(char));
}

// Array vs linked list performance
typedef struct ListNode {
    int data;
    struct ListNode* next;
} ListNode;

typedef struct {
    ListNode* head;
    int count;
} LinkedList;

LinkedList* create_linked_list(int size) {
    LinkedList* list = malloc(sizeof(LinkedList));
    list->head = NULL;
    list->count = 0;

    for (int i = 0; i < size; i++) {
        ListNode* node = malloc(sizeof(ListNode));
        node->data = rand() % 1000;
        node->next = list->head;
        list->head = node;
        list->count++;
    }

    return list;
}

void free_linked_list(LinkedList* list) {
    ListNode* current = list->head;
    while (current != NULL) {
        ListNode* temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}

long sum_array(int* array, int size) {
    long sum = 0;
    for (int i = 0; i < size; i++) {
        sum += array[i];
    }
    return sum;
}

long sum_linked_list(LinkedList* list) {
    long sum = 0;
    ListNode* current = list->head;
    while (current != NULL) {
        sum += current->data;
        current = current->next;
    }
    return sum;
}

void compare_data_structures() {
    const int size = 1000000;

    printf("=== Array vs Linked List Performance ===\n");
    printf("Data size: %d elements\n\n", size);

    // Array test
    int* array = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        array[i] = rand() % 1000;
    }

    clock_t start = clock();
    long array_sum = sum_array(array, size);
    clock_t end = clock();
    double array_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Array:\n");
    printf("  Sum: %ld\n", array_sum);
    printf("  Time: %.6f seconds\n", array_time);
    printf("  Memory: %zu bytes\n", size * sizeof(int));

    // Linked list test
    LinkedList* list = create_linked_list(size);

    start = clock();
    long list_sum = sum_linked_list(list);
    end = clock();
    double list_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("\nLinked List:\n");
    printf("  Sum: %ld\n", list_sum);
    printf("  Time: %.6f seconds\n", list_time);
    printf("  Memory: %zu bytes\n", size * sizeof(ListNode));

    printf("\nPerformance ratio (list/array): %.2fx\n", list_time / array_time);

    free(array);
    free_linked_list(list);
}

int main() {
    memory_layout_demo();
    printf("\n");

    // Matrix operations test
    static int matrix_a[ROWS][COLS];
    static int matrix_b[COLS][ROWS];
    static int matrix_result1[ROWS][ROWS];
    static int matrix_result2[ROWS][ROWS];
    static int matrix_result3[ROWS][ROWS];

    // Initialize matrices
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            matrix_a[i][j] = rand() % 100;
            matrix_b[j][i] = rand() % 100;
        }
    }

    printf("=== Matrix Multiplication Performance ===\n");
    printf("Matrix size: %d x %d\n\n", ROWS, COLS);

    // Test different multiplication methods
    clock_t start, end;
    double time1, time2, time3;

    start = clock();
    matrix_multiply_bad(matrix_a, matrix_b, matrix_result1);
    end = clock();
    time1 = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Cache-inefficient: %.6f seconds\n", time1);

    start = clock();
    matrix_multiply_good(matrix_a, matrix_b, matrix_result2);
    end = clock();
    time2 = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Cache-efficient: %.6f seconds\n", time2);

    start = clock();
    matrix_multiply_blocked(matrix_a, matrix_b, matrix_result3);
    end = clock();
    time3 = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Blocked multiplication: %.6f seconds\n", time3);

    printf("\nPerformance improvements:\n");
    printf("  Efficient/inefficient: %.2fx faster\n", time1 / time2);
    printf("  Blocked/inefficient: %.2fx faster\n", time1 / time3);

    printf("\n");

    // Array traversal patterns
    static int traversal_matrix[ROWS][COLS];
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            traversal_matrix[i][j] = i * COLS + j;
        }
    }

    row_major_traversal(traversal_matrix);
    column_major_traversal(traversal_matrix);

    printf("\n");

    // Data structure comparison
    compare_data_structures();

    return 0;
}
```

## Compiler Optimizations

### Understanding Compiler Flags

```c
// optimization_levels.c - Demonstrate compiler optimization levels
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function that benefits from optimization
double calculate_pi_optimized(int iterations) {
    double pi = 0.0;
    int sign = 1;

    for (int i = 0; i < iterations; i++) {
        pi += (double)sign / (2 * i + 1);
        sign = -sign;
    }

    return 4.0 * pi;
}

// Function with loop unrolling opportunities
void array_processing_optimized(int* input, int* output, int size) {
    int i;
    // Process 4 elements at a time
    for (i = 0; i <= size - 4; i += 4) {
        output[i] = input[i] * 2 + 1;
        output[i + 1] = input[i + 1] * 2 + 1;
        output[i + 2] = input[i + 2] * 2 + 1;
        output[i + 3] = input[i + 3] * 2 + 1;
    }

    // Handle remaining elements
    for (; i < size; i++) {
        output[i] = input[i] * 2 + 1;
    }
}

// Function that benefits from vectorization
void vector_addition(const float* a, const float* b, float* result, int size) {
    for (int i = 0; i < size; i++) {
        result[i] = a[i] + b[i];
    }
}

// Function with inline optimization opportunities
static inline int max_inline(int a, int b) {
    return (a > b) ? a : b;
}

void max_array(int* array, int* result, int size) {
    int current_max = array[0];
    for (int i = 1; i < size; i++) {
        current_max = max_inline(current_max, array[i]);
    }
    *result = current_max;
}

// Function demonstrating branch prediction
int conditional_processing(int* data, int size, int threshold) {
    int count = 0;

    // This loop has unpredictable branches
    for (int i = 0; i < size; i++) {
        if (data[i] > threshold) {
            count += data[i];
        }
    }

    return count;
}

// Optimized version with reduced branches
int conditional_processing_optimized(int* data, int size, int threshold) {
    int count = 0;

    // Use conditional moves to reduce branches
    for (int i = 0; i < size; i++) {
        int diff = data[i] - threshold;
        int mask = (diff >> 31); // All 1s if negative, all 0s if positive
        count += data[i] & ~mask;
    }

    return count;
}

// Function with memory access patterns
void transpose_matrix_naive(int src[100][100], int dst[100][100]) {
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            dst[j][i] = src[i][j];
        }
    }
}

// Optimized transpose using blocking
void transpose_matrix_optimized(int src[100][100], int dst[100][100]) {
    const int BLOCK_SIZE = 16;

    for (int i = 0; i < 100; i += BLOCK_SIZE) {
        for (int j = 0; j < 100; j += BLOCK_SIZE) {
            for (int bi = i; bi < i + BLOCK_SIZE && bi < 100; bi++) {
                for (int bj = j; bj < j + BLOCK_SIZE && bj < 100; bj++) {
                    dst[bj][bi] = src[bi][bj];
                }
            }
        }
    }
}

int main() {
    printf("Compiler Optimization Demonstration\n");
    printf("===================================\n\n");

    const int ARRAY_SIZE = 1000000;
    const int ITERATIONS = 1000000;

    // Allocate arrays
    int* input = malloc(ARRAY_SIZE * sizeof(int));
    int* output = malloc(ARRAY_SIZE * sizeof(int));
    float* a = malloc(ARRAY_SIZE * sizeof(float));
    float* b = malloc(ARRAY_SIZE * sizeof(float));
    float* result = malloc(ARRAY_SIZE * sizeof(float));

    // Initialize data
    for (int i = 0; i < ARRAY_SIZE; i++) {
        input[i] = rand() % 1000;
        output[i] = 0;
        a[i] = (float)rand() / RAND_MAX;
        b[i] = (float)rand() / RAND_MAX;
    }

    // Test pi calculation
    printf("1. Pi Calculation (%d iterations):\n", ITERATIONS);
    double pi = calculate_pi_optimized(ITERATIONS);
    printf("   Calculated Pi: %.10f\n", pi);
    printf("   Actual Pi:     %.10f\n", 3.14159265358979323846);
    printf("   Error:        %.10f\n\n", fabs(pi - 3.14159265358979323846));

    // Test array processing
    printf("2. Array Processing (%d elements):\n", ARRAY_SIZE);
    array_processing_optimized(input, output, ARRAY_SIZE);
    printf("   First 5 results: %d, %d, %d, %d, %d\n\n",
           output[0], output[1], output[2], output[3], output[4]);

    // Test vector addition
    printf("3. Vector Addition (%d elements):\n", ARRAY_SIZE);
    vector_addition(a, b, result, ARRAY_SIZE);
    printf("   First 5 results: %.6f, %.6f, %.6f, %.6f, %.6f\n\n",
           result[0], result[1], result[2], result[3], result[4]);

    // Test max function
    printf("4. Array Maximum:\n");
    int max_val;
    max_array(input, &max_val, ARRAY_SIZE);
    printf("   Maximum value: %d\n", max_val);
    printf("   Expected: 999\n\n");

    // Test conditional processing
    printf("5. Conditional Processing:\n");
    int threshold = 500;
    int count1 = conditional_processing(input, ARRAY_SIZE, threshold);
    int count2 = conditional_processing_optimized(input, ARRAY_SIZE, threshold);
    printf("   Original result: %d\n", count1);
    printf("   Optimized result: %d\n", count2);
    printf("   Results match: %s\n\n", (count1 == count2) ? "Yes" : "No");

    // Test matrix transpose
    printf("6. Matrix Transpose (100x100):\n");
    static int matrix_a[100][100];
    static int matrix_b1[100][100];
    static int matrix_b2[100][100];

    // Initialize matrix
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            matrix_a[i][j] = i * 100 + j;
        }
    }

    // Test both methods
    transpose_matrix_naive(matrix_a, matrix_b1);
    transpose_matrix_optimized(matrix_a, matrix_b2);

    // Verify results are the same
    int match = 1;
    for (int i = 0; i < 100 && match; i++) {
        for (int j = 0; j < 100 && match; j++) {
            if (matrix_b1[i][j] != matrix_b2[i][j]) {
                match = 0;
            }
        }
    }
    printf("   Results match: %s\n", match ? "Yes" : "No");
    printf("   Sample element (50, 75): %d\n", matrix_b2[50][75]);

    // Cleanup
    free(input);
    free(output);
    free(a);
    free(b);
    free(result);

    printf("\nCompilation Recommendations:\n");
    printf("  Debug build:     gcc -g -O0 -Wall program.c\n");
    printf("  Release build:   gcc -O3 -DNDEBUG -march=native program.c\n");
    printf("  Profile build:   gcc -O2 -pg program.c\n");
    printf("  Static analysis: scan-build gcc -Wall -Wextra program.c\n");

    return 0;
}
```

## Parallel Programming

### Multi-threading Optimization

```c
// parallel_optimization.c - Multi-threading for performance
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

#define ARRAY_SIZE 100000000
#define NUM_THREADS 4

typedef struct {
    int* array;
    int start;
    int end;
    long long result;
} ThreadData;

// Sequential sum
long long sequential_sum(int* array, int size) {
    long long sum = 0;
    for (int i = 0; i < size; i++) {
        sum += array[i];
    }
    return sum;
}

// Thread function for parallel sum
void* parallel_sum_thread(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    data->result = 0;

    for (int i = data->start; i < data->end; i++) {
        data->result += data->array[i];
    }

    return NULL;
}

// Parallel sum using multiple threads
long long parallel_sum(int* array, int size, int num_threads) {
    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];
    long long total_sum = 0;

    // Create threads
    int chunk_size = size / num_threads;
    for (int i = 0; i < num_threads; i++) {
        thread_data[i].array = array;
        thread_data[i].start = i * chunk_size;
        thread_data[i].end = (i == num_threads - 1) ? size : (i + 1) * chunk_size;

        pthread_create(&threads[i], NULL, parallel_sum_thread, &thread_data[i]);
    }

    // Wait for threads to complete
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
        total_sum += thread_data[i].result;
    }

    return total_sum;
}

// Parallel array processing with different operations
typedef enum {
    OP_SUM,
    OP_MAX,
    OP_MIN,
    OP_COUNT_EVEN
} Operation;

typedef struct {
    int* array;
    int start;
    int end;
    Operation operation;
    long long result;
} ProcessThreadData;

void* parallel_process_thread(void* arg) {
    ProcessThreadData* data = (ProcessThreadData*)arg;
    long long result = 0;

    switch (data->operation) {
        case OP_SUM:
            for (int i = data->start; i < data->end; i++) {
                result += data->array[i];
            }
            break;

        case OP_MAX:
            result = LLONG_MIN;
            for (int i = data->start; i < data->end; i++) {
                if (data->array[i] > result) {
                    result = data->array[i];
                }
            }
            break;

        case OP_MIN:
            result = LLONG_MAX;
            for (int i = data->start; i < data->end; i++) {
                if (data->array[i] < result) {
                    result = data->array[i];
                }
            }
            break;

        case OP_COUNT_EVEN:
            for (int i = data->start; i < data->end; i++) {
                if (data->array[i] % 2 == 0) {
                    result++;
                }
            }
            break;
    }

    data->result = result;
    return NULL;
}

long long parallel_process(int* array, int size, Operation operation, int num_threads) {
    pthread_t threads[NUM_THREADS];
    ProcessThreadData thread_data[NUM_THREADS];
    long long final_result = 0;

    int chunk_size = size / num_threads;

    for (int i = 0; i < num_threads; i++) {
        thread_data[i].array = array;
        thread_data[i].start = i * chunk_size;
        thread_data[i].end = (i == num_threads - 1) ? size : (i + 1) * chunk_size;
        thread_data[i].operation = operation;

        pthread_create(&threads[i], NULL, parallel_process_thread, &thread_data[i]);
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);

        if (operation == OP_SUM || operation == OP_COUNT_EVEN) {
            final_result += thread_data[i].result;
        } else if (operation == OP_MAX) {
            if (thread_data[i].result > final_result) {
                final_result = thread_data[i].result;
            }
        } else if (operation == OP_MIN) {
            if (thread_data[i].result < final_result) {
                final_result = thread_data[i].result;
            }
        }
    }

    return final_result;
}

// Work stealing queue implementation
typedef struct WorkQueue {
    int* work_items;
    int start;
    int end;
    int capacity;
    pthread_mutex_t mutex;
    pthread_cond_t not_empty;
    pthread_cond_t not_full;
} WorkQueue;

WorkQueue* create_work_queue(int capacity) {
    WorkQueue* queue = malloc(sizeof(WorkQueue));
    queue->work_items = malloc(capacity * sizeof(int));
    queue->start = 0;
    queue->end = 0;
    queue->capacity = capacity;
    pthread_mutex_init(&queue->mutex, NULL);
    pthread_cond_init(&queue->not_empty, NULL);
    pthread_cond_init(&queue->not_full, NULL);
    return queue;
}

void destroy_work_queue(WorkQueue* queue) {
    free(queue->work_items);
    pthread_mutex_destroy(&queue->mutex);
    pthread_cond_destroy(&queue->not_empty);
    pthread_cond_destroy(&queue->not_full);
    free(queue);
}

void enqueue_work(WorkQueue* queue, int work) {
    pthread_mutex_lock(&queue->mutex);

    while ((queue->end + 1) % queue->capacity == queue->start) {
        pthread_cond_wait(&queue->not_full, &queue->mutex);
    }

    queue->work_items[queue->end] = work;
    queue->end = (queue->end + 1) % queue->capacity;
    pthread_cond_signal(&queue->not_empty);

    pthread_mutex_unlock(&queue->mutex);
}

int dequeue_work(WorkQueue* queue) {
    pthread_mutex_lock(&queue->mutex);

    while (queue->start == queue->end) {
        pthread_cond_wait(&queue->not_empty, &queue->mutex);
    }

    int work = queue->work_items[queue->start];
    queue->start = (queue->start + 1) % queue->capacity;
    pthread_cond_signal(&queue->not_full);

    pthread_mutex_unlock(&queue->mutex);
    return work;
}

// Worker thread for work stealing
typedef struct {
    WorkQueue* queue;
    int* results;
    int thread_id;
} WorkerThreadData;

void* worker_thread(void* arg) {
    WorkerThreadData* data = (WorkerThreadData*)arg;

    while (1) {
        int work = dequeue_work(data->queue);
        if (work < 0) break; // Sentinel value

        // Simulate work
        usleep(1000);
        data->results[data->thread_id] += work;
    }

    return NULL;
}

void benchmark_parallel_operations() {
    printf("=== Parallel Processing Benchmark ===\n\n");

    // Initialize test data
    int* test_array = malloc(ARRAY_SIZE * sizeof(int));
    for (int i = 0; i < ARRAY_SIZE; i++) {
        test_array[i] = rand() % 1000;
    }

    printf("Array size: %d elements\n", ARRAY_SIZE);
    printf("Number of threads: %d\n\n", NUM_THREADS);

    // Benchmark sequential vs parallel sum
    clock_t start, end;
    double sequential_time, parallel_time;

    printf("Sum Operation:\n");

    start = clock();
    long long seq_sum = sequential_sum(test_array, ARRAY_SIZE);
    end = clock();
    sequential_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    start = clock();
    long long par_sum = parallel_sum(test_array, ARRAY_SIZE, NUM_THREADS);
    end = clock();
    parallel_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("  Sequential: %lld (%.6f seconds)\n", seq_sum, sequential_time);
    printf("  Parallel:   %lld (%.6f seconds)\n", par_sum, parallel_time);
    printf("  Speedup:    %.2fx\n", sequential_time / parallel_time);

    // Benchmark other operations
    printf("\nOther Operations:\n");

    start = clock();
    long long seq_max = parallel_process(test_array, ARRAY_SIZE, OP_MAX, 1);
    end = clock();
    sequential_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    start = clock();
    long long par_max = parallel_process(test_array, ARRAY_SIZE, OP_MAX, NUM_THREADS);
    end = clock();
    parallel_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("  Max - Sequential: %lld (%.6f seconds)\n", seq_max, sequential_time);
    printf("  Max - Parallel:   %lld (%.6f seconds)\n", par_max, parallel_time);
    printf("  Max - Speedup:    %.2fx\n", sequential_time / parallel_time);

    start = clock();
    long long seq_even = parallel_process(test_array, ARRAY_SIZE, OP_COUNT_EVEN, 1);
    end = clock();
    sequential_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    start = clock();
    long long par_even = parallel_process(test_array, ARRAY_SIZE, OP_COUNT_EVEN, NUM_THREADS);
    end = clock();
    parallel_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("  Even Count - Sequential: %lld (%.6f seconds)\n", seq_even, sequential_time);
    printf("  Even Count - Parallel:   %lld (%.6f seconds)\n", par_even, parallel_time);
    printf("  Even Count - Speedup:    %.2fx\n", sequential_time / parallel_time);

    free(test_array);
}

void demonstrate_work_stealing() {
    printf("\n=== Work Stealing Demonstration ===\n\n");

    WorkQueue* queue = create_work_queue(1000);
    pthread_t threads[NUM_THREADS];
    WorkerThreadData thread_data[NUM_THREADS];
    int results[NUM_THREADS] = {0};

    // Initialize worker threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_data[i].queue = queue;
        thread_data[i].results = results;
        thread_data[i].thread_id = i;
        pthread_create(&threads[i], NULL, worker_thread, &thread_data[i]);
    }

    // Add work items
    printf("Adding 1000 work items to queue...\n");
    for (int i = 0; i < 1000; i++) {
        enqueue_work(queue, rand() % 100);
    }

    // Add sentinel values to stop threads
    for (int i = 0; i < NUM_THREADS; i++) {
        enqueue_work(queue, -1);
    }

    // Wait for threads to complete
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Report results
    printf("Thread results:\n");
    long long total = 0;
    for (int i = 0; i < NUM_THREADS; i++) {
        printf("  Thread %d: %d\n", i, results[i]);
        total += results[i];
    }
    printf("Total work processed: %lld\n", total);

    destroy_work_queue(queue);
}

int main() {
    printf("Parallel Programming Optimization\n");
    printf("==================================\n\n");

    benchmark_parallel_operations();
    demonstrate_work_stealing();

    printf("\nPerformance Optimization Tips:\n");
    printf("1. Profile before optimizing\n");
    printf("2. Focus on algorithmic complexity first\n");
    printf("3. Consider memory access patterns\n");
    printf("4. Use compiler optimizations (-O2, -O3)\n");
    printf("5. Parallelize CPU-bound tasks\n");
    printf("6. Minimize memory allocations\n");
    printf("7. Use appropriate data structures\n");
    printf("8. Consider vectorization opportunities\n");

    return 0;
}
```

## Security Considerations

### Secure Coding Practices

```c
// security_optimization.c - Secure coding practices that also improve performance
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Secure string operations (also optimized)
int safe_strcpy(char* dest, size_t dest_size, const char* src) {
    if (!dest || !src || dest_size == 0) {
        return -1; // Invalid parameters
    }

    size_t src_len = strlen(src);
    if (src_len >= dest_size) {
        return -2; // Destination too small
    }

    memcpy(dest, src, src_len + 1); // Include null terminator
    return 0;
}

// Bounds-checked array access
int safe_array_access(int* array, size_t size, size_t index) {
    if (!array || index >= size) {
        return 0; // Return default value or handle error
    }
    return array[index];
}

// Memory management with error checking
void* safe_malloc(size_t size) {
    if (size == 0) {
        return NULL;
    }

    void* ptr = malloc(size);
    if (ptr) {
        memset(ptr, 0, size); // Initialize to zero for security
    }
    return ptr;
}

// Secure random number generation
void generate_secure_random(unsigned char* buffer, size_t size) {
    // In a real implementation, use /dev/urandom or crypto API
    srand(time(NULL));
    for (size_t i = 0; i < size; i++) {
        buffer[i] = (unsigned char)rand();
    }
}

// Input validation
int validate_input(const char* input, size_t max_length) {
    if (!input) {
        return 0; // Invalid input
    }

    size_t len = strlen(input);
    if (len >= max_length) {
        return 0; // Input too long
    }

    // Check for dangerous characters
    for (size_t i = 0; i < len; i++) {
        if (input[i] < 32 || input[i] > 126) {
            return 0; // Non-printable character
        }
    }

    return 1; // Valid input
}

// Performance comparison
void compare_safe_vs_unsafe() {
    printf("=== Security vs Performance Analysis ===\n\n");

    const int ITERATIONS = 1000000;
    const char test_string[] = "Hello, World!";
    char buffer[64];

    // Time unsafe strcpy
    clock_t start = clock();
    for (int i = 0; i < ITERATIONS; i++) {
        strcpy(buffer, test_string);
    }
    clock_t end = clock();
    double unsafe_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Time safe string copy
    start = clock();
    for (int i = 0; i < ITERATIONS; i++) {
        safe_strcpy(buffer, sizeof(buffer), test_string);
    }
    end = clock();
    double safe_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("String copy performance (%d iterations):\n", ITERATIONS);
    printf("  Unsafe strcpy: %.6f seconds\n", unsafe_time);
    printf("  Safe string copy: %.6f seconds\n", safe_time);
    printf("  Performance ratio: %.2fx\n", safe_time / unsafe_time);

    printf("\nSecurity benefits of safe functions:\n");
    printf("  Prevents buffer overflows\n");
    printf("  Validates input parameters\n");
    printf("  Handles edge cases gracefully\n");
    printf("  Provides error reporting\n");
}

int main() {
    printf("Security and Performance Optimization\n");
    printf("====================================\n\n");

    compare_safe_vs_unsafe();

    // Demonstrate safe practices
    printf("\nSafe Coding Practices:\n");
    printf("1. Use bounds-checked functions\n");
    printf("2. Validate all inputs\n");
    printf("3. Initialize memory properly\n");
    printf("4. Check return values\n");
    printf("5. Use secure random generators\n");
    printf("6. Implement proper error handling\n");
    printf("7. Follow the principle of least privilege\n");
    printf("8. Keep security-critical code simple\n");

    return 0;
}
```

## Best Practices

### Performance Optimization Guidelines

1. **Measure First, Optimize Second**
   - Profile to find bottlenecks
   - Use realistic test data
   - Measure before and after changes

2. **Algorithmic Optimization**
   - Choose the right data structures
   - Consider time and space complexity
   - Balance readability with performance

3. **Memory Efficiency**
   - Minimize memory allocations
   - Use cache-friendly access patterns
   - Align data structures properly

4. **Compiler Optimizations**
   - Use appropriate optimization flags
   - Enable link-time optimization
   - Profile-guided optimization

5. **Parallel Programming**
   - Identify CPU-bound tasks
   - Use appropriate threading models
   - Minimize synchronization overhead

## Exercises

### Exercise 15.1: Profiling
Profile a complex program and identify performance bottlenecks.

### Exercise 15.2: Algorithm Optimization
Optimize an O(n²) algorithm to O(n log n) or O(n).

### Exercise 15.3: Memory Optimization
Improve cache locality in a memory-intensive program.

### Exercise 15.4: Parallel Implementation
Convert a sequential algorithm to a parallel one.

### Exercise 15.5: Compiler Flags
Compare performance with different compiler optimization levels.

## Challenge Problems

### Challenge 15.1: SIMD Optimization
Use SIMD instructions to optimize vector operations.

### Challenge 15.2: Cache Optimization
Implement a cache-oblivious algorithm.

### Challenge 15.3: Real-time Optimization
Optimize a program for real-time performance requirements.

## Quick Reference

### Optimization Techniques
```c
// Algorithm optimization
- Choose appropriate data structures
- Use efficient algorithms (O(log n) vs O(n²))
- Implement memoization for repeated calculations

// Memory optimization
- Use stack allocation for small objects
- Implement memory pools for frequent allocations
- Align data structures for cache efficiency
- Minimize pointer chasing

// Compiler optimizations
gcc -O0     // No optimization
gcc -O1     // Basic optimization
gcc -O2     // Standard optimization (recommended)
gcc -O3     // Aggressive optimization
gcc -Os     // Optimize for size
gcc -march=native  // Optimize for current CPU

// Parallel programming
- Use pthreads for multi-threading
- Implement work stealing queues
- Minimize lock contention
- Use lock-free data structures when possible

// Profiling tools
- gprof: Function-level profiling
- Valgrind: Memory profiling and leak detection
- perf: Linux performance counters
- Intel VTune: Detailed profiling (Intel CPUs)
```

### Performance Checklist
- [ ] Profile to identify bottlenecks
- [ ] Optimize algorithms first
- [ ] Improve memory access patterns
- [ ] Use compiler optimizations
- [ ] Consider parallelization
- [ ] Minimize I/O operations
- [ ] Use appropriate data structures
- [ ] Cache frequently accessed data

## Next Steps
Once you're comfortable with:
- Profiling and identifying bottlenecks
- Applying algorithmic optimizations
- Understanding memory access patterns
- Using compiler optimizations effectively
- Implementing parallel solutions

You're ready for **Chapter 16: C in Modern Development**!