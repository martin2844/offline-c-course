// Chapter 14: Build Systems and Tools - GDB Debugging Demonstration
// Solution to Exercise 14.3: Debug a program with memory leaks and logic errors using GDB

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure with intentional bugs for debugging practice
typedef struct Student {
    char* name;
    int id;
    int* grades;
    int num_grades;
    float average;
} Student;

// Function with memory leak
Student* create_student_with_leak(const char* name, int id) {
    Student* student = (Student*)malloc(sizeof(Student));
    if (student == NULL) return NULL;

    student->name = (char*)malloc(strlen(name) + 1);
    strcpy(student->name, name);
    student->id = id;
    student->grades = NULL;
    student->num_grades = 0;
    student->average = 0.0f;

    // BUG: Memory leak if grades allocation fails
    student->grades = (int*)malloc(5 * sizeof(int));
    if (student->grades == NULL) {
        // We forgot to free student->name and student!
        return NULL;
    }

    return student;
}

// Function with off-by-one error (buffer overflow)
void add_grade_buggy(Student* student, int grade) {
    // BUG: Should be < student->num_grades, not <=
    for (int i = 0; i <= student->num_grades; i++) {  // Off-by-one error
        if (i < 5) {  // We allocated only 5 grades
            student->grades[i] = grade;
        }
    }
    student->num_grades++;
}

// Function with logic error in average calculation
float calculate_average_buggy(Student* student) {
    if (student == NULL || student->num_grades == 0) {
        return 0.0f;
    }

    int sum = 0;
    for (int i = 0; i < student->num_grades; i++) {
        sum += student->grades[i];
    }

    // BUG: Dividing by the wrong number
    student->average = (float)sum / (student->num_grades + 1);  // +1 is wrong
    return student->average;
}

// Function with null pointer dereference potential
void print_student_info(Student* student) {
    printf("Student Info:\n");
    printf("  ID: %d\n", student->id);

    // BUG: No check if student->name is NULL
    printf("  Name: %s\n", student->name);

    printf("  Grades: ");
    for (int i = 0; i <= student->num_grades; i++) {  // Same off-by-one error
        printf("%d ", student->grades[i]);
    }
    printf("\n");
    printf("  Average: %.2f\n", student->average);
}

// Fixed version of create_student
Student* create_student_fixed(const char* name, int id) {
    Student* student = (Student*)malloc(sizeof(Student));
    if (student == NULL) return NULL;

    student->name = (char*)malloc(strlen(name) + 1);
    if (student->name == NULL) {
        free(student);
        return NULL;
    }
    strcpy(student->name, name);

    student->grades = (int*)malloc(5 * sizeof(int));
    if (student->grades == NULL) {
        free(student->name);
        free(student);
        return NULL;
    }

    student->id = id;
    student->num_grades = 0;
    student->average = 0.0f;

    return student;
}

// Fixed version of add_grade
void add_grade_fixed(Student* student, int grade) {
    if (student == NULL || student->num_grades >= 5) return;  // Boundary check

    student->grades[student->num_grades] = grade;
    student->num_grades++;
}

// Fixed version of calculate_average
float calculate_average_fixed(Student* student) {
    if (student == NULL || student->num_grades == 0) {
        return 0.0f;
    }

    int sum = 0;
    for (int i = 0; i < student->num_grades; i++) {
        sum += student->grades[i];
    }

    student->average = (float)sum / student->num_grades;  // Correct division
    return student->average;
}

// Fixed version of print_student_info
void print_student_info_fixed(Student* student) {
    if (student == NULL) {
        printf("Student pointer is NULL\n");
        return;
    }

    printf("Student Info:\n");
    printf("  ID: %d\n", student->id);

    if (student->name != NULL) {
        printf("  Name: %s\n", student->name);
    } else {
        printf("  Name: (NULL)\n");
    }

    printf("  Grades: ");
    for (int i = 0; i < student->num_grades; i++) {  // Correct loop bound
        printf("%d ", student->grades[i]);
    }
    printf("\n");
    printf("  Average: %.2f\n", student->average);
}

// Proper cleanup function
void free_student(Student* student) {
    if (student == NULL) return;

    if (student->name != NULL) {
        free(student->name);
    }
    if (student->grades != NULL) {
        free(student->grades);
    }
    free(student);
}

int main() {
    printf("Debugging Demonstration Program\n");
    printf("================================\n");
    printf("This program contains intentional bugs for GDB practice.\n");
    printf("Compile with: gcc -g -o debug_demo debugging_with_gdb.c\n");
    printf("Run with: gdb ./debug_demo\n");
    printf("\nGDB commands to try:\n");
    printf("  break main           - Set breakpoint at main\n");
    printf("  break create_student_with_leak\n");
    printf("  run                  - Start program\n");
    printf("  next                 - Execute next line\n");
    printf("  step                 - Step into function\n");
    printf("  print student        - Print variable\n");
    printf("  print student->name  - Print struct member\n");
    printf("  info locals          - Show local variables\n");
    printf("  backtrace            - Show call stack\n");
    printf("  continue             - Continue execution\n");
    printf("  quit                 - Exit GDB\n\n");

    printf("Starting demonstration...\n\n");

    // Demonstrate buggy version first
    printf("=== BUGGY VERSION ===\n");
    Student* student1 = create_student_with_leak("Alice", 1001);
    if (student1 != NULL) {
        add_grade_buggy(student1, 85);
        add_grade_buggy(student1, 92);
        add_grade_buggy(student1, 78);

        calculate_average_buggy(student1);
        print_student_info(student1);

        // BUG: We forgot to free student1!
    }

    printf("\n=== FIXED VERSION ===\n");
    Student* student2 = create_student_fixed("Bob", 1002);
    if (student2 != NULL) {
        add_grade_fixed(student2, 88);
        add_grade_fixed(student2, 95);
        add_grade_fixed(student2, 82);

        calculate_average_fixed(student2);
        print_student_info_fixed(student2);

        // Proper cleanup
        free_student(student2);
    }

    // Demonstrate accessing freed memory (use-after-free bug)
    printf("\n=== USE-AFTER-FREE DEMONSTRATION ===\n");
    Student* student3 = create_student_fixed("Charlie", 1003);
    if (student3 != NULL) {
        add_grade_fixed(student3, 90);
        print_student_info_fixed(student3);

        printf("Freeing student3...\n");
        free_student(student3);
        student3 = NULL;  // Set to NULL to prevent accidental use

        // Uncomment the following lines to see use-after-free bug:
        // printf("Trying to access freed memory...\n");
        // print_student_info_fixed(student3);  // This will crash if student3 isn't NULL
    }

    printf("\nDebugging tips:\n");
    printf("1. Always initialize pointers to NULL\n");
    printf("2. Check return values of malloc\n");
    printf("3. Free all allocated memory\n");
    printf("4. Set freed pointers to NULL\n");
    printf("5. Use bounds checking for arrays\n");
    printf("6. Test edge cases (empty input, single element, etc.)\n");
    printf("7. Use Valgrind to detect memory leaks: valgrind ./debug_demo\n");

    return 0;
}