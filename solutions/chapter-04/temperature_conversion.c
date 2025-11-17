#include <stdio.h>

// Function prototypes
float celsius_to_fahrenheit(float celsius);
float fahrenheit_to_celsius(float fahrenheit);
float celsius_to_kelvin(float celsius);
float kelvin_to_celsius(float kelvin);

int main() {
    float temp;

    printf("Temperature Conversion Utilities\n");
    printf("===============================\n");

    // Test Celsius to Fahrenheit
    temp = 25.0f;
    printf("%.1f°C = %.1f°F\n", temp, celsius_to_fahrenheit(temp));

    // Test Fahrenheit to Celsius
    temp = 77.0f;
    printf("%.1f°F = %.1f°C\n", temp, fahrenheit_to_celsius(temp));

    // Test Celsius to Kelvin
    temp = 25.0f;
    printf("%.1f°C = %.1fK\n", temp, celsius_to_kelvin(temp));

    // Test Kelvin to Celsius
    temp = 298.15f;
    printf("%.1fK = %.1f°C\n", temp, kelvin_to_celsius(temp));

    return 0;
}

// Convert Celsius to Fahrenheit
float celsius_to_fahrenheit(float celsius) {
    return (celsius * 9.0f / 5.0f) + 32.0f;
}

// Convert Fahrenheit to Celsius
float fahrenheit_to_celsius(float fahrenheit) {
    return (fahrenheit - 32.0f) * 5.0f / 9.0f;
}

// Convert Celsius to Kelvin
float celsius_to_kelvin(float celsius) {
    return celsius + 273.15f;
}

// Convert Kelvin to Celsius
float kelvin_to_celsius(float kelvin) {
    return kelvin - 273.15f;
}