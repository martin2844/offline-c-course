#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 256
#define MAX_KEY_LENGTH 50
#define MAX_VALUE_LENGTH 100

typedef struct {
    char server[50];
    int port;
    char database[50];
    char username[50];
    int timeout;
    int debug;
} Config;

void trim(char *str) {
    char *end;
    while (isspace((unsigned char)*str)) str++;
    if (*str == 0) return;
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;
    *(end + 1) = '\0';
}

void parse_config(const char *filename, Config *config) {
    FILE *file;
    char line[MAX_LINE_LENGTH];
    char key[MAX_KEY_LENGTH];
    char value[MAX_VALUE_LENGTH];

    // Set defaults
    strcpy(config->server, "localhost");
    config->port = 8080;
    strcpy(config->database, "default");
    strcpy(config->username, "admin");
    config->timeout = 30;
    config->debug = 0;

    file = fopen(filename, "r");
    if (!file) {
        printf("Config file not found, using defaults.\n");
        return;
    }

    while (fgets(line, sizeof(line), file)) {
        // Skip comments and empty lines
        if (line[0] == '#' || line[0] == '\n') continue;

        char *equals = strchr(line, '=');
        if (!equals) continue;

        *equals = '\0';
        strcpy(key, line);
        strcpy(value, equals + 1);

        trim(key);
        trim(value);
        value[strcspn(value, "\n")] = '\0';

        if (strcmp(key, "server") == 0) {
            strcpy(config->server, value);
        } else if (strcmp(key, "port") == 0) {
            config->port = atoi(value);
        } else if (strcmp(key, "database") == 0) {
            strcpy(config->database, value);
        } else if (strcmp(key, "username") == 0) {
            strcpy(config->username, value);
        } else if (strcmp(key, "timeout") == 0) {
            config->timeout = atoi(value);
        } else if (strcmp(key, "debug") == 0) {
            config->debug = (strcmp(value, "true") == 0 || strcmp(value, "1") == 0);
        }
    }

    fclose(file);
}

void display_config(const Config *config) {
    printf("Configuration:\n");
    printf("=============\n");
    printf("Server: %s\n", config->server);
    printf("Port: %d\n", config->port);
    printf("Database: %s\n", config->database);
    printf("Username: %s\n", config->username);
    printf("Timeout: %d seconds\n", config->timeout);
    printf("Debug Mode: %s\n", config->debug ? "ON" : "OFF");
}

int main() {
    Config config;

    // Create sample config file
    FILE *sample = fopen("config.txt", "w");
    if (sample) {
        fprintf(sample, "# Sample Configuration File\n");
        fprintf(sample, "server=example.com\n");
        fprintf(sample, "port=443\n");
        fprintf(sample, "database=production\n");
        fprintf(sample, "username=admin\n");
        fprintf(sample, "timeout=60\n");
        fprintf(sample, "debug=true\n");
        fclose(sample);
        printf("Created sample config.txt\n");
    }

    parse_config("config.txt", &config);
    display_config(&config);

    return 0;
}