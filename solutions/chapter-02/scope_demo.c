#include <stdio.h>

// Global variable
int global_var = 100;

void demonstrate_scope() {
    // Local variable in function
    int local_var = 50;

    printf("Inside function:\n");
    printf("  global_var = %d\n", global_var);
    printf("  local_var = %d\n", local_var);

    // Modify global variable
    global_var = 200;
}

int main() {
    // Local variable in main
    int local_var = 30;

    printf("Global variable demonstration:\n");
    printf("============================\n");

    printf("Before function call:\n");
    printf("  global_var = %d\n", global_var);
    printf("  local_var = %d\n", local_var);

    demonstrate_scope();

    printf("After function call:\n");
    printf("  global_var = %d (modified by function)\n", global_var);
    printf("  local_var = %d (unchanged)\n", local_var);

    // Block scope
    {
        int block_var = 75;
        int local_var = 999; // Shadows main's local_var

        printf("\nInside block:\n");
        printf("  block_var = %d\n", block_var);
        printf("  local_var = %d (shadows main's local_var)\n", local_var);
    }

    printf("\nAfter block:\n");
    printf("  local_var = %d (original value restored)\n", local_var);
    // block_var is not accessible here

    return 0;
}