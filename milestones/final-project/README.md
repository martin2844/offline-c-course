# Final Project: DevTools Utility Suite

**🎯 Capstone Project - Apply All Course Concepts**

## Project Overview

Create a comprehensive DevTools Utility Suite that demonstrates mastery of all C programming concepts learned throughout this course. This project will be a collection of useful developer tools that any programmer would find valuable in their daily work.

## Learning Objectives

By completing this final project, you will have:
- ✅ **Integrated all major C programming concepts** in a single application
- ✅ **Built a professional-grade CLI tool** with multiple utilities
- ✅ **Applied advanced memory management** and file operations
- ✅ **Implemented modular design** with proper error handling
- ✅ **Created a portfolio-worthy project** that demonstrates real-world skills

## Project Features

The DevTools Utility Suite includes:

### Core Utilities
1. **File Analyzer** - Analyze file sizes, types, and statistics
2. **Text Processor** - Search, replace, and transform text files
3. **Code Metrics** - Calculate code complexity and statistics
4. **Hash Generator** - Generate MD5, SHA1, SHA256 hashes
5. **JSON Validator** - Basic JSON validation and pretty-printing
6. **Color Palette Generator** - Generate and display color schemes
7. **URL Encoder/Decoder** - Encode and decode URLs
8. **Base64 Encoder/Decoder** - Encode and decode Base64 data

### Advanced Features
9. **Batch Processor** - Process multiple files simultaneously
10. **Configuration Manager** - Manage tool settings and preferences
11. **Performance Profiler** - Basic performance measurement tools
12. **Plugin System** - Extensible architecture for adding new tools

## Technical Requirements

### Architecture Requirements
- **Modular Design**: Each utility in separate files with clear interfaces
- **Memory Management**: Efficient allocation with proper cleanup
- **Error Handling**: Comprehensive error checking and reporting
- **Configuration**: JSON/INI config file support
- **Logging**: Built-in logging system with different levels
- **Plugin Support**: Easy addition of new utilities

### Code Quality Requirements
- **Consistent Style**: Follow established coding conventions
- **Documentation**: Complete function and module documentation
- **Testing**: Unit tests for core functionality
- **Build System**: Makefile for compilation and installation
- **Cross-platform**: Works on macOS, Linux, and Windows

### User Experience Requirements
- **CLI Interface**: Clean, intuitive command-line interface
- **Help System**: Comprehensive help for each utility
- **Progress Indicators**: Show progress for long operations
- **Error Messages**: Clear, actionable error reporting

## Implementation Guide

### Step 1: Project Structure
```
devtools/
├── README.md                    # This file
├── Makefile                    # Build system
├── main.c                     # Main entry point
├── config.h                   # Global configuration
├── common/                    # Shared utilities
│   ├── utils.h               # Common function prototypes
│   ├── utils.c               // Common function implementations
│   ├── error.h               // Error handling definitions
│   ├── error.c               // Error handling implementation
│   ├── logging.h             // Logging system
│   ├── logging.c             // Logging implementation
│   └── memory.h              // Memory management
│   └── memory.c              // Memory management
├── tools/                     // Individual tool modules
│   ├── file_analyzer/
│   ├── text_processor/
│   ├── code_metrics/
│   ├── hash_generator/
│   ├── json_validator/
│   ├── color_palette/
│   ├── url_encoder/
│   └── base64_encoder/
├── plugins/                   // Plugin system
├── tests/                     // Unit tests
└── docs/                      // Documentation
```

### Step 2: Core System Design

#### Main Entry Point (main.c)
```c
#include "config.h"
#include "common/utils.h"
#include "common/error.h"
#include "common/logging.h"
#include "plugins/plugin_manager.h"

int main(int argc, char *argv[]) {
    // Initialize core systems
    if (!init_devtools()) {
        return EXIT_FAILURE;
    }

    // Parse command line arguments
    Command cmd = parse_arguments(argc, argv);
    if (cmd.error != SUCCESS) {
        print_error(&cmd.error);
        return EXIT_FAILURE;
    }

    // Execute requested command
    int result = execute_command(&cmd);

    // Cleanup
    cleanup_devtools();
    return result;
}
```

#### Core Configuration (config.h)
```c
#ifndef DEVTOOLS_CONFIG_H
#define DEVTOOLS_CONFIG_H

#include <stdbool.h>
#include <stdio.h>

#define DEVTOOLS_VERSION "1.0.0"
#define MAX_TOOLS 50
#define MAX_PATH_LENGTH 1024
#define MAX_LINE_LENGTH 4096

typedef struct {
    char config_file[MAX_PATH_LENGTH];
    char log_file[MAX_PATH_LENGTH];
    bool verbose;
    bool quiet;
    int log_level;
} DevToolsConfig;

typedef struct {
    char name[64];
    char description[256];
    int (*execute)(int argc, char *argv[]);
    void (*help)(void);
} Tool;

typedef struct {
    char command[32];
    Tool *tool;
    int argc;
    char **argv;
} Command;

// Global configuration
extern DevToolsConfig g_config;

// Core system functions
bool init_devtools(void);
void cleanup_devtools(void);
Command parse_arguments(int argc, char *argv[]);
int execute_command(const Command *cmd);

#endif
```

### Step 3: Utility Modules

#### File Analyzer Tool
```c
// tools/file_analyzer/file_analyzer.h
#include "../../config.h"

typedef struct {
    size_t file_count;
    size_t total_size;
    size_t total_lines;
    char file_types[256][32];
    size_t type_counts[256];
    int unique_types;
} FileAnalysis;

int file_analyzer_execute(int argc, char *argv[]);
void file_analyzer_help(void);
FileAnalysis* analyze_files(char **files, int count);
void print_analysis(const FileAnalysis *analysis);
```

#### Text Processor Tool
```c
// tools/text_processor/text_processor.h
#include "../../config.h"

typedef struct {
    char search_term[MAX_LINE_LENGTH];
    char replace_term[MAX_LINE_LENGTH];
    bool case_sensitive;
    bool whole_words;
    bool regex_mode;
} TextProcessorConfig;

int text_processor_execute(int argc, char *argv[]);
void text_processor_help(void);
int process_file(const char *filename, TextProcessorConfig *config);
```

#### Hash Generator Tool
```c
// tools/hash_generator/hash_generator.h
#include "../../config.h"

typedef enum {
    HASH_MD5,
    HASH_SHA1,
    HASH_SHA256,
    HASH_SHA512
} HashType;

int hash_generator_execute(int argc, char *argv[]);
void hash_generator_help(void);
int calculate_hash(const char *filename, HashType type, char *output);
```

### Step 4: Common Utilities

#### Error Handling (common/error.h)
```c
#ifndef DEVTOOLS_ERROR_H
#define DEVTOOLS_ERROR_H

#include <stdio.h>
#include <stdarg.h>

typedef enum {
    SUCCESS = 0,
    ERROR_INVALID_ARGUMENT,
    ERROR_FILE_NOT_FOUND,
    ERROR_PERMISSION_DENIED,
    ERROR_MEMORY_ALLOCATION,
    ERROR_PARSE_ERROR,
    ERROR_NETWORK_ERROR,
    ERROR_TIMEOUT,
    ERROR_UNKNOWN
} ErrorCode;

typedef struct {
    ErrorCode code;
    char message[256];
    char file[64];
    int line;
    char function[64];
} Error;

#define SET_ERROR(ctx, code, msg, ...) \
    do { \
        (ctx)->code = (code); \
        snprintf((ctx)->message, sizeof((ctx)->message), msg, ##__VA_ARGS__); \
        strncpy((ctx)->file, __FILE__, sizeof((ctx)->file) - 1); \
        (ctx)->line = __LINE__; \
        strncpy((ctx)->function, __func__, sizeof((ctx)->function) - 1); \
    } while(0)

void print_error(const Error *error);
const char* error_string(ErrorCode code);

#endif
```

#### Logging System (common/logging.h)
```c
#ifndef DEVTOOLS_LOGGING_H
#define DEVTOOLS_LOGGING_H

typedef enum {
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR,
    LOG_FATAL
} LogLevel;

bool init_logging(const char *filename, LogLevel level);
void cleanup_logging(void);
void log_message(LogLevel level, const char *format, ...);

#define LOG_DEBUG(fmt, ...) log_message(LOG_DEBUG, fmt, ##__VA_ARGS__)
#define LOG_INFO(fmt, ...) log_message(LOG_INFO, fmt, ##__VA_ARGS__)
#define LOG_WARN(fmt, ...) log_message(LOG_WARN, fmt, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...) log_message(LOG_ERROR, fmt, ##__VA_ARGS__)
#define LOG_FATAL(fmt, ...) log_message(LOG_FATAL, fmt, ##__VA_ARGS__)

#endif
```

#### Memory Management (common/memory.h)
```c
#ifndef DEVTOOLS_MEMORY_H
#define DEVTOOLS_MEMORY_H

void* safe_malloc(size_t size);
void* safe_realloc(void *ptr, size_t size);
char* safe_strdup(const char *str);
void safe_free(void **ptr);

#define MALLOC(size) safe_malloc(size)
#define REALLOC(ptr, size) safe_realloc(ptr, size)
#define STRDUP(str) safe_strdup(str)
#define FREE(ptr) safe_free((void**)&ptr)

#endif
```

### Step 5: Plugin System

#### Plugin Manager (plugins/plugin_manager.h)
```c
#ifndef DEVTOOLS_PLUGIN_MANAGER_H
#define DEVTOOLS_PLUGIN_MANAGER_H

#include "../../config.h"

typedef struct {
    Tool tools[MAX_TOOLS];
    int tool_count;
    char plugin_directories[10][MAX_PATH_LENGTH];
    int dir_count;
} PluginManager;

bool plugin_manager_init(void);
void plugin_manager_cleanup(void);
bool register_tool(const Tool *tool);
Tool* find_tool(const char *name);
void list_tools(void);
bool load_plugins(void);

#endif
```

## Development Phases

### Phase 1: Core Infrastructure (Week 1)
1. **Project Setup**: Directory structure and Makefile
2. **Core Systems**: Error handling, logging, memory management
3. **Argument Parser**: Command-line argument processing
4. **Basic Framework**: Tool registration and execution

### Phase 2: Essential Tools (Week 2)
1. **File Analyzer**: File statistics and analysis
2. **Text Processor**: Basic text processing capabilities
3. **Hash Generator**: File hashing utilities
4. **Testing**: Unit tests for core functionality

### Phase 3: Advanced Tools (Week 3)
1. **Code Metrics**: Code analysis and statistics
2. **JSON Validator**: JSON parsing and validation
3. **Base64 Encoder**: Encoding/decoding utilities
4. **URL Encoder**: URL processing tools

### Phase 4: Enhancement (Week 4)
1. **Color Palette**: Color generation and display
2. **Batch Processing**: Multiple file operations
3. **Configuration**: Settings and preferences
4. **Plugin System**: Extensible architecture

### Phase 5: Polish (Week 5)
1. **Documentation**: Comprehensive help and docs
2. **Performance**: Optimization and profiling
3. **Testing**: Complete test suite
4. **Packaging**: Installation and distribution

## Implementation Examples

### Makefile Structure
```makefile
# Makefile for DevTools Utility Suite
CC = clang
CFLAGS = -Wall -Wextra -std=c99 -g
LDFLAGS = -lssl -lcrypto

# Directories
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin

# Core source files
CORE_SOURCES = $(SRC_DIR)/main.c \
              $(SRC_DIR)/common/utils.c \
              $(SRC_DIR)/common/error.c \
              $(SRC_DIR)/common/logging.c \
              $(SRC_DIR)/common/memory.c

# Tool sources
TOOL_SOURCES = $(wildcard $(SRC_DIR)/tools/*/*.c)

# Object files
CORE_OBJECTS = $(CORE_SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
TOOL_OBJECTS = $(TOOL_SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
ALL_OBJECTS = $(CORE_OBJECTS) $(TOOL_OBJECTS)

# Target executable
TARGET = $(BIN_DIR)/devtools

# Rules
all: $(TARGET)

$(TARGET): $(ALL_OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(ALL_OBJECTS) -o $(TARGET) $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

install: $(TARGET)
	cp $(TARGET) /usr/local/bin/

.PHONY: all clean install
```

### Sample Tool Implementation

#### File Analyzer (tools/file_analyzer/file_analyzer.c)
```c
#include "../file_analyzer.h"
#include "../../common/utils.h"
#include "../../common/error.h"
#include "../../common/logging.h"

#include <sys/stat.h>
#include <dirent.h>

static void analyze_single_file(const char *filename, FileAnalysis *analysis) {
    struct stat st;

    if (stat(filename, &st) != 0) {
        LOG_WARN("Cannot stat file: %s", filename);
        return;
    }

    analysis->file_count++;
    analysis->total_size += st.st_size;

    if (S_ISREG(st.st_size)) {
        // Count lines for regular files
        FILE *file = fopen(filename, "r");
        if (file) {
            char buffer[MAX_LINE_LENGTH];
            while (fgets(buffer, sizeof(buffer), file)) {
                analysis->total_lines++;
            }
            fclose(file);
        }
    }

    // Determine file type
    const char *ext = get_file_extension(filename);
    if (ext) {
        // Check if type already exists
        for (int i = 0; i < analysis->unique_types; i++) {
            if (strcmp(analysis->file_types[i], ext) == 0) {
                analysis->type_counts[i]++;
                return;
            }
        }

        // Add new file type
        if (analysis->unique_types < 256) {
            strcpy(analysis->file_types[analysis->unique_types], ext);
            analysis->type_counts[analysis->unique_types] = 1;
            analysis->unique_types++;
        }
    }
}

static void print_file_size(size_t size) {
    const char *units[] = {"B", "KB", "MB", "GB", "TB"};
    double size_d = (double)size;
    int unit = 0;

    while (size_d >= 1024 && unit < 4) {
        size_d /= 1024;
        unit++;
    }

    printf("%.2f %s", size_d, units[unit]);
}

FileAnalysis* analyze_files(char **files, int count) {
    FileAnalysis *analysis = MALLOC(sizeof(FileAnalysis));
    if (!analysis) return NULL;

    memset(analysis, 0, sizeof(FileAnalysis));

    for (int i = 0; i < count; i++) {
        if (is_directory(files[i])) {
            // Recursively analyze directory
            analyze_directory(files[i], analysis);
        } else {
            analyze_single_file(files[i], analysis);
        }
    }

    return analysis;
}

void print_analysis(const FileAnalysis *analysis) {
    printf("File Analysis Results\n");
    printf("====================\n");
    printf("Total files: %zu\n", analysis->file_count);
    printf("Total size: ");
    print_file_size(analysis->total_size);
    printf("\n");
    printf("Total lines: %zu\n", analysis->total_lines);

    printf("\nFile Types:\n");
    for (int i = 0; i < analysis->unique_types; i++) {
        printf("  .%s: %zu files\n", analysis->file_types[i], analysis->type_counts[i]);
    }
}

int file_analyzer_execute(int argc, char *argv[]) {
    if (argc < 2) {
        LOG_ERROR("Usage: devtools file-analyzer <files/directories>");
        return ERROR_INVALID_ARGUMENT;
    }

    LOG_INFO("Analyzing %d files/directories", argc - 1);

    FileAnalysis *analysis = analyze_files(argv + 1, argc - 1);
    if (!analysis) {
        LOG_ERROR("Failed to allocate analysis structure");
        return ERROR_MEMORY_ALLOCATION;
    }

    print_analysis(analysis);
    FREE(analysis);

    return SUCCESS;
}

void file_analyzer_help(void) {
    printf("File Analyzer Tool\n");
    printf("=================\n");
    printf("Analyzes files and directories to provide statistics:\n");
    printf("- File count and total size\n");
    printf("- Line count for text files\n");
    printf("- File type distribution\n");
    printf("- Directory support\n");
    printf("\nUsage:\n");
    printf("  devtools file-analyzer <file1> [file2] [directory1] ...\n");
    printf("  devtools file-analyzer *.c *.h\n");
    printf("  devtools file-analyzer /path/to/project\n");
}
```

## Testing Strategy

### Unit Tests
```c
// tests/test_file_analyzer.c
#include "../tools/file_analyzer/file_analyzer.h"
#include "../common/error.h"
#include <assert.h>

void test_file_analyzer(void) {
    printf("Testing file analyzer...\n");

    // Test with known files
    char *test_files[] = {"test_file.txt", "test_file.c"};
    FileAnalysis *analysis = analyze_files(test_files, 2);

    assert(analysis != NULL);
    assert(analysis->file_count == 2);
    assert(analysis->total_size > 0);

    FREE(analysis);
    printf("File analyzer tests passed!\n");
}
```

### Integration Tests
```c
// tests/test_integration.c
#include "../config.h"

void test_full_workflow(void) {
    printf("Testing full workflow...\n");

    // Test hash generation
    system("./bin/devtools hash-generate Makefile");

    // Test text processing
    system("./bin/devtools text-processor -n \"printf\" -r \"fprintf\" *.c");

    // Test file analysis
    system("./bin/devtools file-analyzer src/");

    printf("Integration tests completed!\n");
}
```

## Building and Installation

### Compilation
```bash
# Clone and build
git clone <repository-url>
cd devtools
make

# Run tests
make test

# Install system-wide
sudo make install
```

### Usage Examples
```bash
# File analysis
devtools file-analyzer /path/to/project

# Generate file hashes
devtools hash-generate --sha256 important_file.zip

# Text processing
devtools text-processor -r "old_function" -n "new_function" *.c

# Code metrics
devtools code-metrics --complexity src/

# JSON validation
devtools json-validator config.json

# Help for specific tool
devtools hash-generate --help
```

## Evaluation Criteria

### Functionality (40%)
- All 8 core tools implemented correctly
- Advanced features working properly
- Cross-platform compatibility
- Robust error handling

### Code Quality (30%)
- Modular, well-organized code
- Consistent coding style
- Comprehensive documentation
- Memory leak-free implementation

### Architecture (20%)
- Plugin system extensible
- Configuration management
- Logging and error systems
- Build system completeness

### User Experience (10%)
- Intuitive command-line interface
- Clear help documentation
- Meaningful error messages
- Performance considerations

## Bonus Features

### Additional Tools
- **Git Integration**: Basic git operations
- **Docker Helper**: Container management utilities
- **SSH Key Manager**: SSH key operations
- **Backup Tool**: File backup and restore

### Advanced Features
- **GUI Interface**: Optional graphical interface
- **Web Interface**: Web-based tool access
- **Remote Operations**: Network file operations
- **Parallel Processing**: Multi-threaded operations

### Integration Features
- **IDE Integration**: Plugin for popular IDEs
- **CI/CD Integration**: Build pipeline tools
- **Cloud Storage**: Integration with cloud services

## Submission Checklist

- [ ] All 8 core tools implemented
- [ ] Plugin system functional
- [ ] Configuration management
- [ ] Complete test suite
- [ ] Comprehensive documentation
- [ ] Installation script
- [ ] User manual
- [ ] Performance benchmarks

## Future Extensions

### Potential Enhancements
1. **Machine Learning**: Code analysis with ML
2. **Cloud Integration**: Remote file operations
3. **Collaboration**: Shared configuration and results
4. **Mobile**: Mobile app companion
5. **AI Assistant**: Intelligent code suggestions

### Community Features
1. **Plugin Repository**: Community-contributed tools
2. **Documentation Wiki**: Community-maintained docs
3. **Issue Tracking**: Bug reports and feature requests
4. **Contributor Guide**: Guidelines for contributions

---

**🎯 Ready to build your ultimate C programming project?**

This DevTools Utility Suite will be your masterpiece - demonstrating mastery of all C programming concepts and creating a tool that developers will actually use!

Good luck, and happy coding! 🚀