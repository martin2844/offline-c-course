#include "config.h"
#include "common/utils.h"
#include "common/error.h"
#include "common/logging.h"
#include "plugins/plugin_manager.h"

#include <getopt.h>
#include <string.h>

DevToolsConfig g_config;

// Forward declarations for tool functions
int file_analyzer_execute(int argc, char *argv[]);
void file_analyzer_help(void);

int text_processor_execute(int argc, char *argv[]);
void text_processor_help(void);

int hash_generator_execute(int argc, char *argv[]);
void hash_generator_help(void);

int json_validator_execute(int argc, char *argv[]);
void json_validator_help(void);

int base64_encoder_execute(int argc, char *argv[]);
void base64_encoder_help(void);

int url_encoder_execute(int argc, char *argv[]);
void url_encoder_help(void);

int code_metrics_execute(int argc, char *argv[]);
void code_metrics_help(void);

int color_palette_execute(int argc, char *argv[]);
void color_palette_help(void);

// Built-in tools array
static Tool builtin_tools[] = {
    {
        .name = "file-analyzer",
        .description = "Analyze files and directories for statistics",
        .execute = file_analyzer_execute,
        .help = file_analyzer_help
    },
    {
        .name = "text-processor",
        .description = "Process and transform text files",
        .execute = text_processor_execute,
        .help = text_processor_help
    },
    {
        .name = "hash-generate",
        .description = "Generate file hashes (MD5, SHA1, SHA256)",
        .execute = hash_generator_execute,
        .help = hash_generator_help
    },
    {
        .name = "json-validator",
        .description = "Validate and pretty-print JSON files",
        .execute = json_validator_execute,
        .help = json_validator_help
    },
    {
        .name = "base64-encoder",
        .description = "Encode and decode Base64 data",
        .execute = base64_encoder_execute,
        .help = base64_encoder_help
    },
    {
        .name = "url-encoder",
        .description = "Encode and decode URLs",
        .execute = url_encoder_execute,
        .help = url_encoder_help
    },
    {
        .name = "code-metrics",
        .description = "Calculate code complexity and statistics",
        .execute = code_metrics_execute,
        .help = code_metrics_help
    },
    {
        .name = "color-palette",
        .description = "Generate and display color palettes",
        .execute = color_palette_execute,
        .help = color_palette_help
    }
};

bool init_devtools(void) {
    // Set default configuration
    strcpy(g_config.config_file, "~/.devtoolsrc");
    strcpy(g_config.log_file, "devtools.log");
    g_config.verbose = false;
    g_config.quiet = false;
    g_config.log_level = LOG_INFO;

    // Initialize logging
    if (!init_logging(g_config.log_file, g_config.log_level)) {
        fprintf(stderr, "Warning: Failed to initialize logging\n");
    }

    // Initialize plugin manager
    if (!plugin_manager_init()) {
        LOG_ERROR("Failed to initialize plugin manager");
        return false;
    }

    // Register built-in tools
    for (int i = 0; i < sizeof(builtin_tools) / sizeof(builtin_tools[0]); i++) {
        if (!register_tool(&builtin_tools[i])) {
            LOG_WARN("Failed to register tool: %s", builtin_tools[i].name);
        }
    }

    // Load external plugins
    load_plugins();

    LOG_INFO("DevTools initialized successfully");
    return true;
}

void cleanup_devtools(void) {
    plugin_manager_cleanup();
    cleanup_logging();
}

void print_version(void) {
    printf("DevTools Utility Suite %s\n", DEVTOOLS_VERSION);
    printf("Built with %s on %s\n", __VERSION__, __DATE__);
    printf("© 2024 DevTools Project\n");
}

void print_help(void) {
    printf("DevTools Utility Suite %s\n\n", DEVTOOLS_VERSION);
    printf("Usage: devtools [options] <tool> [tool-options]\n\n");
    printf("Global Options:\n");
    printf("  -h, --help          Show this help message\n");
    printf("  -v, --verbose       Enable verbose output\n");
    printf("  -q, --quiet         Suppress non-error output\n");
    printf("  --version          Show version information\n");
    printf("  --list-tools       List all available tools\n");
    printf("  --config FILE      Use specified config file\n");
    printf("\nAvailable Tools:\n");

    plugin_manager_list_tools();

    printf("\nExamples:\n");
    printf("  devtools file-analyzer /path/to/project\n");
    printf("  devtools hash-generate --sha256 file.zip\n");
    printf("  devtools text-processor -r \"old\" -n \"new\" *.c\n");
    printf("  devtools json-validator config.json\n");
}

Command parse_arguments(int argc, char *argv[]) {
    Command cmd = {0};

    if (argc < 2) {
        print_help();
        SET_ERROR(&cmd.error, ERROR_INVALID_ARGUMENT, "No arguments provided");
        return cmd;
    }

    // Parse global options
    int c;
    int option_index = 0;
    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"verbose", no_argument, 0, 'v'},
        {"quiet", no_argument, 0, 'q'},
        {"version", no_argument, 0, 1000},
        {"list-tools", no_argument, 0, 1001},
        {"config", required_argument, 0, 'c'},
        {0, 0, 0, 0}
    };

    while ((c = getopt_long(argc, argv, "hvq", long_options, &option_index)) != -1) {
        switch (c) {
            case 'h':
                print_help();
                exit(EXIT_SUCCESS);
                break;

            case 'v':
                g_config.verbose = true;
                break;

            case 'q':
                g_config.quiet = true;
                break;

            case 1000: // --version
                print_version();
                exit(EXIT_SUCCESS);
                break;

            case 1001: // --list-tools
                plugin_manager_list_tools();
                exit(EXIT_SUCCESS);
                break;

            case 'c':
                strncpy(g_config.config_file, optarg, sizeof(g_config.config_file) - 1);
                break;

            case '?':
                SET_ERROR(&cmd.error, ERROR_INVALID_ARGUMENT, "Unknown option");
                return cmd;

            default:
                break;
        }
    }

    if (optind >= argc) {
        SET_ERROR(&cmd.error, ERROR_INVALID_ARGUMENT, "No tool specified");
        return cmd;
    }

    // Parse tool command
    char *tool_name = argv[optind];
    cmd.tool = find_tool(tool_name);
    if (!cmd.tool) {
        SET_ERROR(&cmd.error, ERROR_INVALID_ARGUMENT, "Unknown tool: %s", tool_name);
        return cmd;
    }

    cmd.argc = argc - optind;
    cmd.argv = argv + optind;

    return cmd;
}

int execute_command(const Command *cmd) {
    if (!cmd || !cmd->tool) {
        LOG_ERROR("No valid command to execute");
        return ERROR_INVALID_ARGUMENT;
    }

    LOG_INFO("Executing tool: %s", cmd->tool->name);

    int result = cmd->tool->execute(cmd->argc - 1, cmd->argv + 1);

    if (result != SUCCESS) {
        LOG_ERROR("Tool %s failed with error: %d", cmd->tool->name, result);
    } else {
        LOG_INFO("Tool %s completed successfully", cmd->tool->name);
    }

    return result;
}

int main(int argc, char *argv[]) {
    printf("DevTools Utility Suite %s\n", DEVTOOLS_VERSION);
    printf("=================================\n\n");

    // Initialize core systems
    if (!init_devtools()) {
        fprintf(stderr, "Failed to initialize DevTools\n");
        return EXIT_FAILURE;
    }

    // Parse command line arguments
    Command cmd = parse_arguments(argc, argv);
    if (cmd.error.code != SUCCESS) {
        print_error(&cmd.error);
        cleanup_devtools();
        return EXIT_FAILURE;
    }

    // Execute requested command
    int result = execute_command(&cmd);

    // Cleanup
    cleanup_devtools();

    return (result == SUCCESS) ? EXIT_SUCCESS : EXIT_FAILURE;
}