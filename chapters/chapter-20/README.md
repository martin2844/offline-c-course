# Chapter 20: Code Testing and Quality Assurance

## 🧪 Introduction to Testing and Quality Assurance

Testing and quality assurance are essential skills for professional C programming. This chapter covers comprehensive testing strategies that work completely offline, ensuring robust and reliable code.

### The Quality Crisis in Software Development

Software quality is more important than ever. A single bug can cost millions of dollars, compromise security, or even endanger lives. In C programming, where manual memory management and direct hardware access create additional risks, comprehensive testing isn't optional—it's essential.

**The Cost of Poor Quality:**
- **Therac-25 (1985)**: Radiation therapy machine killed patients due to software bugs
- **Ariane 5 (1996)**: $370 million rocket explosion due to software error
- **Knight Capital (2012)**: $440 million lost in 45 minutes due to trading bug
- **Heartbleed (2014)**: Estimated $500 million global impact
- **Toyota Recall (2009-2011)**: Unintended acceleration issues

**Why C Testing is Critical:**
- **Memory Safety**: Buffer overflows, use-after-free, leaks
- **Pointer Issues**: Null dereferences, invalid arithmetic
- **Resource Management**: File handles, memory, network sockets
- **Undefined Behavior**: Compiler can optimize in unexpected ways
- **Platform Differences**: Behavior varies across systems

### The Testing Mindset

Professional testing isn't about finding bugs—it's about preventing them:

**Testing Philosophy:**
1. **Test Early**: Catch issues when they're cheapest to fix
2. **Test Often**: Continuous validation throughout development
3. **Test Everything**: Not just the happy path, but edge cases and failures
4. **Test Automatically**: Manual testing doesn't scale
5. **Test Systematically**: Structured approach, not random attempts

**The Testing Pyramid:**
```
E2E Tests (10%)
    ▲
Integration Tests (20%)
    ▲
Unit Tests (70%)
```

**Why This Balance:**
- **Unit Tests**: Fast, cheap, many, reliable
- **Integration Tests**: Slower, more expensive, fewer
- **E2E Tests**: Slowest, most expensive, fewest

### The Modern Testing Landscape

**Evolution of Testing Practices:**
```
1970s: Manual testing
1980s: Basic unit testing
1990s: Test automation emerges
2000s: Test-driven development (TDD)
2010s: Continuous integration, DevOps
2020s: AI-assisted testing, chaos engineering
```

**Testing Categories:**

**By Scope:**
- **Unit Tests**: Test individual functions/components
- **Integration Tests**: Test component interactions
- **System Tests**: Test complete system behavior
- **Acceptance Tests**: Validate requirements are met

**By Approach:**
- **Black Box**: Test without knowing internal implementation
- **White Box**: Test with knowledge of internal code
- **Gray Box**: Combination of both approaches

**By Timing:**
- **Static Testing**: Code review, static analysis
- **Dynamic Testing**: Runtime testing, execution testing

### Testing in the C Ecosystem

**C-Specific Challenges:**
- **Memory Management**: Manual allocation/deallocation
- **Pointer Complexity**: Arithmetic, casts, void pointers
- **Undefined Behavior**: Implementation-specific behavior
- **Platform Dependencies**: Different behavior across systems
- **Performance Critical**: Tests must not be too slow

**C Testing Advantages:**
- **Fast Execution**: No virtual machine overhead
- **Direct Control**: Can test at hardware level
- **Fine-Grained Control**: Memory, timing, system calls
- **Portability**: Same tests can run on many platforms

**C Testing Tools:**
- **Frameworks**: Unity, Check, CMocka, Google Test (C++)
- **Static Analysis**: Clang Static Analyzer, Coverity, Cppcheck
- **Memory Debugging**: Valgrind, AddressSanitizer
- **Code Coverage**: gcov, lcov
- **Fuzzing**: AFL, libFuzzer

### The Economic Case for Testing

**Cost of Finding Bugs:**
```
Requirements Phase:    $1
Design Phase:          $10
Implementation Phase:  $100
Testing Phase:         $1,000
Post-Release:          $10,000
```

**ROI Example:**
```
Project A (Minimal Testing):
- Development: 3 months
- Bug Fixes: 2 months post-release
- Support: 6 months extra
- Total: 11 months effort

Project B (Comprehensive Testing):
- Development: 4 months (including testing)
- Bug Fixes: 0.5 months post-release
- Support: 3 months normal
- Total: 7.5 months effort

Savings: 3.5 months (32% reduction in total effort)
```

**Hidden Benefits:**
- **Developer Confidence**: Faster feature development
- **Customer Satisfaction**: Fewer bugs in production
- **Team Morale**: Less time spent on emergency fixes
- **Knowledge Transfer**: Tests serve as documentation
- **Refactoring Safety**: Changes can be made with confidence

### Quality Assurance vs. Quality Control

**Quality Assurance (QA):**
- **Proactive**: Preventing defects
- **Process-focused**: Improving development processes
- **Long-term**: Sustainable quality practices
- **Team-wide**: Everyone involved in quality

**Quality Control (QC):**
- **Reactive**: Detecting defects
- **Product-focused**: Testing the actual product
- **Short-term**: Specific quality checks
- **Specialized**: Often dedicated testing team

**Modern Approach:**
Both are essential - you need both prevention and detection.

### Test-Driven Development (TDD)

**The TDD Cycle:**
```
1. Red: Write a failing test
2. Green: Write minimal code to pass
3. Refactor: Improve code while keeping test green
```

**Benefits:**
- **Design**: Tests drive good design
- **Documentation**: Tests serve as living documentation
- **Regression**: Prevents old bugs from reappearing
- **Confidence**: Refactor safely
- **Focus**: Only implement what's needed

**TDD in C:**
- More challenging due to memory management
- Mocking functions requires careful design
- Static linking affects test isolation
- Setup/teardown is more complex

### Continuous Integration (Offline)

**Traditional CI:**
- Automated builds on every commit
- Automated testing
- Automated deployment
- Cloud-based infrastructure

**Offline CI:**
- Local build scripts
- Automated test running
- Pre-commit hooks
- Local quality gates

**Benefits of Offline CI:**
- **No Dependencies**: Works without internet
- **Fast Feedback**: Immediate results
- **Privacy**: Code stays local
- **Cost**: No cloud infrastructure costs

### Testing Anti-Patterns

**Common Mistakes:**
- **Testing Implementation**: Testing how, not what
- **Mocking Too Much**: Tests don't verify real behavior
- **Brittle Tests**: Break with unrelated changes
- **Test Pollution**: Tests affect each other
- **Coverage Obsession**: High coverage, low value

**Good Practices:**
- **Test Behavior**: Verify external behavior, not implementation
- **Clear Intent**: Tests should explain what they're testing
- **Independent**: Tests should not depend on each other
- **Deterministic**: Same result every time
- **Fast**: Tests should run quickly

### The Psychology of Testing

**Why Developers Avoid Testing:**
- **Perceived Extra Work**: "I need to ship now"
- **Fear of Failure**: Tests will reveal problems
- **Lack of Training**: Don't know how to test effectively
- **Time Pressure**: Deadlines create shortcuts
- **Tooling Complexity**: Testing frameworks can be complex

**Overcoming Resistance:**
- **Start Small**: Begin with simple, valuable tests
- **Show Benefits**: Demonstrate how testing saves time
- **Provide Training**: Teach effective testing techniques
- **Lead by Example**: Management should test too
- **Make it Easy**: Simple tools and processes

### Learning Objectives
- Master testing methodologies and frameworks
- Learn to write effective unit tests and integration tests
- Understand test-driven development (TDD)
- Implement continuous integration offline
- Develop quality assurance practices

This foundation prepares you to understand the practical testing techniques that follow, where you'll learn to build robust, reliable C code through comprehensive testing strategies that work completely offline.

---

## 20.1 Testing Fundamentals

### Understanding Test Types
```c
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// Simple assertion framework
typedef struct {
    int tests_run;
    int tests_passed;
    int tests_failed;
} TestRunner;

void test_init(TestRunner *runner) {
    runner->tests_run = 0;
    runner->tests_passed = 0;
    runner->tests_failed = 0;
}

void test_assert(TestRunner *runner, bool condition, const char *message) {
    runner->tests_run++;
    if (condition) {
        runner->tests_passed++;
        printf("✓ PASS: %s\n", message);
    } else {
        runner->tests_failed++;
        printf("✗ FAIL: %s\n", message);
    }
}

void test_print_summary(TestRunner *runner) {
    printf("\n=== Test Summary ===\n");
    printf("Tests run: %d\n", runner->tests_run);
    printf("Tests passed: %d\n", runner->tests_passed);
    printf("Tests failed: %d\n", runner->tests_failed);
    printf("Success rate: %.1f%%\n",
           (float)runner->tests_passed / runner->tests_run * 100);
}

// Example function to test
int add(int a, int b) {
    return a + b;
}

int divide(int a, int b) {
    if (b == 0) return 0;  // Simple error handling
    return a / b;
}

bool is_even(int n) {
    return n % 2 == 0;
}

// Unit tests
void test_math_functions() {
    TestRunner runner;
    test_init(&runner);

    printf("=== Testing Math Functions ===\n");

    // Test addition
    test_assert(&runner, add(2, 3) == 5, "add(2, 3) == 5");
    test_assert(&runner, add(-1, 1) == 0, "add(-1, 1) == 0");
    test_assert(&runner, add(0, 0) == 0, "add(0, 0) == 0");

    // Test division
    test_assert(&runner, divide(10, 2) == 5, "divide(10, 2) == 5");
    test_assert(&runner, divide(-6, 3) == -2, "divide(-6, 3) == -2");
    test_assert(&runner, divide(5, 2) == 2, "divide(5, 2) == 2");  // Integer division

    // Test even/odd
    test_assert(&runner, is_even(2), "is_even(2) == true");
    test_assert(&runner, !is_even(3), "is_even(3) == false");
    test_assert(&runner, is_even(0), "is_even(0) == true");
    test_assert(&runner, is_even(-4), "is_even(-4) == true");

    test_print_summary(&runner);
}
```

### Custom Test Framework
```c
#include <stdlib.h>
#include <time.h>

// Enhanced test framework with timing
typedef struct {
    const char *name;
    void (*test_func)(TestRunner*);
    double execution_time;
} TestCase;

typedef struct {
    TestCase *tests;
    int test_count;
    TestRunner runner;
    clock_t start_time;
} TestSuite;

TestSuite* test_suite_create() {
    TestSuite *suite = malloc(sizeof(TestSuite));
    suite->tests = malloc(100 * sizeof(TestCase));  // Support up to 100 tests
    suite->test_count = 0;
    test_init(&suite->runner);
    return suite;
}

void test_suite_add_test(TestSuite *suite, const char *name, void (*test_func)(TestRunner*)) {
    if (suite->test_count < 100) {
        suite->tests[suite->test_count].name = name;
        suite->tests[suite->test_count].test_func = test_func;
        suite->test_count++;
    }
}

void test_suite_run_test(TestSuite *suite, int test_index) {
    printf("\n=== Running: %s ===\n", suite->tests[test_index].name);

    TestRunner test_runner;
    test_init(&test_runner);

    clock_t start = clock();
    suite->tests[test_index].test_func(&test_runner);
    clock_t end = clock();

    suite->tests[test_index].execution_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Execution time: %.3f seconds\n", suite->tests[test_index].execution_time);

    // Update overall runner
    suite->runner.tests_run += test_runner.tests_run;
    suite->runner.tests_passed += test_runner.tests_passed;
    suite->runner.tests_failed += test_runner.tests_failed;
}

void test_suite_run_all(TestSuite *suite) {
    printf("=== Starting Test Suite ===\n");
    suite->start_time = clock();

    for (int i = 0; i < suite->test_count; i++) {
        test_suite_run_test(suite, i);
    }

    clock_t total_end = clock();
    double total_time = ((double)(total_end - suite->start_time)) / CLOCKS_PER_SEC;

    printf("\n=== Test Suite Summary ===\n");
    test_print_summary(&suite->runner);
    printf("Total execution time: %.3f seconds\n", total_time);

    // Print slowest tests
    printf("\n=== Slowest Tests ===\n");
    for (int i = 0; i < suite->test_count; i++) {
        printf("%-30s: %.3f seconds\n", suite->tests[i].name, suite->tests[i].execution_time);
    }
}

void test_suite_destroy(TestSuite *suite) {
    free(suite->tests);
    free(suite);
}
```

---

## 20.2 Unit Testing

### String Utilities Testing
```c
#include <string.h>
#include <ctype.h>

// Functions to test
int string_length(const char *str) {
    if (str == NULL) return 0;
    int length = 0;
    while (str[length] != '\0') length++;
    return length;
}

char* string_copy(char *dest, const char *src, size_t dest_size) {
    if (dest == NULL || src == NULL || dest_size == 0) return NULL;

    size_t i = 0;
    while (i < dest_size - 1 && src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}

bool string_equals(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) return str1 == str2;

    while (*str1 && *str2 && *str1 == *str2) {
        str1++;
        str2++;
    }
    return *str1 == *str2;
}

// Unit tests for string functions
void test_string_functions(TestRunner *runner) {
    // Test string_length
    test_assert(runner, string_length("") == 0, "string_length(\"\") == 0");
    test_assert(runner, string_length("hello") == 5, "string_length(\"hello\") == 5");
    test_assert(runner, string_length(NULL) == 0, "string_length(NULL) == 0");

    // Test string_copy
    char dest[100];
    string_copy(dest, "hello world", sizeof(dest));
    test_assert(runner, string_equals(dest, "hello world"), "string_copy basic functionality");

    char small_dest[5];
    string_copy(small_dest, "hello world", sizeof(small_dest));
    test_assert(runner, string_equals(small_dest, "hell"), "string_copy with buffer limit");

    // Test string_equals
    test_assert(runner, string_equals("", ""), "string_equals empty strings");
    test_assert(runner, string_equals("hello", "hello"), "string_equals same strings");
    test_assert(runner, !string_equals("hello", "world"), "string_equals different strings");
    test_assert(runner, string_equals(NULL, NULL), "string_equals NULL strings");
    test_assert(runner, !string_equals("hello", NULL), "string_equals string vs NULL");
}
```

### Data Structure Testing
```c
#include <stdlib.h>

// Simple array-based stack to test
typedef struct {
    int *data;
    int capacity;
    int size;
} Stack;

Stack* stack_create(int capacity) {
    Stack *stack = malloc(sizeof(Stack));
    if (!stack) return NULL;

    stack->data = malloc(capacity * sizeof(int));
    if (!stack->data) {
        free(stack);
        return NULL;
    }

    stack->capacity = capacity;
    stack->size = 0;
    return stack;
}

bool stack_push(Stack *stack, int value) {
    if (stack == NULL || stack->size >= stack->capacity) return false;

    stack->data[stack->size++] = value;
    return true;
}

bool stack_pop(Stack *stack, int *value) {
    if (stack == NULL || stack->size == 0) return false;

    *value = stack->data[--stack->size];
    return true;
}

bool stack_is_empty(Stack *stack) {
    return stack == NULL || stack->size == 0;
}

int stack_size(Stack *stack) {
    return stack ? stack->size : 0;
}

void stack_destroy(Stack *stack) {
    if (stack) {
        free(stack->data);
        free(stack);
    }
}

// Stack tests
void test_stack(TestRunner *runner) {
    Stack *stack = stack_create(3);
    test_assert(runner, stack != NULL, "stack_create returns non-NULL");
    test_assert(runner, stack_is_empty(stack), "new stack is empty");
    test_assert(runner, stack_size(stack) == 0, "new stack size is 0");

    // Test push
    test_assert(runner, stack_push(stack, 10), "push 10 succeeds");
    test_assert(runner, !stack_is_empty(stack), "stack not empty after push");
    test_assert(runner, stack_size(stack) == 1, "stack size is 1 after push");

    test_assert(runner, stack_push(stack, 20), "push 20 succeeds");
    test_assert(runner, stack_push(stack, 30), "push 30 succeeds");
    test_assert(runner, !stack_push(stack, 40), "push beyond capacity fails");

    // Test pop
    int value;
    test_assert(runner, stack_pop(stack, &value), "pop succeeds");
    test_assert(runner, value == 30, "popped value is correct (LIFO)");
    test_assert(runner, stack_size(stack) == 2, "stack size is 2 after pop");

    test_assert(runner, stack_pop(stack, &value), "second pop succeeds");
    test_assert(runner, value == 20, "second popped value is correct");

    test_assert(runner, stack_pop(stack, &value), "third pop succeeds");
    test_assert(runner, value == 10, "third popped value is correct");
    test_assert(runner, stack_is_empty(stack), "stack is empty after removing all items");

    // Test pop from empty stack
    test_assert(runner, !stack_pop(stack, &value), "pop from empty stack fails");

    stack_destroy(stack);
}
```

---

## 20.3 Integration Testing

### File System Integration Tests
```c
#include <stdio.h>
#include <stdlib.h>

// File operations to test
bool write_data_to_file(const char *filename, const char *data) {
    FILE *file = fopen(filename, "w");
    if (!file) return false;

    bool success = (fprintf(file, "%s", data) > 0);
    fclose(file);
    return success;
}

char* read_data_from_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) return NULL;

    // Get file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (file_size < 0) {
        fclose(file);
        return NULL;
    }

    char *data = malloc(file_size + 1);
    if (!data) {
        fclose(file);
        return NULL;
    }

    size_t bytes_read = fread(data, 1, file_size, file);
    data[bytes_read] = '\0';

    fclose(file);
    return data;
}

bool file_exists(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file) {
        fclose(file);
        return true;
    }
    return false;
}

// Integration tests
void test_file_operations(TestRunner *runner) {
    const char *test_filename = "test_file.txt";
    const char *test_data = "Hello, this is test data!";

    // Clean up any existing test file
    remove(test_filename);

    // Test file doesn't exist initially
    test_assert(runner, !file_exists(test_filename), "test file doesn't exist initially");

    // Test write
    test_assert(runner, write_data_to_file(test_filename, test_data), "write data to file succeeds");
    test_assert(runner, file_exists(test_filename), "file exists after write");

    // Test read
    char *read_data = read_data_from_file(test_filename);
    test_assert(runner, read_data != NULL, "read data from file succeeds");
    test_assert(runner, string_equals(read_data, test_data), "read data matches written data");

    if (read_data) free(read_data);

    // Test write with empty data
    test_assert(runner, write_data_to_file(test_filename, ""), "write empty data succeeds");
    read_data = read_data_from_file(test_filename);
    test_assert(runner, read_data != NULL, "read empty data succeeds");
    test_assert(runner, string_equals(read_data, ""), "read empty data matches");

    if (read_data) free(read_data);

    // Test read from non-existent file
    remove(test_filename);
    read_data = read_data_from_file(test_filename);
    test_assert(runner, read_data == NULL, "read from non-existent file returns NULL");

    // Test write to invalid path (should fail gracefully)
    test_assert(runner, !write_data_to_file("/invalid/path/file.txt", test_data),
                "write to invalid path fails gracefully");

    // Clean up
    remove(test_filename);
}
```

### Memory Management Integration Tests
```c
// Memory pool for testing
typedef struct MemoryPool {
    char *pool;
    size_t size;
    size_t used;
    struct MemoryPool *next;
} MemoryPool;

MemoryPool* memory_pool_create(size_t size) {
    MemoryPool *pool = malloc(sizeof(MemoryPool));
    if (!pool) return NULL;

    pool->pool = malloc(size);
    if (!pool->pool) {
        free(pool);
        return NULL;
    }

    pool->size = size;
    pool->used = 0;
    pool->next = NULL;
    return pool;
}

void* memory_pool_alloc(MemoryPool *pool, size_t size) {
    if (!pool || pool->used + size > pool->size) return NULL;

    void *ptr = pool->pool + pool->used;
    pool->used += size;
    return ptr;
}

void memory_pool_reset(MemoryPool *pool) {
    if (pool) pool->used = 0;
}

void memory_pool_destroy(MemoryPool *pool) {
    while (pool) {
        MemoryPool *next = pool->next;
        free(pool->pool);
        free(pool);
        pool = next;
    }
}

// Memory management tests
void test_memory_management(TestRunner *runner) {
    MemoryPool *pool = memory_pool_create(1024);
    test_assert(runner, pool != NULL, "memory pool created successfully");
    test_assert(runner, pool->size == 1024, "memory pool has correct size");
    test_assert(runner, pool->used == 0, "memory pool starts unused");

    // Test allocations
    int *numbers = (int*)memory_pool_alloc(pool, 10 * sizeof(int));
    test_assert(runner, numbers != NULL, "memory pool allocation succeeds");
    test_assert(runner, pool->used == 10 * sizeof(int), "pool usage updated correctly");

    // Test writing to allocated memory
    for (int i = 0; i < 10; i++) {
        numbers[i] = i * i;
    }

    bool data_correct = true;
    for (int i = 0; i < 10; i++) {
        if (numbers[i] != i * i) {
            data_correct = false;
            break;
        }
    }
    test_assert(runner, data_correct, "allocated memory contains correct data");

    // Test pool reset
    memory_pool_reset(pool);
    test_assert(runner, pool->used == 0, "memory pool reset clears usage");

    // Test allocation after reset
    char *text = (char*)memory_pool_alloc(pool, 100);
    test_assert(runner, text != NULL, "allocation after reset succeeds");

    // Test allocation failure when pool is full
    char *large = (char*)memory_pool_alloc(pool, pool->size);
    test_assert(runner, large == NULL, "allocation beyond pool size fails");

    memory_pool_destroy(pool);
}
```

---

## 20.4 Test-Driven Development (TDD)

### TDD Workflow Example
```c
// TDD Example: Calculator with history

// Step 1: Write failing test first
void test_calculator_basic_operations(TestRunner *runner) {
    // These tests will initially fail
    test_assert(runner, calculator_add(2, 3) == 5, "calculator_add(2, 3) == 5");
    test_assert(runner, calculator_subtract(10, 4) == 6, "calculator_subtract(10, 4) == 6");
    test_assert(runner, calculator_multiply(3, 4) == 12, "calculator_multiply(3, 4) == 12");
}

// Step 2: Implement minimal code to make tests pass
typedef struct {
    double result;
    double *history;
    int history_size;
    int history_capacity;
} Calculator;

Calculator* calculator_create() {
    Calculator *calc = malloc(sizeof(Calculator));
    if (!calc) return NULL;

    calc->result = 0;
    calc->history = malloc(10 * sizeof(double));
    calc->history_size = 0;
    calc->history_capacity = 10;

    return calc;
}

double calculator_add(Calculator *calc, double a, double b) {
    calc->result = a + b;

    // Add to history
    if (calc->history_size < calc->history_capacity) {
        calc->history[calc->history_size++] = calc->result;
    }

    return calc->result;
}

double calculator_subtract(Calculator *calc, double a, double b) {
    calc->result = a - b;

    if (calc->history_size < calc->history_capacity) {
        calc->history[calc->history_size++] = calc->result;
    }

    return calc->result;
}

double calculator_multiply(Calculator *calc, double a, double b) {
    calc->result = a * b;

    if (calc->history_size < calc->history_capacity) {
        calc->history[calc->history_size++] = calc->result;
    }

    return calc->result;
}

double calculator_get_result(Calculator *calc) {
    return calc ? calc->result : 0;
}

// Step 3: Add more tests (refactor cycle)
void test_calculator_history(TestRunner *runner) {
    Calculator *calc = calculator_create();

    calculator_add(calc, 2, 3);  // 5
    calculator_subtract(calc, 10, 4);  // 6
    calculator_multiply(calc, 3, 4);  // 12

    test_assert(runner, calc->history_size == 3, "history contains 3 operations");
    test_assert(runner, calc->history[0] == 5, "first history entry is correct");
    test_assert(runner, calc->history[1] == 6, "second history entry is correct");
    test_assert(runner, calc->history[2] == 12, "third history entry is correct");

    calculator_destroy(calc);
}

void calculator_destroy(Calculator *calc) {
    if (calc) {
        free(calc->history);
        free(calc);
    }
}

// Step 4: Run TDD tests
void run_tdd_example() {
    TestSuite *suite = test_suite_create();

    test_suite_add_test(suite, "Calculator Basic Operations", test_calculator_basic_operations);
    test_suite_add_test(suite, "Calculator History", test_calculator_history);

    test_suite_run_all(suite);
    test_suite_destroy(suite);
}
```

---

## 20.5 Mocking and Fakes

### Simple Mock Framework
```c
// Mock framework for testing
typedef struct {
    const char *function_name;
    void *function_ptr;
    int call_count;
    bool should_fail;
} Mock;

typedef struct {
    Mock *mocks;
    int mock_count;
    int mock_capacity;
} MockManager;

MockManager* mock_manager_create() {
    MockManager *manager = malloc(sizeof(MockManager));
    manager->mocks = malloc(10 * sizeof(Mock));
    manager->mock_count = 0;
    manager->mock_capacity = 10;
    return manager;
}

void mock_add_function(MockManager *manager, const char *name, void *func_ptr) {
    if (manager->mock_count < manager->mock_capacity) {
        manager->mocks[manager->mock_count].function_name = name;
        manager->mocks[manager->mock_count].function_ptr = func_ptr;
        manager->mocks[manager->mock_count].call_count = 0;
        manager->mocks[manager->mock_count].should_fail = false;
        manager->mock_count++;
    }
}

void mock_set_should_fail(MockManager *manager, const char *name, bool should_fail) {
    for (int i = 0; i < manager->mock_count; i++) {
        if (strcmp(manager->mocks[i].function_name, name) == 0) {
            manager->mocks[i].should_fail = should_fail;
            break;
        }
    }
}

int mock_get_call_count(MockManager *manager, const char *name) {
    for (int i = 0; i < manager->mock_count; i++) {
        if (strcmp(manager->mocks[i].function_name, name) == 0) {
            return manager->mocks[i].call_count;
        }
    }
    return 0;
}

// Example: Mock network operations
typedef struct {
    bool connected;
    MockManager *mock_manager;
} MockNetwork;

MockNetwork* mock_network_create(MockManager *manager) {
    MockNetwork *network = malloc(sizeof(MockNetwork));
    network->connected = false;
    network->mock_manager = manager;
    return network;
}

bool mock_network_connect(MockNetwork *network, const char *host) {
    // Record mock call
    for (int i = 0; i < network->mock_manager->mock_count; i++) {
        if (strcmp(network->mock_manager->mocks[i].function_name, "connect") == 0) {
            network->mock_manager->mocks[i].call_count++;

            if (network->mock_manager->mocks[i].should_fail) {
                return false;
            }
            break;
        }
    }

    network->connected = true;
    return true;
}

bool mock_network_send(MockNetwork *network, const char *data) {
    if (!network->connected) return false;

    // Record mock call
    for (int i = 0; i < network->mock_manager->mock_count; i++) {
        if (strcmp(network->mock_manager->mocks[i].function_name, "send") == 0) {
            network->mock_manager->mocks[i].call_count++;

            if (network->mock_manager->mocks[i].should_fail) {
                return false;
            }
            break;
        }
    }

    return true;
}

// Test with mocks
void test_network_operations_with_mocks(TestRunner *runner) {
    MockManager *manager = mock_manager_create();

    // We don't need actual function pointers for this example
    mock_add_function(manager, "connect", NULL);
    mock_add_function(manager, "send", NULL);

    MockNetwork *network = mock_network_create(manager);

    // Test successful connection
    test_assert(runner, mock_network_connect(network, "example.com"),
                "network connect succeeds");
    test_assert(runner, mock_network_send(network, "Hello World"),
                "network send succeeds");

    test_assert(runner, mock_get_call_count(manager, "connect") == 1,
                "connect was called once");
    test_assert(runner, mock_get_call_count(manager, "send") == 1,
                "send was called once");

    // Test failed connection
    mock_set_should_fail(manager, "connect", true);
    test_assert(runner, !mock_network_connect(network, "failed.com"),
                "network connect fails when mocked to fail");

    test_assert(runner, mock_get_call_count(manager, "connect") == 2,
                "connect was called twice");

    free(network);
    free(manager->mocks);
    free(manager);
}
```

---

## 20.6 Performance Testing

### Benchmark Framework
```c
#include <time.h>

typedef struct {
    const char *name;
    void (*function)(void);
    double avg_time;
    double min_time;
    double max_time;
    int iterations;
} Benchmark;

typedef struct {
    Benchmark *benchmarks;
    int benchmark_count;
    int benchmark_capacity;
} BenchmarkSuite;

BenchmarkSuite* benchmark_suite_create() {
    BenchmarkSuite *suite = malloc(sizeof(BenchmarkSuite));
    suite->benchmarks = malloc(50 * sizeof(Benchmark));
    suite->benchmark_count = 0;
    suite->benchmark_capacity = 50;
    return suite;
}

void benchmark_suite_add(BenchmarkSuite *suite, const char *name,
                        void (*function)(void), int iterations) {
    if (suite->benchmark_count < suite->benchmark_capacity) {
        suite->benchmarks[suite->benchmark_count].name = name;
        suite->benchmarks[suite->benchmark_count].function = function;
        suite->benchmarks[suite->benchmark_count].iterations = iterations;
        suite->benchmark_count++;
    }
}

void benchmark_run(Benchmark *bench) {
    double total_time = 0;
    bench->min_time = INFINITY;
    bench->max_time = 0;

    for (int i = 0; i < bench->iterations; i++) {
        clock_t start = clock();
        bench->function();
        clock_t end = clock();

        double elapsed = ((double)(end - start)) / CLOCKS_PER_SEC;
        total_time += elapsed;

        if (elapsed < bench->min_time) bench->min_time = elapsed;
        if (elapsed > bench->max_time) bench->max_time = elapsed;
    }

    bench->avg_time = total_time / bench->iterations;
}

void benchmark_suite_run_all(BenchmarkSuite *suite) {
    printf("=== Running Benchmarks ===\n");

    for (int i = 0; i < suite->benchmark_count; i++) {
        benchmark_run(&suite->benchmarks[i]);

        printf("\n%s (%d iterations):\n", suite->benchmarks[i].name,
               suite->benchmarks[i].iterations);
        printf("  Average: %.6f seconds\n", suite->benchmarks[i].avg_time);
        printf("  Min:     %.6f seconds\n", suite->benchmarks[i].min_time);
        printf("  Max:     %.6f seconds\n", suite->benchmarks[i].max_time);
    }

    // Find fastest and slowest
    if (suite->benchmark_count > 0) {
        int fastest_idx = 0, slowest_idx = 0;

        for (int i = 1; i < suite->benchmark_count; i++) {
            if (suite->benchmarks[i].avg_time < suite->benchmarks[fastest_idx].avg_time) {
                fastest_idx = i;
            }
            if (suite->benchmarks[i].avg_time > suite->benchmarks[slowest_idx].avg_time) {
                slowest_idx = i;
            }
        }

        printf("\n=== Performance Summary ===\n");
        printf("Fastest: %s (%.6f seconds)\n",
               suite->benchmarks[fastest_idx].name,
               suite->benchmarks[fastest_idx].avg_time);
        printf("Slowest: %s (%.6f seconds)\n",
               suite->benchmarks[slowest_idx].name,
               suite->benchmarks[slowest_idx].avg_time);
    }
}

// Example benchmark functions
void benchmark_string_copy() {
    char dest[1000];
    const char *src = "This is a test string for benchmarking purposes.";
    for (int i = 0; i < 1000; i++) {
        string_copy(dest, src, sizeof(dest));
    }
}

void benchmark_string_length() {
    const char *long_string = "This is a much longer string that takes more time to process. " \
                             "We repeat it multiple times to make the benchmark more meaningful. " \
                             "This is a much longer string that takes more time to process.";

    for (int i = 0; i < 10000; i++) {
        string_length(long_string);
    }
}

void benchmark_calculator_operations() {
    Calculator *calc = calculator_create();

    for (int i = 0; i < 100000; i++) {
        calculator_add(calc, i, i+1);
        calculator_subtract(calc, i+100, i);
        calculator_multiply(calc, i, 2);
    }

    calculator_destroy(calc);
}

// Run performance tests
void run_performance_tests() {
    BenchmarkSuite *suite = benchmark_suite_create();

    benchmark_suite_add(suite, "String Copy", benchmark_string_copy, 100);
    benchmark_suite_add(suite, "String Length", benchmark_string_length, 100);
    benchmark_suite_add(suite, "Calculator Operations", benchmark_calculator_operations, 50);

    benchmark_suite_run_all(suite);

    free(suite->benchmarks);
    free(suite);
}
```

---

## 20.7 Continuous Integration (Offline)

### Local CI Script
```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

typedef struct {
    int total_tests;
    int passed_tests;
    int failed_tests;
    double total_time;
    bool compilation_success;
} CIResult;

bool compile_project() {
    printf("=== Compiling Project ===\n");

    // Use system to compile (in real implementation)
    int result = system("gcc -Wall -Wextra -g test_main.c calculator.c -o test_program");

    bool success = (result == 0);
    printf("Compilation: %s\n", success ? "SUCCESS" : "FAILED");

    return success;
}

CIResult run_ci_pipeline() {
    CIResult result = {0};

    clock_t start_time = clock();

    printf("=== Running CI Pipeline ===\n");

    // Step 1: Compilation
    result.compilation_success = compile_project();
    if (!result.compilation_success) {
        printf("CI FAILED: Compilation errors\n");
        return result;
    }

    // Step 2: Run unit tests
    printf("\n=== Running Unit Tests ===\n");
    TestSuite *unit_suite = test_suite_create();

    test_suite_add_test(unit_suite, "String Functions", test_string_functions);
    test_suite_add_test(unit_suite, "Stack Operations", test_stack);
    test_suite_add_test(unit_suite, "Calculator Basic", test_calculator_basic_operations);

    // Save original test counts
    int original_run = unit_suite->runner.tests_run;
    int original_passed = unit_suite->runner.tests_passed;
    int original_failed = unit_suite->runner.tests_failed;

    test_suite_run_all(unit_suite);

    result.total_tests += unit_suite->runner.tests_run;
    result.passed_tests += unit_suite->runner.tests_passed;
    result.failed_tests += unit_suite->runner.tests_failed;

    test_suite_destroy(unit_suite);

    // Step 3: Run integration tests
    printf("\n=== Running Integration Tests ===\n");
    TestSuite *integration_suite = test_suite_create();

    test_suite_add_test(integration_suite, "File Operations", test_file_operations);
    test_suite_add_test(integration_suite, "Memory Management", test_memory_management);
    test_suite_add_test(integration_suite, "Network Mock", test_network_operations_with_mocks);

    test_suite_run_all(integration_suite);

    result.total_tests += integration_suite->runner.tests_run;
    result.passed_tests += integration_suite->runner.tests_passed;
    result.failed_tests += integration_suite->runner.tests_failed;

    test_suite_destroy(integration_suite);

    // Step 4: Performance tests
    printf("\n=== Running Performance Tests ===\n");
    run_performance_tests();

    clock_t end_time = clock();
    result.total_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    // Print CI results
    printf("\n=== CI Pipeline Results ===\n");
    printf("Total tests: %d\n", result.total_tests);
    printf("Passed: %d\n", result.passed_tests);
    printf("Failed: %d\n", result.failed_tests);
    printf("Success rate: %.1f%%\n",
           (float)result.passed_tests / result.total_tests * 100);
    printf("Total time: %.2f seconds\n", result.total_time);

    // Write results to file for record keeping
    FILE *report = fopen("ci_report.txt", "w");
    if (report) {
        fprintf(report, "CI Pipeline Report\n");
        fprintf(report, "===================\n");
        fprintf(report, "Compilation: %s\n", result.compilation_success ? "PASS" : "FAIL");
        fprintf(report, "Total tests: %d\n", result.total_tests);
        fprintf(report, "Passed: %d\n", result.passed_tests);
        fprintf(report, "Failed: %d\n", result.failed_tests);
        fprintf(report, "Success rate: %.1f%%\n",
                (float)result.passed_tests / result.total_tests * 100);
        fprintf(report, "Total time: %.2f seconds\n", result.total_time);
        fclose(report);

        printf("CI report saved to ci_report.txt\n");
    }

    return result;
}
```

---

## 🎯 Chapter Summary

### Key Concepts Covered
1. **Testing Fundamentals**: Unit tests, integration tests, test frameworks
2. **Test-Driven Development**: Red-Green-Refactor cycle
3. **Mocking and Fakes**: Isolating components for testing
4. **Performance Testing**: Benchmarking and profiling
5. **Continuous Integration**: Automated testing pipelines
6. **Quality Assurance**: Code quality metrics and standards

### Skills Developed
- Writing comprehensive test suites
- Implementing custom testing frameworks
- Understanding TDD methodology
- Creating mock objects for isolated testing
- Measuring and optimizing performance
- Setting up offline CI pipelines

### Applications
- Software development workflows
- Quality assurance processes
- Performance optimization
- Code reliability improvements
- Automated testing systems

---

## 💻 Exercises

### Exercise 1: Complete Test Framework
Extend the test framework with setup/teardown functions, parameterized tests, and test categories.

### Exercise 2: Mock Network Library
Create a comprehensive mock network library for testing applications that depend on external services.

### Exercise 3: Performance Profiler
Build a performance profiler that tracks function execution times and memory usage.

### Exercise 4: TDD Project
Start a new project using pure TDD methodology, writing tests before implementation.

### Exercise 5: Coverage Tool
Implement a code coverage tool that tracks which lines of code are executed during tests.

---

## 📚 Further Reading

- "Test-Driven Development: By Example" by Kent Beck
- "Working Effectively with Legacy Code" by Michael Feathers
- "xUnit Test Patterns" by Gerard Meszaros
- "The Clean Coder" by Robert C. Martin (testing chapters)
- "Code Complete" by Steve McConnell (quality assurance chapters)