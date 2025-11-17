#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>

#define MAX_LOG_MESSAGE 256

typedef enum {
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR,
    LOG_CRITICAL
} LogLevel;

const char* log_level_names[] = {"DEBUG", "INFO", "WARN", "ERROR", "CRITICAL"};

typedef struct {
    FILE *file;
    LogLevel min_level;
    int console_output;
} Logger;

int init_logger(Logger *logger, const char *filename, LogLevel min_level) {
    logger->file = fopen(filename, "a");
    if (!logger->file) {
        return 0;
    }
    logger->min_level = min_level;
    logger->console_output = 1;
    return 1;
}

void log_message(Logger *logger, LogLevel level, const char *format, ...) {
    if (level < logger->min_level) return;

    va_list args;
    time_t now;
    struct tm *timeinfo;
    char timestamp[32];
    char message[MAX_LOG_MESSAGE];

    time(&now);
    timeinfo = localtime(&now);
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeinfo);

    va_start(args, format);
    vsnprintf(message, sizeof(message), format, args);
    va_end(args);

    // Write to file
    fprintf(logger->file, "[%s] %s: %s\n", timestamp, log_level_names[level], message);
    fflush(logger->file);

    // Also write to console if enabled
    if (logger->console_output) {
        printf("[%s] %s: %s\n", timestamp, log_level_names[level], message);
    }
}

void close_logger(Logger *logger) {
    if (logger->file) {
        fclose(logger->file);
        logger->file = NULL;
    }
}

int main() {
    Logger logger;

    printf("Logging System Demo\n");
    printf("==================\n");

    if (!init_logger(&logger, "app.log", LOG_INFO)) {
        printf("Failed to initialize logger\n");
        return 1;
    }

    // Simulate application with different log levels
    log_message(&logger, LOG_INFO, "Application starting up");
    log_message(&logger, LOG_DEBUG, "Debug: Internal variables initialized");
    log_message(&logger, LOG_INFO, "Connecting to database");

    log_message(&logger, LOG_WARNING, "Configuration file missing, using defaults");

    log_message(&logger, LOG_INFO, "Database connection established");
    log_message(&logger, LOG_ERROR, "Failed to load user preferences");

    log_message(&logger, LOG_CRITICAL, "System running out of memory");

    log_message(&logger, LOG_INFO, "Application shutting down");

    close_logger(&logger);
    printf("\nAll log messages written to app.log\n");

    return 0;
}