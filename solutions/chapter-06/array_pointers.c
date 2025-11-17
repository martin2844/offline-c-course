#include <stdio.h>

void print_array(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int calculate_sum(int *arr, int size) {
    int sum = 0;
    int *end = arr + size;

    while (arr < end) {
        sum += *arr;
        arr++;
    }
    return sum;
}

float calculate_average(int *arr, int size) {
    return (float)calculate_sum(arr, size) / size;
}

void reverse_array(int *arr, int size) {
    int *start = arr;
    int *end = arr + size - 1;

    while (start < end) {
        int temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = sizeof(numbers) / sizeof(numbers[0]);

    printf("Array Operations with Pointers\n");
    printf("=============================\n");

    printf("Original array: ");
    print_array(numbers, size);

    printf("Sum: %d\n", calculate_sum(numbers, size));
    printf("Average: %.2f\n", calculate_average(numbers, size));

    reverse_array(numbers, size);
    printf("Reversed array: ");
    print_array(numbers, size);

    printf("\nDemonstrating pointer arithmetic:\n");
    int *ptr = numbers;
    for (int i = 0; i < size; i++) {
        printf("ptr[%d] = %d (address: %p)\n", i, *(ptr + i), (void*)(ptr + i));
    }

    return 0;
}