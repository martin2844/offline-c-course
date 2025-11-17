# Chapter 3: Control Flow - FAQ

## if-else Statements

### Q: What's the difference between `=` and `==`?
A: `=` is assignment (stores a value), `==` is comparison (checks equality). Common mistake: `if (x = 5)` should be `if (x == 5)`.

### Q: Why do we use braces `{}` even for single statements?
A: While not required for single statements, braces prevent bugs and improve readability:
```c
// Dangerous - easy to make mistakes
if (condition)
    do_something();
    do_another_thing(); // This always runs!

// Safe - clear intent
if (condition) {
    do_something();
}
```

### Q: What's the difference between `else if` and nested `if`?
A: `else if` creates a chain where only one condition can execute. Nested `if` statements are independent and multiple can execute.

### Q: Can I have multiple `else` statements?
A: No. Each `if` can have at most one `else`, and `else if` chains together. Structure:
```c
if (condition1) {
    // Code
} else if (condition2) {
    // Code
} else if (condition3) {
    // Code
} else {
    // Code
}
```

### Q: What happens if I don't include an `else`?
A: Nothing happens if the condition is false. The program continues execution after the `if` statement.

## Logical Operators

### Q: What's the difference between `&&` and `&`?
A: `&&` is logical AND (boolean operation). `&` is bitwise AND (bit manipulation). Use `&&` for conditions: `if (x > 0 && y > 0)`.

### Q: What's the difference between `||` and `|`?
A: `||` is logical OR. `|` is bitwise OR. Use `||` for conditions: `if (x > 0 || y > 0)`.

### Q: What is "short-circuit evaluation"?
A: The compiler stops evaluating as soon as the result is known:
```c
if (x != 0 && y / x > 2)  // If x is 0, second part isn't evaluated
if (x > 0 || check_condition())  // If x > 0, second part isn't evaluated
```

### Q: What does `!` operator do?
A: `!` is logical NOT (inverts boolean value): `if (!done)` means "if not done".

### Q: Can I combine multiple logical operators?
A: Yes, but use parentheses for clarity:
```c
if ((x > 0 && y < 10) || (z == 0))
```

## Switch Statements

### Q: When should I use `switch` vs `if-else`?
A: Use `switch` when comparing a single variable against multiple constant values. Use `if-else` for complex conditions or range checks.

### Q: Why do I need `break` in `switch` statements?
A: Without `break`, execution "falls through" to the next case. This is intentional in some cases but usually a bug.

### Q: What is "fall-through" in switch statements?
A: When one case intentionally continues to the next without `break`:
```c
switch (grade) {
    case 'A':
    case 'B':
        printf("Good job!\n");
        break;
    case 'C':
        printf("Needs improvement\n");
        break;
}
```

### Q: Can `switch` work with strings?
A: Not directly. `switch` only works with integral types (int, char, enum). For strings, use `if-else` with `strcmp()`.

### Q: What does the `default` case do?
A: It executes when no other case matches. It's like the final `else` in an `if-else` chain.

### Q: Should I always include a `default` case?
A: Generally yes, even if it's just to handle unexpected values. Good for debugging and error handling.

## Loops

### Q: What's the difference between `for`, `while`, and `do-while`?
A:
- `for`: Known number of iterations: `for (int i = 0; i < 10; i++)`
- `while`: Unknown iterations, condition checked first: `while (condition)`
- `do-while`: Unknown iterations, condition checked last (always runs once): `do {} while (condition)`

### Q: When should I use each type of loop?
A:
- Use `for` when you know exactly how many iterations
- Use `while` when iterations depend on a condition
- Use `do-while` when you need the loop body to run at least once

### Q: What is an infinite loop and how do I create one?
A: An infinite loop never terminates. Common forms:
```c
while (1) { ... }           // Most common
for (;;) { ... }             // Alternative syntax
do {} while (1);            // Rare
```

### Q: How do I break out of an infinite loop?
A: Use `break;` or `return;` or call `exit(0);` to exit the program.

### Q: What's the difference between `break` and `continue`?
A:
- `break`: Exit the loop immediately
- `continue`: Skip to next iteration of loop

### Q: Can I use `break` and `continue` in any loop?
A: Yes, both work in `for`, `while`, and `do-while` loops.

### Q: What's the difference between `++i` and `i++`?
A:
- `++i` (pre-increment): Increment first, then use value
- `i++` (post-increment): Use value first, then increment
In `for` loops, it doesn't matter which you use.

## Loop Control

### Q: What does "off-by-one error" mean?
A: Common bug where loop runs one too many or one too few times:
```c
// Wrong - runs 11 times instead of 10
for (int i = 0; i <= 10; i++)

// Correct - runs 10 times
for (int i = 0; i < 10; i++)
```

### Q: How can I avoid off-by-one errors?
A:
- Use `!=` instead of `<` when appropriate: `for (int i = 0; i != 10; i++)`
- Test boundary conditions
- Be explicit about range: "for elements 0 through 9"

### Q: Can I nest loops?
A: Yes, you can nest any combination of loops:
```c
for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 3; j++) {
        // Code runs 15 times (5 * 3)
    }
}
```

### Q: How do I break out of nested loops?
A: Use a flag variable or `goto` (rare):
```c
int done = 0;
for (...) {
    for (...) {
        if (condition) {
            done = 1;
            break;
        }
    }
    if (done) break;
}
```

### Q: What's a "sentinel value"?
A: Special value that signals end of input or loop termination:
```c
int value;
while (1) {
    scanf("%d", &value);
    if (value == -1) break;  // -1 is sentinel value
}
```

## Common Mistakes

### Q: Why does my loop not run when I expect it to?
A: Common causes:
- Condition is initially false: `while (x < 0)` when x starts positive
- Off-by-one error: `for (int i = 0; i <= size; i++)` should be `< size`
- Integer overflow causing unexpected values

### Q: Why does my loop run forever?
A: Common causes:
- Forgot to increment loop counter
- Condition never becomes false
- Using assignment (`=`) instead of comparison (`==`)

### Q: What's wrong with `if (x = 5)`?
A: This assigns 5 to x and always evaluates to true. Use `if (x == 5)`.

### Q: Why does my switch statement always execute the first case?
A: You're probably using `=` instead of `==` in case statements, which isn't allowed.

## Best Practices

### Q: Should I always use braces with if statements?
A: Yes, even for single statements. It prevents bugs and makes code clearer.

### Q: What's the best way to check multiple conditions?
A: Use parentheses to make intent clear:
```c
if ((age >= 18 && age <= 65) || (has_permission))
```

### Q: How should I structure my loops for clarity?
A:
```c
// Good - clear bounds and purpose
for (int i = 0; i < student_count; i++) {
    process_student(students[i]);
}

// Clear condition checking
while (!is_done() && has_more_data()) {
    process_data();
}
```

### Q: What's the best way to handle user input validation?
A: Use loops with input validation:
```c
int age;
do {
    printf("Enter age (0-120): ");
    scanf("%d", &age);
} while (age < 0 || age > 120);
```

## Performance

### Q: Are switch statements faster than if-else chains?
A: Usually yes, especially for many cases. Compilers often optimize `switch` to jump tables.

### Q: Does loop order matter for performance?
A: Sometimes. Accessing memory sequentially is usually faster than random access:
```c
// Faster - sequential access
for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++)
        matrix[i][j] = 0;

// Slower - non-sequential access
for (int j = 0; j < cols; j++)
    for (int i = 0; i < rows; i++)
        matrix[i][j] = 0;
```

### Q: Should I optimize loops manually?
A: Generally no. Modern compilers are very good at loop optimization. Focus on clear, correct code first.

---

## 💡 Pro Tips

1. **Always use braces** with control statements, even for single lines
2. **Prefer `switch` over long `if-else` chains** for readability
3. **Be careful with integer comparisons** in loops
4. **Use meaningful variable names** in loop conditions
5. **Test edge cases**: empty arrays, single elements, boundary values
6. **Use constants** instead of magic numbers in conditions
7. **Consider early returns** to reduce nesting
8. **Use `const`** when variables aren't modified in loops
9. **Be explicit about loop bounds** - `i < n` vs `i <= n-1`
10. **Watch out for integer overflow** in loop conditions