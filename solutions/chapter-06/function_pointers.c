#include <stdio.h>

// Mathematical operations
int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }
int multiply(int a, int b) { return a * b; }
int divide(int a, int b) { return b != 0 ? a / b : 0; }

// Function that takes a function pointer
int calculate(int a, int b, int (*operation)(int, int)) {
    return operation(a, b);
}

// Array of operations
int main() {
    int a = 20, b = 5;

    printf("Function Pointers Calculator\n");
    printf("===========================\n");

    // Using function pointers directly
    int (*op_ptr)(int, int);

    op_ptr = add;
    printf("%d + %d = %d\n", a, b, op_ptr(a, b));

    op_ptr = subtract;
    printf("%d - %d = %d\n", a, b, op_ptr(a, b));

    op_ptr = multiply;
    printf("%d * %d = %d\n", a, b, op_ptr(a, b));

    op_ptr = divide;
    printf("%d / %d = %d\n", a, b, op_ptr(a, b));

    // Using calculate function
    printf("\nUsing calculate function:\n");
    printf("calculate(%d, %d, add) = %d\n", a, b, calculate(a, b, add));
    printf("calculate(%d, %d, subtract) = %d\n", a, b, calculate(a, b, subtract));

    // Array of function pointers
    int (*operations[])(int, int) = {add, subtract, multiply, divide};
    const char *op_names[] = {"add", "subtract", "multiply", "divide"};

    printf("\nUsing array of function pointers:\n");
    for (int i = 0; i < 4; i++) {
        printf("%s: %d\n", op_names[i], operations[i](a, b));
    }

    return 0;
}