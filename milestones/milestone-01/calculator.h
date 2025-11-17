#ifndef CALCULATOR_H
#define CALCULATOR_H

// Basic operations
float add(float a, float b);
float subtract(float a, float b);
float multiply(float a, float b);
int divide(float a, float b, float *result);

// Advanced operations
float power(float base, float exponent);
int square_root(float number, float *result);
long factorial(int number);

// Number theory operations
int gcd(int a, int b);
int lcm(int a, int b);
int is_prime(int number);

// Unit conversions
float celsius_to_fahrenheit(float celsius);
float fahrenheit_to_celsius(float fahrenheit);
float inches_to_cm(float inches);
float pounds_to_kg(float pounds);

// Memory operations
void store_memory(float value);
float recall_memory(void);
void clear_memory(void);

// Input validation functions
int get_float_input(float *value, const char *prompt);
int get_int_input(int *value, const char *prompt);
void clear_input_buffer(void);

// Menu display functions
void display_main_menu(void);
void display_basic_ops_menu(void);
void display_advanced_ops_menu(void);
void display_conversion_menu(void);

#endif