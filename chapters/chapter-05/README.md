# Chapter 5: Arrays and Strings

## Learning Objectives
By the end of this chapter, you will be able to:
- Understand and use one-dimensional and multi-dimensional arrays
- Implement array algorithms (searching, sorting)
- Work with strings and string manipulation
- Use standard string library functions
- Handle array bounds and memory issues
- Apply arrays in practical applications

## Introduction to Arrays

An array is a collection of elements of the same data type stored in contiguous memory locations. Arrays allow you to:
- **Store multiple values** in a single variable
- **Access elements efficiently** using indices
- **Organize data** in structured ways
- **Implement algorithms** for data processing

## One-Dimensional Arrays

### Array Declaration and Initialization
```c
#include <stdio.h>

int main() {
    // Different ways to declare and initialize arrays

    // Method 1: Declare and initialize
    int numbers[5] = {10, 20, 30, 40, 50};

    // Method 2: Declare with partial initialization
    int partial[5] = {1, 2, 3};  // Rest will be 0

    // Method 3: Declare without initialization (contains garbage values)
    int uninitialized[5];

    // Method 4: Initialize with all zeros
    int zeros[5] = {0};

    // Method 5: Let compiler determine size
    int auto_size[] = {5, 10, 15, 20, 25};

    return 0;
}
```

### Accessing Array Elements
```c
#include <stdio.h>

int main() {
    int scores[5] = {85, 92, 78, 95, 88};

    // Access individual elements using index (0-based)
    printf("First score: %d\n", scores[0]);    // 85
    printf("Third score: %d\n", scores[2]);    // 78
    printf("Last score: %d\n", scores[4]);     // 88

    // Modify array elements
    scores[2] = 82;  // Change 78 to 82
    printf("Updated third score: %d\n", scores[2]);

    return 0;
}
```

### Array Size and Bounds
```c
#include <stdio.h>

int main() {
    int data[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

    // Calculate array size
    int size = sizeof(data) / sizeof(data[0]);
    printf("Array size: %d elements\n", size);

    // Iterate through array
    printf("Array elements: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");

    // Reverse iteration
    printf("Array in reverse: ");
    for (int i = size - 1; i >= 0; i--) {
        printf("%d ", data[i]);
    }
    printf("\n");

    return 0;
}
```

### Input and Output with Arrays
```c
#include <stdio.h>

int main() {
    int numbers[5];

    printf("Enter 5 integers:\n");

    // Input array elements
    for (int i = 0; i < 5; i++) {
        printf("Element %d: ", i);
        scanf("%d", &numbers[i]);
    }

    // Output array elements
    printf("\nYou entered: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    // Calculate sum and average
    int sum = 0;
    for (int i = 0; i < 5; i++) {
        sum += numbers[i];
    }

    float average = (float)sum / 5;
    printf("Sum: %d\n", sum);
    printf("Average: %.2f\n", average);

    return 0;
}
```

## Multi-Dimensional Arrays

### Two-Dimensional Arrays
```c
#include <stdio.h>

int main() {
    // 2D array declaration and initialization
    int matrix[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };

    // Access elements with row and column indices
    printf("Element at [0][0]: %d\n", matrix[0][0]);  // 1
    printf("Element at [1][2]: %d\n", matrix[1][2]);  // 7
    printf("Element at [2][3]: %d\n", matrix[2][3]);  // 12

    // Print entire matrix
    printf("\nMatrix:\n");
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 4; col++) {
            printf("%3d ", matrix[row][col]);
        }
        printf("\n");
    }

    return 0;
}
```

### Matrix Operations
```c
#include <stdio.h>

#define ROWS 3
#define COLS 3

int main() {
    int matrix1[ROWS][COLS] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    int matrix2[ROWS][COLS] = {
        {9, 8, 7},
        {6, 5, 4},
        {3, 2, 1}
    };

    int sum[ROWS][COLS];

    // Matrix addition
    printf("Matrix Addition:\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            sum[i][j] = matrix1[i][j] + matrix2[i][j];
            printf("%3d ", sum[i][j]);
        }
        printf("\n");
    }

    // Find diagonal elements
    printf("\nDiagonal elements of matrix1: ");
    for (int i = 0; i < ROWS; i++) {
        printf("%d ", matrix1[i][i]);
    }
    printf("\n");

    return 0;
}
```

## Array Algorithms

### Linear Search
```c
#include <stdio.h>

// Linear search function
int linear_search(int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            return i;  // Return index if found
        }
    }
    return -1;  // Return -1 if not found
}

int main() {
    int numbers[] = {64, 34, 25, 12, 22, 11, 90, 88, 76, 50};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    int target, index;

    printf("Array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    printf("Enter number to search: ");
    scanf("%d", &target);

    index = linear_search(numbers, size, target);

    if (index != -1) {
        printf("%d found at index %d\n", target, index);
    } else {
        printf("%d not found in the array\n", target);
    }

    return 0;
}
```

### Bubble Sort
```c
#include <stdio.h>

// Bubble sort function
void bubble_sort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap elements
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Function to print array
void print_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int numbers[] = {64, 34, 25, 12, 22, 11, 90, 88, 76, 50};
    int size = sizeof(numbers) / sizeof(numbers[0]);

    printf("Original array: ");
    print_array(numbers, size);

    bubble_sort(numbers, size);

    printf("Sorted array:   ");
    print_array(numbers, size);

    return 0;
}
```

### Find Maximum and Minimum
```c
#include <stdio.h>

// Function to find maximum and minimum
void find_min_max(int arr[], int size, int *min, int *max) {
    *min = arr[0];
    *max = arr[0];

    for (int i = 1; i < size; i++) {
        if (arr[i] < *min) {
            *min = arr[i];
        }
        if (arr[i] > *max) {
            *max = arr[i];
        }
    }
}

int main() {
    int data[] = {15, 8, 23, 4, 42, 16, 7, 19, 31};
    int size = sizeof(data) / sizeof(data[0]);
    int minimum, maximum;

    find_min_max(data, size, &minimum, &maximum);

    printf("Array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");

    printf("Minimum: %d\n", minimum);
    printf("Maximum: %d\n", maximum);

    return 0;
}
```

## Introduction to Strings

In C, strings are arrays of characters terminated by a null character (`\0`).

### String Basics
```c
#include <stdio.h>

int main() {
    // Different ways to declare strings

    // Method 1: String literal (automatically null-terminated)
    char greeting[] = "Hello, World!";

    // Method 2: Character array with explicit size
    char name[20] = "Alice";

    // Method 3: Initialize character by character
    char custom[] = {'H', 'e', 'l', 'l', 'o', '\0'};

    printf("Greeting: %s\n", greeting);
    printf("Name: %s\n", name);
    printf("Custom: %s\n", custom);

    // String length calculation
    int length = 0;
    while (greeting[length] != '\0') {
        length++;
    }
    printf("Length of greeting: %d\n", length);

    return 0;
}
```

### String Input and Output
```c
#include <stdio.h>

int main() {
    char name[50];
    char city[30];

    printf("Enter your name: ");
    // scanf with %s stops at whitespace
    scanf("%s", name);

    // Clear the input buffer
    while (getchar() != '\n');

    printf("Enter your city: ");
    // fgets reads entire line (including spaces)
    fgets(city, sizeof(city), stdin);

    // Remove newline from fgets input
    int i = 0;
    while (city[i] != '\0' && city[i] != '\n') {
        i++;
    }
    city[i] = '\0';

    printf("\nHello, %s from %s!\n", name, city);

    return 0;
}
```

### Common String Functions

#### String Length
```c
#include <stdio.h>

// Custom string length function
int string_length(const char str[]) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

int main() {
    char text[] = "C Programming";

    printf("String: %s\n", text);
    printf("Length (custom): %d\n", string_length(text));
    printf("Length (strlen): %zu\n", strlen(text));  // Using standard library

    return 0;
}
```

#### String Copy
```c
#include <stdio.h>
#include <string.h>

// Custom string copy function
void string_copy(char dest[], const char src[]) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';  // Add null terminator
}

int main() {
    char source[] = "Hello, C!";
    char destination[50];

    // Custom copy
    string_copy(destination, source);
    printf("Custom copy: %s\n", destination);

    // Standard library copy
    strcpy(destination, source);
    printf("strcpy copy: %s\n", destination);

    // Safe copy (prevents buffer overflow)
    strncpy(destination, source, sizeof(destination) - 1);
    destination[sizeof(destination) - 1] = '\0';  // Ensure null termination
    printf("strncpy copy: %s\n", destination);

    return 0;
}
```

#### String Concatenation
```c
#include <stdio.h>
#include <string.h>

// Custom string concatenation
void string_concatenate(char dest[], const char src[]) {
    int i = 0, j = 0;

    // Find end of destination string
    while (dest[i] != '\0') {
        i++;
    }

    // Copy source to end of destination
    while (src[j] != '\0') {
        dest[i] = src[j];
        i++;
        j++;
    }
    dest[i] = '\0';  // Add null terminator
}

int main() {
    char first[50] = "Hello";
    char second[] = ", World!";

    // Custom concatenation
    string_concatenate(first, second);
    printf("Custom concat: %s\n", first);

    // Reset first string
    strcpy(first, "Hello");

    // Standard library concatenation
    strcat(first, second);
    printf("strcat concat: %s\n", first);

    // Safe concatenation
    char safe[50] = "Hello";
    strncat(safe, second, sizeof(safe) - strlen(safe) - 1);
    printf("strncat concat: %s\n", safe);

    return 0;
}
```

#### String Comparison
```c
#include <stdio.h>
#include <string.h>

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
    char str1[] = "Apple";
    char str2[] = "Banana";
    char str3[] = "Apple";

    // Custom comparison
    int result1 = string_compare(str1, str2);
    int result2 = string_compare(str1, str3);

    printf("Custom compare('%s', '%s'): %d\n", str1, str2, result1);
    printf("Custom compare('%s', '%s'): %d\n", str1, str3, result2);

    // Standard library comparison
    result1 = strcmp(str1, str2);
    result2 = strcmp(str1, str3);

    printf("strcmp('%s', '%s'): %d\n", str1, str2, result1);
    printf("strcmp('%s', '%s'): %d\n", str1, str3, result2);

    return 0;
}
```

## String Processing Applications

### Word Counter
```c
#include <stdio.h>
#include <ctype.h>  // For isspace() function

int count_words(const char text[]) {
    int count = 0;
    int in_word = 0;
    int i = 0;

    while (text[i] != '\0') {
        if (isspace(text[i])) {
            in_word = 0;
        } else if (!in_word) {
            in_word = 1;
            count++;
        }
        i++;
    }

    return count;
}

int main() {
    char text[200];

    printf("Enter a sentence: ");
    fgets(text, sizeof(text), stdin);

    // Remove newline
    int len = strlen(text);
    if (len > 0 && text[len - 1] == '\n') {
        text[len - 1] = '\0';
    }

    printf("Text: \"%s\"\n", text);
    printf("Character count: %zu\n", strlen(text));
    printf("Word count: %d\n", count_words(text));

    return 0;
}
```

### String Reversal
```c
#include <stdio.h>
#include <string.h>

// Function to reverse a string
void reverse_string(char str[]) {
    int length = strlen(str);
    int start = 0;
    int end = length - 1;

    while (start < end) {
        // Swap characters
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;

        start++;
        end--;
    }
}

// Function to check if string is a palindrome
int is_palindrome(const char str[]) {
    int length = strlen(str);
    int start = 0;
    int end = length - 1;

    while (start < end) {
        if (str[start] != str[end]) {
            return 0;  // Not a palindrome
        }
        start++;
        end--;
    }

    return 1;  // Is a palindrome
}

int main() {
    char text[100];

    printf("Enter a string: ");
    fgets(text, sizeof(text), stdin);

    // Remove newline
    int len = strlen(text);
    if (len > 0 && text[len - 1] == '\n') {
        text[len - 1] = '\0';
    }

    printf("Original: %s\n", text);

    reverse_string(text);
    printf("Reversed: %s\n", text);

    reverse_string(text);  // Restore original
    if (is_palindrome(text)) {
        printf("'%s' is a palindrome!\n", text);
    } else {
        printf("'%s' is not a palindrome.\n", text);
    }

    return 0;
}
```

### Simple Text Processing
```c
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to convert to uppercase
void to_uppercase(char str[]) {
    int i = 0;
    while (str[i] != '\0') {
        str[i] = toupper(str[i]);
        i++;
    }
}

// Function to count vowels
int count_vowels(const char str[]) {
    int count = 0;
    int i = 0;

    while (str[i] != '\0') {
        char c = tolower(str[i]);
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            count++;
        }
        i++;
    }

    return count;
}

int main() {
    char text[200];

    printf("Enter a line of text: ");
    fgets(text, sizeof(text), stdin);

    // Remove newline
    int len = strlen(text);
    if (len > 0 && text[len - 1] == '\n') {
        text[len - 1] = '\0';
    }

    printf("Original: %s\n", text);

    to_uppercase(text);
    printf("Uppercase: %s\n", text);

    printf("Character count: %zu\n", strlen(text));
    printf("Vowel count: %d\n", count_vowels(text));

    return 0;
}
```

## Common String Library Functions

### Essential String Functions
```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>  // For atoi, atof

int main() {
    // String manipulation
    char str1[50] = "Hello";
    char str2[] = " World";
    char numbers[] = "12345";
    char float_str[] = "3.14159";

    // Length
    printf("Length of '%s': %zu\n", str1, strlen(str1));

    // Copy
    char copy[50];
    strcpy(copy, str1);
    printf("Copy: %s\n", copy);

    // Concatenation
    strcat(str1, str2);
    printf("Concatenated: %s\n", str1);

    // Comparison
    printf("Compare 'apple' and 'banana': %d\n", strcmp("apple", "banana"));
    printf("Compare 'apple' and 'apple': %d\n", strcmp("apple", "apple"));

    // Find substring
    char text[] = "Hello, C Programming!";
    char *found = strstr(text, "C");
    if (found != NULL) {
        printf("Found 'C' at position: %ld\n", found - text);
    }

    // Find character
    char *char_found = strchr(text, 'P');
    if (char_found != NULL) {
        printf("Found 'P' at position: %ld\n", char_found - text);
    }

    // String to number conversion
    int num = atoi(numbers);
    float pi = atof(float_str);

    printf("String '%s' to integer: %d\n", numbers, num);
    printf("String '%s' to float: %.5f\n", float_str, pi);

    return 0;
}
```

## Array Applications

### Student Grade Management
```c
#include <stdio.h>

#define MAX_STUDENTS 5
#define MAX_NAME_LENGTH 30

struct Student {
    char name[MAX_NAME_LENGTH];
    int grades[3];  // 3 subjects
    float average;
};

// Function to calculate average
float calculate_average(int grades[], int num_subjects) {
    int sum = 0;
    for (int i = 0; i < num_subjects; i++) {
        sum += grades[i];
    }
    return (float)sum / num_subjects;
}

int main() {
    struct Student students[MAX_STUDENTS];

    // Input student data
    for (int i = 0; i < MAX_STUDENTS; i++) {
        printf("Enter name of student %d: ", i + 1);
        fgets(students[i].name, MAX_NAME_LENGTH, stdin);

        // Remove newline
        int len = strlen(students[i].name);
        if (len > 0 && students[i].name[len - 1] == '\n') {
            students[i].name[len - 1] = '\0';
        }

        printf("Enter grades for 3 subjects: ");
        for (int j = 0; j < 3; j++) {
            scanf("%d", &students[i].grades[j]);
        }
        while (getchar() != '\n');  // Clear input buffer

        students[i].average = calculate_average(students[i].grades, 3);
    }

    // Display results
    printf("\nStudent Results:\n");
    printf("================\n");
    for (int i = 0; i < MAX_STUDENTS; i++) {
        printf("%s: ", students[i].name);
        for (int j = 0; j < 3; j++) {
            printf("%d ", students[i].grades[j]);
        }
        printf("(Average: %.2f)\n", students[i].average);
    }

    return 0;
}
```

## Best Practices

### Array Safety
1. **Always check bounds** when accessing array elements
2. **Use sizeof(array)/sizeof(element[0])** to calculate array size
3. **Initialize arrays** to avoid garbage values
4. **Use safe string functions** (strncpy, strncat)
5. **Check for null terminators** in strings

### Memory Management
1. **Avoid buffer overflow** by checking array bounds
2. **Clear input buffers** after using scanf
3. **Initialize string buffers** properly
4. **Handle string termination** correctly

### Performance Considerations
1. **Linear search** is O(n) - suitable for small arrays
2. **Bubble sort** is O(n²) - not efficient for large datasets
3. **String operations** can be expensive - cache results when possible
4. **Multi-dimensional arrays** may have cache locality issues

## Common Errors and Solutions

### Array Index Out of Bounds
```c
// WRONG - Can access beyond array bounds
int arr[5];
arr[5] = 10;  // Error: valid indices are 0-4

// RIGHT - Check bounds
int arr[5];
int index = 5;
if (index < 5) {
    arr[index] = 10;
}
```

### String Buffer Overflow
```c
// WRONG - Can overflow buffer
char small[5];
strcpy(small, "This is too long");  // Buffer overflow!

// RIGHT - Use safe functions
char small[5];
strncpy(small, "This is too long", sizeof(small) - 1);
small[sizeof(small) - 1] = '\0';  // Ensure null termination
```

### Uninitialized Arrays
```c
// WRONG - Using uninitialized values
int numbers[5];
printf("%d\n", numbers[0]);  // Garbage value!

// RIGHT - Initialize arrays
int numbers[5] = {0};  // All elements initialized to 0
```

## Exercises

### Exercise 5.1: Array Statistics
Create a program that finds the sum, average, min, and max of an integer array.

### Exercise 5.2: Array Reversal
Write a function that reverses the elements of an array in-place.

### Exercise 5.3: Duplicate Element Finder
Create a program that finds duplicate elements in an array.

### Exercise 5.4: String Palindrome Checker
Write a program that checks if a string is a palindrome (ignoring spaces and case).

### Exercise 5.5: Simple Contact List
Create an array-based contact list that stores names and phone numbers.

## Challenge Problems

### Challenge 5.1: Array Rotation
Write a function to rotate an array by k positions to the right.

### Challenge 5.2: String Tokenizer
Implement a simple string tokenizer that splits a string by spaces.

### Challenge 5.3: Matrix Multiplication
Implement matrix multiplication for two 2D arrays.

## Quick Reference

### Array Operations
- **Declaration**: `type array[size];`
- **Initialization**: `type array[] = {values};`
- **Size calculation**: `sizeof(array) / sizeof(array[0])`
- **Access**: `array[index]`

### String Functions
- **Length**: `strlen(string)`
- **Copy**: `strcpy(dest, src)`, `strncpy(dest, src, n)`
- **Concatenation**: `strcat(dest, src)`, `strncat(dest, src, n)`
- **Comparison**: `strcmp(str1, str2)`, `strncmp(str1, str2, n)`
- **Search**: `strstr(haystack, needle)`, `strchr(string, character)`

### String to Number Conversion
- **Integer**: `atoi(string)`
- **Float**: `atof(string)`
- **Long**: `atol(string)`

## Next Steps
Once you're comfortable with:
- Working with single and multi-dimensional arrays
- Implementing array algorithms
- Manipulating strings safely
- Using string library functions
- Building practical applications with arrays

You're ready to move to **Chapter 6: Pointers** - one of the most important concepts in C!