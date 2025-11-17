#include <stdio.h>

int main() {
    int choice;
    float num1, num2, result;

    printf("Simple Calculator Menu\n");
    printf("======================\n");

    do {
        printf("\nMenu Options:\n");
        printf("1. Add two numbers\n");
        printf("2. Subtract two numbers\n");
        printf("3. Multiply two numbers\n");
        printf("4. Divide two numbers\n");
        printf("5. Find square of a number\n");
        printf("6. Exit\n");
        printf("Enter your choice (1-6): ");
        scanf("%d", &choice);

        // Input validation
        if (choice < 1 || choice > 6) {
            printf("Invalid choice! Please enter a number between 1 and 6.\n");
            continue;
        }

        if (choice >= 1 && choice <= 4) {
            printf("Enter first number: ");
            scanf("%f", &num1);
            printf("Enter second number: ");
            scanf("%f", &num2);
        } else if (choice == 5) {
            printf("Enter a number: ");
            scanf("%f", &num1);
        }

        switch (choice) {
            case 1:
                result = num1 + num2;
                printf("%.2f + %.2f = %.2f\n", num1, num2, result);
                break;
            case 2:
                result = num1 - num2;
                printf("%.2f - %.2f = %.2f\n", num1, num2, result);
                break;
            case 3:
                result = num1 * num2;
                printf("%.2f * %.2f = %.2f\n", num1, num2, result);
                break;
            case 4:
                if (num2 != 0) {
                    result = num1 / num2;
                    printf("%.2f / %.2f = %.2f\n", num1, num2, result);
                } else {
                    printf("Error: Division by zero is not allowed!\n");
                }
                break;
            case 5:
                result = num1 * num1;
                printf("%.2f squared = %.2f\n", num1, result);
                break;
            case 6:
                printf("Thank you for using the calculator. Goodbye!\n");
                break;
        }

    } while (choice != 6);

    return 0;
}