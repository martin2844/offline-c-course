#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char input_file[256];
    char output_file[256];
    int verbose;
    int number;
    int help;
    int version;
    char mode[50];
} Config;

void init_config(Config *config) {
    memset(config, 0, sizeof(Config));
}

void print_help(const char *program_name) {
    printf("Usage: %s [options]\n\n", program_name);
    printf("Options:\n");
    printf("  -h, --help          Show this help message\n");
    printf("  -v, --verbose       Enable verbose output\n");
    printf("  -i, --input FILE    Input file path\n");
    printf("  -o, --output FILE   Output file path\n");
    printf("  -n, --number NUM    Number to process\n");
    printf("  -m, --mode MODE     Processing mode\n");
    printf("  --version           Show version information\n");
}

void print_version() {
    printf("Advanced Argument Parser v2.0\n");
    printf("Built: %s %s\n", __DATE__, __TIME__);
}

void print_config(const Config *config) {
    printf("Configuration:\n");
    printf("  Input file: %s\n", strlen(config->input_file) ? config->input_file : "(none)");
    printf("  Output file: %s\n", strlen(config->output_file) ? config->output_file : "(none)");
    printf("  Verbose: %s\n", config->verbose ? "enabled" : "disabled");
    printf("  Number: %s\n", config->number ? "specified" : "not specified");
    if (config->number) {
        printf("  Number value: %d\n", config->number);
    }
    printf("  Mode: %s\n", strlen(config->mode) ? config->mode : "default");
}

int parse_arguments(int argc, char *argv[], Config *config) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            config->help = 1;
            return 1;
        }
        else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--verbose") == 0) {
            config->verbose = 1;
        }
        else if (strcmp(argv[i], "--version") == 0) {
            config->version = 1;
            return 1;
        }
        else if (strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--input") == 0) {
            if (i + 1 < argc) {
                strncpy(config->input_file, argv[++i], sizeof(config->input_file) - 1);
            } else {
                printf("Error: %s requires a filename\n", argv[i]);
                return 0;
            }
        }
        else if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0) {
            if (i + 1 < argc) {
                strncpy(config->output_file, argv[++i], sizeof(config->output_file) - 1);
            } else {
                printf("Error: %s requires a filename\n", argv[i]);
                return 0;
            }
        }
        else if (strcmp(argv[i], "-n") == 0 || strcmp(argv[i], "--number") == 0) {
            if (i + 1 < argc) {
                config->number = atoi(argv[++i]);
            } else {
                printf("Error: %s requires a number\n", argv[i]);
                return 0;
            }
        }
        else if (strcmp(argv[i], "-m") == 0 || strcmp(argv[i], "--mode") == 0) {
            if (i + 1 < argc) {
                strncpy(config->mode, argv[++i], sizeof(config->mode) - 1);
            } else {
                printf("Error: %s requires a mode\n", argv[i]);
                return 0;
            }
        }
        else {
            printf("Error: Unknown option '%s'\n", argv[i]);
            print_help(argv[0]);
            return 0;
        }
    }

    return 1;
}

int main(int argc, char *argv[]) {
    Config config;

    printf("Advanced Argument Parser\n");
    printf("=======================\n");

    init_config(&config);

    if (argc < 2) {
        print_help(argv[0]);
        return 0;
    }

    if (!parse_arguments(argc, argv, &config)) {
        return 1;
    }

    if (config.help) {
        print_help(argv[0]);
        return 0;
    }

    if (config.version) {
        print_version();
        return 0;
    }

    print_config(&config);

    if (config.verbose) {
        printf("\nVerbose mode is enabled\n");
        printf("Arguments processed successfully\n");
        printf("Ready to execute main functionality\n");
    }

    return 0;
}