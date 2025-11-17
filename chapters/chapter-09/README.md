# Chapter 9: Memory Management

## Learning Objectives
By the end of this chapter, you will be able to:
- Understand memory layout in C programs
- Use dynamic memory allocation functions
- Detect and prevent memory leaks
- Implement efficient memory management
- Handle memory allocation failures
- Optimize memory usage in applications
- Use memory debugging tools

## Memory Layout in C Programs

### Program Memory Organization
```c
#include <stdio.h>
#include <stdlib.h>

int global_var = 100;          // Data segment (initialized)
static int static_var = 200;   // Data segment (initialized)
int uninit_global;             // BSS segment (uninitialized)

void demonstrate_memory_layout() {
    int local_var = 50;        // Stack
    static int static_local = 75; // Data segment (initialized)
    int *heap_var;             // Heap

    printf("Memory Layout Demo\n");
    printf("=================\n");
    printf("Local variable (stack): %p\n", (void*)&local_var);
    printf("Static local (data): %p\n", (void*)&static_local);
    printf("Global variable (data): %p\n", (void*)&global_var);
    printf("Uninitialized global (BSS): %p\n", (void*)&uninit_global);

    heap_var = (int*)malloc(sizeof(int));
    if (heap_var) {
        printf("Heap variable: %p\n", (void*)heap_var);
        free(heap_var);
    }

    printf("Function address: %p\n", (void*)demonstrate_memory_layout);
}

int main() {
    demonstrate_memory_layout();

    printf("\nMemory Segments:\n");
    printf("Text: Program code and constants\n");
    printf("Data: Initialized global and static variables\n");
    printf("BSS: Uninitialized global and static variables\n");
    printf("Heap: Dynamically allocated memory\n");
    printf("Stack: Local variables and function calls\n");

    return 0;
}
```

### Stack vs Heap Memory
```c
#include <stdio.h>
#include <stdlib.h>

void stack_allocation() {
    int numbers[1000];  // Stack allocation
    printf("Stack array address: %p\n", (void*)numbers);
    // Automatically freed when function returns
}

void heap_allocation() {
    int *numbers = (int*)malloc(1000 * sizeof(int));  // Heap allocation
    if (numbers) {
        printf("Heap array address: %p\n", (void*)numbers);
        free(numbers);  // Manual deallocation required
    }
}

int main() {
    printf("Stack vs Heap Memory\n");
    printf("====================\n");

    printf("Stack allocation:\n");
    stack_allocation();

    printf("\nHeap allocation:\n");
    heap_allocation();

    printf("\nComparison:\n");
    printf("Stack:\n");
    printf("  - Automatic allocation/deallocation\n");
    printf("  - Fast access\n");
    printf("  - Limited size (typically a few MB)\n");
    printf("  - LIFO order\n");

    printf("\nHeap:\n");
    printf("  - Manual allocation/deallocation\n");
    printf("  - Slower than stack\n");
    printf("  - Larger size (limited by system memory)\n");
    printf("  - Flexible allocation order\n");
    printf("  - Can cause memory leaks\n");

    return 0;
}
```

## Dynamic Memory Allocation Functions

### malloc and free
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int *numbers;
    char *text;
    int size;

    printf("malloc and free Demo\n");
    printf("===================\n");

    // Allocate memory for integers
    printf("Enter number of integers: ");
    scanf("%d", &size);

    numbers = (int*)malloc(size * sizeof(int));
    if (numbers == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    printf("Successfully allocated %d integers (%zu bytes)\n",
           size, size * sizeof(int));

    // Initialize and display
    for (int i = 0; i < size; i++) {
        numbers[i] = (i + 1) * 10;
    }

    printf("Array contents: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    // Free the memory
    free(numbers);
    printf("Memory freed.\n");

    // Allocate memory for string
    text = (char*)malloc(100 * sizeof(char));
    if (text == NULL) {
        printf("String allocation failed!\n");
        return 1;
    }

    strcpy(text, "Hello, dynamic memory!");
    printf("String: %s\n", text);

    free(text);
    printf("String memory freed.\n");

    return 0;
}
```

### calloc for Zero-Initialized Memory
```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *numbers1, *numbers2;
    int size = 10;

    printf("calloc vs malloc\n");
    printf("=================\n");

    // malloc - uninitialized memory (contains garbage)
    numbers1 = (int*)malloc(size * sizeof(int));
    if (numbers1) {
        printf("malloc allocation (uninitialized):\n");
        for (int i = 0; i < size; i++) {
            printf("numbers1[%d] = %d\n", i, numbers1[i]);
        }
        free(numbers1);
    }

    // calloc - zero-initialized memory
    numbers2 = (int*)calloc(size, sizeof(int));
    if (numbers2) {
        printf("\ncalloc allocation (zero-initialized):\n");
        for (int i = 0; i < size; i++) {
            printf("numbers2[%d] = %d\n", i, numbers2[i]);
        }
        free(numbers2);
    }

    printf("\ncalloc advantages:\n");
    printf("- Memory is initialized to zero\n");
    printf("- Safer for numeric data\n");
    printf("- Slightly slower than malloc\n");

    return 0;
}
```

### realloc for Resizing Memory
```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *numbers = NULL;
    int capacity = 5;
    int count = 0;

    printf("realloc Demo\n");
    printf("============\n");

    // Initial allocation
    numbers = (int*)malloc(capacity * sizeof(int));
    if (numbers == NULL) {
        printf("Initial allocation failed!\n");
        return 1;
    }

    printf("Initial capacity: %d\n", capacity);

    // Add numbers and resize as needed
    for (int i = 1; i <= 20; i++) {
        if (count >= capacity) {
            // Resize array
            int new_capacity = capacity * 2;
            int *new_numbers = (int*)realloc(numbers, new_capacity * sizeof(int));

            if (new_numbers == NULL) {
                printf("Reallocation failed!\n");
                free(numbers);
                return 1;
            }

            numbers = new_numbers;
            capacity = new_capacity;
            printf("Resized to capacity: %d\n", capacity);
        }

        numbers[count] = i * i;
        count++;
    }

    printf("\nFinal array (first %d elements):\n", count);
    for (int i = 0; i < count; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    printf("Final capacity: %d\n", capacity);
    printf("Elements used: %d\n", count);

    // Shrink to fit
    numbers = (int*)realloc(numbers, count * sizeof(int));
    printf("Shrunk to exact size: %zu bytes\n", count * sizeof(int));

    free(numbers);
    return 0;
}
```

## Memory Allocation Patterns

### Dynamic Array Implementation
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    int count;
    int capacity;
} StringArray;

int init_array(StringArray *array, int initial_capacity) {
    array->items = (char**)malloc(initial_capacity * sizeof(char*));
    if (array->items == NULL) {
        return 0; // Failed
    }

    array->count = 0;
    array->capacity = initial_capacity;
    return 1; // Success
}

int add_item(StringArray *array, const char *item) {
    // Resize if needed
    if (array->count >= array->capacity) {
        int new_capacity = array->capacity * 2;
        char **new_items = (char**)realloc(array->items,
                                           new_capacity * sizeof(char*));
        if (new_items == NULL) {
            return 0; // Failed
        }
        array->items = new_items;
        array->capacity = new_capacity;
    }

    // Allocate memory for string and copy
    array->items[array->count] = (char*)malloc(strlen(item) + 1);
    if (array->items[array->count] == NULL) {
        return 0; // Failed
    }

    strcpy(array->items[array->count], item);
    array->count++;
    return 1; // Success
}

void free_array(StringArray *array) {
    for (int i = 0; i < array->count; i++) {
        free(array->items[i]);
    }
    free(array->items);
    array->items = NULL;
    array->count = 0;
    array->capacity = 0;
}

void display_array(const StringArray *array) {
    printf("Array (%d/%d items):\n", array->count, array->capacity);
    for (int i = 0; i < array->count; i++) {
        printf("  [%d] %s\n", i, array->items[i]);
    }
}

int main() {
    StringArray fruits;

    printf("Dynamic String Array\n");
    printf("====================\n");

    if (!init_array(&fruits, 3)) {
        printf("Failed to initialize array\n");
        return 1;
    }

    // Add items (will trigger resizing)
    add_item(&fruits, "Apple");
    add_item(&fruits, "Banana");
    add_item(&fruits, "Orange");
    add_item(&fruits, "Grape");  // Triggers resize
    add_item(&fruits, "Mango");
    add_item(&fruits, "Pineapple");
    add_item(&fruits, "Strawberry");

    display_array(&fruits);
    free_array(&fruits);

    return 0;
}
```

### Memory Pool Allocator
```c
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *memory;
    size_t size;
    size_t used;
} MemoryPool;

MemoryPool* create_pool(size_t size) {
    MemoryPool *pool = (MemoryPool*)malloc(sizeof(MemoryPool));
    if (!pool) return NULL;

    pool->memory = (char*)malloc(size);
    if (!pool->memory) {
        free(pool);
        return NULL;
    }

    pool->size = size;
    pool->used = 0;
    return pool;
}

void* pool_alloc(MemoryPool *pool, size_t size) {
    if (pool->used + size > pool->size) {
        return NULL; // Not enough memory
    }

    void *ptr = pool->memory + pool->used;
    pool->used += size;
    return ptr;
}

void destroy_pool(MemoryPool *pool) {
    if (pool) {
        free(pool->memory);
        free(pool);
    }
}

void display_pool_info(const MemoryPool *pool) {
    printf("Pool Info:\n");
    printf("  Total size: %zu bytes\n", pool->size);
    printf("  Used: %zu bytes\n", pool->used);
    printf("  Available: %zu bytes\n", pool->size - pool->used);
    printf("  Utilization: %.1f%%\n",
           (float)pool->used * 100 / pool->size);
}

int main() {
    MemoryPool *pool = create_pool(1024);  // 1KB pool
    if (!pool) {
        printf("Failed to create memory pool\n");
        return 1;
    }

    printf("Memory Pool Allocator\n");
    printf("=====================\n");

    display_pool_info(pool);

    // Allocate various sized blocks
    int *numbers = (int*)pool_alloc(pool, 10 * sizeof(int));
    char *text = (char*)pool_alloc(pool, 100);
    double *values = (double*)pool_alloc(pool, 5 * sizeof(double));

    printf("\nAfter allocations:\n");
    display_pool_info(pool);

    if (numbers) {
        printf("Allocated %zu bytes for integers\n", 10 * sizeof(int));
        for (int i = 0; i < 10; i++) {
            numbers[i] = i * i;
        }
    }

    if (text) {
        printf("Allocated %zu bytes for text\n", 100);
        strcpy(text, "Memory pool is working!");
    }

    if (values) {
        printf("Allocated %zu bytes for doubles\n", 5 * sizeof(double));
        for (int i = 0; i < 5; i++) {
            values[i] = i * 3.14;
        }
    }

    // Try to allocate more than available
    char *too_big = (char*)pool_alloc(pool, 2000);
    if (!too_big) {
        printf("\nFailed to allocate 2000 bytes (expected - not enough space)\n");
    }

    display_pool_info(pool);

    destroy_pool(pool);
    return 0;
}
```

## Memory Leak Detection and Prevention

### Simple Memory Leak Detector
```c
#include <stdio.h>
#include <stdlib.h>

typedef struct Allocation {
    void *ptr;
    size_t size;
    const char *file;
    int line;
    struct Allocation *next;
} Allocation;

static Allocation *allocations = NULL;
static size_t total_allocated = 0;
static int allocation_count = 0;

void* debug_malloc(size_t size, const char *file, int line) {
    void *ptr = malloc(size);
    if (ptr) {
        Allocation *alloc = (Allocation*)malloc(sizeof(Allocation));
        if (alloc) {
            alloc->ptr = ptr;
            alloc->size = size;
            alloc->file = file;
            alloc->line = line;
            alloc->next = allocations;
            allocations = alloc;

            total_allocated += size;
            allocation_count++;

            printf("MALLOC: %zu bytes at %p (%s:%d)\n", size, ptr, file, line);
        }
    }
    return ptr;
}

void debug_free(void *ptr, const char *file, int line) {
    if (!ptr) return;

    // Find and remove allocation from list
    Allocation **current = &allocations;
    while (*current) {
        if ((*current)->ptr == ptr) {
            Allocation *to_remove = *current;
            *current = (*current)->next;

            printf("FREE: %zu bytes at %p (%s:%d)\n",
                   to_remove->size, ptr, file, line);

            total_allocated -= to_remove->size;
            allocation_count--;

            free(to_remove);
            break;
        }
        current = &(*current)->next;
    }

    free(ptr);
}

void print_memory_leaks() {
    printf("\n=== MEMORY LEAK REPORT ===\n");
    if (allocations) {
        printf("LEAKS DETECTED:\n");
        Allocation *current = allocations;
        while (current) {
            printf("Leaked: %zu bytes at %p (allocated at %s:%d)\n",
                   current->size, current->ptr, current->file, current->line);
            current = current->next;
        }
    } else {
        printf("No memory leaks detected!\n");
    }
    printf("Total allocated: %zu bytes\n", total_allocated);
    printf("Active allocations: %d\n", allocation_count);
    printf("=========================\n");
}

// Macros for easier use
#define MALLOC(size) debug_malloc(size, __FILE__, __LINE__)
#define FREE(ptr) debug_free(ptr, __FILE__, __LINE__)

int main() {
    printf("Memory Leak Detection\n");
    printf("=====================\n");

    // Normal allocation and deallocation
    int *normal = (int*)MALLOC(sizeof(int));
    *normal = 42;
    printf("Normal allocation: %d\n", *normal);
    FREE(normal);

    // Intentional leak for demonstration
    char *leaked = (char*)MALLOC(100);
    strcpy(leaked, "This will be leaked");

    // Another leak
    int *another_leak = (int*)MALLOC(10 * sizeof(int));

    printf("\nProgram ending - checking for leaks...\n");
    print_memory_leaks();

    return 0;
}
```

### Safe Memory Wrapper Functions
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void* safe_malloc(size_t size) {
    void *ptr = malloc(size);
    if (ptr == NULL) {
        fprintf(stderr, "Fatal error: Memory allocation failed for %zu bytes\n", size);
        exit(EXIT_FAILURE);
    }
    return ptr;
}

void* safe_realloc(void *ptr, size_t size) {
    void *new_ptr = realloc(ptr, size);
    if (new_ptr == NULL && size > 0) {
        fprintf(stderr, "Fatal error: Memory reallocation failed for %zu bytes\n", size);
        free(ptr);
        exit(EXIT_FAILURE);
    }
    return new_ptr;
}

char* safe_strdup(const char *str) {
    char *new_str = (char*)safe_malloc(strlen(str) + 1);
    strcpy(new_str, str);
    return new_str;
}

void safe_free(void **ptr) {
    if (ptr && *ptr) {
        free(*ptr);
        *ptr = NULL;
    }
}

int main() {
    printf("Safe Memory Wrapper Functions\n");
    printf("===========================\n");

    // Test safe_malloc
    int *numbers = (int*)safe_malloc(10 * sizeof(int));
    printf("Allocated integers successfully\n");

    for (int i = 0; i < 10; i++) {
        numbers[i] = (i + 1) * 10;
    }

    // Test safe_realloc
    numbers = (int*)safe_realloc(numbers, 20 * sizeof(int));
    printf("Reallocated to 20 integers successfully\n");

    // Test safe_strdup
    char *text = safe_strdup("Hello, safe memory management!");
    printf("Duplicated string: %s\n", text);

    // Test safe_free
    safe_free((void**)&text);
    printf("String freed (pointer set to NULL)\n");

    if (text == NULL) {
        printf("Pointer is NULL after safe_free (correct)\n");
    }

    safe_free((void**)&numbers);
    printf("Integer array freed\n");

    return 0;
}
```

## Advanced Memory Management

### Custom Garbage Collector (Simple)
```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_OBJECTS 1000

typedef struct {
    void *ptr;
    bool marked;
    size_t size;
} GCObject;

static GCObject objects[MAX_OBJECTS];
static int object_count = 0;

void gc_add(void *ptr, size_t size) {
    if (object_count < MAX_OBJECTS) {
        objects[object_count].ptr = ptr;
        objects[object_count].marked = false;
        objects[object_count].size = size;
        object_count++;
    }
}

void gc_mark_all() {
    for (int i = 0; i < object_count; i++) {
        objects[i].marked = false;
    }
}

void gc_mark_root(void *ptr) {
    for (int i = 0; i < object_count; i++) {
        if (objects[i].ptr == ptr) {
            objects[i].marked = true;
            break;
        }
    }
}

void gc_collect() {
    printf("Garbage collection started...\n");
    int collected = 0;
    size_t freed_bytes = 0;

    for (int i = 0; i < object_count; ) {
        if (!objects[i].marked) {
            printf("Freeing unmarked object: %zu bytes\n", objects[i].size);
            freed_bytes += objects[i].size;
            free(objects[i].ptr);

            // Remove from array
            for (int j = i; j < object_count - 1; j++) {
                objects[j] = objects[j + 1];
            }
            object_count--;
            collected++;
        } else {
            i++;
        }
    }

    printf("GC completed: collected %d objects, freed %zu bytes\n",
           collected, freed_bytes);
}

void gc_stats() {
    size_t total_memory = 0;
    int marked_objects = 0;

    for (int i = 0; i < object_count; i++) {
        total_memory += objects[i].size;
        if (objects[i].marked) {
            marked_objects++;
        }
    }

    printf("GC Stats: %d objects, %zu bytes, %d marked\n",
           object_count, total_memory, marked_objects);
}

int main() {
    printf("Simple Garbage Collector\n");
    printf("========================\n");

    // Simulate object allocation
    int *data1 = (int*)malloc(100 * sizeof(int));
    int *data2 = (int*)malloc(50 * sizeof(int));
    int *data3 = (int*)malloc(75 * sizeof(int));
    int *data4 = (int*)malloc(200 * sizeof(int));

    // Add to GC
    gc_add(data1, 100 * sizeof(int));
    gc_add(data2, 50 * sizeof(int));
    gc_add(data3, 75 * sizeof(int));
    gc_add(data4, 200 * sizeof(int));

    // Initialize data
    for (int i = 0; i < 100; i++) data1[i] = i;
    for (int i = 0; i < 50; i++) data2[i] = i * 2;

    // Mark some objects as roots (still in use)
    gc_mark_root(data1);
    gc_mark_root(data3);

    printf("Before GC:\n");
    gc_stats();

    // Run garbage collection
    gc_collect();

    printf("\nAfter GC:\n");
    gc_stats();

    // data2 and data4 should be freed, data1 and data3 remain
    printf("\nData1 still accessible: %d\n", data1[0]);
    printf("Data3 still accessible: %d\n", data3[0]);

    // Clean up remaining objects
    free(data1);
    free(data3);

    return 0;
}
```

### Memory Pool for Performance
```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define POOL_SIZE 1024 * 1024  // 1MB
#define NUM_ALLOCATIONS 10000

typedef struct {
    char *pool;
    size_t offset;
    size_t size;
} SimplePool;

SimplePool* create_pool(size_t size) {
    SimplePool *pool = (SimplePool*)malloc(sizeof(SimplePool));
    if (!pool) return NULL;

    pool->pool = (char*)malloc(size);
    if (!pool->pool) {
        free(pool);
        return NULL;
    }

    pool->offset = 0;
    pool->size = size;
    return pool;
}

void* pool_alloc(SimplePool *pool, size_t size) {
    if (pool->offset + size > pool->size) {
        return NULL; // Pool exhausted
    }

    void *ptr = pool->pool + pool->offset;
    pool->offset += size;
    return ptr;
}

void destroy_pool(SimplePool *pool) {
    if (pool) {
        free(pool->pool);
        free(pool);
    }
}

double test_standard_allocation() {
    clock_t start = clock();
    void *pointers[NUM_ALLOCATIONS];

    for (int i = 0; i < NUM_ALLOCATIONS; i++) {
        pointers[i] = malloc(100);
    }

    for (int i = 0; i < NUM_ALLOCATIONS; i++) {
        free(pointers[i]);
    }

    clock_t end = clock();
    return ((double)(end - start)) / CLOCKS_PER_SEC * 1000; // milliseconds
}

double test_pool_allocation() {
    SimplePool *pool = create_pool(POOL_SIZE);
    if (!pool) return -1;

    clock_t start = clock();
    void *pointers[NUM_ALLOCATIONS];

    for (int i = 0; i < NUM_ALLOCATIONS; i++) {
        pointers[i] = pool_alloc(pool, 100);
        if (!pointers[i]) break; // Pool exhausted
    }

    destroy_pool(pool);
    clock_t end = clock();

    return ((double)(end - start)) / CLOCKS_PER_SEC * 1000; // milliseconds
}

int main() {
    printf("Memory Performance Comparison\n");
    printf("============================\n");

    double std_time = test_standard_allocation();
    double pool_time = test_pool_allocation();

    printf("Standard malloc/free: %.2f ms\n", std_time);
    printf("Pool allocation: %.2f ms\n", pool_time);

    if (pool_time > 0) {
        printf("Performance improvement: %.1fx\n", std_time / pool_time);
    }

    printf("\nBenefits of memory pools:\n");
    printf("- Faster allocation/deallocation\n");
    printf("- Reduced fragmentation\n");
    printf("- Better cache locality\n");
    printf("- Simpler deallocation (free entire pool)\n");

    return 0;
}
```

## Memory Debugging Tools

### Valgrind Integration Example
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void demonstrate_memory_issues() {
    printf("Demonstrating Memory Issues (for Valgrind)\n");
    printf("===========================================\n");

    // Issue 1: Memory leak
    char *leaked = (char*)malloc(100);
    strcpy(leaked, "This memory will be leaked");
    printf("1. Created memory leak: %s\n", leaked);
    // Forgot to free(leaked)

    // Issue 2: Use after free
    int *use_after_free = (int*)malloc(sizeof(int));
    *use_after_free = 42;
    free(use_after_free);
    printf("2. Freed memory, but pointer still accessible (UB): %d\n", *use_after_free);

    // Issue 3: Buffer overflow
    char buffer[10];
    strcpy(buffer, "This string is too long for buffer"); // Overflow
    printf("3. Buffer overflow occurred\n");

    // Issue 4: Double free
    int *double_free = (int*)malloc(sizeof(int));
    *double_free = 100;
    free(double_free);
    free(double_free); // Double free
    printf("4. Double free occurred\n");

    // Issue 5: Uninitialized memory
    int *uninitialized = (int*)malloc(sizeof(int));
    printf("5. Uninitialized value: %d\n", *uninitialized);
    free(uninitialized);

    // Good practice example
    char *good = (char*)malloc(50);
    if (good) {
        strcpy(good, "Properly managed memory");
        printf("6. Good example: %s\n", good);
        free(good);
        good = NULL; // Prevent use after free
    }
}

int main() {
    printf("Memory Debugging Examples\n");
    printf("=========================\n");
    printf("Run this program with Valgrind:\n");
    printf("valgrind --leak-check=full --show-leak-kinds=all ./program\n\n");

    demonstrate_memory_issues();

    printf("\nCommon Valgrind Issues:\n");
    printf("- Definitely lost: Memory leaks\n");
    printf("- Invalid write: Buffer overflow\n");
    printf("- Invalid read: Use after free or uninitialized memory\n");
    printf("- Double free: Freeing same memory twice\n");
    printf("- Still reachable: Memory not freed at program exit\n");

    return 0;
}
```

## Best Practices

### Memory Management Guidelines
1. **Always check** return values of allocation functions
2. **Free all allocated memory** to prevent leaks
3. **Set pointers to NULL** after freeing
4. **Use appropriate allocation functions** for your needs
5. **Initialize allocated memory** to prevent undefined behavior

### Performance Optimization
1. **Pool allocation** for many small objects
2. **Avoid frequent reallocation** - allocate upfront when possible
3. **Use stack allocation** for small, short-lived objects
4. **Align data properly** for better performance
5. **Profile memory usage** to find bottlenecks

### Debugging Techniques
1. **Use memory debuggers** like Valgrind
2. **Implement custom allocators** with tracking
3. **Add assert statements** for pointer validation
4. **Use static analysis tools** to catch issues
5. **Test with memory sanitizers**

## Common Errors and Solutions

### Error: Memory Leak
**Cause**: Forgetting to free allocated memory
**Solution**: Track all allocations and ensure corresponding frees

### Error: Double Free
**Cause**: Freeing the same pointer twice
**Solution**: Set pointer to NULL after freeing

### Error: Buffer Overflow
**Cause**: Writing beyond allocated memory
**Solution**: Check bounds and allocate sufficient memory

### Error: Use After Free
**Cause**: Using memory after it's been freed
**Solution**: Set pointer to NULL and check before use

### Error: Dangling Pointer
**Cause**: Pointer to memory that's been reallocated
**Solution**: Update all references when memory moves

## Exercises

### Exercise 9.1: Dynamic Matrix
Create a dynamic 2D matrix with proper memory management.

### Exercise 9.2: Memory Pool
Implement a memory pool for fixed-size allocations.

### Exercise 9.3: String Builder
Create a dynamic string that grows as needed.

### Exercise 9.4: Leak Detector
Build a simple memory leak detection system.

### Exercise 9.5: Performance Test
Compare malloc vs pool allocation performance.

## Challenge Problems

### Challenge 9.1: Smart Pointer
Implement a reference-counted smart pointer system.

### Challenge 9.2: Memory Allocator
Write your own malloc/free implementation.

### Challenge 9.3: Defragmentation
Implement heap defragmentation for a custom allocator.

## Quick Reference

### Memory Allocation Functions
- **malloc(size)**: Allocate uninitialized memory
- **calloc(count, size)**: Allocate zero-initialized memory
- **realloc(ptr, size)**: Resize allocated memory
- **free(ptr)**: Deallocate memory

### Memory Layout
- **Stack**: Automatic local variables
- **Heap**: Dynamic allocation
- **Data**: Global and static variables
- **Text**: Program code

### Debugging Tools
- **Valgrind**: Memory error detection
- **AddressSanitizer**: Fast memory error detector
- **Static analysis**: Compile-time checking

## Next Steps
Once you're comfortable with:
- Dynamic memory allocation and deallocation
- Memory leak detection and prevention
- Performance optimization techniques
- Debugging memory issues
- Implementing custom allocators

You're ready for **Chapter 10: Advanced Topics**!

Proper memory management is crucial for robust, efficient C programs and separates professional developers from beginners.