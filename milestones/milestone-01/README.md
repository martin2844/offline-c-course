# Milestone 1: Calculator Project

**🎯 Apply Chapters 1-4: Functions, Control Flow, Variables, and Basic I/O**

## Project Overview

Create a comprehensive command-line calculator that demonstrates all the concepts you've learned so far:
- Variables and data types
- Control flow (if/else, switch, loops)
- Functions and modular programming
- Input/output and user interaction
- Error handling and validation

## Learning Objectives

After completing this project, you will have:
- ✅ Built a complete, functional application
- ✅ Applied modular programming principles
- ✅ Implemented robust input validation
- ✅ Created a user-friendly interface
- ✅ Practiced debugging and testing

## Project Requirements

### Core Features
1. **Basic Operations**: Addition, Subtraction, Multiplication, Division
2. **Advanced Operations**: Power, Square Root, Factorial
3. **Number Theory**: GCD, LCM, Prime checking
4. **Memory Functions**: Store and recall results
5. **Unit Conversion**: Temperature, length conversions

### Technical Requirements
- **Modular Design**: Separate functions for each operation
- **Error Handling**: Validate all user inputs
- **User Interface**: Clean, menu-driven interface
- **Documentation**: Function comments and user instructions
- **Testing**: Test all major functions

## Implementation Guide

### Step 1: Project Structure
Create these files:
```
calculator/
├── main.c              # Main program and menu
├── calculator.h        # Function prototypes
├── basic_ops.c         # Basic operations
├── advanced_ops.c      # Advanced operations
├── number_theory.c     # Number theory functions
├── unit_conversion.c   # Conversion functions
├── memory_ops.c        # Memory store/recall
└── utils.c            # Utility functions
```

### Step 2: Design the Calculator Functions

#### Basic Operations (basic_ops.c)
```c
float add(float a, float b);
float subtract(float a, float b);
float multiply(float a, float b);
int divide(float a, float b, float *result);
```

#### Advanced Operations (advanced_ops.c)
```c
float power(float base, float exponent);
int square_root(float number, float *result);
long factorial(int number);
```

#### Number Theory (number_theory.c)
```c
int gcd(int a, int b);
int lcm(int a, int b);
int is_prime(int number);
```

#### Unit Conversions (unit_conversion.c)
```c
float celsius_to_fahrenheit(float celsius);
float inches_to_cm(float inches);
float pounds_to_kg(float pounds);
```

#### Memory Operations (memory_ops.c)
```c
void store_memory(float value);
float recall_memory(void);
void clear_memory(void);
```

### Step 3: Main Menu Structure
```
Advanced Calculator Menu
========================
1. Basic Operations (+, -, *, /)
2. Advanced Operations (^, √, !)
3. Number Theory (GCD, LCM, Prime)
4. Unit Conversions
5. Memory Functions
6. History
0. Exit

Enter your choice:
```

### Step 4: Input Validation
- Validate numeric input
- Handle division by zero
- Check for valid menu choices
- Handle buffer overflow in string input

## Sample Implementation Approach

### Calculator Header (calculator.h)
```c
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

// Input validation
int get_float_input(float *value, const char *prompt);
int get_int_input(int *value, const char *prompt);

#endif
```

### Main Program Structure
```c
int main() {
    int choice;

    printf("Welcome to Advanced Calculator!\n");

    do {
        display_main_menu();
        if (get_int_input(&choice, "Enter your choice: ")) {
            process_menu_choice(choice);
        } else {
            printf("Invalid input. Please try again.\n");
        }
    } while (choice != 0);

    printf("Thank you for using Advanced Calculator!\n");
    return 0;
}
```

## Development Steps

### Phase 1: Basic Calculator
1. **Set up project structure**
2. **Implement basic operations**
3. **Create simple menu system**
4. **Add input validation**

### Phase 2: Advanced Features
1. **Add advanced operations**
2. **Implement number theory functions**
3. **Create unit conversion module**
4. **Add memory functions**

### Phase 3: Polish and Enhancement
1. **Add history functionality**
2. **Improve user interface**
3. **Add comprehensive error handling**
4. **Test all features**

## Challenges to Solve

### Challenge 1: Robust Input Handling
- Handle non-numeric input gracefully
- Prevent buffer overflows
- Validate range of inputs

### Challenge 2: Mathematical Precision
- Handle floating-point precision issues
- Prevent overflow in factorial calculations
- Handle edge cases (negative numbers, zero)

### Challenge 3: User Experience
- Clear menu navigation
- Helpful error messages
- Intuitive operation flow

## Testing Your Calculator

### Test Cases
1. **Basic Operations**
   - Normal cases: 5 + 3 = 8
   - Edge cases: 0 + 0 = 0
   - Negative numbers: -5 + 3 = -2
   - Division by zero: 5 / 0 = error

2. **Advanced Operations**
   - Power: 2^3 = 8
   - Square root: √16 = 4
   - Factorial: 5! = 120

3. **Input Validation**
   - Non-numeric input
   - Very large numbers
   - Invalid menu choices

### Sample Test Plan
```c
void run_tests() {
    printf("Running calculator tests...\n");

    // Test basic operations
    assert(add(5, 3) == 8.0f);
    assert(subtract(10, 4) == 6.0f);
    assert(multiply(3, 7) == 21.0f);

    // Test advanced operations
    assert(power(2, 3) == 8.0f);
    assert(factorial(5) == 120);

    printf("All tests passed!\n");
}
```

## Bonus Features (Optional)

### Advanced Calculations
- Trigonometric functions (sin, cos, tan)
- Logarithmic functions
- Statistical operations (mean, median, mode)

### Enhanced UI
- Color-coded output
- Progress bars for calculations
- Keyboard shortcuts

### Data Persistence
- Save calculation history to file
- Load previous sessions
- Export results

## Evaluation Criteria

### Functionality (40%)
- All required operations work correctly
- Proper error handling
- Input validation

### Code Quality (30%)
- Modular design
- Clear function organization
- Good naming conventions
- Appropriate comments

### User Experience (20%)
- Clean interface
- Clear instructions
- Helpful error messages
- Intuitive navigation

### Testing (10%)
- Comprehensive test coverage
- Edge case handling
- Error scenarios

## Submission Checklist

- [ ] All basic operations implemented
- [ ] Advanced operations working
- [ ] Input validation complete
- [ ] Error handling robust
- [ ] User interface clear
- [ ] Code well-commented
- [ ] Functions properly modularized
- [ ] Test cases passing
- [ ] Project documentation complete

## Next Steps

After completing this calculator:
1. **Review your code** for improvements
2. **Add extra features** if you're interested
3. **Move to Chapter 5** to learn about arrays and strings
4. **Start thinking about Milestone 2** (Contact Manager)

## Troubleshooting

### Common Issues
- **Compilation errors**: Check function prototypes and includes
- **Input bugs**: Verify input validation logic
- **Math errors**: Test edge cases and precision
- **Memory issues**: Check for proper variable scope

### Debugging Tips
- Use printf statements to trace execution
- Test functions individually
- Check return values carefully
- Test with various input types

---

**🎯 Ready to build your first complete C application?**

This calculator project will solidify your understanding of all concepts from Chapters 1-4 and prepare you for the more advanced topics ahead!

Good luck, and happy coding! 🚀