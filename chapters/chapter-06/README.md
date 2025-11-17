# Chapter 6: Pointers

## Learning Objectives
By the end of this chapter, you will be able to:
- Understand what pointers are and how they work
- Declare and use pointers
- Perform pointer arithmetic
- Use pointers with arrays and functions
- Understand pointer-to-pointer concepts
- Apply pointers in practical applications
- Avoid common pointer pitfalls

## Introduction to Pointers

A pointer is a variable that stores the memory address of another variable. Pointers are one of the most powerful features of C because they allow you to:
- **Direct memory access** and manipulation
- **Dynamic memory allocation**
- **Efficient array and string processing**
- **Function parameter modification**
- **Complex data structures**

### Memory Addresses

Every variable in your program is stored at a specific memory address. You can think of memory as a series of numbered storage locations.

```c
#include <stdio.h>

int main() {
    int number = 42;
    char letter = 'A';
    float pi = 3.14159f;

    printf("Variables and their addresses:\n");
    printf("number = %d, address = %p\n", number, (void*)&number);
    printf("letter = %c, address = %p\n", letter, (void*)&letter);
    printf("pi = %.2f, address = %p\n", pi, (void*)&pi);

    // Size of different pointer types
    printf("\nPointer sizes:\n");
    printf("Size of int pointer: %zu bytes\n", sizeof(int*));
    printf("Size of char pointer: %zu bytes\n", sizeof(char*));
    printf("Size of float pointer: %zu bytes\n", sizeof(float*));

    return 0;
}
```

## Pointer Declaration and Basic Usage

### Declaring Pointers
```c
#include <stdio.h>

int main() {
    int number = 42;
    int *ptr;        // Declare a pointer to int

    // Assign the address of number to ptr
    ptr = &number;   // & operator gets the address

    printf("Pointer Basics:\n");
    printf("number = %d\n", number);
    printf("address of number = %p\n", (void*)&number);
    printf("ptr = %p\n", (void*)ptr);
    printf("value pointed to by ptr = %d\n", *ptr);  // * operator dereferences

    // Modify value through pointer
    *ptr = 100;  // Change the value at the address ptr points to
    printf("After *ptr = 100:\n");
    printf("number = %d\n", number);

    return 0;
}
```

### Multiple Pointers
```c
#include <stdio.h>

int main() {
    int a = 10, b = 20, c = 30;

    int *ptr1, *ptr2, *ptr3;

    ptr1 = &a;
    ptr2 = &b;
    ptr3 = &c;

    printf("Multiple Pointers:\n");
    printf("a = %d, ptr1 points to %d\n", a, *ptr1);
    printf("b = %d, ptr2 points to %d\n", b, *ptr2);
    printf("c = %d, ptr3 points to %d\n", c, *ptr3);

    // Reassign pointers
    ptr2 = ptr1;  // ptr2 now points to the same address as ptr1
    printf("After ptr2 = ptr1, ptr2 points to %d\n", *ptr2);

    return 0;
}
```

## Pointers and Functions

### Pass by Reference Using Pointers
```c
#include <stdio.h>

// Function that modifies variables through pointers
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function that returns multiple values through pointers
void calculate_stats(int numbers[], int size, int *sum, float *average, int *max) {
    *sum = 0;
    *max = numbers[0];

    for (int i = 0; i < size; i++) {
        *sum += numbers[i];
        if (numbers[i] > *max) {
            *max = numbers[i];
        }
    }

    *average = (float)*sum / size;
}

int main() {
    // Example 1: Swap function
    int x = 5, y = 10;
    printf("Before swap: x = %d, y = %d\n", x, y);
    swap(&x, &y);
    printf("After swap: x = %d, y = %d\n", x, y);

    // Example 2: Multiple return values
    int data[] = {3, 7, 2, 9, 4};
    int size = sizeof(data) / sizeof(data[0]);
    int total, maximum;
    float avg;

    calculate_stats(data, size, &total, &avg, &maximum);

    printf("\nArray: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");
    printf("Sum: %d\n", total);
    printf("Average: %.2f\n", avg);
    printf("Maximum: %d\n", maximum);

    return 0;
}
```

## Pointers and Arrays

### Array-Pointer Relationship
```c
#include <stdio.h>

int main() {
    int numbers[] = {10, 20, 30, 40, 50};
    int *ptr = numbers;  // Array name decays to pointer

    printf("Array-Pointer Relationship:\n");
    printf("numbers[0] = %d\n", numbers[0]);
    printf("*numbers = %d\n", *numbers);
    printf("ptr = %p\n", (void*)ptr);
    printf("numbers = %p\n", (void*)numbers);

    printf("\nAccessing elements:\n");
    for (int i = 0; i < 5; i++) {
        printf("numbers[%d] = %d, *(numbers + %d) = %d, *(ptr + %d) = %d\n",
               i, numbers[i], i, *(numbers + i), i, *(ptr + i));
    }

    printf("\nPointer arithmetic:\n");
    printf("ptr = %p, *ptr = %d\n", (void*)ptr, *ptr);
    ptr++;  // Move to next element
    printf("ptr++ = %p, *ptr = %d\n", (void*)ptr, *ptr);
    ptr += 2;  // Move two elements forward
    printf("ptr += 2 = %p, *ptr = %d\n", (void*)ptr, *ptr);

    return 0;
}
```

### Pointer Arithmetic with Arrays
```c
#include <stdio.h>

void print_array(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);  // arr[i] is equivalent to *(arr + i)
    }
    printf("\n");
}

void reverse_array(int *arr, int size) {
    int *start = arr;
    int *end = arr + size - 1;

    while (start < end) {
        // Swap values using pointers
        int temp = *start;
        *start = *end;
        *end = temp;

        start++;
        end--;
    }
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = sizeof(numbers) / sizeof(numbers[0]);

    printf("Original array: ");
    print_array(numbers, size);

    reverse_array(numbers, size);

    printf("Reversed array: ");
    print_array(numbers, size);

    // Demonstrate pointer traversal
    printf("\nTraversing with pointers:\n");
    int *ptr = numbers;
    for (int i = 0; i < size; i++) {
        printf("Element %d: %d (address %p)\n", i, *ptr, (void*)ptr);
        ptr++;
    }

    return 0;
}
```

## Pointers and Strings

### String Manipulation with Pointers
```c
#include <stdio.h>
#include <string.h>

// Custom string length using pointers
int string_length(const char *str) {
    int length = 0;
    while (*str != '\0') {  // Dereference pointer
        length++;
        str++;  // Move to next character
    }
    return length;
}

// Custom string copy using pointers
void string_copy(char *dest, const char *src) {
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';  // Add null terminator
}

// Function to reverse string using pointers
void reverse_string(char *str) {
    char *start = str;
    char *end = str + string_length(str) - 1;

    while (start < end) {
        // Swap characters
        char temp = *start;
        *start = *end;
        *end = temp;

        start++;
        end--;
    }
}

int main() {
    char message[] = "Hello, Pointers!";

    printf("String Operations with Pointers:\n");
    printf("Original: %s\n", message);
    printf("Length: %d\n", string_length(message));

    // Test string copy
    char copy[50];
    string_copy(copy, message);
    printf("Copy: %s\n", copy);

    // Test string reversal
    reverse_string(message);
    printf("Reversed: %s\n", message);

    // Character pointer operations
    char *ptr = message;
    printf("\nCharacter by character:\n");
    while (*ptr != '\0') {
        printf("%c ", *ptr);
        ptr++;
    }
    printf("\n");

    return 0;
}
```

## Advanced Pointer Concepts

### Pointers to Pointers
```c
#include <stdio.h>

int main() {
    int value = 42;
    int *ptr = &value;      // Pointer to int
    int **pptr = &ptr;      // Pointer to pointer to int

    printf("Pointers to Pointers:\n");
    printf("value = %d\n", value);
    printf("&value = %p\n", (void*)&value);
    printf("ptr = %p\n", (void*)ptr);
    printf("*ptr = %d\n", *ptr);
    printf("&ptr = %p\n", (void*)&ptr);
    printf("pptr = %p\n", (void*)pptr);
    printf("*pptr = %p\n", (void*)*pptr);
    printf("**pptr = %d\n", **pptr);

    // Modify value through double pointer
    **pptr = 100;
    printf("After **pptr = 100, value = %d\n", value);

    return 0;
}
```

### Function Pointers
```c
#include <stdio.h>

// Some functions to be pointed to
int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }
int multiply(int a, int b) { return a * b; }

// Function that takes a function pointer as parameter
int calculate(int a, int b, int (*operation)(int, int)) {
    return operation(a, b);
}

int main() {
    int a = 10, b = 5;

    // Function pointer declaration
    int (*func_ptr)(int, int);

    printf("Function Pointers:\n");

    // Point to different functions
    func_ptr = add;
    printf("%d + %d = %d\n", a, b, func_ptr(a, b));

    func_ptr = subtract;
    printf("%d - %d = %d\n", a, b, func_ptr(a, b));

    func_ptr = multiply;
    printf("%d * %d = %d\n", a, b, func_ptr(a, b));

    // Using function pointer as parameter
    printf("\nUsing calculate function:\n");
    printf("calculate(%d, %d, add) = %d\n", a, b, calculate(a, b, add));
    printf("calculate(%d, %d, subtract) = %d\n", a, b, calculate(a, b, subtract));

    return 0;
}
```

### Array of Pointers
```c
#include <stdio.h>

int main() {
    // Array of integer pointers
    int a = 10, b = 20, c = 30, d = 40;
    int *ptr_array[4] = {&a, &b, &c, &d};

    printf("Array of Pointers:\n");
    for (int i = 0; i < 4; i++) {
        printf("ptr_array[%d] = %p, *ptr_array[%d] = %d\n",
               i, (void*)ptr_array[i], i, *ptr_array[i]);
    }

    // Array of character pointers (like command line arguments)
    const char *fruits[] = {"Apple", "Banana", "Orange", "Grape"};
    int num_fruits = sizeof(fruits) / sizeof(fruits[0]);

    printf("\nArray of String Literals:\n");
    for (int i = 0; i < num_fruits; i++) {
        printf("fruits[%d] = %s\n", i, fruits[i]);
    }

    return 0;
}
```

## Dynamic Memory Allocation

### malloc and free
```c
#include <stdio.h>
#include <stdlib.h>  // Required for malloc and free

int main() {
    int *dynamic_array;
    int size;

    printf("Dynamic Memory Allocation:\n");
    printf("Enter array size: ");
    scanf("%d", &size);

    // Allocate memory for the array
    dynamic_array = (int*)malloc(size * sizeof(int));

    if (dynamic_array == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    printf("Enter %d integers:\n", size);
    for (int i = 0; i < size; i++) {
        scanf("%d", &dynamic_array[i]);
    }

    printf("You entered: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", dynamic_array[i]);
    }
    printf("\n");

    // Find sum
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += dynamic_array[i];
    }
    printf("Sum: %d\n", sum);

    // Free the allocated memory
    free(dynamic_array);
    printf("Memory freed.\n");

    return 0;
}
```

### calloc and realloc
```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *array1, *array2;
    int initial_size = 5, new_size = 10;

    // calloc - allocates and initializes to zero
    array1 = (int*)calloc(initial_size, sizeof(int));
    if (array1 == NULL) {
        printf("calloc failed!\n");
        return 1;
    }

    printf("calloc initialization (should be zeros):\n");
    for (int i = 0; i < initial_size; i++) {
        printf("%d ", array1[i]);
    }
    printf("\n");

    // Fill with some values
    for (int i = 0; i < initial_size; i++) {
        array1[i] = (i + 1) * 10;
    }

    printf("After filling:\n");
    for (int i = 0; i < initial_size; i++) {
        printf("%d ", array1[i]);
    }
    printf("\n");

    // realloc - resize the array
    array2 = (int*)realloc(array1, new_size * sizeof(int));
    if (array2 == NULL) {
        printf("realloc failed!\n");
        free(array1);
        return 1;
    }

    printf("After realloc to size %d:\n", new_size);
    for (int i = 0; i < new_size; i++) {
        printf("%d ", array2[i]);
    }
    printf("\n");

    // Fill new elements
    for (int i = initial_size; i < new_size; i++) {
        array2[i] = (i + 1) * 10;
    }

    printf("After filling new elements:\n");
    for (int i = 0; i < new_size; i++) {
        printf("%d ", array2[i]);
    }
    printf("\n");

    free(array2);
    return 0;
}
```

## Common Pointer Pitfalls

### Null Pointer Dereference
```c
#include <stdio.h>
#include <stdlib.h>

void safe_pointer_use() {
    int *ptr = NULL;  // Initialize to NULL

    // Always check before dereferencing
    if (ptr != NULL) {
        printf("Value: %d\n", *ptr);
    } else {
        printf("Pointer is NULL, cannot dereference\n");
    }

    // Allocate memory and check
    ptr = (int*)malloc(sizeof(int));
    if (ptr == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    *ptr = 42;  // Now safe to dereference
    printf("Value after allocation: %d\n", *ptr);

    free(ptr);
    ptr = NULL;  // Set to NULL after freeing

    // This check will prevent use-after-free
    if (ptr != NULL) {
        printf("This won't print\n");
    }
}

int main() {
    safe_pointer_use();
    return 0;
}
```

### Dangling Pointers
```c
#include <stdio.h>
#include <stdlib.h>

void dangling_pointer_example() {
    int *ptr;

    // Allocate memory
    ptr = (int*)malloc(sizeof(int));
    *ptr = 100;

    printf("Before free: *ptr = %d\n", *ptr);

    // Free memory
    free(ptr);

    // Now ptr is a dangling pointer - don't use it!
    // printf("After free: *ptr = %d\n", *ptr);  // DANGEROUS!

    // Solution: Set to NULL after freeing
    ptr = NULL;

    if (ptr != NULL) {
        printf("This won't print - pointer is NULL\n");
    }
}

void local_variable_pointer() {
    int *ptr;
    int local_var = 50;

    ptr = &local_var;
    printf("Local variable: *ptr = %d\n", *ptr);

    // When function ends, local_var is destroyed
    // ptr becomes a dangling pointer if returned
}

int main() {
    dangling_pointer_example();
    return 0;
}
```

## Practical Applications

### Dynamic Array Implementation
```c
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
    arr->size = 0;
    arr->capacity = initial_capacity;
}

// Add element to dynamic array
void push_back(DynamicArray *arr, int value) {
    if (arr->size >= arr->capacity) {
        // Resize array
        arr->capacity *= 2;
        arr->data = (int*)realloc(arr->data, arr->capacity * sizeof(int));
    }

    arr->data[arr->size] = value;
    arr->size++;
}

// Get element at index
int get(DynamicArray *arr, int index) {
    if (index >= 0 && index < arr->size) {
        return arr->data[index];
    }
    return -1;  // Error value
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
    init_array(&arr, 2);

    // Add elements
    push_back(&arr, 10);
    push_back(&arr, 20);
    push_back(&arr, 30);
    push_back(&arr, 40);

    printf("Dynamic Array:\n");
    printf("Size: %d, Capacity: %d\n", arr.size, arr.capacity);
    printf("Elements: ");
    for (int i = 0; i < arr.size; i++) {
        printf("%d ", get(&arr, i));
    }
    printf("\n");

    free_array(&arr);
    return 0;
}
```

### Linked List Introduction
```c
#include <stdio.h>
#include <stdlib.h>

// Node structure for linked list
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Create a new node
Node* create_node(int data) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

// Print linked list
void print_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

// Free linked list
void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    // Create linked list: 1 -> 2 -> 3 -> NULL
    Node *head = create_node(1);
    head->next = create_node(2);
    head->next->next = create_node(3);

    printf("Linked List:\n");
    print_list(head);

    free_list(head);
    return 0;
}
```

## Best Practices

### Pointer Safety
1. **Always initialize pointers** to NULL or valid addresses
2. **Check for NULL** before dereferencing
3. **Free allocated memory** to prevent leaks
4. **Set pointers to NULL** after freeing
5. **Avoid returning pointers** to local variables

### Memory Management
1. **Every malloc should have a corresponding free**
2. **Check return value** of malloc/calloc/realloc
3. **Free memory in the reverse order** of allocation
4. **Use valgrind or similar tools** to detect memory leaks

### Code Readability
1. **Use meaningful pointer names**
2. **Add comments explaining pointer operations**
3. **Keep pointer operations simple** and clear
4. **Use const pointers** when not modifying data

## Common Errors and Solutions

### Error: Segmentation Fault
**Cause**: Dereferencing NULL or invalid pointer
**Solution**: Always check pointers before dereferencing

### Error: Memory Leak
**Cause**: Not freeing allocated memory
**Solution**: Ensure every malloc has a corresponding free

### Error: Use After Free
**Cause**: Using pointer after memory is freed
**Solution**: Set pointer to NULL after freeing

### Error: Buffer Overflow
**Cause**: Writing beyond allocated memory
**Solution**: Check array bounds and allocation sizes

## Exercises

### Exercise 6.1: Pointer Basics
Create a program that demonstrates pointer declaration, assignment, and dereferencing.

### Exercise 6.2: Array with Pointers
Rewrite array operations (sum, average, reverse) using pointers instead of array indexing.

### Exercise 6.3: String Functions with Pointers
Implement string length, copy, and concatenation using only pointers.

### Exercise 6.4: Dynamic Array
Create a program that uses dynamic memory allocation to create an array of user-specified size.

### Exercise 6.5: Function Pointers
Create a calculator that uses function pointers to perform operations.

## Challenge Problems

### Challenge 6.1: Custom Memory Allocator
Implement a simple memory allocator using malloc and free.

### Challenge 6.2: Double Pointer Matrix
Create a 2D matrix using double pointers and dynamic allocation.

### Challenge 6.3: Linked List Operations
Implement a complete linked list with insert, delete, and search operations.

## Quick Reference

### Pointer Operations
- **Declaration**: `type *ptr;`
- **Address**: `&variable`
- **Dereference**: `*ptr`
- **Pointer arithmetic**: `ptr + n`, `ptr - n`

### Memory Functions
- **Allocate**: `malloc(size)`, `calloc(count, size)`
- **Resize**: `realloc(ptr, new_size)`
- **Free**: `free(ptr)`

### Pointer Types
- **Normal pointer**: `int *ptr`
- **Pointer to pointer**: `int **pptr`
- **Function pointer**: `int (*func_ptr)(int, int)`
- **Array of pointers**: `type *array[size]`

## Next Steps
Once you're comfortable with:
- Understanding pointer concepts and syntax
- Using pointers with arrays and functions
- Performing pointer arithmetic
- Managing dynamic memory
- Avoiding common pointer pitfalls

You're ready to move to **Chapter 7: Structures and Unions**!

Mastering pointers is crucial for advanced C programming and understanding how computers manage memory at a low level.