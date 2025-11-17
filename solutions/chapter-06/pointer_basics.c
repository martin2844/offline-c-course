#include <stdio.h>

int main() {
    int number = 42;
    int *ptr;          // Declare pointer
    int **pptr;         // Declare pointer to pointer

    // Assign address of number to pointer
    ptr = &number;
    pptr = &ptr;

    printf("Pointer Basics Demo\n");
    printf("==================\n");

    // Display variable information
    printf("Variable 'number':\n");
    printf("  Value: %d\n", number);
    printf("  Address: %p\n", (void*)&number);
    printf("  Size: %zu bytes\n", sizeof(number));

    // Display pointer information
    printf("\nPointer 'ptr':\n");
    printf("  Value (address it points to): %p\n", (void*)ptr);
    printf("  Address of pointer itself: %p\n", (void*)&ptr);
    printf("  Size: %zu bytes\n", sizeof(ptr));
    printf("  Value pointed to: %d\n", *ptr);

    // Display double pointer information
    printf("\nPointer to pointer 'pptr':\n");
    printf("  Value (address of ptr): %p\n", (void*)pptr);
    printf("  Value pointed to by pptr: %p\n", (void*)*pptr);
    printf("  Value pointed to by *pptr: %d\n", **pptr);

    // Modify values through pointers
    printf("\nModifying values through pointers:\n");
    *ptr = 100;
    printf("After *ptr = 100, number = %d\n", number);

    **pptr = 200;
    printf("After **pptr = 200, number = %d\n", number);

    return 0;
}