#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    int id;
    float salary;
    char department[30];
} Employee;

void write_binary_data(const char *filename) {
    FILE *file;
    Employee employees[] = {
        {"John Smith", 1001, 50000.0f, "Engineering"},
        {"Jane Doe", 1002, 60000.0f, "Marketing"},
        {"Bob Johnson", 1003, 55000.0f, "Engineering"},
        {"Alice Brown", 1004, 65000.0f, "Management"}
    };
    int count = sizeof(employees) / sizeof(employees[0]);

    file = fopen(filename, "wb");
    if (!file) {
        printf("Error creating file\n");
        return;
    }

    // Write count first
    fwrite(&count, sizeof(int), 1, file);

    // Write employee data
    fwrite(employees, sizeof(Employee), count, file);

    fclose(file);
    printf("Wrote %d employees to %s\n", count, filename);
}

void read_binary_data(const char *filename) {
    FILE *file;
    Employee *employees;
    int count;

    file = fopen(filename, "rb");
    if (!file) {
        printf("Error opening file\n");
        return;
    }

    // Read count
    if (fread(&count, sizeof(int), 1, file) != 1) {
        printf("Error reading count\n");
        fclose(file);
        return;
    }

    // Allocate memory
    employees = (Employee*)malloc(count * sizeof(Employee));
    if (!employees) {
        printf("Memory allocation failed\n");
        fclose(file);
        return;
    }

    // Read employee data
    if (fread(employees, sizeof(Employee), count, file) != count) {
        printf("Error reading employee data\n");
        free(employees);
        fclose(file);
        return;
    }

    fclose(file);

    // Display data
    printf("\nEmployee Records:\n");
    printf("==================\n");
    printf("%-20s %-6s %-10s %-15s\n", "Name", "ID", "Salary", "Department");
    printf("%-20s %-6s %-10s %-15s\n", "----", "--", "------", "----------");

    for (int i = 0; i < count; i++) {
        printf("%-20s %-6d $%-9.0f %-15s\n",
               employees[i].name, employees[i].id,
               employees[i].salary, employees[i].department);
    }

    free(employees);
}

void update_employee_salary(const char *filename, int id, float new_salary) {
    FILE *file;
    Employee employee;
    long position;

    file = fopen(filename, "rb+");
    if (!file) {
        printf("Error opening file for update\n");
        return;
    }

    // Skip count
    fseek(file, sizeof(int), SEEK_SET);

    // Find employee
    while (fread(&employee, sizeof(Employee), 1, file) == 1) {
        if (employee.id == id) {
            // Go back to beginning of this record
            position = ftell(file) - sizeof(Employee);
            fseek(file, position, SEEK_SET);

            // Update salary
            employee.salary = new_salary;
            fwrite(&employee, sizeof(Employee), 1, file);

            printf("Updated salary for employee %d to $%.0f\n", id, new_salary);
            fclose(file);
            return;
        }
    }

    printf("Employee with ID %d not found\n", id);
    fclose(file);
}

int main() {
    const char *filename = "employees.dat";

    printf("Binary File Operations Demo\n");
    printf("===========================\n");

    write_binary_data(filename);
    read_binary_data(filename);

    printf("\nUpdating employee salary...\n");
    update_employee_salary(filename, 1002, 62000.0f);

    printf("\nAfter update:\n");
    read_binary_data(filename);

    return 0;
}