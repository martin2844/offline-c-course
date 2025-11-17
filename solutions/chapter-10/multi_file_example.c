#include <stdio.h>
#include "math_utils.h"
#include "string_utils.h"

int main() {
    printf("Multi-File Program Example\n");
    printf("==========================\n");

    // Test math utilities
    int numbers[] = {5, 3, 8, 1, 9, 2};
    int count = sizeof(numbers) / sizeof(numbers[0]);

    printf("Numbers: ");
    for (int i = 0; i < count; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    printf("Maximum: %d\n", find_max(numbers, count));
    printf("Minimum: %d\n", find_min(numbers, count));
    printf("Average: %.2f\n", calculate_average(numbers, count));

    // Test string utilities
    char text[] = "Hello, C Programming World!";
    printf("\nOriginal text: \"%s\"\n", text);
    printf("Text length: %d\n", string_length(text));

    reverse_string(text);
    printf("Reversed: \"%s\"\n", text);

    if (is_palindrome("racecar")) {
        printf("racecar is a palindrome\n");
    }
    if (!is_palindrome("hello")) {
        printf("hello is not a palindrome\n");
    }

    return 0;
}