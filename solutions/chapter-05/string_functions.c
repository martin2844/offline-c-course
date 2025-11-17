#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Custom string length function
int string_length(const char str[]) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

// Custom string copy function
void string_copy(char dest[], const char src[]) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

// Custom string concatenation
void string_concatenate(char dest[], const char src[]) {
    int i = 0, j = 0;

    // Find end of destination
    while (dest[i] != '\0') {
        i++;
    }

    // Copy source to destination
    while (src[j] != '\0') {
        dest[i] = src[j];
        i++;
        j++;
    }
    dest[i] = '\0';
}

// Custom string comparison
int string_compare(const char str1[], const char str2[]) {
    int i = 0;

    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return str1[i] - str2[i];
        }
        i++;
    }

    return str1[i] - str2[i];
}

int main() {
    char str1[100] = "Hello";
    char str2[] = ", World!";
    char str3[100];

    printf("String Functions Demo\n");
    printf("====================\n");

    // Test length functions
    printf("Length of '%s':\n", str1);
    printf("  Custom: %d\n", string_length(str1));
    printf("  strlen: %zu\n", strlen(str1));

    // Test copy functions
    string_copy(str3, str1);
    printf("\nCopy '%s' to str3: %s\n", str1, str3);

    // Test concatenation
    string_concatenate(str3, str2);
    printf("Concatenated: %s\n", str3);

    // Test comparison
    printf("\nComparison results:\n");
    printf("Custom compare('%s', '%s'): %d\n", str1, str2, string_compare(str1, str2));
    printf("strcmp('%s', '%s'): %d\n", str1, str2, strcmp(str1, str2));

    return 0;
}