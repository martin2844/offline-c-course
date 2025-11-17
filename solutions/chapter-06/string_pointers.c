#include <stdio.h>
#include <string.h>

// String length using pointers
int string_length(const char *str) {
    int length = 0;
    while (*str != '\0') {
        length++;
        str++;
    }
    return length;
}

// String copy using pointers
void string_copy(char *dest, const char *src) {
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
}

// String concatenation using pointers
void string_concatenate(char *dest, const char *src) {
    // Find end of destination
    while (*dest != '\0') {
        dest++;
    }

    // Copy source to destination
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
}

// String comparison using pointers
int string_compare(const char *str1, const char *str2) {
    while (*str1 != '\0' && *str2 != '\0') {
        if (*str1 != *str2) {
            return *str1 - *str2;
        }
        str1++;
        str2++;
    }
    return *str1 - *str2;
}

// String reversal using pointers
void reverse_string(char *str) {
    char *start = str;
    char *end = str + string_length(str) - 1;

    while (start < end) {
        char temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}

int main() {
    char str1[100] = "Hello";
    char str2[] = ", World!";
    char str3[100];

    printf("String Operations with Pointers\n");
    printf("===============================\n");

    // Test string length
    printf("Length of '%s': %d\n", str1, string_length(str1));

    // Test string copy
    string_copy(str3, str1);
    printf("Copy: '%s'\n", str3);

    // Test string concatenation
    string_concatenate(str3, str2);
    printf("Concatenated: '%s'\n", str3);

    // Test string comparison
    printf("Compare '%s' and '%s': %d\n", str1, str2, string_compare(str1, str2));

    // Test string reversal
    reverse_string(str3);
    printf("Reversed: '%s'\n", str3);

    return 0;
}