# Chapter 12: Algorithms and Problem Solving

## Learning Objectives
By the end of this chapter, you will be able to:
- Implement advanced searching algorithms (binary search, string searching)
- Master fundamental sorting algorithms and understand their trade-offs
- Apply recursive problem-solving techniques effectively
- Understand and analyze algorithmic complexity using Big O notation
- Recognize and implement common problem-solving patterns

## Introduction to Algorithms

An algorithm is a step-by-step procedure for solving a problem or accomplishing a task. In programming, choosing the right algorithm can make the difference between code that runs in milliseconds and code that takes hours.

### The Algorithm Mindset

Algorithmic thinking is more than just knowing specific algorithms - it's a way of approaching problems systematically:

1. **Problem Analysis**: Understand what you're trying to solve
2. **Solution Design**: Create a step-by-step approach
3. **Complexity Analysis**: Evaluate efficiency and scalability
4. **Implementation**: Translate design into working code
5. **Optimization**: Improve the solution based on analysis

### Why Algorithmic Thinking Matters

1. **Efficiency**: Better algorithms solve problems faster and use fewer resources
   - **Linear vs Logarithmic**: O(n) vs O(log n) can mean seconds vs milliseconds
   - **Space Efficiency**: Clever algorithms can use dramatically less memory
   - **Real-world Impact**: Database queries, network routing, data processing

2. **Scalability**: Good algorithms handle large inputs gracefully
   - **Small Input (n=100)**: O(n²) and O(n log n) both seem fast
   - **Large Input (n=1,000,000)**: O(n²) becomes impractical, O(n log n) remains usable
   - **Modern Data**: With big data, algorithmic choice is critical

3. **Problem Solving**: Algorithmic thinking helps break down complex problems
   - **Decomposition**: Breaking large problems into smaller subproblems
   - **Pattern Recognition**: Identifying common problem types
   - **Abstraction**: Focusing on essential details while ignoring irrelevant ones

4. **Interview Preparation**: Algorithmic questions are common in technical interviews
   - **Big Tech**: FAANG companies emphasize algorithmic problem-solving
   - **Problem Types**: Arrays, strings, trees, graphs, dynamic programming
   - **Communication**: Being able to explain your thought process is crucial

### Understanding Algorithmic Complexity

Before diving into specific algorithms, let's establish a foundation for analyzing them:

#### Time Complexity: How Runtime Grows with Input

**O(1) - Constant Time:**
- Operation takes the same time regardless of input size
- Examples: Array access, hash table lookup (average case)
- ```
int getElement(int arr[], int index) {
    return arr[index];  // Always one operation
}
```

**O(log n) - Logarithmic Time:**
- Runtime grows logarithmically with input size
- Often involves dividing the problem in half repeatedly
- Examples: Binary search, balanced tree operations
- **Why log n?** Because log₂(1,000,000) ≈ 20, so 1 million items take ~20 operations

**O(n) - Linear Time:**
- Runtime grows linearly with input size
- Examples: Simple search, finding maximum in an array
- ```
int findMax(int arr[], int size) {
    int max = arr[0];
    for (int i = 1; i < size; i++) {  // n-1 operations
        if (arr[i] > max) max = arr[i];
    }
    return max;
}
```

**O(n log n) - Linearithmic Time:**
- Combination of linear and logarithmic growth
- Common in efficient sorting algorithms
- Examples: Merge sort, heap sort

**O(n²) - Quadratic Time:**
- Runtime grows quadratically with input size
- Often involves nested loops over the input
- Examples: Bubble sort, insertion sort (worst case)
- **Problem**: 1000 items → 1,000,000 operations; 1,000,000 items → 1,000,000,000,000 operations

#### Space Complexity: How Memory Usage Grows with Input

**In-place Algorithms**: Use O(1) extra space
- Modify input directly without additional data structures
- Examples: Bubble sort, in-place quicksort

**Auxiliary Space Algorithms**: Use O(n) or more extra space
- Create additional data structures during execution
- Examples: Merge sort (needs O(n) auxiliary array), recursive algorithms

#### Best, Average, and Worst Case

Not all algorithms perform the same across all inputs:

**Binary Search Analysis:**
- **Best Case**: O(1) - target is the middle element
- **Average Case**: O(log n) - target could be anywhere
- **Worst Case**: O(log n) - target at either end

**Linear Search Analysis:**
- **Best Case**: O(1) - target is the first element
- **Average Case**: O(n) - target is somewhere in the middle
- **Worst Case**: O(n) - target is the last element or not present

### Common Algorithmic Paradigms

Understanding these patterns helps you recognize and solve similar problems:

#### 1. Divide and Conquer
- **Idea**: Break problem into smaller subproblems, solve recursively, combine results
- **Examples**: Binary search, merge sort, quicksort
- **Pattern**: If you can solve a smaller version of the problem, combine solutions

#### 2. Greedy Algorithms
- **Idea**: Make locally optimal choices hoping for global optimum
- **Examples**: Dijkstra's algorithm, Huffman coding
- **Pattern**: When local choices lead to global solutions

#### 3. Dynamic Programming
- **Idea**: Solve by breaking into subproblems and storing results (memoization)
- **Examples**: Fibonacci sequence, shortest paths
- **Pattern**: When subproblems overlap and can be reused

#### 4. Backtracking
- **Idea**: Try possibilities, backtrack when they don't work
- **Examples**: N-Queens problem, maze solving
- **Pattern**: When you need to explore all possibilities systematically

### Problem-Solving Strategy

When faced with a new algorithmic problem:

1. **Understand the Problem**
   - What are the inputs and outputs?
   - What are the constraints?
   - What does an optimal solution look like?

2. **Start with a Simple Solution**
   - Brute force is often straightforward
   - Helps verify your understanding
   - Provides a baseline for comparison

3. **Look for Patterns**
   - Have you seen this type of problem before?
   - Can you apply known algorithms or techniques?
   - Are there simplifications you can make?

4. **Analyze Complexity**
   - What's the time complexity of your solution?
   - Is it optimal for the given constraints?
   - Can you do better?

5. **Iterate and Improve**
   - Refine your approach
   - Consider edge cases
   - Optimize for the specific problem constraints

This foundation will help you understand and implement the specific algorithms we'll cover in this chapter.

## Searching Algorithms

### Binary Search

Binary search is a divide-and-conquer algorithm that finds an item in a **sorted** array by repeatedly dividing the search interval in half.

```c
#include <stdio.h>
#include <stdlib.h>

// Iterative binary search
int binary_search_iterative(int arr[], int size, int target) {
    int left = 0;
    int right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            return mid; // Found
        }

        if (arr[mid] < target) {
            left = mid + 1; // Search right half
        } else {
            right = mid - 1; // Search left half
        }
    }

    return -1; // Not found
}

// Recursive binary search
int binary_search_recursive(int arr[], int left, int right, int target) {
    if (left > right) {
        return -1; // Not found
    }

    int mid = left + (right - left) / 2;

    if (arr[mid] == target) {
        return mid; // Found
    }

    if (arr[mid] < target) {
        return binary_search_recursive(arr, mid + 1, right, target);
    } else {
        return binary_search_recursive(arr, left, mid - 1, target);
    }
}

// Find first occurrence of target (handles duplicates)
int binary_search_first(int arr[], int size, int target) {
    int left = 0;
    int right = size - 1;
    int result = -1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            result = mid; // Remember current position
            right = mid - 1; // Continue searching left half
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return result;
}

// Find last occurrence of target (handles duplicates)
int binary_search_last(int arr[], int size, int target) {
    int left = 0;
    int right = size - 1;
    int result = -1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            result = mid; // Remember current position
            left = mid + 1; // Continue searching right half
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return result;
}

// Lower bound: first element >= target
int binary_search_lower_bound(int arr[], int size, int target) {
    int left = 0;
    int right = size;

    while (left < right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    return (left < size) ? left : -1;
}

// Upper bound: first element > target
int binary_search_upper_bound(int arr[], int size, int target) {
    int left = 0;
    int right = size;

    while (left < right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] <= target) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    return (left < size) ? left : -1;
}

int main() {
    int arr[] = {1, 3, 3, 5, 7, 9, 11, 13, 13, 13, 15};
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("Binary Search Demo\n");
    printf("==================\n");
    printf("Array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n\n");

    // Test different search operations
    int search_values[] = {3, 6, 13, 16};
    int num_searches = sizeof(search_values) / sizeof(search_values[0]);

    for (int i = 0; i < num_searches; i++) {
        int target = search_values[i];
        printf("Searching for %d:\n", target);

        int result_iter = binary_search_iterative(arr, size, target);
        int result_rec = binary_search_recursive(arr, 0, size - 1, target);
        int first = binary_search_first(arr, size, target);
        int last = binary_search_last(arr, size, target);
        int lower = binary_search_lower_bound(arr, size, target);
        int upper = binary_search_upper_bound(arr, size, target);

        printf("  Iterative: %s\n", result_iter != -1 ? "Found" : "Not found");
        printf("  Recursive: %s\n", result_rec != -1 ? "Found" : "Not found");

        if (result_iter != -1) {
            printf("  First occurrence: %d\n", first);
            printf("  Last occurrence: %d\n", last);
            printf("  Count: %d\n", (first != -1 && last != -1) ? last - first + 1 : 0);
        }
        printf("  Lower bound: %d\n", lower);
        printf("  Upper bound: %d\n\n", upper);
    }

    return 0;
}
```

### String Searching Algorithms

```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Naive string matching
int naive_search(const char* text, const char* pattern) {
    int n = strlen(text);
    int m = strlen(pattern);

    for (int i = 0; i <= n - m; i++) {
        int j;

        // Check if pattern matches at position i
        for (j = 0; j < m; j++) {
            if (text[i + j] != pattern[j]) {
                break;
            }
        }

        if (j == m) {
            return i; // Pattern found at position i
        }
    }

    return -1; // Pattern not found
}

// Find all occurrences of pattern in text
int find_all_occurrences(const char* text, const char* pattern, int* positions) {
    int n = strlen(text);
    int m = strlen(pattern);
    int count = 0;

    for (int i = 0; i <= n - m; i++) {
        int j;

        for (j = 0; j < m; j++) {
            if (text[i + j] != pattern[j]) {
                break;
            }
        }

        if (j == m) {
            positions[count++] = i;
        }
    }

    return count;
}

// Improved string matching with early termination
int improved_search(const char* text, const char* pattern) {
    int n = strlen(text);
    int m = strlen(pattern);

    // Check if pattern is longer than text
    if (m > n) return -1;

    // Find first character of pattern in text
    for (int i = 0; i <= n - m; i++) {
        if (text[i] == pattern[0]) {
            int j;

            // Check remaining characters
            for (j = 1; j < m; j++) {
                if (text[i + j] != pattern[j]) {
                    break;
                }
            }

            if (j == m) {
                return i; // Found
            }
        }
    }

    return -1; // Not found
}

// KMP (Knuth-Morris-Pratt) preprocessing
void compute_lps(const char* pattern, int* lps) {
    int m = strlen(pattern);
    int len = 0; // Length of the previous longest prefix suffix

    lps[0] = 0; // lps[0] is always 0
    int i = 1;

    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
                // Don't increment i here
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// KMP string matching
int kmp_search(const char* text, const char* pattern) {
    int n = strlen(text);
    int m = strlen(pattern);

    if (m == 0) return 0;
    if (n < m) return -1;

    // Create lps array
    int* lps = (int*)malloc(m * sizeof(int));
    if (lps == NULL) return -1;

    compute_lps(pattern, lps);

    int i = 0; // Index for text
    int j = 0; // Index for pattern

    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == m) {
            free(lps);
            return i - j; // Pattern found at index i - j
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }

    free(lps);
    return -1; // Pattern not found
}

// String searching utilities
void print_search_result(const char* text, const char* pattern, int algorithm, int result) {
    const char* alg_names[] = {"Naive", "Improved", "KMP"};
    printf("%s search for \"%s\" in \"%s\": ",
           alg_names[algorithm], pattern, text);

    if (result != -1) {
        printf("Found at position %d\n", result);
    } else {
        printf("Not found\n");
    }
}

int main() {
    const char* text = "ABABDABACDABABCABAB";
    const char* pattern = "ABABCABAB";
    const char* short_text = "hello world";
    const char* short_pattern = "world";

    printf("String Searching Demo\n");
    printf("=====================\n\n");

    // Test with long strings
    printf("Long string example:\n");
    printf("Text:    %s\n", text);
    printf("Pattern: %s\n\n", pattern);

    int result1 = naive_search(text, pattern);
    int result2 = improved_search(text, pattern);
    int result3 = kmp_search(text, pattern);

    print_search_result(text, pattern, 0, result1);
    print_search_result(text, pattern, 1, result2);
    print_search_result(text, pattern, 2, result3);

    printf("\nShort string example:\n");
    printf("Text:    %s\n", short_text);
    printf("Pattern: %s\n\n", short_pattern);

    result1 = naive_search(short_text, short_pattern);
    result2 = improved_search(short_text, short_pattern);
    result3 = kmp_search(short_text, short_pattern);

    print_search_result(short_text, short_pattern, 0, result1);
    print_search_result(short_text, short_pattern, 1, result2);
    print_search_result(short_text, short_pattern, 2, result3);

    // Find all occurrences
    printf("\nFinding all occurrences:\n");
    const char* multi_text = "abcabcabc";
    const char* multi_pattern = "abc";
    int positions[20];
    int count = find_all_occurrences(multi_text, multi_pattern, positions);

    printf("Text: %s\n", multi_text);
    printf("Pattern: %s\n", multi_pattern);
    printf("Occurrences: ");
    for (int i = 0; i < count; i++) {
        printf("%d ", positions[i]);
    }
    printf("(Total: %d)\n", count);

    return 0;
}
```

## Sorting Algorithms

### Basic Sorting Algorithms

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Utility functions
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void print_array(int arr[], int size, const char* label) {
    printf("%s: [", label);
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i < size - 1) printf(", ");
    }
    printf("]\n");
}

void copy_array(int src[], int dest[], int size) {
    for (int i = 0; i < size; i++) {
        dest[i] = src[i];
    }
}

// Bubble Sort
void bubble_sort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int swapped = 0;

        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                swapped = 1;
            }
        }

        // If no swapping occurred, array is already sorted
        if (!swapped) break;
    }
}

// Optimized Bubble Sort
void bubble_sort_optimized(int arr[], int size) {
    int n = size;
    while (n > 1) {
        int new_n = 0;

        for (int i = 1; i < n; i++) {
            if (arr[i - 1] > arr[i]) {
                swap(&arr[i - 1], &arr[i]);
                new_n = i;
            }
        }

        n = new_n;
    }
}

// Selection Sort
void selection_sort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int min_index = i;

        // Find minimum element in unsorted portion
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }

        // Swap with first unsorted element
        if (min_index != i) {
            swap(&arr[i], &arr[min_index]);
        }
    }
}

// Insertion Sort
void insertion_sort(int arr[], int size) {
    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;

        // Move elements that are greater than key
        // to one position ahead of their current position
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}

// Merge function for merge sort
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary arrays
    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));

    if (L == NULL || R == NULL) {
        free(L);
        free(R);
        return;
    }

    // Copy data to temporary arrays
    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }

    // Merge the temporary arrays back into arr[left..right]
    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy remaining elements of L[]
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy remaining elements of R[]
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

// Merge Sort
void merge_sort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Sort first and second halves
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);

        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

// Quick Sort partition function
int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // Choose last element as pivot
    int i = (low - 1);     // Index of smaller element

    for (int j = low; j <= high - 1; j++) {
        // If current element is smaller than the pivot
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// Quick Sort
void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        // Sort elements before and after partition
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

// Counting Sort (for non-negative integers)
void counting_sort(int arr[], int size) {
    if (size <= 1) return;

    // Find maximum value
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    // Create count array
    int* count = (int*)calloc(max + 1, sizeof(int));
    int* output = (int*)malloc(size * sizeof(int));

    if (count == NULL || output == NULL) {
        free(count);
        free(output);
        return;
    }

    // Store count of each element
    for (int i = 0; i < size; i++) {
        count[arr[i]]++;
    }

    // Change count[i] so that count[i] contains actual
    // position of this element in output array
    for (int i = 1; i <= max; i++) {
        count[i] += count[i - 1];
    }

    // Build output array
    for (int i = size - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    // Copy output array to original array
    for (int i = 0; i < size; i++) {
        arr[i] = output[i];
    }

    free(count);
    free(output);
}

// Compare function for qsort
int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

// Test sorting algorithms
void test_sorting_algorithm(const char* name, void (*sort_func)(int[], int),
                           int original[], int size) {
    int* arr = (int*)malloc(size * sizeof(int));
    if (arr == NULL) return;

    copy_array(original, arr, size);

    printf("Testing %s:\n", name);
    print_array(arr, size, "  Before");

    sort_func(arr, size);

    print_array(arr, size, "  After");

    // Verify array is sorted
    int sorted = 1;
    for (int i = 0; i < size - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            sorted = 0;
            break;
        }
    }

    printf("  %s\n\n", sorted ? "✓ Sorted correctly" : "✗ Not sorted");

    free(arr);
}

// Test recursive sorting algorithms
void test_recursive_sorting(const char* name, void (*sort_func)(int[], int, int),
                           int original[], int size) {
    int* arr = (int*)malloc(size * sizeof(int));
    if (arr == NULL) return;

    copy_array(original, arr, size);

    printf("Testing %s:\n", name);
    print_array(arr, size, "  Before");

    sort_func(arr, 0, size - 1);

    print_array(arr, size, "  After");

    // Verify array is sorted
    int sorted = 1;
    for (int i = 0; i < size - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            sorted = 0;
            break;
        }
    }

    printf("  %s\n\n", sorted ? "✓ Sorted correctly" : "✗ Not sorted");

    free(arr);
}

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90, 88, 76, 50, 42};
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("Sorting Algorithms Demo\n");
    printf("=======================\n");
    print_array(arr, size, "Original array");
    printf("\n");

    // Test all sorting algorithms
    test_sorting_algorithm("Bubble Sort", bubble_sort, arr, size);
    test_sorting_algorithm("Optimized Bubble Sort", bubble_sort_optimized, arr, size);
    test_sorting_algorithm("Selection Sort", selection_sort, arr, size);
    test_sorting_algorithm("Insertion Sort", insertion_sort, arr, size);
    test_recursive_sorting("Merge Sort", merge_sort, arr, size);
    test_recursive_sorting("Quick Sort", quick_sort, arr, size);
    test_sorting_algorithm("Counting Sort", counting_sort, arr, size);

    // Test standard library qsort
    int* arr_copy = (int*)malloc(size * sizeof(int));
    if (arr_copy != NULL) {
        copy_array(arr, arr_copy, size);

        printf("Testing Standard qsort:\n");
        print_array(arr_copy, size, "  Before");

        qsort(arr_copy, size, sizeof(int), compare);

        print_array(arr_copy, size, "  After");
        printf("  ✓ Sorted correctly\n\n");

        free(arr_copy);
    }

    return 0;
}
```

## Recursion Techniques

### Advanced Recursion Patterns

```c
#include <stdio.h>
#include <stdlib.h>

// Tower of Hanoi - Classic recursion example
void tower_of_hanoi(int n, char from_rod, char to_rod, char aux_rod) {
    if (n == 1) {
        printf("Move disk 1 from %c to %c\n", from_rod, to_rod);
        return;
    }

    tower_of_hanoi(n - 1, from_rod, aux_rod, to_rod);
    printf("Move disk %d from %c to %c\n", n, from_rod, to_rod);
    tower_of_hanoi(n - 1, aux_rod, to_rod, from_rod);
}

// Fibonacci with memoization (dynamic programming)
#define MAX_FIB 100

long long fib_memo[MAX_FIB];

long long fibonacci_memoization(int n) {
    // Base cases
    if (n <= 1) return n;

    // Return cached value if available
    if (fib_memo[n] != -1) {
        return fib_memo[n];
    }

    // Compute and cache the result
    fib_memo[n] = fibonacci_memoization(n - 1) + fibonacci_memoization(n - 2);
    return fib_memo[n];
}

// Initialize memoization array
void init_fib_memo() {
    for (int i = 0; i < MAX_FIB; i++) {
        fib_memo[i] = -1;
    }
}

// Power function with fast exponentiation
double power(double base, int exp) {
    if (exp == 0) return 1.0;
    if (exp == 1) return base;

    // Handle negative exponents
    if (exp < 0) {
        return 1.0 / power(base, -exp);
    }

    // Fast exponentiation: x^n = (x^(n/2))^2 if n is even
    if (exp % 2 == 0) {
        double half = power(base, exp / 2);
        return half * half;
    } else {
        return base * power(base, exp - 1);
    }
}

// Generate all subsets of a set
void generate_subsets(char set[], int n, int index, char current[], int current_size) {
    if (index == n) {
        printf("{ ");
        for (int i = 0; i < current_size; i++) {
            printf("%c ", current[i]);
        }
        printf("}\n");
        return;
    }

    // Exclude current element
    generate_subsets(set, n, index + 1, current, current_size);

    // Include current element
    current[current_size] = set[index];
    generate_subsets(set, n, index + 1, current, current_size + 1);
}

// Generate all permutations of a string
void swap_chars(char* a, char* b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

void generate_permutations(char* str, int start, int end) {
    if (start == end) {
        printf("%s\n", str);
        return;
    }

    for (int i = start; i <= end; i++) {
        swap_chars(&str[start], &str[i]);
        generate_permutations(str, start + 1, end);
        swap_chars(&str[start], &str[i]); // Backtrack
    }
}

// Backtracking: N-Queens problem
#define N 8

int board[N][N];

void print_board() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%c ", board[i][j] ? 'Q' : '.');
        }
        printf("\n");
    }
    printf("\n");
}

int is_safe(int row, int col) {
    // Check this row on left side
    for (int i = 0; i < col; i++) {
        if (board[row][i]) return 0;
    }

    // Check upper diagonal on left side
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j]) return 0;
    }

    // Check lower diagonal on left side
    for (int i = row, j = col; i < N && j >= 0; i++, j--) {
        if (board[i][j]) return 0;
    }

    return 1;
}

int solve_n_queens(int col) {
    // Base case: If all queens are placed, return true
    if (col >= N) {
        return 1;
    }

    // Try placing queen in all rows one by one
    for (int row = 0; row < N; row++) {
        if (is_safe(row, col)) {
            board[row][col] = 1;

            if (solve_n_queens(col + 1)) {
                return 1;
            }

            // If placing queen doesn't lead to solution, backtrack
            board[row][col] = 0;
        }
    }

    return 0;
}

// Euclidean algorithm for GCD (recursive)
int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

// Binary Search in rotated sorted array
int search_rotated(int arr[], int left, int right, int target) {
    if (left > right) {
        return -1;
    }

    int mid = left + (right - left) / 2;

    if (arr[mid] == target) {
        return mid;
    }

    // Check if left half is sorted
    if (arr[left] <= arr[mid]) {
        if (target >= arr[left] && target <= arr[mid]) {
            return search_rotated(arr, left, mid - 1, target);
        } else {
            return search_rotated(arr, mid + 1, right, target);
        }
    } else {
        // Right half is sorted
        if (target >= arr[mid] && target <= arr[right]) {
            return search_rotated(arr, mid + 1, right, target);
        } else {
            return search_rotated(arr, left, mid - 1, target);
        }
    }
}

int main() {
    printf("Advanced Recursion Techniques\n");
    printf("=============================\n\n");

    // 1. Tower of Hanoi
    printf("1. Tower of Hanoi (3 disks):\n");
    tower_of_hanoi(3, 'A', 'C', 'B');
    printf("\n");

    // 2. Fibonacci with memoization
    printf("2. Fibonacci with memoization:\n");
    init_fib_memo();
    for (int i = 0; i <= 20; i++) {
        printf("F(%d) = %lld\n", i, fibonacci_memoization(i));
    }
    printf("\n");

    // 3. Fast exponentiation
    printf("3. Fast exponentiation:\n");
    printf("2^10 = %.0f\n", power(2.0, 10));
    printf("3^-2 = %.6f\n", power(3.0, -2));
    printf("5^7 = %.0f\n", power(5.0, 7));
    printf("\n");

    // 4. Generate subsets
    printf("4. Subsets of {A, B, C}:\n");
    char set[] = {'A', 'B', 'C'};
    char current[3];
    generate_subsets(set, 3, 0, current, 0);
    printf("\n");

    // 5. Generate permutations
    printf("5. Permutations of \"ABC\":\n");
    char str[] = "ABC";
    generate_permutations(str, 0, 2);
    printf("\n");

    // 6. N-Queens problem (using 4 queens for display)
    printf("6. N-Queens problem (4 queens):\n");
    #undef N
    #define N 4

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            board[i][j] = 0;
        }
    }

    if (solve_n_queens(0)) {
        print_board();
    } else {
        printf("No solution exists\n");
    }
    printf("\n");

    // 7. GCD using Euclidean algorithm
    printf("7. GCD using recursion:\n");
    printf("GCD(48, 18) = %d\n", gcd(48, 18));
    printf("GCD(60, 25) = %d\n", gcd(60, 25));
    printf("GCD(17, 13) = %d\n", gcd(17, 13));
    printf("\n");

    // 8. Search in rotated sorted array
    printf("8. Binary search in rotated array:\n");
    int rotated[] = {15, 18, 2, 3, 6, 12};
    int n = sizeof(rotated) / sizeof(rotated[0]);

    printf("Array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", rotated[i]);
    }
    printf("\n");

    int targets[] = {3, 15, 12, 7};
    for (int i = 0; i < 4; i++) {
        int result = search_rotated(rotated, 0, n - 1, targets[i]);
        if (result != -1) {
            printf("Found %d at index %d\n", targets[i], result);
        } else {
            printf("%d not found\n", targets[i]);
        }
    }

    return 0;
}
```

## Algorithmic Complexity

### Big O Notation and Analysis

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Generate random array
void generate_random_array(int arr[], int size, int max_value) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % max_value;
    }
}

// O(1) - Constant time
int get_first_element(int arr[], int size) {
    if (size > 0) {
        return arr[0];
    }
    return -1;
}

// O(log n) - Logarithmic time
int binary_search_demo(int arr[], int size, int target) {
    int left = 0, right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) return mid;
        if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }

    return -1;
}

// O(n) - Linear time
int find_max(int arr[], int size) {
    if (size == 0) return -1;

    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

// O(n log n) - Linearithmic time (simplified merge sort)
void simple_sort_for_demo(int arr[], int size) {
    // This is just for demonstration - not a real O(n log n) sort
    // Using qsort from stdlib
    qsort(arr, size, sizeof(int),
          [](const void* a, const void* b) {
              return (*(int*)a - *(int*)b);
          });
}

// O(n²) - Quadratic time
void bubble_sort_demo(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// O(2^n) - Exponential time (Fibonacci without memoization)
long long fibonacci_naive(int n) {
    if (n <= 1) return n;
    return fibonacci_naive(n - 1) + fibonacci_naive(n - 2);
}

// O(n!) - Factorial time (generate all permutations)
void factorial_time_demo() {
    printf("Factorial time complexity example:\n");
    printf("Permutations of 3 elements: 3! = 6 permutations\n");
    printf("Permutations of 4 elements: 4! = 24 permutations\n");
    printf("Permutations of 5 elements: 5! = 120 permutations\n");
    printf("Permutations of 10 elements: 10! = 3,628,800 permutations\n");
    printf("Permutations of 20 elements: 20! ≈ 2.4 × 10^18 permutations\n");
}

// Performance measurement function
double measure_time(void (*func)(int[], int), int arr[], int size) {
    clock_t start, end;
    double cpu_time_used;

    // Create a copy of the array to sort
    int* arr_copy = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        arr_copy[i] = arr[i];
    }

    start = clock();
    func(arr_copy, size);
    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    free(arr_copy);
    return cpu_time_used;
}

// Complexity comparison table
void print_complexity_table() {
    printf("\nComplexity Comparison Table:\n");
    printf("Input Size |  O(1)  | O(log n) |  O(n)  | O(n log n) | O(n²)   | O(2ⁿ)   | O(n!)   \n");
    printf("-----------|--------|----------|--------|------------|---------|---------|----------\n");

    int sizes[] = {1, 10, 100, 1000, 10000};

    for (int i = 0; i < 5; i++) {
        int n = sizes[i];
        printf("%10d |%7d |%9.2f |%7d |%11.0f |%8.0f |%8.0f |%9.0f\n",
               n,
               1,                                                    // O(1)
               n == 0 ? 0 : log2(n),                                // O(log n)
               n,                                                    // O(n)
               n == 0 ? 0 : n * log2(n),                            // O(n log n)
               (long long)n * n,                                    // O(n²)
               n < 64 ? (long long)pow(2, n) : -1,                  // O(2ⁿ)
               n < 13 ? (long long)exp(lgamma(n + 1)) : -1);        // O(n!)
    }
}

// Memory complexity demonstration
void memory_complexity_demo() {
    printf("\nMemory Complexity Examples:\n");
    printf("1. O(1) Space: Single variable, basic operations\n");
    printf("2. O(n) Space: Array of size n, basic recursion\n");
    printf("3. O(n²) Space: 2D matrix, nested data structures\n");
    printf("4. O(2ⁿ) Space: Tree recursion without memoization\n");
    printf("5. O(n!) Space: Generating all permutations\n");
}

int main() {
    printf("Algorithmic Complexity Analysis\n");
    printf("==============================\n");

    srand(time(NULL));

    // Demonstrate different complexities
    printf("\n1. O(1) - Constant Time Example:\n");
    int small_array[] = {5, 2, 8, 1, 9};
    printf("First element: %d\n", get_first_element(small_array, 5));

    printf("\n2. O(log n) - Logarithmic Time Example:\n");
    int sorted_array[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
    int search_target = 13;
    int result = binary_search_demo(sorted_array, 10, search_target);
    printf("Found %d at index %d\n", search_target, result);

    printf("\n3. O(n) - Linear Time Example:\n");
    int max_val = find_max(small_array, 5);
    printf("Maximum value: %d\n", max_val);

    printf("\n4. Performance Comparison:\n");

    // Test with different array sizes
    int sizes[] = {100, 1000, 5000};

    for (int i = 0; i < 3; i++) {
        int size = sizes[i];
        int* test_array = (int*)malloc(size * sizeof(int));
        generate_random_array(test_array, size, 10000);

        printf("\nArray size: %d elements\n", size);

        // Test bubble sort (O(n²))
        double time_bubble = measure_time(bubble_sort_demo, test_array, size);
        printf("Bubble sort (O(n²)): %.6f seconds\n", time_bubble);

        free(test_array);
    }

    printf("\n5. Exponential vs Polynomial Growth:\n");
    printf("For n = 20:\n");
    printf("n² = 400 operations\n");
    printf("2ⁿ = 1,048,576 operations\n");
    printf("n! = 2,432,902,008,176,640,000 operations\n");

    factorial_time_demo();

    print_complexity_table();
    memory_complexity_demo();

    printf("\nKey Insights:\n");
    printf("1. Algorithm choice matters most for large inputs\n");
    printf("2. O(n log n) is often the best achievable for comparison sorts\n");
    printf("3. Exponential algorithms become impractical quickly\n");
    printf("4. Space complexity is as important as time complexity\n");
    printf("5. Real-world performance depends on both complexity and constants\n");

    return 0;
}
```

## Common Problem-Solving Patterns

### Essential Algorithmic Patterns

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Pattern 1: Two Pointers
int two_sum_sorted(int arr[], int size, int target) {
    int left = 0, right = size - 1;

    while (left < right) {
        int sum = arr[left] + arr[right];

        if (sum == target) {
            printf("Found pair: %d + %d = %d\n", arr[left], arr[right], target);
            return 1;
        } else if (sum < target) {
            left++;
        } else {
            right--;
        }
    }

    return 0;
}

// Pattern 2: Sliding Window
int max_subarray_sum(int arr[], int size, int k) {
    if (size < k) return -1;

    int window_sum = 0;
    int max_sum;

    // Calculate sum of first window
    for (int i = 0; i < k; i++) {
        window_sum += arr[i];
    }

    max_sum = window_sum;

    // Slide the window
    for (int i = k; i < size; i++) {
        window_sum += arr[i] - arr[i - k];
        if (window_sum > max_sum) {
            max_sum = window_sum;
        }
    }

    return max_sum;
}

// Pattern 3: Frequency Counting
void find_duplicates(int arr[], int size) {
    int max_val = 0;

    // Find maximum value
    for (int i = 0; i < size; i++) {
        if (arr[i] > max_val) max_val = arr[i];
    }

    int* frequency = (int*)calloc(max_val + 1, sizeof(int));

    // Count frequencies
    for (int i = 0; i < size; i++) {
        frequency[arr[i]]++;
    }

    printf("Duplicates found: ");
    int found = 0;
    for (int i = 0; i <= max_val; i++) {
        if (frequency[i] > 1) {
            printf("%d ", i);
            found = 1;
        }
    }

    if (!found) {
        printf("No duplicates");
    }
    printf("\n");

    free(frequency);
}

// Pattern 4: Prefix Sum
void range_sum_queries(int arr[], int size, int queries[][2], int num_queries) {
    // Create prefix sum array
    int* prefix_sum = (int*)malloc((size + 1) * sizeof(int));
    prefix_sum[0] = 0;

    for (int i = 0; i < size; i++) {
        prefix_sum[i + 1] = prefix_sum[i] + arr[i];
    }

    // Answer queries
    printf("Range sum queries:\n");
    for (int i = 0; i < num_queries; i++) {
        int left = queries[i][0];
        int right = queries[i][1];
        int sum = prefix_sum[right + 1] - prefix_sum[left];
        printf("Sum of arr[%d..%d] = %d\n", left, right, sum);
    }

    free(prefix_sum);
}

// Pattern 5: Divide and Conquer - Find peak element
int find_peak_element(int arr[], int left, int right) {
    if (left == right) {
        return left;
    }

    int mid = left + (right - left) / 2;

    if (arr[mid] > arr[mid + 1]) {
        return find_peak_element(arr, left, mid);
    } else {
        return find_peak_element(arr, mid + 1, right);
    }
}

// Pattern 6: Greedy - Activity selection problem
typedef struct {
    int start;
    int end;
} Activity;

int compare_activities(const void* a, const void* b) {
    Activity* actA = (Activity*)a;
    Activity* actB = (Activity*)b;
    return actA->end - actB->end;
}

void activity_selection(Activity activities[], int n) {
    // Sort activities by end time
    qsort(activities, n, sizeof(Activity), compare_activities);

    printf("Selected activities:\n");
    int count = 0;
    int last_end = -1;

    for (int i = 0; i < n; i++) {
        if (activities[i].start >= last_end) {
            printf("Activity %d: Start=%d, End=%d\n",
                   count + 1, activities[i].start, activities[i].end);
            last_end = activities[i].end;
            count++;
        }
    }

    printf("Maximum activities: %d\n", count);
}

// Pattern 7: Dynamic Programming - Coin Change
int coin_change(int coins[], int n, int amount) {
    int* dp = (int*)malloc((amount + 1) * sizeof(int));

    for (int i = 0; i <= amount; i++) {
        dp[i] = amount + 1; // Initialize with "infinity"
    }

    dp[0] = 0;

    for (int i = 1; i <= amount; i++) {
        for (int j = 0; j < n; j++) {
            if (coins[j] <= i) {
                dp[i] = (dp[i] < dp[i - coins[j]] + 1) ? dp[i] : dp[i - coins[j]] + 1;
            }
        }
    }

    int result = dp[amount] > amount ? -1 : dp[amount];
    free(dp);
    return result;
}

// Pattern 8: Backtracking - Generate parentheses
void generate_parentheses(int n, int open, int close, char* current, int index, int** results, int* result_count) {
    if (index == 2 * n) {
        current[index] = '\0';

        // Add to results (simplified for demo)
        printf("%s\n", current);
        (*result_count)++;
        return;
    }

    if (open < n) {
        current[index] = '(';
        generate_parentheses(n, open + 1, close, current, index + 1, results, result_count);
    }

    if (close < open) {
        current[index] = ')';
        generate_parentheses(n, open, close + 1, current, index + 1, results, result_count);
    }
}

int main() {
    printf("Common Problem-Solving Patterns\n");
    printf("===============================\n\n");

    // Pattern 1: Two Pointers
    printf("1. Two Pointers Pattern - Two Sum in Sorted Array:\n");
    int sorted_arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int target = 15;
    two_sum_sorted(sorted_arr, 9, target);
    printf("\n");

    // Pattern 2: Sliding Window
    printf("2. Sliding Window Pattern - Maximum Subarray Sum:\n");
    int window_arr[] = {2, 1, 5, 1, 3, 2};
    int k = 3;
    int max_sum = max_subarray_sum(window_arr, 6, k);
    printf("Maximum sum of window size %d: %d\n\n", k, max_sum);

    // Pattern 3: Frequency Counting
    printf("3. Frequency Counting Pattern - Find Duplicates:\n");
    int dup_arr[] = {1, 2, 3, 4, 5, 2, 3, 6, 7, 3};
    find_duplicates(dup_arr, 10);
    printf("\n");

    // Pattern 4: Prefix Sum
    printf("4. Prefix Sum Pattern - Range Sum Queries:\n");
    int prefix_arr[] = {1, 2, 3, 4, 5};
    int queries[][2] = {{0, 2}, {1, 3}, {0, 4}};
    range_sum_queries(prefix_arr, 5, queries, 3);
    printf("\n");

    // Pattern 5: Divide and Conquer
    printf("5. Divide and Conquer Pattern - Find Peak Element:\n");
    int peak_arr[] = {1, 3, 20, 4, 1, 0};
    int peak_index = find_peak_element(peak_arr, 0, 5);
    printf("Peak element %d at index %d\n\n", peak_arr[peak_index], peak_index);

    // Pattern 6: Greedy
    printf("6. Greedy Pattern - Activity Selection:\n");
    Activity activities[] = {
        {1, 4}, {3, 5}, {0, 6}, {5, 7}, {8, 9}, {5, 9}
    };
    activity_selection(activities, 6);
    printf("\n");

    // Pattern 7: Dynamic Programming
    printf("7. Dynamic Programming Pattern - Coin Change:\n");
    int coins[] = {1, 3, 4};
    int amount = 6;
    int min_coins = coin_change(coins, 3, amount);
    printf("Minimum coins for amount %d: %d\n\n", amount, min_coins);

    // Pattern 8: Backtracking
    printf("8. Backtracking Pattern - Generate Parentheses:\n");
    char current[7]; // For n=3
    int result_count = 0;
    printf("Valid parentheses for n=3:\n");
    generate_parentheses(3, 0, 0, current, 0, NULL, &result_count);
    printf("Total combinations: %d\n", result_count);

    printf("\nPattern Recognition Tips:\n");
    printf("1. Two Pointers: Sorted arrays, finding pairs\n");
    printf("2. Sliding Window: Subarrays, fixed-size windows\n");
    printf("3. Frequency Counting: Counting occurrences, duplicates\n");
    printf("4. Prefix Sum: Range queries, cumulative sums\n");
    printf("5. Divide and Conquer: Break problems into smaller subproblems\n");
    printf("6. Greedy: Local optimal leads to global optimal\n");
    printf("7. Dynamic Programming: Overlapping subproblems, optimal substructure\n");
    printf("8. Backtracking: Exploration, combination problems\n");

    return 0;
}
```

## Best Practices

### Algorithm Implementation Guidelines

1. **Choose the Right Data Structure**
   - Arrays for indexed access and memory efficiency
   - Linked lists for frequent insertions/deletions
   - Hash tables for fast lookups
   - Trees for ordered data and range queries

2. **Handle Edge Cases**
   - Empty arrays, single elements
   - Duplicates in sorted arrays
   - Integer overflow with large numbers
   - Memory allocation failures

3. **Optimize for the Common Case**
   - Consider input size distribution
   - Profile before optimizing
   - Balance time vs space complexity
   - Use appropriate algorithmic patterns

4. **Write Clean, Readable Code**
   - Use descriptive variable names
   - Add meaningful comments
   - Break complex algorithms into functions
   - Follow consistent coding style

## Exercises

### Exercise 12.1: Advanced Binary Search
Implement binary search for finding the square root of a number.

### Exercise 12.2: Sorting Comparison
Compare performance of different sorting algorithms on various data patterns.

### Exercise 12.3: Dynamic Programming
Solve the knapsack problem using dynamic programming.

### Exercise 12.4: Pattern Recognition
Identify and implement the appropriate algorithmic pattern for given problems.

### Exercise 12.5: Complexity Analysis
Analyze and improve the time/space complexity of given algorithms.

## Challenge Problems

### Challenge 12.1: Advanced Data Structures
Implement a self-balancing binary search tree (AVL or Red-Black).

### Challenge 12.2: Graph Algorithms
Implement Dijkstra's algorithm for shortest path finding.

### Challenge 12.3: String Algorithms
Implement the Rabin-Karp string matching algorithm.

## Quick Reference

### Algorithm Complexity Summary
```c
// Common Time Complexities
O(1)      - Constant time
O(log n)  - Logarithmic time
O(n)      - Linear time
O(n log n) - Linearithmic time
O(n²)     - Quadratic time
O(n³)     - Cubic time
O(2ⁿ)     - Exponential time
O(n!)     - Factorial time

// Sorting Algorithms
Bubble Sort    - O(n²) time, O(1) space
Selection Sort - O(n²) time, O(1) space
Insertion Sort - O(n²) time, O(1) space
Merge Sort     - O(n log n) time, O(n) space
Quick Sort     - O(n log n) avg, O(n²) worst, O(log n) space
Counting Sort  - O(n + k) time, O(k) space

// Searching Algorithms
Linear Search  - O(n) time
Binary Search  - O(log n) time (requires sorted array)
Hash Table     - O(1) average, O(n) worst
```

## Next Steps
Once you're comfortable with:
- Implementing fundamental sorting and searching algorithms
- Understanding algorithmic complexity and analysis
- Recognizing and applying problem-solving patterns
- Writing efficient recursive solutions

You're ready for **Chapter 13: System Programming**!