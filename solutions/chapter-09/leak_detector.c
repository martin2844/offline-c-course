#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

#define MALLOC(size) debug_malloc(size, __FILE__, __LINE__)
#define FREE(ptr) debug_free(ptr, __FILE__, __LINE__)

void test_memory_management() {
    printf("Testing memory management...\n");

    // Test 1: Normal allocation and free
    int *normal = (int*)MALLOC(sizeof(int));
    *normal = 42;
    printf("Normal allocation: %d\n", *normal);
    FREE(normal);

    // Test 2: Multiple allocations
    char *strings[5];
    for (int i = 0; i < 5; i++) {
        strings[i] = (char*)MALLOC(50);
        if (strings[i]) {
            sprintf(strings[i], "String %d", i);
        }
    }

    // Free some, leak others
    for (int i = 0; i < 3; i++) {
        FREE(strings[i]);
    }

    // Test 3: Array allocation
    double *array = (double*)MALLOC(10 * sizeof(double));
    if (array) {
        for (int i = 0; i < 10; i++) {
            array[i] = i * 3.14;
        }
    }
    // Intentionally not freeing this to show leak detection

    printf("Memory test completed.\n");
}

int main() {
    printf("Memory Leak Detector\n");
    printf("====================\n");

    test_memory_management();

    printf("\nProgram ending - checking for leaks...\n");
    print_memory_leaks();

    return 0;
}