#include <stdio.h>
#include <stdlib.h>

// Bit manipulation functions
int count_set_bits(int num) {
    int count = 0;
    while (num) {
        count += num & 1;
        num >>= 1;
    }
    return count;
}

int reverse_bits(int num) {
    int reversed = 0;
    for (int i = 0; i < 32; i++) {
        reversed = (reversed << 1) | (num & 1);
        num >>= 1;
    }
    return reversed;
}

int find_lowest_set_bit(int num) {
    if (num == 0) return -1;

    int position = 0;
    while ((num & 1) == 0) {
        num >>= 1;
        position++;
    }
    return position;
}

int find_highest_set_bit(int num) {
    if (num == 0) return -1;

    int position = 0;
    while (num != 0) {
        num >>= 1;
        position++;
    }
    return position - 1;
}

int is_power_of_two(int num) {
    return num > 0 && (num & (num - 1)) == 0;
}

int next_power_of_two(int num) {
    if (num <= 1) return 1;

    num--;
    num |= num >> 1;
    num |= num >> 2;
    num |= num >> 4;
    num |= num >> 8;
    num |= num >> 16;
    num++;

    return num;
}

void print_binary(int num, int bits) {
    for (int i = bits - 1; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
    }
}

int main() {
    printf("Bitwise Operations Library\n");
    printf("==========================\n");

    int test_numbers[] = {0, 1, 7, 15, 32, 1023, 65535};
    int num_tests = sizeof(test_numbers) / sizeof(test_numbers[0]);

    for (int i = 0; i < num_tests; i++) {
        int num = test_numbers[i];

        printf("\nNumber: %d\n", num);
        printf("Binary: ");
        print_binary(num, 16);
        printf("\n");
        printf("Set bits: %d\n", count_set_bits(num));
        printf("Lowest set bit: %d\n", find_lowest_set_bit(num));
        printf("Highest set bit: %d\n", find_highest_set_bit(num));
        printf("Is power of two: %s\n", is_power_of_two(num) ? "Yes" : "No");
        printf("Next power of two: %d\n", next_power_of_two(num));
        printf("Reversed bits: %d\n", reverse_bits(num));
    }

    // Interactive demo
    printf("\nInteractive Demo\n");
    printf("==============\n");
    int input;
    printf("Enter a number (or 0 to quit): ");
    scanf("%d", &input);

    while (input != 0) {
        printf("\nAnalysis of %d:\n", input);
        printf("Binary: ");
        print_binary(input, 32);
        printf("\n");
        printf("Set bits: %d\n", count_set_bits(input));
        printf("Lowest set bit: %d\n", find_lowest_set_bit(input));
        printf("Highest set bit: %d\n", find_highest_set_bit(input));
        printf("Is power of two: %s\n", is_power_of_two(input) ? "Yes" : "No");
        printf("Next power of two: %d\n", next_power_of_two(input));

        printf("\nEnter another number (or 0 to quit): ");
        scanf("%d", &input);
    }

    printf("\nGoodbye!\n");
    return 0;
}