#include <stdio.h>

int main() {
    // Integer division vs floating-point division
    int a = 7, b = 3;

    printf("Type Casting Demonstration:\n");
    printf("==========================\n");

    // Integer division (truncates)
    int int_div = a / b;
    printf("Integer division: %d / %d = %d\n", a, b, int_div);

    // Floating-point division with casting
    float float_div1 = (float)a / b;
    float float_div2 = a / (float)b;
    float float_div3 = (float)a / (float)b;

    printf("Floating-point division:\n");
    printf("  (float)%d / %d = %.3f\n", a, b, float_div1);
    printf("  %d / (float)%d = %.3f\n", a, b, float_div2);
    printf("  (float)%d / (float)%d = %.3f\n", a, b, float_div3);

    // Truncation when assigning to smaller types
    double large_double = 123.789;
    int truncated = large_double;
    char small_char = large_double; // May overflow

    printf("\nData truncation:\n");
    printf("  double: %.3f\n", large_double);
    printf("  int (truncated): %d\n", truncated);
    printf("  char (may overflow): %d\n", small_char);

    // Promotion in expressions
    char c1 = 100, c2 = 50;
    int result = c1 + c2; // Automatically promoted to int

    printf("\nAutomatic promotion:\n");
    printf("  char '%d' + char '%d' = int %d\n", c1, c2, result);

    return 0;
}