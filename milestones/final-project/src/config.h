#ifndef DEVTOOLS_CONFIG_H
#define DEVTOOLS_CONFIG_H

#include <stdbool.h>
#include <stdio.h>

// Version information
#define DEVTOOLS_VERSION "1.0.0"
#define DEVTOOLS_NAME "DevTools Utility Suite"

// System limits
#define MAX_TOOLS 50
#define MAX_PATH_LENGTH 1024
#define MAX_LINE_LENGTH 4096
#define MAX_STRING_LENGTH 256
#define MAX_ARGUMENTS 100

// Return codes
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

// Buffer sizes for hashing
#define MD5_DIGEST_LENGTH 32
#define SHA1_DIGEST_LENGTH 40
#define SHA256_DIGEST_LENGTH 64
#define SHA512_DIGEST_LENGTH 128

// Color definitions
#define COLOR_RESET "\033[0m"
#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_BLUE "\033[34m"
#define COLOR_MAGENTA "\033[35m"
#define COLOR_CYAN "\033[36m"
#define COLOR_WHITE "\033[37m"

// Error codes
typedef enum {
    SUCCESS = 0,
    ERROR_INVALID_ARGUMENT = -1,
    ERROR_FILE_NOT_FOUND = -2,
    ERROR_PERMISSION_DENIED = -3,
    ERROR_MEMORY_ALLOCATION = -4,
    ERROR_PARSE_ERROR = -5,
    ERROR_NETWORK_ERROR = -6,
    ERROR_TIMEOUT = -7,
    ERROR_PLUGIN_ERROR = -8,
    ERROR_UNKNOWN = -9
} ErrorCode;

// Log levels
typedef enum {
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR,
    LOG_FATAL
} LogLevel;

// Hash types
typedef enum {
    HASH_MD5,
    HASH_SHA1,
    HASH_SHA256,
    HASH_SHA512
} HashType;

// JSON token types
typedef enum {
    JSON_NULL,
    JSON_BOOL,
    JSON_NUMBER,
    JSON_STRING,
    JSON_ARRAY_START,
    JSON_ARRAY_END,
    JSON_OBJECT_START,
    JSON_OBJECT_END,
    JSON_COLON,
    JSON_COMMA,
    JSON_EOF,
    JSON_ERROR
} JsonTokenType;

// Configuration structure
typedef struct {
    char config_file[MAX_PATH_LENGTH];
    char log_file[MAX_PATH_LENGTH];
    bool verbose;
    bool quiet;
    bool color_output;
    int log_level;
    int tab_size;
    bool confirm_operations;
} DevToolsConfig;

// Tool structure
typedef struct {
    char name[64];
    char description[256];
    char version[16];
    char author[64];
    int (*execute)(int argc, char *argv[]);
    void (*help)(void);
    void (*version)(void);
} Tool;

// Command structure
typedef struct {
    Tool *tool;
    int argc;
    char **argv;
    Error error;
} Command;

// File analysis structure
typedef struct {
    size_t file_count;
    size_t total_size;
    size_t total_lines;
    char file_types[256][32];
    size_t type_counts[256];
    int unique_types;
    time_t newest_file;
    time_t oldest_file;
} FileAnalysis;

// Text processor configuration
typedef struct {
    char search_term[MAX_LINE_LENGTH];
    char replace_term[MAX_LINE_LENGTH];
    bool case_sensitive;
    bool whole_words;
    bool regex_mode;
    bool backup_files;
    bool recursive;
    char file_pattern[MAX_PATH_LENGTH];
    int context_lines;
} TextProcessorConfig;

// JSON validation result
typedef struct {
    bool valid;
    int line_number;
    int column;
    char error_message[MAX_STRING_LENGTH];
} JsonValidationResult;

// Color structure
typedef struct {
    char name[32];
    char hex[8];
    int rgb[3];
    float hsl[3];
} Color;

// Color palette structure
typedef struct {
    char name[64];
    Color colors[16];
    int color_count;
    char scheme[32]; // "monochromatic", "analogous", "complementary", "triadic"
} ColorPalette;

// Global configuration (defined in main.c)
extern DevToolsConfig g_config;

#endif // DEVTOOLS_CONFIG_H