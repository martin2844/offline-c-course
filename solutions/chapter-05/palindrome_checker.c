#include <stdio.h>
#include <string.h>
#include <ctype.h>

int is_palindrome(const char str[]) {
    int left = 0;
    int right = strlen(str) - 1;

    while (left < right) {
        // Skip non-alphanumeric characters
        while (left < right && !isalnum(str[left])) {
            left++;
        }
        while (left < right && !isalnum(str[right])) {
            right--;
        }

        // Compare characters (case-insensitive)
        if (tolower(str[left]) != tolower(str[right])) {
            return 0; // Not a palindrome
        }

        left++;
        right--;
    }

    return 1; // Is a palindrome
}

void normalize_string(char str[]) {
    int i = 0, j = 0;
    char temp[100];

    // Remove non-alphanumeric characters and convert to lowercase
    while (str[i] != '\0') {
        if (isalnum(str[i])) {
            temp[j++] = tolower(str[i]);
        }
        i++;
    }
    temp[j] = '\0';

    // Copy back to original string
    strcpy(str, temp);
}

int main() {
    char text[100];
    char original[100];

    printf("Palindrome Checker\n");
    printf("==================\n");

    printf("Enter a string: ");
    fgets(text, sizeof(text), stdin);

    // Remove newline character
    int len = strlen(text);
    if (len > 0 && text[len - 1] == '\n') {
        text[len - 1] = '\0';
    }

    // Keep original for display
    strcpy(original, text);

    // Check if palindrome
    if (is_palindrome(text)) {
        printf("\"%s\" is a palindrome! ✓\n", original);
    } else {
        printf("\"%s\" is not a palindrome. ✗\n", original);
    }

    // Demonstrate with known palindromes
    printf("\nTesting known palindromes:\n");
    char test1[] = "A man a plan a canal Panama";
    char test2[] = "racecar";
    char test3[] = "hello";

    printf("\"%s\": %s\n", test1, is_palindrome(test1) ? "Palindrome ✓" : "Not palindrome ✗");
    printf("\"%s\": %s\n", test2, is_palindrome(test2) ? "Palindrome ✓" : "Not palindrome ✗");
    printf("\"%s\": %s\n", test3, is_palindrome(test3) ? "Palindrome ✓" : "Not palindrome ✗");

    return 0;
}