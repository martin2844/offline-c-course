#include <stdio.h>
#include <stdlib.h>

#define POOL_SIZE 4096
#define BLOCK_SIZE 64
#define MAX_BLOCKS (POOL_SIZE / BLOCK_SIZE)

typedef struct {
    char memory[POOL_SIZE];
    int used[MAX_BLOCKS];  // 0 = free, 1 = used
    int total_used;
} MemoryPool;

MemoryPool* create_pool() {
    MemoryPool *pool = (MemoryPool*)malloc(sizeof(MemoryPool));
    if (!pool) return NULL;

    for (int i = 0; i < MAX_BLOCKS; i++) {
        pool->used[i] = 0;
    }
    pool->total_used = 0;

    return pool;
}

void destroy_pool(MemoryPool *pool) {
    free(pool);
}

void* pool_alloc(MemoryPool *pool) {
    if (!pool) return NULL;

    // Find first free block
    for (int i = 0; i < MAX_BLOCKS; i++) {
        if (!pool->used[i]) {
            pool->used[i] = 1;
            pool->total_used++;
            return &pool->memory[i * BLOCK_SIZE];
        }
    }

    return NULL; // Pool full
}

void pool_free(MemoryPool *pool, void *ptr) {
    if (!pool || !ptr) return;

    // Find which block this pointer belongs to
    char *memory_ptr = (char*)ptr;
    int block = (memory_ptr - pool->memory) / BLOCK_SIZE;

    if (block >= 0 && block < MAX_BLOCKS) {
        pool->used[block] = 0;
        pool->total_used--;
    }
}

void print_pool_stats(MemoryPool *pool) {
    if (!pool) return;

    printf("Pool Statistics:\n");
    printf("  Total blocks: %d\n", MAX_BLOCKS);
    printf("  Used blocks: %d\n", pool->total_used);
    printf("  Free blocks: %d\n", MAX_BLOCKS - pool->total_used);
    printf("  Usage: %.1f%%\n", (float)pool->total_used * 100 / MAX_BLOCKS);
}

int main() {
    MemoryPool *pool;
    void *ptrs[10];
    int num_allocated = 0;

    printf("Memory Pool Demo\n");
    printf("===============\n");

    pool = create_pool();
    if (!pool) {
        printf("Failed to create pool\n");
        return 1;
    }

    print_pool_stats(pool);

    // Allocate some blocks
    printf("\nAllocating blocks...\n");
    for (int i = 0; i < 8; i++) {
        ptrs[i] = pool_alloc(pool);
        if (ptrs[i]) {
            sprintf((char*)ptrs[i], "Block %d data", i);
            printf("Allocated block %d: %s\n", i, (char*)ptrs[i]);
            num_allocated++;
        } else {
            printf("Failed to allocate block %d\n", i);
            break;
        }
    }

    print_pool_stats(pool);

    // Free some blocks
    printf("\nFreeing blocks 2, 4, 6...\n");
    pool_free(pool, ptrs[2]);
    pool_free(pool, ptrs[4]);
    pool_free(pool, ptrs[6]);

    print_pool_stats(pool);

    // Allocate more blocks
    printf("\nAllocating more blocks...\n");
    void *new_ptr1 = pool_alloc(pool);
    void *new_ptr2 = pool_alloc(pool);
    void *new_ptr3 = pool_alloc(pool);

    if (new_ptr1) {
        sprintf((char*)new_ptr1, "New block 1");
        printf("New block 1: %s\n", (char*)new_ptr1);
    }
    if (new_ptr2) {
        sprintf((char*)new_ptr2, "New block 2");
        printf("New block 2: %s\n", (char*)new_ptr2);
    }
    if (new_ptr3) {
        sprintf((char*)new_ptr3, "New block 3");
        printf("New block 3: %s\n", (char*)new_ptr3);
    }

    print_pool_stats(pool);

    // Free all allocated blocks
    printf("\nFreeing all blocks...\n");
    for (int i = 0; i < num_allocated; i++) {
        if (ptrs[i]) {
            pool_free(pool, ptrs[i]);
        }
    }
    if (new_ptr1) pool_free(pool, new_ptr1);
    if (new_ptr2) pool_free(pool, new_ptr2);
    if (new_ptr3) pool_free(pool, new_ptr3);

    print_pool_stats(pool);

    destroy_pool(pool);
    return 0;
}