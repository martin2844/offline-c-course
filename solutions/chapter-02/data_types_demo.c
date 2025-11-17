#include <stdio.h>

int main() {
    // Integer types
    int age = 25;
    short small_num = 100;
    long large_num = 1000000L;
    long long very_large = 9000000000LL;

    // Unsigned integers
    unsigned int positive = 42;

    // Floating-point types
    float price = 19.99f;
    double precise = 3.1415926535;

    // Character type
    char grade = 'A';

    printf("Data Types Demo:\n");
    printf("Age (int): %d\n", age);
    printf("Small number (short): %d\n", small_num);
    printf("Large number (long): %ld\n", large_num);
    printf("Very large (long long): %lld\n", very_large);
    printf("Positive (unsigned int): %u\n", positive);
    printf("Price (float): %.2f\n", price);
    printf("Precise (double): %.10f\n", precise);
    printf("Grade (char): %c (ASCII: %d)\n", grade, grade);

    return 0;
}