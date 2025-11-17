#include <stdio.h>

int find_min(int arr[], int size);
int find_max(int arr[], int size);
int calculate_sum(int arr[], int size);
float calculate_average(int arr[], int size);

int main() {
    int numbers[] = {64, 34, 25, 12, 22, 11, 90, 88, 76, 50};
    int size = sizeof(numbers) / sizeof(numbers[0]);

    printf("Array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    printf("Statistics:\n");
    printf("- Minimum: %d\n", find_min(numbers, size));
    printf("- Maximum: %d\n", find_max(numbers, size));
    printf("- Sum: %d\n", calculate_sum(numbers, size));
    printf("- Average: %.2f\n", calculate_average(numbers, size));

    return 0;
}

int find_min(int arr[], int size) {
    int min = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    return min;
}

int find_max(int arr[], int size) {
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

int calculate_sum(int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

float calculate_average(int arr[], int size) {
    return (float)calculate_sum(arr, size) / size;
}