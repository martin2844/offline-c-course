// Chapter 15: Performance Optimization - Algorithm Comparison
// Solution to Exercise 15.2: Compare performance with different compiler optimization levels

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

// Function to be optimized - calculates prime numbers
void find_primes_naive(int limit, int* primes, int* count) {
    *count = 0;

    for (int num = 2; num <= limit; num++) {
        int is_prime = 1;

        // Naive primality test
        for (int i = 2; i < num; i++) {
            if (num % i == 0) {
                is_prime = 0;
                break;
            }
        }

        if (is_prime) {
            primes[(*count)++] = num;
        }
    }
}

// Optimized prime finding function
void find_primes_optimized(int limit, int* primes, int* count) {
    *count = 0;

    for (int num = 2; num <= limit; num++) {
        int is_prime = 1;

        // Optimized primality test - check up to sqrt(num)
        int sqrt_num = (int)sqrt(num);
        for (int i = 2; i <= sqrt_num; i++) {
            if (num % i == 0) {
                is_prime = 0;
                break;
            }
        }

        if (is_prime) {
            primes[(*count)++] = num;
        }
    }
}

// Sieve of Eratosthenes - most efficient approach
void find_primes_sieve(int limit, int* primes, int* count) {
    // Create boolean array "prime[0..limit]"
    char* prime = (char*)malloc((limit + 1) * sizeof(char));
    memset(prime, 1, (limit + 1) * sizeof(char));

    *count = 0;

    // 0 and 1 are not prime numbers
    prime[0] = prime[1] = 0;

    for (int p = 2; p * p <= limit; p++) {
        // If prime[p] is not changed, then it is a prime
        if (prime[p]) {
            // Update all multiples of p
            for (int i = p * p; i <= limit; i += p) {
                prime[i] = 0;
            }
        }
    }

    // Collect prime numbers
    for (int p = 2; p <= limit; p++) {
        if (prime[p]) {
            primes[(*count)++] = p;
        }
    }

    free(prime);
}

// Function that benefits from loop unrolling
void array_processing(int* input, int* output, int size) {
    int i;
    // Process 4 elements at a time (loop unrolling)
    for (i = 0; i <= size - 4; i += 4) {
        output[i] = input[i] * input[i];
        output[i + 1] = input[i + 1] * input[i + 1];
        output[i + 2] = input[i + 2] * input[i + 2];
        output[i + 3] = input[i + 3] * input[i + 3];
    }

    // Handle remaining elements
    for (; i < size; i++) {
        output[i] = input[i] * input[i];
    }
}

// Matrix multiplication function
void matrix_multiply(int a[100][100], int b[100][100], int result[100][100]) {
    // Initialize result matrix
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            result[i][j] = 0;
        }
    }

    // Multiply matrices
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            for (int k = 0; k < 100; k++) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

// Timing utility
double get_time() {
    clock_t start = clock();
    return (double)start / CLOCKS_PER_SEC;
}

// Run benchmark for a function
void benchmark_function(const char* name, void (*func)(int, int*, int*),
                       int limit, int* primes, int* count) {
    printf("Benchmarking %s (limit: %d):\n", name, limit);

    double start = get_time();
    func(limit, primes, count);
    double end = get_time();

    printf("  Time: %.6f seconds\n", end - start);
    printf("  Primes found: %d\n", *count);
    printf("  First 10 primes: ");
    for (int i = 0; i < (*count < 10 ? *count : 10); i++) {
        printf("%d ", primes[i]);
    }
    printf("\n\n");
}

// Performance comparison with optimization levels
void compare_optimization_levels() {
    printf("=== Optimization Level Comparison ===\n");
    printf("Compile with different optimization levels to see the difference:\n");
    printf("  gcc -O0 -o program program.c  (No optimization)\n");
    printf("  gcc -O1 -o program program.c  (Basic optimization)\n");
    printf("  gcc -O2 -o program program.c  (Standard optimization)\n");
    printf("  gcc -O3 -o program program.c  (Aggressive optimization)\n");
    printf("  gcc -Os -o program program.c  (Optimize for size)\n\n");
}

int main() {
    printf("Performance Optimization Comparison\n");
    printf("==================================\n");

    compare_optimization_levels();

    const int LIMIT = 10000;
    int* primes = malloc(LIMIT * sizeof(int));
    int count;

    // Benchmark prime finding algorithms
    printf("=== Prime Finding Algorithm Comparison ===\n");

    benchmark_function("Naive Prime Finding", find_primes_naive, LIMIT, primes, &count);
    benchmark_function("Optimized Prime Finding", find_primes_optimized, LIMIT, primes, &count);
    benchmark_function("Sieve of Eratosthenes", find_primes_sieve, LIMIT, primes, &count);

    // Benchmark array processing
    printf("=== Array Processing Benchmark ===\n");
    const int ARRAY_SIZE = 1000000;
    int* input = malloc(ARRAY_SIZE * sizeof(int));
    int* output = malloc(ARRAY_SIZE * sizeof(int));

    // Initialize array
    for (int i = 0; i < ARRAY_SIZE; i++) {
        input[i] = rand() % 1000;
    }

    double start = get_time();
    array_processing(input, output, ARRAY_SIZE);
    double end = get_time();

    printf("Array processing (%d elements):\n", ARRAY_SIZE);
    printf("  Time: %.6f seconds\n", end - start);
    printf("  First 5 results: %d, %d, %d, %d, %d\n",
           output[0], output[1], output[2], output[3], output[4]);

    // Benchmark matrix multiplication
    printf("\n=== Matrix Multiplication Benchmark ===\n");
    static int matrix_a[100][100];
    static int matrix_b[100][100];
    static int matrix_result[100][100];

    // Initialize matrices
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            matrix_a[i][j] = rand() % 10;
            matrix_b[i][j] = rand() % 10;
        }
    }

    start = get_time();
    matrix_multiply(matrix_a, matrix_b, matrix_result);
    end = get_time();

    printf("Matrix multiplication (100x100):\n");
    printf("  Time: %.6f seconds\n", end - start);
    printf("  Sample result [0][0]: %d\n", matrix_result[0][0]);

    printf("\n=== Optimization Tips ===\n");
    printf("1. Use appropriate data structures\n");
    printf("2. Minimize memory allocations\n");
    printf("3. Consider algorithmic complexity first\n");
    printf("4. Use compiler optimizations\n");
    printf("5. Profile before optimizing\n");
    printf("6. Consider cache locality\n");
    printf("7. Use vectorization when possible\n");
    printf("8. Parallelize independent operations\n");

    free(primes);
    free(input);
    free(output);

    return 0;
}