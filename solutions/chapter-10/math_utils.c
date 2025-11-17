#include "math_utils.h"

int find_max(int numbers[], int count) {
    if (count <= 0) return 0;

    int max = numbers[0];
    for (int i = 1; i < count; i++) {
        if (numbers[i] > max) {
            max = numbers[i];
        }
    }
    return max;
}

int find_min(int numbers[], int count) {
    if (count <= 0) return 0;

    int min = numbers[0];
    for (int i = 1; i < count; i++) {
        if (numbers[i] < min) {
            min = numbers[i];
        }
    }
    return min;
}

float calculate_average(int numbers[], int count) {
    if (count <= 0) return 0.0f;

    int sum = 0;
    for (int i = 0; i < count; i++) {
        sum += numbers[i];
    }
    return (float)sum / count;
}

int gcd(int a, int b) {
    a = a < 0 ? -a : a;
    b = b < 0 ? -b : b;

    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int lcm(int a, int b) {
    if (a == 0 || b == 0) return 0;
    return (a / gcd(a, b)) * b;
}

int is_prime(int n) {
    if (n <= 1) return 0;
    if (n == 2) return 1;
    if (n % 2 == 0) return 0;

    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return 0;
    }
    return 1;
}