#include "calculator.h"

// Temperature conversion functions
float celsius_to_fahrenheit(float celsius) {
    return (celsius * 9.0f / 5.0f) + 32.0f;
}

float fahrenheit_to_celsius(float fahrenheit) {
    return (fahrenheit - 32.0f) * 5.0f / 9.0f;
}

// Length conversion
float inches_to_cm(float inches) {
    return inches * 2.54f;
}

// Weight conversion
float pounds_to_kg(float pounds) {
    return pounds * 0.453592f;
}