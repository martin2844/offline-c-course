// Chapter 13: System Programming - Simple Shell Implementation
// Solution to Exercise 13.1: Create a parent-child process pair that communicates through pipes

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGS 64
#define PROMPT "myshell> "

void print_prompt() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s%s$ ", cwd, PROMPT);
    } else {
        printf("%s", PROMPT);
    }
    fflush(stdout);
}

void parse_command(char* command, char** args) {
    int i = 0;
    char* token = strtok(command, " \t\n");

    while (token != NULL && i < MAX_ARGS - 1) {
        args[i++] = token;
        token = strtok(NULL, " \t\n");
    }
    args[i] = NULL;
}

int execute_command(char** args) {
    if (args[0] == NULL) {
        return 0;  // Empty command
    }

    // Built-in commands
    if (strcmp(args[0], "cd") == 0) {
        if (args[1] == NULL) {
            chdir(getenv("HOME"));
        } else {
            if (chdir(args[1]) != 0) {
                perror("cd");
            }
        }
        return 0;
    }

    if (strcmp(args[0], "exit") == 0) {
        exit(0);
    }

    if (strcmp(args[0], "pwd") == 0) {
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("%s\n", cwd);
        } else {
            perror("pwd");
        }
        return 0;
    }

    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        execvp(args[0], args);
        // If execvp returns, there was an error
        perror("execvp");
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        // Fork failed
        perror("fork");
    } else {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
    }

    return 0;
}

// Demonstration of pipe communication between parent and child
void demonstrate_pipe_communication() {
    printf("=== Pipe Communication Demonstration ===\n");

    int pipefd[2];
    pid_t pid;
    char write_msg[] = "Hello from parent process!";
    char read_msg[100];

    // Create pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process - read from pipe
        close(pipefd[1]);  // Close write end

        ssize_t bytes_read = read(pipefd[0], read_msg, sizeof(read_msg));
        if (bytes_read > 0) {
            read_msg[bytes_read] = '\0';
            printf("Child received: %s\n", read_msg);
        }

        close(pipefd[0]);
        exit(EXIT_SUCCESS);
    } else {
        // Parent process - write to pipe
        close(pipefd[0]);  // Close read end

        printf("Parent writing to pipe: %s\n", write_msg);
        write(pipefd[1], write_msg, strlen(write_msg) + 1);

        close(pipefd[1]);
        wait(NULL);  // Wait for child
    }
}

int main() {
    printf("Simple Shell Implementation\n");
    printf("===========================\n");

    // First, demonstrate pipe communication
    demonstrate_pipe_communication();
    printf("\nStarting interactive shell...\n\n");

    char command[MAX_COMMAND_LENGTH];
    char* args[MAX_ARGS];

    while (1) {
        print_prompt();

        if (fgets(command, sizeof(command), stdin) == NULL) {
            printf("\n");
            break;  // EOF (Ctrl+D)
        }

        // Remove newline character
        command[strcspn(command, "\n")] = '\0';

        // Skip empty commands
        if (strlen(command) == 0) {
            continue;
        }

        parse_command(command, args);
        execute_command(args);
    }

    printf("Goodbye!\n");
    return 0;
}