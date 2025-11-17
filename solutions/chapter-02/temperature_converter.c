#include <stdio.h>

int main() {
    float celsius, fahrenheit;

    printf("Temperature Converter\n");
    printf("=====================\n");
    printf("Enter temperature in Celsius: ");
    scanf("%f", &celsius);

    // Convert Celsius to Fahrenheit: F = (C * 9/5) + 32
    fahrenheit = (celsius * 9.0f / 5.0f) + 32.0f;

    printf("%.1f°C = %.1f°F\n", celsius, fahrenheit);

    // Bonus: Show some common temperatures
    printf("\nCommon temperatures:\n");
    printf("0°C = %.1f°F (Freezing point of water)\n", (0.0f * 9.0f / 5.0f) + 32.0f);
    printf("100°C = %.1f°F (Boiling point of water)\n", (100.0f * 9.0f / 5.0f) + 32.0f);
    printf("37°C = %.1f°F (Normal body temperature)\n", (37.0f * 9.0f / 5.0f) + 32.0f);

    return 0;
}