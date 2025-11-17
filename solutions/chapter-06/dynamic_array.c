#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
    int capacity;
} DynamicArray;

// Initialize dynamic array
void init_array(DynamicArray *arr, int initial_capacity) {
    arr->data = (int*)malloc(initial_capacity * sizeof(int));
    if (arr->data == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    arr->size = 0;
    arr->capacity = initial_capacity;
}

// Add element to dynamic array
void push_back(DynamicArray *arr, int value) {
    if (arr->size >= arr->capacity) {
        // Resize array (double the capacity)
        int new_capacity = arr->capacity * 2;
        int *new_data = (int*)realloc(arr->data, new_capacity * sizeof(int));
        if (new_data == NULL) {
            printf("Memory reallocation failed!\n");
            return;
        }
        arr->data = new_data;
        arr->capacity = new_capacity;
        printf("Resized array to capacity %d\n", new_capacity);
    }

    arr->data[arr->size] = value;
    arr->size++;
}

// Get element at index
int get(DynamicArray *arr, int index) {
    if (index >= 0 && index < arr->size) {
        return arr->data[index];
    }
    printf("Index out of bounds!\n");
    return -1;
}

// Print array
void print_array(DynamicArray *arr) {
    printf("Array (size %d, capacity %d): [", arr->size, arr->capacity);
    for (int i = 0; i < arr->size; i++) {
        printf("%d", arr->data[i]);
        if (i < arr->size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

// Free array memory
void free_array(DynamicArray *arr) {
    free(arr->data);
    arr->data = NULL;
    arr->size = 0;
    arr->capacity = 0;
}

int main() {
    DynamicArray arr;
    init_array(&arr, 2);  // Start with capacity 2

    printf("Dynamic Array Demo\n");
    printf("==================\n");

    // Add elements (will trigger resizing)
    printf("Adding elements 10, 20, 30, 40, 50:\n");
    push_back(&arr, 10);
    push_back(&arr, 20);
    push_back(&arr, 30);  // This should trigger resize
    push_back(&arr, 40);
    push_back(&arr, 50);

    print_array(&arr);

    // Access elements
    printf("\nElement at index 2: %d\n", get(&arr, 2));
    printf("Element at index 4: %d\n", get(&arr, 4));

    // Test bounds checking
    printf("Element at index 10: %d\n", get(&arr, 10));  // Should show error

    free_array(&arr);
    printf("\nMemory freed. Array size: %d\n", arr.size);

    return 0;
}