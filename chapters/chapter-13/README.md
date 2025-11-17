# Chapter 13: System Programming

## Learning Objectives
By the end of this chapter, you will be able to:
- Use system calls for process management and information retrieval
- Implement basic inter-process communication mechanisms
- Create networked applications using sockets
- Work with file systems and system APIs
- Understand multi-threading concepts and synchronization

## Introduction to System Programming

System programming involves writing software that interacts directly with the operating system kernel and hardware. It's the foundation for system utilities, device drivers, servers, and performance-critical applications.

### The Operating System Interface

When you write most C programs, you work in "user space" with the standard library providing abstractions. System programming drops down a level to interact directly with the operating system kernel through **system calls**.

```
Your C Program
    ↓
Standard Library (stdio, stdlib, etc.)
    ↓
System Call Interface (API)
    ↓
Operating System Kernel
    ↓
Hardware (CPU, Memory, Disk, Network)
```

**System Calls** are the gateway between user programs and the kernel:
- **File Operations**: open(), read(), write(), close()
- **Process Management**: fork(), exec(), wait(), exit()
- **Memory Management**: malloc(), brk(), mmap()
- **Communication**: pipe(), socket(), signal()
- **Information**: getpid(), getuid(), time()

### Why System Programming Matters

1. **Performance**: Direct access to system resources for maximum efficiency
   - **No Abstraction Overhead**: Direct system calls avoid library overhead
   - **Resource Control**: Fine-grained control over CPU, memory, and I/O
   - **Real-time Needs**: Critical for applications requiring precise timing

2. **Control**: Fine-grained control over system behavior and resources
   - **Process Creation**: Launch and manage other programs
   - **Resource Limits**: Control memory usage, file handles, CPU time
   - **Priority Management**: Set scheduling priorities for performance

3. **Integration**: Building software that works closely with the OS
   - **System Utilities**: Commands like ls, ps, grep
   - **Servers**: Web servers, database servers, daemons
   - **Device Drivers**: Software to control hardware devices

4. **Foundation**: Essential for systems programming, embedded development, and server applications
   - **Infrastructure**: Building blocks of modern computing
   - **Embedded Systems**: Programming microcontrollers and IoT devices
   - **Cloud Computing**: Virtualization, containers, orchestration

### Unix Philosophy and System Programming

Unix system programming follows key principles that have influenced decades of software development:

**1. Everything is a File**
- Files, directories, devices, pipes, sockets all appear as files
- Unified interface for I/O operations
- Simple, consistent API across different resources

**2. Small, Single-Purpose Programs**
- Each tool does one thing well
- Combine tools using pipes and redirection
- Composability leads to powerful systems

**3. Text-Based Interfaces**
- Human-readable formats
- Easy to debug and manipulate
- Universal compatibility

### System Programming vs Application Programming

| Aspect | Application Programming | System Programming |
|--------|-------------------------|-------------------|
| **Focus** | User features, business logic | System resources, performance |
| **Libraries** | Frameworks, GUI libraries | System calls, kernel APIs |
| **Error Handling** | User-friendly messages | errno, system error codes |
| **Portability** | Cross-platform compatibility | Platform-specific optimization |
| **Performance** | Generally adequate | Critical optimization needed |
| **Debugging** | Application debuggers | System debuggers, strace, lsof |
| **Examples** | Web apps, desktop apps | Compilers, shells, servers |

### Cross-Platform Considerations

While system programming often involves platform-specific code, understanding the differences helps write portable software:

**POSIX (Portable Operating System Interface)**
- Standard for Unix-like systems (Linux, macOS, BSD)
- Defines common system calls and behavior
- Enables code portability across platforms

**Major System Programming Platforms:**
- **Linux**: Open source, extensive documentation, server dominance
- **Windows**: Different API (Win32), but POSIX compatibility layers available
- **macOS**: Unix-based, good POSIX support
- **Embedded**: Bare metal or RTOS (Real-Time Operating Systems)

### System Programming Safety and Security

System programming requires extra care due to the potential impact:

**Security Considerations:**
- **Privilege Escalation**: Running with elevated permissions
- **Resource Exhaustion**: Preventing denial of service
- **Input Validation**: System calls can be attack vectors
- **Buffer Overflows**: Common in low-level code

**Safety Practices:**
- **Error Checking**: Always check system call return values
- **Resource Cleanup**: Properly close files, free memory
- **Privilege Minimization**: Drop unnecessary privileges
- **Defensive Programming**: Assume inputs can be malicious

### Development Tools for System Programming

**Essential Tools:**
- **Man Pages**: `man open`, `man fork` for documentation
- **Strace**: Trace system calls made by a program
- **GDB**: Debug system-level issues
- **Valgrind**: Memory error detection
- **Make**: Build system for managing compilation

**Example: Using strace to understand system calls**
```bash
# Trace all system calls made by 'ls'
strace ls

# Trace specific system calls
strace -e trace=open,read,write ls

# Count system calls
strace -c ls
```

### Common System Programming Patterns

**1. Error Handling Pattern**
```c
// Standard error checking pattern
if (system_call(...) == -1) {
    perror("System call failed");
    exit(EXIT_FAILURE);
}
```

**2. Resource Management Pattern**
```c
// Ensure resources are cleaned up
FILE *file = fopen("data.txt", "r");
if (!file) {
    perror("fopen failed");
    return -1;
}

// ... use file ...

fclose(file);  // Always close
```

**3. Process Creation Pattern**
```c
// Fork-exec-wait pattern
pid_t pid = fork();
if (pid == -1) {
    perror("fork failed");
    exit(EXIT_FAILURE);
}

if (pid == 0) {
    // Child process
    execlp("program", "program", NULL);
    perror("exec failed");  // Only reached if exec fails
    exit(EXIT_FAILURE);
}

// Parent process
int status;
waitpid(pid, &status, 0);
```

This foundation prepares you to understand the practical system programming examples that follow.

## Process Management

### Process Information and Control

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h>

// Get system information
void print_system_info() {
    printf("=== System Information ===\n");
    printf("Process ID (PID): %d\n", getpid());
    printf("Parent Process ID (PPID): %d\n", getppid());
    printf("User ID (UID): %d\n", getuid());
    printf("Group ID (GID): %d\n", getgid());
    printf("Effective User ID: %d\n", geteuid());
    printf("Effective Group ID: %d\n", getegid());
}

// Process creation and management
void process_demo() {
    printf("\n=== Process Creation Demo ===\n");

    pid_t pid = fork();

    if (pid < 0) {
        // Fork failed
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process
        printf("Child process:\n");
        printf("  PID: %d\n", getpid());
        printf("  Parent PID: %d\n", getppid());

        // Sleep for a moment
        sleep(2);
        printf("Child process finishing...\n");
        exit(0);
    } else {
        // Parent process
        printf("Parent process:\n");
        printf("  PID: %d\n", getpid());
        printf("  Child PID: %d\n", pid);

        // Wait for child to finish
        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            printf("Child exited with status: %d\n", WEXITSTATUS(status));
        }
    }
}

// Execute external commands
void exec_demo() {
    printf("\n=== Process Execution Demo ===\n");

    pid_t pid = fork();

    if (pid == 0) {
        // Child process executes command
        printf("Child executing 'ls -la'...\n");

        // Execute the ls command
        execlp("ls", "ls", "-la", NULL);

        // This line only reached if execlp fails
        perror("execlp failed");
        exit(1);
    } else if (pid > 0) {
        // Parent waits for child
        int status;
        waitpid(pid, &status, 0);
        printf("Command execution completed.\n");
    }
}

// Signal handling
volatile sig_atomic_t signal_received = 0;

void signal_handler(int signum) {
    signal_received = signum;
    printf("\nReceived signal: %d\n", signum);
}

void signal_demo() {
    printf("\n=== Signal Handling Demo ===\n");

    // Set up signal handler
    struct sigaction sa;
    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        return;
    }

    printf("Signal handler installed. Press Ctrl+C to test.\n");
    printf("Main process PID: %d\n", getpid());
    printf("Sleeping for 10 seconds... (try Ctrl+C)\n");

    // Sleep in 1-second intervals to check for signals
    for (int i = 0; i < 10; i++) {
        sleep(1);
        if (signal_received) {
            printf("Signal detected! Breaking out of sleep.\n");
            break;
        }
        printf("%d seconds remaining...\n", 10 - i - 1);
    }

    printf("Signal demo completed.\n");
}

// Process timing and measurement
void timing_demo() {
    printf("\n=== Process Timing Demo ===\n");

    clock_t start, end;
    double cpu_time_used;

    // Measure CPU time for computation
    start = clock();

    // Do some computation
    volatile long sum = 0;
    for (int i = 0; i < 100000000; i++) {
        sum += i;
    }

    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Computation completed.\n");
    printf("Sum: %ld\n", sum);
    printf("CPU time used: %f seconds\n", cpu_time_used);

    // Measure wall clock time
    struct timespec wall_start, wall_end;
    clock_gettime(CLOCK_MONOTONIC, &wall_start);

    // Simulate I/O bound operation
    printf("Simulating I/O operation (sleep for 2 seconds)...\n");
    sleep(2);

    clock_gettime(CLOCK_MONOTONIC, &wall_end);

    double wall_time = (wall_end.tv_sec - wall_start.tv_sec) +
                      (wall_end.tv_nsec - wall_start.tv_nsec) / 1e9;

    printf("Wall clock time: %f seconds\n", wall_time);
}

int main() {
    printf("System Programming Demo\n");
    printf("=======================\n");

    // System information
    print_system_info();

    // Process creation
    process_demo();

    // Process execution
    exec_demo();

    // Signal handling
    signal_demo();

    // Timing and measurement
    timing_demo();

    printf("\nAll demos completed successfully!\n");

    return 0;
}
```

### Environment and Configuration

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Environment variable operations
void environment_demo() {
    printf("=== Environment Variables ===\n");

    // Print all environment variables
    printf("\nAll environment variables:\n");
    extern char **environ;

    for (int i = 0; environ[i] != NULL; i++) {
        printf("%s\n", environ[i]);
    }

    // Get specific environment variables
    printf("\nSpecific environment variables:\n");
    printf("HOME: %s\n", getenv("HOME"));
    printf("PATH: %s\n", getenv("PATH"));
    printf("USER: %s\n", getenv("USER"));
    printf("SHELL: %s\n", getenv("SHELL"));

    // Set a new environment variable
    printf("\nSetting new environment variable...\n");
    if (setenv("MY_VAR", "Hello from C", 1) == 0) {
        printf("MY_VAR set to: %s\n", getenv("MY_VAR"));
    }

    // Remove environment variable
    printf("\nRemoving environment variable...\n");
    if (unsetenv("MY_VAR") == 0) {
        printf("MY_VAR removed: %s\n", getenv("MY_VAR") ? "Still exists" : "Removed successfully");
    }
}

// Working directory operations
void directory_demo() {
    printf("\n=== Directory Operations ===\n");

    char current_dir[1024];

    // Get current working directory
    if (getcwd(current_dir, sizeof(current_dir)) != NULL) {
        printf("Current working directory: %s\n", current_dir);
    } else {
        perror("getcwd failed");
    }

    // Change directory (if possible)
    printf("\nAttempting to change to /tmp...\n");
    if (chdir("/tmp") == 0) {
        if (getcwd(current_dir, sizeof(current_dir)) != NULL) {
            printf("New working directory: %s\n", current_dir);
        }

        // Change back
        printf("Changing back to original directory...\n");
        chdir("..");
        // In a real scenario, you'd want to save and restore the original path
    } else {
        printf("Could not change to /tmp\n");
    }
}

// System resource limits
void limits_demo() {
    printf("\n=== System Resource Limits ===\n");

    // Get various system limits
    long max_open_files = sysconf(_SC_OPEN_MAX);
    long max_processes = sysconf(_SC_CHILD_MAX);
    long clock_ticks = sysconf(_SC_CLK_TCK);
    long page_size = sysconf(_SC_PAGESIZE);

    printf("Maximum open files: %ld\n", max_open_files);
    printf("Maximum processes: %ld\n", max_processes);
    printf("Clock ticks per second: %ld\n", clock_ticks);
    printf("System page size: %ld bytes\n", page_size);

    // Host information
    char hostname[256];
    if (gethostname(hostname, sizeof(hostname)) == 0) {
        printf("Hostname: %s\n", hostname);
    }

    // System name and version
    printf("\nSystem information:\n");
    printf("POSIX version: %ld\n", sysconf(_SC_VERSION));
    printf("OS name (POSIX): %s\n",
#ifdef _POSIX_VERSION
           "POSIX compliant"
#else
           "Non-POSIX"
#endif
    );
}

// Command line argument parsing
void argument_demo(int argc, char *argv[]) {
    printf("\n=== Command Line Arguments ===\n");
    printf("Program name: %s\n", argv[0]);
    printf("Number of arguments: %d\n", argc - 1);

    printf("\nArguments:\n");
    for (int i = 1; i < argc; i++) {
        printf("  argv[%d]: %s\n", i, argv[i]);
    }

    // Simple option parsing
    printf("\nOption parsing:\n");
    int verbose = 0;
    int help = 0;
    char *filename = NULL;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--verbose") == 0) {
            verbose = 1;
            printf("  Verbose mode enabled\n");
        } else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            help = 1;
            printf("  Help requested\n");
        } else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) {
            filename = argv[++i];
            printf("  Filename: %s\n", filename);
        } else if (argv[i][0] == '-') {
            printf("  Unknown option: %s\n", argv[i]);
        } else {
            printf("  Positional argument: %s\n", argv[i]);
        }
    }
}

int main(int argc, char *argv[]) {
    printf("System Configuration Demo\n");
    printf("========================\n");

    // Command line arguments
    argument_demo(argc, argv);

    // Environment variables
    environment_demo();

    // Directory operations
    directory_demo();

    // System limits
    limits_demo();

    return 0;
}
```

## Inter-Process Communication

### Pipes and Communication

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

// Basic pipe communication
void pipe_demo() {
    printf("=== Basic Pipe Demo ===\n");

    int pipefd[2];
    pid_t pid;
    char write_msg[] = "Hello from parent process!";
    char read_msg[100];

    // Create pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(1);
    }

    pid = fork();

    if (pid == 0) {
        // Child process - read from pipe
        close(pipefd[1]); // Close write end

        // Read from pipe
        ssize_t bytes_read = read(pipefd[0], read_msg, sizeof(read_msg));
        if (bytes_read > 0) {
            printf("Child received: %s\n", read_msg);
        }

        close(pipefd[0]);
        exit(0);
    } else {
        // Parent process - write to pipe
        close(pipefd[0]); // Close read end

        // Write to pipe
        printf("Parent writing to pipe: %s\n", write_msg);
        write(pipefd[1], write_msg, strlen(write_msg) + 1);

        close(pipefd[1]);
        wait(NULL); // Wait for child
    }
}

// Bidirectional communication
void bidirectional_pipe_demo() {
    printf("\n=== Bidirectional Pipe Demo ===\n");

    int pipe1[2], pipe2[2]; // Two pipes for bidirectional communication
    pid_t pid;

    // Create pipes
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("pipe");
        exit(1);
    }

    pid = fork();

    if (pid == 0) {
        // Child process
        close(pipe1[1]); // Close write end of pipe1
        close(pipe2[0]); // Close read end of pipe2

        char buffer[100];

        // Read from parent via pipe1
        read(pipe1[0], buffer, sizeof(buffer));
        printf("Child received: %s\n", buffer);

        // Send response to parent via pipe2
        char response[] = "Hello back from child!";
        write(pipe2[1], response, strlen(response) + 1);

        close(pipe1[0]);
        close(pipe2[1]);
        exit(0);
    } else {
        // Parent process
        close(pipe1[0]); // Close read end of pipe1
        close(pipe2[1]); // Close write end of pipe2

        // Send message to child via pipe1
        char message[] = "Hello from parent!";
        write(pipe1[1], message, strlen(message) + 1);

        // Read response from child via pipe2
        char response[100];
        read(pipe2[0], response, sizeof(response));
        printf("Parent received: %s\n", response);

        close(pipe1[1]);
        close(pipe2[0]);
        wait(NULL);
    }
}

// Piped command execution
void piped_command_demo() {
    printf("\n=== Piped Command Demo ===\n");

    int pipefd[2];
    pid_t pid1, pid2;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        return;
    }

    // First child: ls -la
    pid1 = fork();
    if (pid1 == 0) {
        close(pipefd[0]); // Close read end
        dup2(pipefd[1], STDOUT_FILENO); // Redirect stdout to pipe
        close(pipefd[1]);

        execlp("ls", "ls", "-la", NULL);
        perror("execlp ls");
        exit(1);
    }

    // Second child: wc -l
    pid2 = fork();
    if (pid2 == 0) {
        close(pipefd[1]); // Close write end
        dup2(pipefd[0], STDIN_FILENO); // Redirect stdin from pipe
        close(pipefd[0]);

        execlp("wc", "wc", "-l", NULL);
        perror("execlp wc");
        exit(1);
    }

    // Parent
    close(pipefd[0]);
    close(pipefd[1]);

    // Wait for both children
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    printf("Pipe command completed.\n");
}

// Named pipes (FIFOs)
void fifo_demo() {
    printf("\n=== Named Pipe (FIFO) Demo ===\n");

    const char* fifo_name = "/tmp/myfifo";

    // Create named pipe
    if (mkfifo(fifo_name, 0666) == -1) {
        perror("mkfifo");
        printf("FIFO might already exist, continuing...\n");
    }

    pid_t pid = fork();

    if (pid == 0) {
        // Writer process
        FILE* fifo = fopen(fifo_name, "w");
        if (fifo == NULL) {
            perror("fopen");
            exit(1);
        }

        printf("Writer: Sending message through FIFO...\n");
        fprintf(fifo, "Hello through named pipe!\n");
        fclose(fifo);

        exit(0);
    } else {
        // Reader process
        sleep(1); // Give writer time to start

        FILE* fifo = fopen(fifo_name, "r");
        if (fifo == NULL) {
            perror("fopen");
            return;
        }

        char buffer[100];
        if (fgets(buffer, sizeof(buffer), fifo) != NULL) {
            printf("Reader: Received: %s", buffer);
        }

        fclose(fifo);
        wait(NULL);

        // Clean up
        unlink(fifo_name);
    }
}

int main() {
    printf("Inter-Process Communication Demo\n");
    printf("================================\n");

    // Basic pipe
    pipe_demo();

    // Bidirectional communication
    bidirectional_pipe_demo();

    // Piped commands
    piped_command_demo();

    // Named pipes
    fifo_demo();

    printf("\nAll IPC demos completed!\n");

    return 0;
}
```

## Network Programming

### Basic Socket Programming

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define PORT 8080
#define BUFFER_SIZE 1024

// Simple TCP server
void tcp_server() {
    printf("=== TCP Server Demo ===\n");

    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};

    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        return;
    }

    // Set socket options
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        close(server_fd);
        return;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind socket to port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        return;
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        return;
    }

    printf("TCP Server listening on port %d...\n", PORT);
    printf("Run the client in another terminal to test.\n");
    printf("Press Ctrl+C to stop the server.\n");

    // Accept incoming connection
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept");
        close(server_fd);
        return;
    }

    printf("Connection accepted from %s:%d\n",
           inet_ntoa(address.sin_addr), ntohs(address.sin_port));

    // Read data from client
    int valread = read(new_socket, buffer, BUFFER_SIZE);
    if (valread > 0) {
        printf("Client message: %s\n", buffer);

        // Send response
        char *response = "Hello from server!";
        send(new_socket, response, strlen(response), 0);
        printf("Response sent to client\n");
    }

    close(new_socket);
    close(server_fd);
}

// Simple TCP client
void tcp_client() {
    printf("=== TCP Client Demo ===\n");

    int sock = 0;
    struct sockaddr_in serv_addr;
    char *message = "Hello from client!";
    char buffer[BUFFER_SIZE] = {0};

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket creation error");
        return;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 address from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        close(sock);
        return;
    }

    // Connect to server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed. Make sure the server is running.\n");
        close(sock);
        return;
    }

    printf("Connected to server. Sending message...\n");

    // Send message
    send(sock, message, strlen(message), 0);
    printf("Message sent\n");

    // Read response
    int valread = read(sock, buffer, BUFFER_SIZE);
    if (valread > 0) {
        printf("Server response: %s\n", buffer);
    }

    close(sock);
}

// DNS resolution demo
void dns_demo() {
    printf("\n=== DNS Resolution Demo ===\n");

    char hostname[] = "www.google.com";
    struct hostent *host_entry;
    struct in_addr **addr_list;

    // Resolve hostname
    host_entry = gethostbyname(hostname);
    if (host_entry == NULL) {
        printf("Failed to resolve hostname\n");
        return;
    }

    printf("Hostname: %s\n", hostname);

    // Print IP addresses
    addr_list = (struct in_addr **)host_entry->h_addr_list;
    printf("IP addresses:\n");
    for (int i = 0; addr_list[i] != NULL; i++) {
        printf("  %s\n", inet_ntoa(*addr_list[i]));
    }

    // Print other information
    printf("Host name: %s\n", host_entry->h_name);
    printf("Address type: %s\n", host_entry->h_addrtype == AF_INET ? "IPv4" : "IPv6");
    printf("Address length: %d bytes\n", host_entry->h_length);
}

// UDP server (datagram)
void udp_server() {
    printf("\n=== UDP Server Demo ===\n");

    int sockfd;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in servaddr, cliaddr;

    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        return;
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    // Server configuration
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT + 1); // Use different port for UDP

    // Bind socket
    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("bind failed");
        close(sockfd);
        return;
    }

    printf("UDP Server listening on port %d...\n", PORT + 1);

    int len, n;
    len = sizeof(cliaddr);

    // Receive datagram
    n = recvfrom(sockfd, (char *)buffer, BUFFER_SIZE, MSG_WAITALL,
                 (struct sockaddr *)&cliaddr, &len);
    buffer[n] = '\0';

    printf("Received from client: %s\n", buffer);

    // Send response
    char *response = "UDP server response!";
    sendto(sockfd, (const char *)response, strlen(response), MSG_CONFIRM,
           (const struct sockaddr *)&cliaddr, len);
    printf("Response sent to client\n");

    close(sockfd);
}

// UDP client
void udp_client() {
    printf("\n=== UDP Client Demo ===\n");

    int sockfd;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in servaddr;

    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        return;
    }

    memset(&servaddr, 0, sizeof(servaddr));

    // Server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT + 1);
    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);

    char *message = "Hello UDP server!";

    // Send message
    sendto(sockfd, (const char *)message, strlen(message), MSG_CONFIRM,
           (const struct sockaddr *)&servaddr, sizeof(servaddr));
    printf("UDP message sent\n");

    // Receive response
    int n, len;
    len = sizeof(servaddr);
    n = recvfrom(sockfd, (char *)buffer, BUFFER_SIZE, MSG_WAITALL,
                 (struct sockaddr *)&servaddr, &len);
    buffer[n] = '\0';
    printf("Server response: %s\n", buffer);

    close(sockfd);
}

int main(int argc, char *argv[]) {
    printf("Network Programming Demo\n");
    printf("=======================\n");

    if (argc > 1 && strcmp(argv[1], "server") == 0) {
        // Run server mode
        dns_demo();
        tcp_server();
    } else if (argc > 1 && strcmp(argv[1], "client") == 0) {
        // Run client mode
        sleep(1); // Give server time to start
        dns_demo();
        tcp_client();
    } else if (argc > 1 && strcmp(argv[1], "udp_server") == 0) {
        udp_server();
    } else if (argc > 1 && strcmp(argv[1], "udp_client") == 0) {
        udp_client();
    } else {
        printf("Usage:\n");
        printf("  %s server     - Run TCP server\n", argv[0]);
        printf("  %s client     - Run TCP client\n", argv[0]);
        printf("  %s udp_server - Run UDP server\n", argv[0]);
        printf("  %s udp_client - Run UDP client\n", argv[0]);
        printf("\nDNS Demo:\n");
        dns_demo();
    }

    return 0;
}
```

## File System Operations

### Advanced File Handling

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <time.h>

// File metadata operations
void file_metadata_demo() {
    printf("=== File Metadata Demo ===\n");

    const char *filename = __FILE__; // Use current source file

    struct stat file_stat;

    if (stat(filename, &file_stat) == -1) {
        perror("stat");
        return;
    }

    printf("File: %s\n", filename);
    printf("Size: %ld bytes\n", file_stat.st_size);
    printf("Blocks: %ld\n", file_stat.st_blocks);
    printf("Block size: %ld bytes\n", file_stat.st_blksize);

    // File type
    printf("File type: ");
    if (S_ISREG(file_stat.st_mode)) {
        printf("Regular file\n");
    } else if (S_ISDIR(file_stat.st_mode)) {
        printf("Directory\n");
    } else if (S_ISLNK(file_stat.st_mode)) {
        printf("Symbolic link\n");
    } else {
        printf("Other\n");
    }

    // Permissions
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

    // Owner and group
    printf("Owner UID: %d\n", file_stat.st_uid);
    printf("Group GID: %d\n", file_stat.st_gid);

    // Timestamps
    printf("Last access: %s", ctime(&file_stat.st_atime));
    printf("Last modification: %s", ctime(&file_stat.st_mtime));
    printf("Last status change: %s", ctime(&file_stat.st_ctime));

    // Inode information
    printf("Inode: %ld\n", file_stat.st_ino);
    printf("Device: %ld\n", file_stat.st_dev);
    printf("Links: %ld\n", file_stat.st_nlink);
}

// Directory operations
void directory_demo() {
    printf("\n=== Directory Operations Demo ===\n");

    const char *dir_path = ".";
    DIR *dir;
    struct dirent *entry;

    printf("Contents of directory '%s':\n", dir_path);

    dir = opendir(dir_path);
    if (dir == NULL) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        printf("%-20s", entry->d_name);

        // File type
        switch (entry->d_type) {
            case DT_REG:
                printf("(regular file)");
                break;
            case DT_DIR:
                printf("(directory)");
                break;
            case DT_LNK:
                printf("(symlink)");
                break;
            case DT_BLK:
                printf("(block device)");
                break;
            case DT_CHR:
                printf("(character device)");
                break;
            case DT_FIFO:
                printf("(FIFO)");
                break;
            case DT_SOCK:
                printf("(socket)");
                break;
            default:
                printf("(unknown)");
                break;
        }

        printf("\n");
    }

    closedir(dir);
}

// Advanced file operations
void advanced_file_ops() {
    printf("\n=== Advanced File Operations ===\n");

    const char *test_file = "/tmp/test_file.txt";
    const char *content = "Hello, System Programming!";

    // Create and write file with specific permissions
    int fd = open(test_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        return;
    }

    // Write using system call
    ssize_t bytes_written = write(fd, content, strlen(content));
    if (bytes_written == -1) {
        perror("write");
        close(fd);
        return;
    }

    printf("Written %ld bytes to %s\n", bytes_written, test_file);
    close(fd);

    // Read using system call
    fd = open(test_file, O_RDONLY);
    if (fd == -1) {
        perror("open for reading");
        return;
    }

    char buffer[100];
    ssize_t bytes_read = read(fd, buffer, sizeof(buffer) - 1);
    if (bytes_read == -1) {
        perror("read");
        close(fd);
        return;
    }

    buffer[bytes_read] = '\0';
    printf("Read %ld bytes: %s\n", bytes_read, buffer);
    close(fd);

    // File operations with positioning
    fd = open(test_file, O_RDWR);
    if (fd != -1) {
        printf("\nFile positioning operations:\n");
        printf("Current position: %ld\n", lseek(fd, 0, SEEK_CUR));

        // Seek to end
        off_t end_pos = lseek(fd, 0, SEEK_END);
        printf("File size (seek to end): %ld\n", end_pos);

        // Seek to beginning
        lseek(fd, 0, SEEK_SET);

        // Append more content
        const char *more_content = " More content!";
        write(fd, more_content, strlen(more_content));

        // Get new file size
        end_pos = lseek(fd, 0, SEEK_END);
        printf("New file size: %ld\n", end_pos);

        close(fd);
    }

    // Clean up
    unlink(test_file);
}

// Symbolic link operations
void symlink_demo() {
    printf("\n=== Symbolic Link Demo ===\n");

    const char *target = "/tmp/target.txt";
    const char *link_path = "/tmp/symlink.txt";

    // Create target file
    FILE *target_file = fopen(target, "w");
    if (target_file) {
        fprintf(target_file, "This is the target file content.");
        fclose(target_file);
    }

    // Create symbolic link
    if (symlink(target, link_path) == -1) {
        perror("symlink");
        return;
    }

    printf("Created symbolic link: %s -> %s\n", link_path, target);

    // Read link target
    char buffer[256];
    ssize_t len = readlink(link_path, buffer, sizeof(buffer) - 1);
    if (len != -1) {
        buffer[len] = '\0';
        printf("Link points to: %s\n", buffer);
    }

    // Stat operations
    struct stat target_stat, link_stat;

    if (stat(link_path, &target_stat) == 0) {
        printf("Stat (follows link):\n");
        printf("  Size: %ld bytes\n", target_stat.st_size);
        printf("  Type: %s\n", S_ISREG(target_stat.st_mode) ? "regular file" : "other");
    }

    if (lstat(link_path, &link_stat) == 0) {
        printf("Lstat (doesn't follow link):\n");
        printf("  Size: %ld bytes\n", link_stat.st_size);
        printf("  Type: %s\n", S_ISLNK(link_stat.st_mode) ? "symbolic link" : "other");
    }

    // Clean up
    unlink(link_path);
    unlink(target);
}

// Temporary file operations
void temp_file_demo() {
    printf("\n=== Temporary File Demo ===\n");

    // Create temporary file
    char temp_filename[] = "/tmp/tempfileXXXXXX";
    int temp_fd = mkstemp(temp_filename);

    if (temp_fd == -1) {
        perror("mkstemp");
        return;
    }

    printf("Created temporary file: %s\n", temp_filename);

    // Write to temporary file
    const char *temp_content = "This is temporary content.";
    write(temp_fd, temp_content, strlen(temp_content));

    // Read back
    lseek(temp_fd, 0, SEEK_SET);
    char buffer[100];
    ssize_t bytes_read = read(temp_fd, buffer, sizeof(buffer) - 1);
    buffer[bytes_read] = '\0';

    printf("Temporary file content: %s\n", buffer);

    // File is automatically removed when closed and unlinked
    unlink(temp_filename);
    close(temp_fd);
    printf("Temporary file removed.\n");
}

int main() {
    printf("File System Operations Demo\n");
    printf("==========================\n");

    // File metadata
    file_metadata_demo();

    // Directory operations
    directory_demo();

    // Advanced file operations
    advanced_file_ops();

    // Symbolic links
    symlink_demo();

    // Temporary files
    temp_file_demo();

    printf("\nAll file system demos completed!\n");

    return 0;
}
```

## Multi-threading Basics

### Thread Creation and Synchronization

```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

// Basic thread demonstration
void* thread_function(void* arg) {
    int thread_num = *(int*)arg;

    printf("Thread %d: Starting\n", thread_num);

    // Simulate work
    for (int i = 0; i < 3; i++) {
        printf("Thread %d: Working... %d\n", thread_num, i + 1);
        sleep(1);
    }

    printf("Thread %d: Finishing\n", thread_num);

    return NULL;
}

void basic_thread_demo() {
    printf("=== Basic Thread Demo ===\n");

    pthread_t threads[3];
    int thread_args[3];

    // Create threads
    for (int i = 0; i < 3; i++) {
        thread_args[i] = i + 1;

        if (pthread_create(&threads[i], NULL, thread_function, &thread_args[i]) != 0) {
            perror("pthread_create");
            return;
        }

        printf("Main: Created thread %d\n", i + 1);
    }

    // Wait for threads to complete
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
        printf("Main: Thread %d finished\n", i + 1);
    }

    printf("Main: All threads completed\n");
}

// Shared data and mutex demo
typedef struct {
    int counter;
    pthread_mutex_t mutex;
} SharedData;

void* increment_counter(void* arg) {
    SharedData* data = (SharedData*)arg;

    for (int i = 0; i < 100000; i++) {
        // Lock mutex before accessing shared data
        pthread_mutex_lock(&data->mutex);

        data->counter++;

        // Unlock mutex after accessing shared data
        pthread_mutex_unlock(&data->mutex);
    }

    return NULL;
}

void mutex_demo() {
    printf("\n=== Mutex Synchronization Demo ===\n");

    SharedData data;
    data.counter = 0;

    // Initialize mutex
    if (pthread_mutex_init(&data.mutex, NULL) != 0) {
        perror("mutex_init");
        return;
    }

    pthread_t threads[4];

    printf("Initial counter value: %d\n", data.counter);

    // Create threads that increment counter
    for (int i = 0; i < 4; i++) {
        if (pthread_create(&threads[i], NULL, increment_counter, &data) != 0) {
            perror("pthread_create");
            return;
        }
    }

    // Wait for all threads
    for (int i = 0; i < 4; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Final counter value: %d\n", data.counter);
    printf("Expected value: 400000\n");

    // Destroy mutex
    pthread_mutex_destroy(&data.mutex);
}

// Producer-consumer with condition variables
#define BUFFER_SIZE 5

typedef struct {
    int buffer[BUFFER_SIZE];
    int count;
    int in;
    int out;
    pthread_mutex_t mutex;
    pthread_cond_t not_empty;
    pthread_cond_t not_full;
} CircularBuffer;

void* producer(void* arg) {
    CircularBuffer* cb = (CircularBuffer*)arg;

    for (int i = 0; i < 10; i++) {
        // Lock mutex
        pthread_mutex_lock(&cb->mutex);

        // Wait if buffer is full
        while (cb->count == BUFFER_SIZE) {
            printf("Producer: Buffer full, waiting...\n");
            pthread_cond_wait(&cb->not_full, &cb->mutex);
        }

        // Add item to buffer
        cb->buffer[cb->in] = i;
        printf("Producer: Produced %d at position %d\n", i, cb->in);
        cb->in = (cb->in + 1) % BUFFER_SIZE;
        cb->count++;

        // Signal that buffer is not empty
        pthread_cond_signal(&cb->not_empty);

        // Unlock mutex
        pthread_mutex_unlock(&cb->mutex);

        usleep(100000); // Simulate production time
    }

    return NULL;
}

void* consumer(void* arg) {
    CircularBuffer* cb = (CircularBuffer*)arg;

    for (int i = 0; i < 10; i++) {
        // Lock mutex
        pthread_mutex_lock(&cb->mutex);

        // Wait if buffer is empty
        while (cb->count == 0) {
            printf("Consumer: Buffer empty, waiting...\n");
            pthread_cond_wait(&cb->not_empty, &cb->mutex);
        }

        // Remove item from buffer
        int item = cb->buffer[cb->out];
        printf("Consumer: Consumed %d from position %d\n", item, cb->out);
        cb->out = (cb->out + 1) % BUFFER_SIZE;
        cb->count--;

        // Signal that buffer is not full
        pthread_cond_signal(&cb->not_full);

        // Unlock mutex
        pthread_mutex_unlock(&cb->mutex);

        usleep(150000); // Simulate consumption time
    }

    return NULL;
}

void condition_variable_demo() {
    printf("\n=== Producer-Consumer Demo ===\n");

    CircularBuffer cb;
    cb.count = 0;
    cb.in = 0;
    cb.out = 0;

    // Initialize mutex and condition variables
    pthread_mutex_init(&cb.mutex, NULL);
    pthread_cond_init(&cb.not_empty, NULL);
    pthread_cond_init(&cb.not_full, NULL);

    pthread_t producer_thread, consumer_thread;

    // Create producer and consumer threads
    pthread_create(&producer_thread, NULL, producer, &cb);
    pthread_create(&consumer_thread, NULL, consumer, &cb);

    // Wait for threads to complete
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    // Clean up
    pthread_mutex_destroy(&cb.mutex);
    pthread_cond_destroy(&cb.not_empty);
    pthread_cond_destroy(&cb.not_full);
}

// Thread attributes demo
void thread_attributes_demo() {
    printf("\n=== Thread Attributes Demo ===\n");

    pthread_attr_t attr;
    pthread_t thread;

    // Initialize thread attributes
    pthread_attr_init(&attr);

    // Set detach state
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    // Get stack size
    size_t stack_size;
    pthread_attr_getstacksize(&attr, &stack_size);
    printf("Default stack size: %zu bytes\n", stack_size);

    // Set new stack size
    size_t new_stack_size = 1024 * 1024; // 1MB
    pthread_attr_setstacksize(&attr, new_stack_size);
    printf("Set stack size to: %zu bytes\n", new_stack_size);

    // Create thread with attributes
    if (pthread_create(&thread, &attr, thread_function, &(int){1}) == 0) {
        printf("Thread created with custom attributes\n");
        pthread_join(thread, NULL);
    }

    // Destroy attributes
    pthread_attr_destroy(&attr);
}

// Thread-safe data structure
typedef struct {
    int value;
    pthread_mutex_t lock;
} ThreadSafeCounter;

void init_counter(ThreadSafeCounter* counter) {
    counter->value = 0;
    pthread_mutex_init(&counter->lock, NULL);
}

void destroy_counter(ThreadSafeCounter* counter) {
    pthread_mutex_destroy(&counter->lock);
}

void increment(ThreadSafeCounter* counter) {
    pthread_mutex_lock(&counter->lock);
    counter->value++;
    pthread_mutex_unlock(&counter->lock);
}

int get_value(ThreadSafeCounter* counter) {
    pthread_mutex_lock(&counter->lock);
    int value = counter->value;
    pthread_mutex_unlock(&counter->lock);
    return value;
}

void* counter_thread(void* arg) {
    ThreadSafeCounter* counter = (ThreadSafeCounter*)arg;

    for (int i = 0; i < 1000; i++) {
        increment(counter);
    }

    return NULL;
}

void thread_safe_data_demo() {
    printf("\n=== Thread-Safe Data Structure Demo ===\n");

    ThreadSafeCounter counter;
    init_counter(&counter);

    pthread_t threads[10];

    printf("Initial counter value: %d\n", get_value(&counter));

    // Create threads that increment the counter
    for (int i = 0; i < 10; i++) {
        pthread_create(&threads[i], NULL, counter_thread, &counter);
    }

    // Wait for all threads
    for (int i = 0; i < 10; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Final counter value: %d\n", get_value(&counter));
    printf("Expected value: 10000\n");

    destroy_counter(&counter);
}

int main() {
    printf("Multi-threading Demo\n");
    printf("==================\n");

    // Basic thread creation
    basic_thread_demo();

    // Mutex synchronization
    mutex_demo();

    // Condition variables
    condition_variable_demo();

    // Thread attributes
    thread_attributes_demo();

    // Thread-safe data structures
    thread_safe_data_demo();

    printf("\nAll threading demos completed!\n");

    return 0;
}
```

## Best Practices

### System Programming Guidelines

1. **Error Handling**
   - Always check return values from system calls
   - Use perror() or strerror() for error messages
   - Handle edge cases and partial operations

2. **Resource Management**
   - Close file descriptors and sockets
   - Free allocated memory
   - Clean up temporary resources

3. **Security Considerations**
   - Validate input from untrusted sources
   - Use appropriate file permissions
   - Avoid buffer overflows and injection attacks

4. **Performance Optimization**
   - Use appropriate buffer sizes
   - Minimize system calls
   - Consider asynchronous operations

5. **Portability**
   - Use POSIX standard functions
   - Handle different platform behaviors
   - Document platform-specific code

## Exercises

### Exercise 13.1: Process Communication
Create a parent-child process pair that communicates through pipes.

### Exercise 13.2: Simple Web Server
Implement a basic HTTP server that serves static files.

### Exercise 13.3: File Monitor
Create a program that monitors changes in a directory.

### Exercise 13.4: Thread Pool
Implement a thread pool for concurrent task processing.

### Exercise 13.5: System Information Tool
Create a utility that displays comprehensive system information.

## Challenge Problems

### Challenge 13.1: Multi-threaded Server
Build a multi-threaded server that handles multiple concurrent clients.

### Challenge 13.2: IPC Mechanisms Comparison
Compare performance of different IPC mechanisms.

### Challenge 13.3: Real-time System
Implement a real-time data processing system with threads and shared memory.

## Quick Reference

### Common System Calls
```c
// Process Management
pid_t fork(void);
pid_t getpid(void);
pid_t getppid(void);
int execvp(const char *file, char *const argv[]);
void exit(int status);

// File Operations
int open(const char *pathname, int flags, mode_t mode);
ssize_t read(int fd, void *buf, size_t count);
ssize_t write(int fd, const void *buf, size_t count);
int close(int fd);
off_t lseek(int fd, off_t offset, int whence);

// Directory Operations
DIR *opendir(const char *name);
struct dirent *readdir(DIR *dirp);
int closedir(DIR *dirp);

// Pipe Operations
int pipe(int pipefd[2]);

// Socket Operations
int socket(int domain, int type, int protocol);
int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
int listen(int sockfd, int backlog);
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

// Thread Operations
int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                   void *(*start_routine) (void *), void *arg);
int pthread_join(pthread_t thread, void **retval);
int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);
int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_unlock(pthread_mutex_t *mutex);
```

## Next Steps
Once you're comfortable with:
- Process creation and management
- Inter-process communication mechanisms
- Network programming fundamentals
- File system operations
- Basic multi-threading concepts

You're ready for **Chapter 14: Build Systems and Tools**!