# Chapter 7: Structures and Unions

## Learning Objectives
By the end of this chapter, you will be able to:
- Understand and use structures to group related data
- Create and initialize structures
- Access structure members using dot and arrow operators
- Work with arrays of structures
- Use pointers to structures
- Understand unions and their applications
- Apply typedef for better code readability

## Introduction to Structures

A structure (or struct) is a user-defined data type that groups together related data items of different types under a single name. Structures allow you to:
- **Organize complex data** in meaningful ways
- **Group related information** together
- **Create custom data types** for specific applications
- **Pass complex data** to functions efficiently

## Basic Structure Definition and Usage

### Defining a Structure
```c
#include <stdio.h>

// Structure definition
struct Person {
    char name[50];
    int age;
    float height;
    char gender;
};

int main() {
    // Declare structure variables
    struct Person person1;
    struct Person person2 = {"Alice Johnson", 25, 5.6f, 'F'};

    // Assign values to structure members
    strcpy(person1.name, "Bob Smith");
    person1.age = 30;
    person1.height = 6.0f;
    person1.gender = 'M';

    // Access structure members using dot operator
    printf("Person 1:\n");
    printf("  Name: %s\n", person1.name);
    printf("  Age: %d\n", person1.age);
    printf("  Height: %.1f ft\n", person1.height);
    printf("  Gender: %c\n", person1.gender);

    printf("\nPerson 2:\n");
    printf("  Name: %s\n", person2.name);
    printf("  Age: %d\n", person2.age);
    printf("  Height: %.1f ft\n", person2.height);
    printf("  Gender: %c\n", person2.gender);

    return 0;
}
```

### Structure Initialization
```c
#include <stdio.h>
#include <string.h>

struct Book {
    char title[100];
    char author[50];
    float price;
    int year;
    char isbn[20];
};

int main() {
    // Different initialization methods

    // Method 1: Initialize all members
    struct Book book1 = {"The C Programming Language",
                        "Brian Kernighan & Dennis Ritchie",
                        45.99f, 1978, "978-0131103627"};

    // Method 2: Designated initializers (C99 and later)
    struct Book book2 = {
        .title = "Clean Code",
        .author = "Robert Martin",
        .price = 37.99f,
        .year = 2008,
        .isbn = "978-0132350884"
    };

    // Method 3: Partial initialization
    struct Book book3 = {"The Pragmatic Programmer", 42.50f};

    // Uninitialized members get default values (0 for numbers, empty for strings)
    printf("Book 1:\n");
    printf("  Title: %s\n", book1.title);
    printf("  Author: %s\n", book1.author);
    printf("  Price: $%.2f\n", book1.price);
    printf("  Year: %d\n", book1.year);
    printf("  ISBN: %s\n", book1.isbn);

    printf("\nBook 2:\n");
    printf("  Title: %s\n", book2.title);
    printf("  Price: $%.2f\n", book2.price);

    printf("\nBook 3 (partial initialization):\n");
    printf("  Title: %s\n", book3.title);
    printf("  Price: $%.2f\n", book3.price);
    printf("  Author: '%s' (empty string)\n", book3.author);
    printf("  Year: %d (zero)\n", book3.year);

    return 0;
}
```

## Structures with Functions

### Passing Structures to Functions
```c
#include <stdio.h>
#include <string.h>

struct Point {
    float x;
    float y;
};

struct Rectangle {
    struct Point top_left;
    struct Point bottom_right;
};

// Function that takes structure by value
void print_point(struct Point p) {
    printf("(%.2f, %.2f)", p.x, p.y);
}

// Function that returns a structure
struct Point create_point(float x, float y) {
    struct Point p;
    p.x = x;
    p.y = y;
    return p;
}

// Function that modifies structure (needs pointer)
void move_point(struct Point *p, float dx, float dy) {
    p->x += dx;  // Arrow operator for pointer to structure
    p->y += dy;
}

// Function that calculates rectangle area
float calculate_area(struct Rectangle rect) {
    float width = rect.bottom_right.x - rect.top_left.x;
    float height = rect.top_left.y - rect.bottom_right.y;
    return width * height;
}

int main() {
    // Create points
    struct Point p1 = create_point(2.0f, 5.0f);
    struct Point p2 = {8.0f, 1.0f};

    printf("Points:\n");
    printf("  p1 = ");
    print_point(p1);
    printf("\n  p2 = ");
    print_point(p2);
    printf("\n");

    // Move point p1
    move_point(&p1, 1.0f, -1.0f);
    printf("After moving p1 by (1.0, -1.0): ");
    print_point(p1);
    printf("\n");

    // Create rectangle
    struct Rectangle rect = {p1, p2};
    printf("\nRectangle with top-left ");
    print_point(rect.top_left);
    printf(" and bottom-right ");
    print_point(rect.bottom_right);
    printf("\nArea: %.2f\n", calculate_area(rect));

    return 0;
}
```

## typedef with Structures

### Using typedef for Cleaner Code
```c
#include <stdio.h>
#include <string.h>

// Without typedef
struct Student_ {
    char name[50];
    int id;
    float gpa;
};

// With typedef - more readable
typedef struct {
    char name[50];
    int id;
    float gpa;
} Student;

// Another way to use typedef
typedef struct Employee_ {
    char name[50];
    int employee_id;
    float salary;
    char department[30];
} Employee;

int main() {
    // Without typedef
    struct Student_ student1 = {"John Doe", 1001, 3.8f};

    // With typedef - cleaner syntax
    Student student2 = {"Jane Smith", 1002, 3.9f};
    Employee emp = {"Mike Johnson", 2001, 75000.0f, "Engineering"};

    printf("Student Information:\n");
    printf("Student 1: %s (ID: %d, GPA: %.1f)\n",
           student1.name, student1.id, student1.gpa);
    printf("Student 2: %s (ID: %d, GPA: %.1f)\n",
           student2.name, student2.id, student2.gpa);

    printf("\nEmployee Information:\n");
    printf("%s (ID: %d)\n", emp.name, emp.employee_id);
    printf("Department: %s\n", emp.department);
    printf("Salary: $%.2f\n", emp.salary);

    return 0;
}
```

## Arrays of Structures

### Working with Multiple Structure Instances
```c
#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 5

typedef struct {
    char name[50];
    int id;
    float marks[3];  // Marks for 3 subjects
    float average;
} Student;

// Function to calculate average marks
float calculate_average(float marks[], int num_subjects) {
    float sum = 0;
    for (int i = 0; i < num_subjects; i++) {
        sum += marks[i];
    }
    return sum / num_subjects;
}

// Function to input student data
void input_student(Student *s) {
    printf("Enter student name: ");
    fgets(s->name, sizeof(s->name), stdin);

    // Remove newline character
    s->name[strcspn(s->name, "\n")] = '\0';

    printf("Enter student ID: ");
    scanf("%d", &s->id);

    printf("Enter marks for 3 subjects: ");
    for (int i = 0; i < 3; i++) {
        scanf("%f", &s->marks[i]);
    }

    // Calculate average
    s->average = calculate_average(s->marks, 3);

    // Clear input buffer
    while (getchar() != '\n');
}

// Function to display student data
void display_student(const Student *s) {
    printf("Name: %s\n", s->name);
    printf("ID: %d\n", s->id);
    printf("Marks: %.1f, %.1f, %.1f\n", s->marks[0], s->marks[1], s->marks[2]);
    printf("Average: %.2f\n", s->average);
}

// Function to find student with highest average
int find_top_student(const Student students[], int num_students) {
    int top_index = 0;
    float highest_avg = students[0].average;

    for (int i = 1; i < num_students; i++) {
        if (students[i].average > highest_avg) {
            highest_avg = students[i].average;
            top_index = i;
        }
    }

    return top_index;
}

int main() {
    Student students[MAX_STUDENTS];
    int num_students;

    printf("Student Record System\n");
    printf("====================\n");
    printf("Enter number of students (max %d): ", MAX_STUDENTS);
    scanf("%d", &num_students);
    while (getchar() != '\n');  // Clear input buffer

    if (num_students > MAX_STUDENTS) {
        num_students = MAX_STUDENTS;
    }

    // Input student data
    for (int i = 0; i < num_students; i++) {
        printf("\nEnter details for student %d:\n", i + 1);
        input_student(&students[i]);
    }

    // Display all students
    printf("\n--- Student Records ---\n");
    for (int i = 0; i < num_students; i++) {
        printf("\nStudent %d:\n", i + 1);
        display_student(&students[i]);
    }

    // Find and display top student
    int top_index = find_top_student(students, num_students);
    printf("\n--- Top Student ---\n");
    display_student(&students[top_index]);

    return 0;
}
```

## Pointers to Structures

### Efficient Structure Handling with Pointers
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    int age;
    float salary;
} Employee;

// Function to create employee with dynamic memory
Employee* create_employee(const char *name, int age, float salary) {
    Employee *emp = (Employee*)malloc(sizeof(Employee));
    if (emp == NULL) {
        return NULL;
    }

    // Allocate memory for name
    emp->name = (char*)malloc(strlen(name) + 1);
    if (emp->name == NULL) {
        free(emp);
        return NULL;
    }

    strcpy(emp->name, name);
    emp->age = age;
    emp->salary = salary;

    return emp;
}

// Function to display employee
void display_employee(const Employee *emp) {
    printf("Employee: %s\n", emp->name);
    printf("Age: %d\n", emp->age);
    printf("Salary: $%.2f\n", emp->salary);
}

// Function to give raise
void give_raise(Employee *emp, float percentage) {
    emp->salary *= (1.0f + percentage / 100.0f);
    printf("Given %.1f%% raise to %s\n", percentage, emp->name);
}

// Function to free employee memory
void free_employee(Employee *emp) {
    if (emp != NULL) {
        free(emp->name);
        free(emp);
    }
}

int main() {
    // Create employees dynamically
    Employee *emp1 = create_employee("Alice Johnson", 28, 60000.0f);
    Employee *emp2 = create_employee("Bob Smith", 35, 75000.0f);

    if (emp1 == NULL || emp2 == NULL) {
        printf("Memory allocation failed!\n");
        free_employee(emp1);
        free_employee(emp2);
        return 1;
    }

    printf("Employee Information:\n");
    printf("=====================\n");

    display_employee(emp1);
    printf("\n");
    display_employee(emp2);

    // Give raises
    printf("\n--- Giving Raises ---\n");
    give_raise(emp1, 5.0f);
    give_raise(emp2, 3.5f);

    printf("\n--- Updated Information ---\n");
    display_employee(emp1);
    printf("\n");
    display_employee(emp2);

    // Clean up
    free_employee(emp1);
    free_employee(emp2);

    return 0;
}
```

## Nested Structures

### Structures Within Structures
```c
#include <stdio.h>
#include <string.h>

typedef struct {
    int day;
    int month;
    int year;
} Date;

typedef struct {
    int hours;
    int minutes;
    int seconds;
} Time;

typedef struct {
    Date date;
    Time time;
} DateTime;

typedef struct {
    char description[100];
    DateTime start;
    DateTime end;
    char location[50];
} Event;

// Function to print date
void print_date(const Date *d) {
    printf("%02d/%02d/%d", d->day, d->month, d->year);
}

// Function to print time
void print_time(const Time *t) {
    printf("%02d:%02d:%02d", t->hours, t->minutes, t->seconds);
}

// Function to print datetime
void print_datetime(const DateTime *dt) {
    print_date(&dt->date);
    printf(" ");
    print_time(&dt->time);
}

int main() {
    Event meeting;

    // Initialize nested structures
    strcpy(meeting.description, "Team Meeting");
    meeting.location = "Conference Room A";

    // Set start time
    meeting.start.date.day = 15;
    meeting.start.date.month = 1;
    meeting.start.date.year = 2024;
    meeting.start.time.hours = 14;
    meeting.start.time.minutes = 30;
    meeting.start.time.seconds = 0;

    // Set end time
    meeting.end.date.day = 15;
    meeting.end.date.month = 1;
    meeting.end.date.year = 2024;
    meeting.end.time.hours = 15;
    meeting.end.time.minutes = 30;
    meeting.end.time.seconds = 0;

    printf("Event Details:\n");
    printf("==============\n");
    printf("Description: %s\n", meeting.description);
    printf("Location: %s\n", meeting.location);
    printf("Start: ");
    print_datetime(&meeting.start);
    printf("\n");
    printf("End: ");
    print_datetime(&meeting.end);
    printf("\n");

    return 0;
}
```

## Unions

### Understanding Unions
A union is a special data type that allows storing different data types in the same memory location. Unlike structures, unions can only hold one value at a time.

```c
#include <stdio.h>

// Union definition
union Data {
    int i;
    float f;
    char str[20];
};

// Union with different sized members
union MultiType {
    char c;
    short s;
    int i;
    long l;
    float f;
    double d;
};

typedef struct {
    union {
        int int_value;
        float float_value;
        char string_value[50];
    } data;
    int type;  // 0 = int, 1 = float, 2 = string
} Variant;

int main() {
    // Basic union usage
    union Data data;

    printf("Union Demonstration:\n");
    printf("===================\n");

    // Store integer
    data.i = 42;
    printf("As integer: %d\n", data.i);

    // Store float (overwrites integer)
    data.f = 3.14f;
    printf("As float: %.2f\n", data.f);

    // Store string (overwrites float)
    strcpy(data.str, "Hello");
    printf("As string: %s\n", data.str);

    // Note: Only one member is valid at a time
    printf("\nSize of union: %zu bytes\n", sizeof(union Data));
    printf("Size of largest member (char[20]): %zu bytes\n", sizeof(char[20]));

    // Show memory layout
    printf("\nMemory Layout:\n");
    printf("Union address: %p\n", (void*)&data);
    printf("Integer at same address: %p\n", (void*)&data.i);
    printf("Float at same address: %p\n", (void*)&data.f);
    printf("String at same address: %p\n", (void*)data.str);

    // Variant type example
    printf("\nVariant Type Example:\n");
    printf("=====================\n");

    Variant var1, var2, var3;

    var1.type = 0;  // int
    var1.data.int_value = 100;

    var2.type = 1;  // float
    var2.data.float_value = 99.99f;

    var3.type = 2;  // string
    strcpy(var3.data.string_value, "Variant string");

    // Print based on type
    printf("Variant 1 (type %d): ", var1.type);
    switch (var1.type) {
        case 0: printf("%d\n", var1.data.int_value); break;
        case 1: printf("%.2f\n", var1.data.float_value); break;
        case 2: printf("%s\n", var1.data.string_value); break;
    }

    printf("Variant 2 (type %d): ", var2.type);
    switch (var2.type) {
        case 0: printf("%d\n", var2.data.int_value); break;
        case 1: printf("%.2f\n", var2.data.float_value); break;
        case 2: printf("%s\n", var2.data.string_value); break;
    }

    printf("Variant 3 (type %d): ", var3.type);
    switch (var3.type) {
        case 0: printf("%d\n", var3.data.int_value); break;
        case 1: printf("%.2f\n", var3.data.float_value); break;
        case 2: printf("%s\n", var3.data.string_value); break;
    }

    return 0;
}
```

## Structure Padding and Alignment

### Understanding Memory Layout
```c
#include <stdio.h>

// Structure without careful ordering (potential padding)
struct BadOrder {
    char c;      // 1 byte
    double d;    // 8 bytes (might need 7 bytes padding after c)
    int i;       // 4 bytes
    char s[10];  // 10 bytes
};

// Structure with careful ordering (less padding)
struct GoodOrder {
    double d;    // 8 bytes
    int i;       // 4 bytes
    char s[10];  // 10 bytes
    char c;      // 1 byte
};

// Packed structure (no padding)
#pragma pack(push, 1)
struct Packed {
    char c;      // 1 byte
    double d;    // 8 bytes
    int i;       // 4 bytes
    char s[10];  // 10 bytes
};
#pragma pack(pop)

int main() {
    printf("Structure Memory Layout\n");
    printf("=======================\n");

    printf("Size of char: %zu byte(s)\n", sizeof(char));
    printf("Size of int: %zu byte(s)\n", sizeof(int));
    printf("Size of double: %zu byte(s)\n", sizeof(double));
    printf("Size of char[10]: %zu byte(s)\n", sizeof(char[10]));
    printf("\n");

    printf("BadOrder structure:\n");
    printf("  Size: %zu bytes\n", sizeof(struct BadOrder));
    printf("  Expected minimum: %d bytes (1 + 8 + 4 + 10)\n", 23);
    printf("  Padding: %zu bytes\n", sizeof(struct BadOrder) - 23);

    printf("\nGoodOrder structure:\n");
    printf("  Size: %zu bytes\n", sizeof(struct GoodOrder));
    printf("  Expected minimum: %d bytes (8 + 4 + 10 + 1)\n", 23);
    printf("  Padding: %zu bytes\n", sizeof(struct GoodOrder) - 23);

    printf("\nPacked structure:\n");
    printf("  Size: %zu bytes\n", sizeof(struct Packed));
    printf("  Expected minimum: %d bytes (1 + 8 + 4 + 10)\n", 23);
    printf("  Padding: %zu bytes\n", sizeof(struct Packed) - 23);

    return 0;
}
```

## Practical Applications

### Student Management System
```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STUDENTS 100
#define MAX_COURSES 10

typedef struct {
    char code[10];
    char name[50];
    int credits;
    float grade;
} Course;

typedef struct {
    int id;
    char name[50];
    int age;
    char major[30];
    Course courses[MAX_COURSES];
    int num_courses;
    float gpa;
} Student;

// Function prototypes
void add_course(Student *s, const char *code, const char *name, int credits, float grade);
float calculate_gpa(const Student *s);
void display_student(const Student *s);
void list_students(const Student students[], int count);

int main() {
    Student students[MAX_STUDENTS];
    int student_count = 0;
    int choice;

    printf("Student Management System\n");
    printf("========================\n");

    while (1) {
        printf("\nMenu:\n");
        printf("1. Add student\n");
        printf("2. Add course to student\n");
        printf("3. Display student\n");
        printf("4. List all students\n");
        printf("5. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        while (getchar() != '\n');  // Clear input buffer

        switch (choice) {
            case 1: {
                if (student_count >= MAX_STUDENTS) {
                    printf("Maximum students reached!\n");
                    break;
                }

                Student s;
                s.id = 1000 + student_count;
                s.num_courses = 0;

                printf("Enter student name: ");
                fgets(s.name, sizeof(s.name), stdin);
                s.name[strcspn(s.name, "\n")] = '\0';

                printf("Enter age: ");
                scanf("%d", &s.age);
                while (getchar() != '\n');

                printf("Enter major: ");
                fgets(s.major, sizeof(s.major), stdin);
                s.major[strcspn(s.major, "\n")] = '\0';

                s.gpa = 0.0f;
                students[student_count++] = s;
                printf("Student added with ID: %d\n", s.id);
                break;
            }

            case 2: {
                int student_id;
                printf("Enter student ID: ");
                scanf("%d", &student_id);
                while (getchar() != '\n');

                // Find student
                int found = 0;
                for (int i = 0; i < student_count; i++) {
                    if (students[i].id == student_id) {
                        found = 1;
                        if (students[i].num_courses >= MAX_COURSES) {
                            printf("Maximum courses reached!\n");
                            break;
                        }

                        char code[10], name[50];
                        int credits;
                        float grade;

                        printf("Enter course code: ");
                        fgets(code, sizeof(code), stdin);
                        code[strcspn(code, "\n")] = '\0';

                        printf("Enter course name: ");
                        fgets(name, sizeof(name), stdin);
                        name[strcspn(name, "\n")] = '\0';

                        printf("Enter credits: ");
                        scanf("%d", &credits);

                        printf("Enter grade (0-4): ");
                        scanf("%f", &grade);
                        while (getchar() != '\n');

                        add_course(&students[i], code, name, credits, grade);
                        students[i].gpa = calculate_gpa(&students[i]);
                        printf("Course added successfully!\n");
                        break;
                    }
                }

                if (!found) {
                    printf("Student not found!\n");
                }
                break;
            }

            case 3: {
                int student_id;
                printf("Enter student ID: ");
                scanf("%d", &student_id);
                while (getchar() != '\n');

                int found = 0;
                for (int i = 0; i < student_count; i++) {
                    if (students[i].id == student_id) {
                        found = 1;
                        display_student(&students[i]);
                        break;
                    }
                }

                if (!found) {
                    printf("Student not found!\n");
                }
                break;
            }

            case 4:
                list_students(students, student_count);
                break;

            case 5:
                printf("Goodbye!\n");
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}

void add_course(Student *s, const char *code, const char *name, int credits, float grade) {
    if (s->num_courses < MAX_COURSES) {
        strcpy(s->courses[s->num_courses].code, code);
        strcpy(s->courses[s->num_courses].name, name);
        s->courses[s->num_courses].credits = credits;
        s->courses[s->num_courses].grade = grade;
        s->num_courses++;
    }
}

float calculate_gpa(const Student *s) {
    if (s->num_courses == 0) return 0.0f;

    float total_grade_points = 0.0f;
    int total_credits = 0;

    for (int i = 0; i < s->num_courses; i++) {
        total_grade_points += s->courses[i].grade * s->courses[i].credits;
        total_credits += s->courses[i].credits;
    }

    return total_credits > 0 ? total_grade_points / total_credits : 0.0f;
}

void display_student(const Student *s) {
    printf("\n=== Student Information ===\n");
    printf("ID: %d\n", s->id);
    printf("Name: %s\n", s->name);
    printf("Age: %d\n", s->age);
    printf("Major: %s\n", s->major);
    printf("GPA: %.2f\n", s->gpa);

    if (s->num_courses > 0) {
        printf("\nCourses:\n");
        for (int i = 0; i < s->num_courses; i++) {
            printf("  %s - %s (%d credits) - Grade: %.1f\n",
                   s->courses[i].code, s->courses[i].name,
                   s->courses[i].credits, s->courses[i].grade);
        }
    }
}

void list_students(const Student students[], int count) {
    printf("\n=== All Students ===\n");
    if (count == 0) {
        printf("No students in the system.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        printf("%d - %s (%s) - GPA: %.2f\n",
               students[i].id, students[i].name,
               students[i].major, students[i].gpa);
    }
}
```

## Best Practices

### Structure Design
1. **Group related data** logically
2. **Use meaningful member names**
3. **Consider data alignment** for performance
4. **Use typedef** for better readability
5. **Initialize structures** properly

### Memory Management
1. **Be careful with pointers** in structures
2. **Free allocated memory** for dynamic members
3. **Consider memory usage** with large structures
4. **Use stack allocation** for small structures

### Code Organization
1. **Separate structure definitions** from implementation
2. **Use header files** for structure declarations
3. **Create accessor functions** for complex structures
4. **Document structure purposes** and usage

## Common Errors and Solutions

### Error: Accessing uninitialized structure
**Cause**: Using structure members before initialization
**Solution**: Initialize structures or use designated initializers

### Error: Structure padding issues
**Cause**: Unexpected structure size due to alignment
**Solution**: Understand padding or use packed structures if needed

### Error: Memory leaks with structures
**Cause**: Not freeing dynamically allocated members
**Solution**: Free all allocated memory in destructor functions

### Error: Pointer confusion
**Cause**: Using dot operator instead of arrow (or vice versa)
**Solution**: Use dot with structures, arrow with pointers to structures

## Exercises

### Exercise 7.1: Basic Structures
Create a `Person` structure with name, age, and height. Write functions to input and display person data.

### Exercise 7.2: Array of Structures
Create an array of `Book` structures and implement functions to add, search, and display books.

### Exercise 7.3: Nested Structures
Create `Address` and `Person` structures where Person contains an Address.

### Exercise 7.4: Union Usage
Create a union that can store different numeric types and a structure that tracks which type is stored.

### Exercise 7.5: Dynamic Structure Allocation
Write functions to create, modify, and free structures using dynamic memory allocation.

## Challenge Problems

### Challenge 7.1: Database System
Create a simple database using structures for records.

### Challenge 7.2: Graph Data Structure
Implement a graph using structures for vertices and edges.

### Challenge 7.3: JSON Parser
Create a simple JSON parser using structures and unions.

## Quick Reference

### Structure Declaration
```c
// Without typedef
struct StructureName {
    type member1;
    type member2;
};

// With typedef
typedef struct {
    type member1;
    type member2;
} TypeName;
```

### Structure Access
- **Dot operator**: `structure.member` (for structure variables)
- **Arrow operator**: `pointer->member` (for pointers to structures)

### Union Declaration
```c
union UnionName {
    type member1;
    type member2;
    // Members share the same memory location
};
```

### Structure with Pointers
```c
typedef struct {
    type *member;  // Pointer member
    int size;      // Size information
} DynamicStructure;
```

## Next Steps
Once you're comfortable with:
- Defining and using structures
- Working with arrays of structures
- Using pointers to structures
- Understanding unions
- Creating complex data structures

You're ready for **Milestone 2: Contact Manager** and then **Chapter 8: File I/O**!

Structures and unions provide the foundation for creating complex data structures and are essential for real-world programming applications.