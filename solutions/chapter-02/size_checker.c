#include <stdio.h>

int main() {
    printf("Data Type Sizes on This System:\n");
    printf("================================\n");
    printf("char: %zu byte(s)\n", sizeof(char));
    printf("unsigned char: %zu byte(s)\n", sizeof(unsigned char));
    printf("short: %zu byte(s)\n", sizeof(short));
    printf("unsigned short: %zu byte(s)\n", sizeof(unsigned short));
    printf("int: %zu byte(s)\n", sizeof(int));
    printf("unsigned int: %zu byte(s)\n", sizeof(unsigned int));
    printf("long: %zu byte(s)\n", sizeof(long));
    printf("unsigned long: %zu byte(s)\n", sizeof(unsigned long));
    printf("long long: %zu byte(s)\n", sizeof(long long));
    printf("unsigned long long: %zu byte(s)\n", sizeof(unsigned long long));
    printf("float: %zu byte(s)\n", sizeof(float));
    printf("double: %zu byte(s)\n", sizeof(double));
    printf("long double: %zu byte(s)\n", sizeof(long double));

    return 0;
}