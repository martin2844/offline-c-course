#include <stdio.h>

void reverse_array(int arr[], int size);
void print_array(int arr[], int size);

int main() {
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = sizeof(numbers) / sizeof(numbers[0]);

    printf("Original array: ");
    print_array(numbers, size);

    reverse_array(numbers, size);

    printf("Reversed array: ");
    print_array(numbers, size);

    return 0;
}

void reverse_array(int arr[], int size) {
    int start = 0;
    int end = size - 1;

    while (start < end) {
        // Swap elements
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;

        // Move towards center
        start++;
        end--;
    }
}

void print_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}