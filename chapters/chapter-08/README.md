# Chapter 8: File I/O

## Learning Objectives
By the end of this chapter, you will be able to:
- Understand file streams and file pointers
- Read from and write to text files
- Work with binary files
- Handle file errors and edge cases
- Navigate files with different modes
- Implement file-based data persistence
- Create professional file handling functions

## Introduction to File I/O

File Input/Output (I/O) allows your programs to read from and write to files on disk. This enables:
- **Data persistence** - Store data between program runs
- **Configuration files** - Save and load program settings
- **Data processing** - Read and process external data files
- **Logging** - Record program activity and errors
- **Import/Export** - Exchange data with other applications

## File Streams and Pointers

### FILE Pointer
```c
#include <stdio.h>

int main() {
    // FILE is a structure defined in stdio.h
    // FILE* is a pointer to a FILE structure
    FILE *file_pointer;

    printf("File I/O Basics\n");
    printf("==============\n");

    // The FILE structure contains information about:
    // - Current position in file
    // - Buffer for reading/writing
    // - Error and EOF indicators
    // - File opening mode

    printf("Size of FILE structure: %zu bytes\n", sizeof(FILE));
    printf("Size of FILE pointer: %zu bytes\n", sizeof(FILE*));

    return 0;
}
```

### File Opening Modes
```c
#include <stdio.h>

int main() {
    printf("File Opening Modes\n");
    printf("==================\n");

    printf("Text File Modes:\n");
    printf("  \"r\"   - Read only (file must exist)\n");
    printf("  \"w\"   - Write only (creates new or overwrites)\n");
    printf("  \"a\"   - Append (creates new or adds to end)\n");
    printf("  \"r+\"  - Read and write (file must exist)\n");
    printf("  \"w+\"  - Read and write (creates new or overwrites)\n");
    printf("  \"a+\"  - Read and append (creates new or adds to end)\n");

    printf("\nBinary File Modes (add 'b'):\n");
    printf("  \"rb\"  - Read binary\n");
    printf("  \"wb\"  - Write binary\n");
    printf("  \"ab\"  - Append binary\n");
    printf("  \"r+b\" - Read and write binary\n");
    printf("  \"w+b\" - Read and write binary\n");
    printf("  \"a+b\" - Read and append binary\n");

    printf("\nUpdate Modes (add '+'):\n");
    printf("  '+' allows both reading and writing\n");

    return 0;
}
```

## Writing to Text Files

### Basic File Writing
```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char text[] = "Hello, File I/O World!";
    int numbers[] = {10, 20, 30, 40, 50};

    // Open file for writing
    file = fopen("example.txt", "w");

    if (file == NULL) {
        printf("Error: Could not open file for writing.\n");
        return 1;
    }

    printf("Writing to file...\n");

    // Write strings using fprintf
    fprintf(file, "=== My First File ===\n");
    fprintf(file, "This is a text file created with C.\n");
    fprintf(file, "Message: %s\n", text);

    // Write numbers using fprintf
    fprintf(file, "Numbers: ");
    for (int i = 0; i < 5; i++) {
        fprintf(file, "%d ", numbers[i]);
    }
    fprintf(file, "\n");

    // Write formatted data
    fprintf(file, "Floating point: %.2f\n", 3.14159f);
    fprintf(file, "Character: %c\n", 'A');

    // Close the file
    fclose(file);
    printf("File written successfully.\n");

    return 0;
}
```

### Writing User Input to File
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_NOTES_LENGTH 200

typedef struct {
    char name[MAX_NAME_LENGTH];
    int age;
    float score;
    char notes[MAX_NOTES_LENGTH];
} Student;

int main() {
    FILE *file;
    Student student;
    char choice;

    // Open file for appending
    file = fopen("students.txt", "a");

    if (file == NULL) {
        printf("Error: Could not open students.txt\n");
        return 1;
    }

    printf("Student Data Entry\n");
    printf("==================\n");

    do {
        // Get student data
        printf("\nEnter student name: ");
        fgets(student.name, MAX_NAME_LENGTH, stdin);
        student.name[strcspn(student.name, "\n")] = '\0';

        printf("Enter age: ");
        scanf("%d", &student.age);

        printf("Enter score: ");
        scanf("%f", &student.score);
        while (getchar() != '\n'); // Clear input buffer

        printf("Enter notes: ");
        fgets(student.notes, MAX_NOTES_LENGTH, stdin);
        student.notes[strcspn(student.notes, "\n")] = '\0';

        // Write to file
        fprintf(file, "%s,%d,%.2f,%s\n",
                student.name, student.age, student.score, student.notes);

        printf("Student saved. Add another? (y/n): ");
        scanf(" %c", &choice);
        while (getchar() != '\n'); // Clear input buffer

    } while (choice == 'y' || choice == 'Y');

    fclose(file);
    printf("All students saved to students.txt\n");

    return 0;
}
```

## Reading from Text Files

### Basic File Reading
```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char line[256];

    // Open file for reading
    file = fopen("example.txt", "r");

    if (file == NULL) {
        printf("Error: Could not open file for reading.\n");
        return 1;
    }

    printf("Reading from file:\n");
    printf("==================\n");

    // Read file line by line
    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line);
    }

    // Check if we reached end of file normally
    if (feof(file)) {
        printf("\n\nReached end of file successfully.\n");
    } else if (ferror(file)) {
        printf("\nError occurred while reading file.\n");
    }

    // Close the file
    fclose(file);

    return 0;
}
```

### Reading Structured Data
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100

typedef struct {
    char name[50];
    int age;
    float score;
    char notes[200];
} Student;

int main() {
    FILE *file;
    Student students[MAX_STUDENTS];
    int student_count = 0;
    char line[300];

    // Open file for reading
    file = fopen("students.txt", "r");

    if (file == NULL) {
        printf("Error: Could not open students.txt\n");
        printf("Make sure the file exists from the previous example.\n");
        return 1;
    }

    printf("Reading Student Data\n");
    printf("====================\n");

    // Read CSV data
    while (fgets(line, sizeof(line), file) != NULL && student_count < MAX_STUDENTS) {
        // Parse CSV line
        char *token = strtok(line, ",");
        if (token) strcpy(students[student_count].name, token);

        token = strtok(NULL, ",");
        if (token) students[student_count].age = atoi(token);

        token = strtok(NULL, ",");
        if (token) students[student_count].score = atof(token);

        token = strtok(NULL, ",\n");
        if (token) strcpy(students[student_count].notes, token);

        student_count++;
    }

    fclose(file);

    // Display loaded data
    printf("\nLoaded %d students:\n", student_count);
    printf("%-20s %-5s %-8s %s\n", "Name", "Age", "Score", "Notes");
    printf("%-20s %-5s %-8s %s\n", "----", "---", "-----", "-----");

    for (int i = 0; i < student_count; i++) {
        printf("%-20s %-5d %-8.1f %s\n",
               students[i].name, students[i].age,
               students[i].score, students[i].notes);
    }

    return 0;
}
```

## Binary File Operations

### Writing Binary Data
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    int age;
    float height;
    char gender;
} Person;

int main() {
    FILE *file;
    Person people[] = {
        {"Alice Johnson", 25, 5.6f, 'F'},
        {"Bob Smith", 30, 6.0f, 'M'},
        {"Carol Davis", 28, 5.4f, 'F'}
    };

    int num_people = sizeof(people) / sizeof(people[0]);

    // Open file for binary writing
    file = fopen("people.dat", "wb");

    if (file == NULL) {
        printf("Error: Could not open file for binary writing.\n");
        return 1;
    }

    printf("Writing binary data...\n");

    // Write the number of records first
    fwrite(&num_people, sizeof(int), 1, file);

    // Write all people records
    fwrite(people, sizeof(Person), num_people, file);

    fclose(file);
    printf("Wrote %d records to people.dat\n", num_people);

    return 0;
}
```

### Reading Binary Data
```c
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[50];
    int age;
    float height;
    char gender;
} Person;

int main() {
    FILE *file;
    Person *people;
    int num_people;

    // Open file for binary reading
    file = fopen("people.dat", "rb");

    if (file == NULL) {
        printf("Error: Could not open file for binary reading.\n");
        printf("Make sure people.dat exists from the previous example.\n");
        return 1;
    }

    printf("Reading binary data...\n");

    // Read the number of records
    if (fread(&num_people, sizeof(int), 1, file) != 1) {
        printf("Error reading file header.\n");
        fclose(file);
        return 1;
    }

    // Allocate memory for people
    people = (Person*)malloc(num_people * sizeof(Person));
    if (people == NULL) {
        printf("Memory allocation failed.\n");
        fclose(file);
        return 1;
    }

    // Read all people records
    size_t records_read = fread(people, sizeof(Person), num_people, file);
    fclose(file);

    printf("Read %zu records from people.dat\n", records_read);

    // Display data
    printf("\nPeople Records:\n");
    printf("%-20s %-5s %-8s %s\n", "Name", "Age", "Height", "Gender");
    printf("%-20s %-5s %-8s %s\n", "----", "---", "------", "------");

    for (int i = 0; i < num_people; i++) {
        printf("%-20s %-5d %-8.1f %c\n",
               people[i].name, people[i].age,
               people[i].height, people[i].gender);
    }

    // Free allocated memory
    free(people);

    return 0;
}
```

## File Positioning

### File Pointer Manipulation
```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char text[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char buffer[10];

    // Create test file
    file = fopen("alphabet.txt", "w");
    if (file == NULL) return 1;

    fprintf(file, "%s", text);
    fclose(file);

    // Open for reading and positioning
    file = fopen("alphabet.txt", "r");
    if (file == NULL) return 1;

    printf("File Positioning Demo\n");
    printf("=====================\n");

    // Get current position
    long current_pos = ftell(file);
    printf("Initial position: %ld\n", current_pos);

    // Read first 5 characters
    size_t bytes_read = fread(buffer, 1, 5, file);
    buffer[bytes_read] = '\0';
    printf("First 5 chars: %s\n", buffer);

    current_pos = ftell(file);
    printf("Position after reading: %ld\n", current_pos);

    // Seek to beginning
    fseek(file, 0, SEEK_SET);
    printf("After fseek(0, SEEK_SET): %ld\n", ftell(file));

    // Seek to specific position
    fseek(file, 10, SEEK_SET);
    printf("After fseek(10, SEEK_SET): %ld\n", ftell(file));

    // Read 3 characters from position 10
    bytes_read = fread(buffer, 1, 3, file);
    buffer[bytes_read] = '\0';
    printf("3 chars from pos 10: %s\n", buffer);

    // Seek to end
    fseek(file, 0, SEEK_END);
    printf("After fseek(0, SEEK_END): %ld\n", ftell(file));

    // Get file size
    long file_size = ftell(file);
    printf("File size: %ld bytes\n", file_size);

    // Seek from current position
    fseek(file, -5, SEEK_CUR);
    printf("After fseek(-5, SEEK_CUR): %ld\n", ftell(file));

    // Read last 5 characters
    bytes_read = fread(buffer, 1, 5, file);
    buffer[bytes_read] = '\0';
    printf("Last 5 chars: %s\n", buffer);

    // Rewind to beginning (same as fseek(file, 0, SEEK_SET))
    rewind(file);
    printf("After rewind(): %ld\n", ftell(file));

    fclose(file);

    return 0;
}
```

## Error Handling in File Operations

### Robust File Handling
```c
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void print_file_error(const char *filename, const char *operation) {
    printf("Error %s file '%s': %s\n",
           operation, filename, strerror(errno));
}

int safe_file_read(const char *filename) {
    FILE *file;
    char line[256];
    int line_number = 0;

    printf("Reading file with error handling: %s\n", filename);

    // Try to open file
    file = fopen(filename, "r");
    if (file == NULL) {
        print_file_error(filename, "opening");
        return 0;
    }

    printf("File opened successfully. Reading contents:\n");
    printf("=====================================\n");

    // Read file with error checking
    while (fgets(line, sizeof(line), file) != NULL) {
        line_number++;

        // Check for read errors
        if (ferror(file)) {
            printf("Error reading line %d\n", line_number);
            print_file_error(filename, "reading");
            clearerr(file); // Clear error flags
            break;
        }

        printf("Line %2d: %s", line_number, line);
    }

    // Check how we exited the loop
    if (feof(file)) {
        printf("\nReached end of file successfully.\n");
    } else if (ferror(file)) {
        printf("\nReading stopped due to error.\n");
    }

    // Close file with error checking
    if (fclose(file) != 0) {
        print_file_error(filename, "closing");
        return 0;
    }

    printf("File closed successfully.\n");
    return 1;
}

int copy_file(const char *source, const char *destination) {
    FILE *src, *dst;
    char buffer[1024];
    size_t bytes_read, bytes_written;

    printf("Copying '%s' to '%s'\n", source, destination);

    // Open source file
    src = fopen(source, "rb");
    if (src == NULL) {
        print_file_error(source, "opening source");
        return 0;
    }

    // Open destination file
    dst = fopen(destination, "wb");
    if (dst == NULL) {
        print_file_error(destination, "opening destination");
        fclose(src);
        return 0;
    }

    // Copy file content
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        bytes_written = fwrite(buffer, 1, bytes_read, dst);
        if (bytes_written != bytes_read) {
            printf("Error writing to destination file.\n");
            fclose(src);
            fclose(dst);
            return 0;
        }
    }

    // Check for read errors
    if (ferror(src)) {
        printf("Error reading source file.\n");
    }

    fclose(src);
    fclose(dst);

    printf("File copied successfully.\n");
    return 1;
}

int main() {
    // Test error handling
    printf("File Error Handling Demo\n");
    printf("=======================\n\n");

    // Try to read existing file
    safe_file_read("alphabet.txt");

    printf("\n");

    // Try to read non-existent file
    safe_file_read("nonexistent.txt");

    printf("\n");

    // Test file copying
    if (copy_file("alphabet.txt", "alphabet_backup.txt")) {
        printf("Copy successful.\n");
    }

    return 0;
}
```

## File Processing Applications

### Simple Logging System
```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_MESSAGE_LENGTH 200

typedef enum {
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR
} LogLevel;

const char* log_level_strings[] = {"INFO", "WARNING", "ERROR"};

void log_message(FILE *log_file, LogLevel level, const char *message) {
    time_t now;
    struct tm *timeinfo;
    char timestamp[80];

    // Get current time
    time(&now);
    timeinfo = localtime(&now);
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeinfo);

    // Write log entry
    fprintf(log_file, "[%s] %s: %s\n",
            timestamp, log_level_strings[level], message);
    fflush(log_file); // Ensure immediate write

    // Also display on console
    printf("[%s] %s: %s\n",
           timestamp, log_level_strings[level], message);
}

int main() {
    FILE *log_file;

    // Open log file in append mode
    log_file = fopen("application.log", "a");

    if (log_file == NULL) {
        printf("Error: Could not open log file.\n");
        return 1;
    }

    printf("Logging System Demo\n");
    printf("==================\n");

    // Simulate application with logging
    log_message(log_file, LOG_INFO, "Application started");
    log_message(log_file, LOG_INFO, "Initializing components");

    log_message(log_file, LOG_WARNING, "Configuration file not found, using defaults");
    log_message(log_file, LOG_INFO, "Database connection established");

    log_message(log_file, LOG_ERROR, "Failed to load user preferences");

    log_message(log_file, LOG_INFO, "Application shutting down");

    fclose(log_file);
    printf("\nLog entries written to application.log\n");

    return 0;
}
```

### Configuration File Parser
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_CONFIG_LINE 256
#define MAX_CONFIG_VALUE 100

typedef struct {
    char database_name[50];
    int port;
    char username[30];
    int max_connections;
    int debug_mode;
} Config;

void trim_whitespace(char *str) {
    char *end;

    // Trim leading space
    while (isspace((unsigned char)*str)) str++;

    if (*str == 0) {  // All spaces
        return;
    }

    // Trim trailing space
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;

    // Write new null terminator
    *(end + 1) = '\0';
}

int parse_config_file(const char *filename, Config *config) {
    FILE *file;
    char line[MAX_CONFIG_LINE];
    char key[50], value[MAX_CONFIG_VALUE];

    // Initialize default values
    strcpy(config->database_name, "default.db");
    config->port = 8080;
    strcpy(config->username, "admin");
    config->max_connections = 100;
    config->debug_mode = 0;

    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Config file not found, using defaults.\n");
        return 0;
    }

    printf("Reading configuration from %s\n", filename);

    while (fgets(line, sizeof(line), file) != NULL) {
        // Skip comments and empty lines
        if (line[0] == '#' || line[0] == '\n') {
            continue;
        }

        // Parse key=value format
        char *equals = strchr(line, '=');
        if (equals == NULL) continue;

        *equals = '\0';  // Split line at '='

        strcpy(key, line);
        strcpy(value, equals + 1);

        // Trim whitespace
        trim_whitespace(key);
        trim_whitespace(value);

        // Remove newline from value
        value[strcspn(value, "\n")] = '\0';

        // Set configuration values
        if (strcmp(key, "database_name") == 0) {
            strcpy(config->database_name, value);
        } else if (strcmp(key, "port") == 0) {
            config->port = atoi(value);
        } else if (strcmp(key, "username") == 0) {
            strcpy(config->username, value);
        } else if (strcmp(key, "max_connections") == 0) {
            config->max_connections = atoi(value);
        } else if (strcmp(key, "debug_mode") == 0) {
            config->debug_mode = (strcmp(value, "true") == 0 ||
                                strcmp(value, "1") == 0);
        }
    }

    fclose(file);
    return 1;
}

void display_config(const Config *config) {
    printf("\nCurrent Configuration:\n");
    printf("=======================\n");
    printf("Database Name: %s\n", config->database_name);
    printf("Port: %d\n", config->port);
    printf("Username: %s\n", config->username);
    printf("Max Connections: %d\n", config->max_connections);
    printf("Debug Mode: %s\n", config->debug_mode ? "ON" : "OFF");
}

int main() {
    Config config;

    printf("Configuration File Parser\n");
    printf("========================\n");

    // First, create a sample config file
    FILE *config_file = fopen("config.txt", "w");
    if (config_file != NULL) {
        fprintf(config_file, "# Application Configuration\n");
        fprintf(config_file, "database_name=myapp.db\n");
        fprintf(config_file, "port=3306\n");
        fprintf(config_file, "username=admin\n");
        fprintf(config_file, "max_connections=200\n");
        fprintf(config_file, "debug_mode=true\n");
        fclose(config_file);
        printf("Created sample config.txt\n");
    }

    // Parse configuration
    parse_config_file("config.txt", &config);

    // Display configuration
    display_config(&config);

    return 0;
}
```

## File System Operations

### File Information and Attributes
```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>

void print_file_info(const char *filename) {
    struct stat file_stat;

    if (stat(filename, &file_stat) == 0) {
        printf("\nFile Information: %s\n", filename);
        printf("========================%s\n", "========================");

        printf("Size: %ld bytes\n", file_stat.st_size);

        // File permissions
        printf("Permissions: ");
        printf((file_stat.st_mode & S_IRUSR) ? "r" : "-");
        printf((file_stat.st_mode & S_IWUSR) ? "w" : "-");
        printf((file_stat.st_mode & S_IXUSR) ? "x" : "-");
        printf((file_stat.st_mode & S_IRGRP) ? "r" : "-");
        printf((file_stat.st_mode & S_IWGRP) ? "w" : "-");
        printf((file_stat.st_mode & S_IXGRP) ? "x" : "-");
        printf((file_stat.st_mode & S_IROTH) ? "r" : "-");
        printf((file_stat.st_mode & S_IWOTH) ? "w" : "-");
        printf((file_stat.st_mode & S_IXOTH) ? "x" : "-");
        printf("\n");

        // File type
        printf("Type: ");
        if (S_ISREG(file_stat.st_mode)) {
            printf("Regular file\n");
        } else if (S_ISDIR(file_stat.st_mode)) {
            printf("Directory\n");
        } else if (S_ISLNK(file_stat.st_mode)) {
            printf("Symbolic link\n");
        } else {
            printf("Other\n");
        }

        // Timestamps
        printf("Last modified: %s", ctime(&file_stat.st_mtime));
        printf("Last accessed: %s", ctime(&file_stat.st_atime));
        printf("Created: %s", ctime(&file_stat.st_ctime));
    } else {
        printf("Could not get information for %s\n", filename);
    }
}

long get_file_size(const char *filename) {
    FILE *file;
    long size;

    file = fopen(filename, "rb");
    if (file == NULL) {
        return -1;
    }

    // Seek to end
    fseek(file, 0, SEEK_END);
    size = ftell(file);

    fclose(file);
    return size;
}

int file_exists(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file) {
        fclose(file);
        return 1;
    }
    return 0;
}

int main() {
    printf("File System Operations\n");
    printf("======================\n");

    // Check if files exist
    printf("\nFile Existence Check:\n");
    printf("alphabet.txt exists: %s\n",
           file_exists("alphabet.txt") ? "Yes" : "No");
    printf("nonexistent.txt exists: %s\n",
           file_exists("nonexistent.txt") ? "Yes" : "No");

    // Get file sizes
    printf("\nFile Sizes:\n");
    long size1 = get_file_size("alphabet.txt");
    long size2 = get_file_size("students.txt");

    if (size1 >= 0) printf("alphabet.txt: %ld bytes\n", size1);
    if (size2 >= 0) printf("students.txt: %ld bytes\n", size2);

    // Display detailed file information
    if (file_exists("alphabet.txt")) {
        print_file_info("alphabet.txt");
    }

    return 0;
}
```

## Best Practices

### File Handling Guidelines
1. **Always check return values** of file operations
2. **Close files** when you're done with them
3. **Use appropriate file modes** for your needs
4. **Handle errors gracefully** with meaningful messages
5. **Check for file existence** before operations

### Memory Management
1. **Free allocated memory** after file operations
2. **Buffer sizes** should be appropriate for your data
3. **Flush file buffers** when immediate write is needed
4. **Use binary mode** for non-text data

### Security Considerations
1. **Validate filenames** from user input
2. **Check file permissions** before operations
3. **Use absolute paths** when possible
4. **Sanitize input** before file operations

## Common Errors and Solutions

### Error: "Permission denied"
**Cause**: Insufficient file permissions
**Solution**: Check file permissions and choose appropriate location

### Error: "File not found"
**Cause**: File doesn't exist or wrong path
**Solution**: Use file_exists() to check before operations

### Error: "File already exists"
**Cause**: Trying to create file that exists
**Solution**: Check for existence or use different mode

### Error: "Disk full"
**Cause**: No space on disk
**Solution**: Check available space before writing

## Exercises

### Exercise 8.1: File Statistics
Create a program that counts lines, words, and characters in a text file.

### Exercise 8.2: Word Reverser
Create a program that reads a text file and writes each word reversed to a new file.

### Exercise 8.3: File Merger
Create a program that merges multiple text files into one.

### Exercise 8.4: Log Analyzer
Create a program that parses log files and extracts error messages.

### Exercise 8.5: Data Exporter
Create a program that exports structured data to CSV format.

## Challenge Problems

### Challenge 8.1: Simple Text Editor
Create a basic text editor with file operations.

### Challenge 8.2: File Encryption
Implement simple file encryption/decryption.

### Challenge 8.3: Directory Browser
Create a program that lists and navigates directories.

## Quick Reference

### File Operations
- **Open**: `FILE *fopen(filename, mode)`
- **Close**: `int fclose(FILE *stream)`
- **Read**: `size_t fread(buffer, size, count, file)`
- **Write**: `size_t fwrite(buffer, size, count, file)`

### Text I/O
- **Formatted read**: `int fscanf(file, format, ...)`
- **Formatted write**: `int fprintf(file, format, ...)`
- **Line read**: `char *fgets(buffer, size, file)`
- **Line write**: `int fputs(string, file)`

### Binary I/O
- **Read**: `size_t fread(buffer, size, count, file)`
- **Write**: `size_t fwrite(buffer, size, count, file)`

### File Positioning
- **Get position**: `long ftell(file)`
- **Set position**: `int fseek(file, offset, origin)`
- **Rewind**: `void rewind(file)`
- **End of file**: `int feof(file)`
- **Error check**: `int ferror(file)`

### Origin Values for fseek
- **SEEK_SET**: Beginning of file
- **SEEK_CUR**: Current position
- **SEEK_END**: End of file

## Next Steps
Once you're comfortable with:
- Reading and writing text files
- Working with binary files
- File positioning and seeking
- Error handling in file operations
- Creating file-based applications

You're ready to move to **Chapter 9: Memory Management**!