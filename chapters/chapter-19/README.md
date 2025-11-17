# Chapter 19: Parallel Computing and Concurrency

## 🚀 Introduction to Parallel Computing

Parallel computing enables simultaneous execution of multiple tasks to improve performance and handle complex workloads. This chapter explores advanced concurrency concepts using offline-capable tools and techniques.

### The Parallel Computing Revolution

We're living in the era of multi-core processors. Your phone likely has 4-8 cores, your laptop 4-16 cores, and servers can have hundreds of cores. Sequential programming can't leverage this hardware effectively - parallel computing is no longer optional, it's essential.

**The End of "Free Lunch":**
For decades, programmers relied on Moore's Law - automatic speed increases from faster single cores. That era ended around 2005. Now, performance gains come from:
- **More Cores**: Parallel execution
- **Better Architecture**: Cache improvements, SIMD
- **Specialized Hardware**: GPUs, TPUs, AI accelerators

**Why Parallel Computing in C?**
- **Direct Hardware Access**: C gives you low-level control over threading
- **Performance Critical**: Systems programming often needs maximum performance
- **Legacy Systems**: Many existing C systems need parallelization
- **Foundation**: Understanding parallelism helps with higher-level languages

### The Parallel Computing Landscape

**Historical Context:**
```
1970s: Mainframe computers - Limited parallelism
1980s: Early parallel machines - Expensive, specialized
1990s: Multi-threading emerges - OS-level support
2000s: Multi-core CPUs become standard - Ubiquitous parallelism
2010s: Massive parallelism - GPUs, many-core systems
2020s: Heterogeneous computing - CPUs + GPUs + specialized hardware
```

**Modern Hardware Trends:**
- **Consumer Devices**: 4-16 cores common, 32+ cores emerging
- **Server Hardware**: 64-128 cores standard, 256+ cores available
- **Mobile Devices**: 4-8 cores with specialized AI cores
- **Embedded Systems**: Multi-core microcontrollers becoming common

### Concurrency vs. Parallelism: Understanding the Distinction

**Concurrency is about dealing with lots of things at once.**
**Parallelism is about doing lots of things at once.**

```
Concurrency:
[Coffee] [Toast] [Eggs]
  |        |       |
  Wait     Wait    Wait
  |        |       |
Ready?   Ready?  Ready?
  |        |       |
Complete Complete Complete

Parallelism:
[Coffee] [Toast] [Eggs]
   \       |       /
    \      |      /
     Simultaneous
        Execution
```

**Concurrency Examples:**
- **Web Server**: Handling multiple client connections
- **GUI Application**: UI thread + background workers
- **Operating System**: Managing multiple processes

**Parallelism Examples:**
- **Video Encoding**: Splitting video into chunks
- **Scientific Computing**: Matrix operations across cores
- **Image Processing**: Filter operations on image regions

### The Challenges of Parallel Programming

Parallel programming is fundamentally more complex than sequential programming:

**1. Coordination Complexity**
```c
// Sequential: Easy to understand
void process_data() {
    step1();
    step2();  // Always runs after step1
    step3();  // Always runs after step2
}

// Parallel: Complex coordination
void process_data_parallel() {
    thread_create(step1);
    thread_create(step2);  // May run before, during, or after step1
    thread_create(step3);  // Complex coordination needed
    // Need to wait for all to complete
}
```

**2. Shared State Problems**
- **Race Conditions**: Multiple threads accessing same data
- **Deadlocks**: Threads waiting for each other
- **Starvation**: Some threads never get resources
- **Livelocks**: Threads keep changing state but make no progress

**3. Debugging Complexity**
- **Non-Deterministic**: Bugs may only appear sometimes
- **Timing Dependent**: Results vary with execution speed
- **Hard to Reproduce**: Race conditions are intermittent
- **Tool Limitations**: Debuggers can alter timing

**4. Performance Pitfalls**
- **Overhead**: Thread creation, synchronization costs
- **Contention**: Multiple threads competing for resources
- **Cache Effects**: False sharing, cache invalidation
- **Load Balancing**: Uneven work distribution

### The Performance Promise

Despite the challenges, parallel programming offers significant benefits:

**Speedup Potential:**
```
Theoretical Speedup: 1 / (S + P/N)
Where:
S = Serial portion of code
P = Parallel portion of code
N = Number of processors

Example: 90% parallel code on 8 cores
Speedup = 1 / (0.1 + 0.9/8) = 4.7x speedup
```

**Real-World Speedups:**
- **Image Processing**: 4-16x speedup (highly parallelizable)
- **Web Servers**: 2-8x speedup (I/O bound limits)
- **Scientific Computing**: 10-100x speedup (embarrassingly parallel)
- **Databases**: 2-4x speedup (limited by contention)

**Amdahl's Law Reality:**
- Most applications have some serial portion
- Diminishing returns as cores increase
- Communication overhead grows with parallelism
- Memory bandwidth often becomes bottleneck

### Parallel Programming Paradigms

**1. Shared Memory (POSIX Threads)**
```c
// Threads share memory directly
int shared_data = 0;

void* thread_func(void* arg) {
    shared_data++;  // Direct access to shared data
    return NULL;
}
```
**Pros**: Fast communication, simple data sharing
**Cons**: Complex synchronization, race conditions

**2. Message Passing (MPI-style)**
```c
// Threads communicate via messages
void send_message(int target_thread, Message* msg);
Message* receive_message(int timeout);
```
**Pros**: No shared state, easier reasoning
**Cons**: Communication overhead, more complex

**3. Data Parallel**
```c
// Same operation on different data
void process_array_parallel(int* data, int size) {
    #pragma omp parallel for
    for (int i = 0; i < size; i++) {
        data[i] = process(data[i]);
    }
}
```
**Pros**: Simple to understand, good for arrays
**Cons**: Limited to certain problem types

**4. Task Parallel**
```c
// Different tasks executed in parallel
void run_tasks() {
    thread_create(network_task);
    thread_create(file_io_task);
    thread_create(computation_task);
    wait_for_all();
}
```
**Pros**: Flexible, good for heterogeneous work
**Cons**: Load balancing challenges

### The Modern Parallel Computing Ecosystem

**Hardware Diversity:**
- **CPU Cores**: General-purpose, sequential execution
- **GPU Cores**: Specialized, parallel execution
- **AI Accelerators**: Matrix multiplication, neural networks
- **DSPs**: Digital signal processing
- **FPGAs**: Reconfigurable hardware

**Software Tools:**
- **Pthreads**: Standard C threading
- **OpenMP**: High-level parallel programming
- **MPI**: Distributed systems parallelism
- **CUDA/OpenCL**: GPU programming
- **Intel TBB**: High-level parallel patterns

**Industry Applications:**
- **Big Data**: Hadoop, Spark using parallel processing
- **Machine Learning**: Training neural networks on GPUs
- **Web Services**: Handling millions of concurrent requests
- **Scientific Computing**: Weather modeling, genome sequencing

### Learning Parallel Programming

**Gradual Approach:**
1. **Understand the Basics**: Processes, threads, synchronization
2. **Simple Patterns**: Producer-consumer, thread pools
3. **Advanced Concepts**: Lock-free algorithms, memory models
4. **Domain-Specific**: GPU programming, distributed systems

**Practical Skills:**
- **Thread Management**: Create, join, synchronize threads
- **Synchronization**: Mutexes, semaphores, condition variables
- **Data Structures**: Thread-safe versions of common structures
- **Performance Analysis**: Identify bottlenecks, measure speedup
- **Debugging**: Find and fix concurrency bugs

### Career Impact

**High-Demand Skills:**
- **Cloud Computing**: Distributed systems, microservices
- **Big Data**: Parallel data processing frameworks
- **Machine Learning**: GPU programming, model training
- **Game Development**: Multi-threaded engines, networking
- **High-Frequency Trading**: Low-latency parallel systems

**Salary Premium:**
Parallel programming skills typically command 15-30% higher salaries due to:
- **Complexity**: Fewer developers master these skills
- **Demand**: High demand across all tech sectors
- **Impact**: Direct impact on system performance and scalability

This foundation prepares you to understand the practical parallel programming techniques that follow, where you'll learn to harness the full power of modern multi-core systems using C's low-level threading capabilities.

### Learning Objectives
- Understand parallel computing concepts and terminology
- Master threading and synchronization primitives
- Learn parallel algorithms and design patterns
- Implement concurrent data structures
- Optimize for multi-core processors

---

## 19.1 Parallel Computing Fundamentals

### Understanding Concurrency vs Parallelism
```c
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// Concurrency: Multiple tasks making progress independently
// Parallelism: Multiple tasks executing simultaneously

// Sequential approach
void sequential_task() {
    printf("Task 1 started\n");
    sleep(1);
    printf("Task 1 completed\n");

    printf("Task 2 started\n");
    sleep(1);
    printf("Task 2 completed\n");
}

// Concurrent approach
void* worker_task(void* arg) {
    int task_id = *(int*)arg;
    printf("Task %d started\n", task_id);
    sleep(1);
    printf("Task %d completed\n", task_id);
    return NULL;
}

void concurrent_task() {
    pthread_t thread1, thread2;
    int task1_id = 1, task2_id = 2;

    pthread_create(&thread1, NULL, worker_task, &task1_id);
    pthread_create(&thread2, NULL, worker_task, &task2_id);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
}
```

### Thread Safety Basics
```c
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Global variable (not thread-safe)
int counter = 0;

// Thread-safe counter with mutex
typedef struct {
    int value;
    pthread_mutex_t mutex;
} SafeCounter;

void safe_counter_init(SafeCounter *counter) {
    counter->value = 0;
    pthread_mutex_init(&counter->mutex, NULL);
}

void safe_counter_increment(SafeCounter *counter) {
    pthread_mutex_lock(&counter->mutex);
    counter->value++;
    pthread_mutex_unlock(&counter->mutex);
}

int safe_counter_get(SafeCounter *counter) {
    pthread_mutex_lock(&counter->mutex);
    int value = counter->value;
    pthread_mutex_unlock(&counter->mutex);
    return value;
}

void safe_counter_destroy(SafeCounter *counter) {
    pthread_mutex_destroy(&counter->mutex);
}

// Worker function that increments counter
void* counter_worker(void* arg) {
    SafeCounter *safe_counter = (SafeCounter*)arg;

    for (int i = 0; i < 100000; i++) {
        safe_counter_increment(safe_counter);
    }

    return NULL;
}
```

---

## 19.2 Synchronization Primitives

### Mutexes and Locks
```c
#include <pthread.h>
#include <stdio.h>

typedef struct {
    int data;
    pthread_mutex_t mutex;
    pthread_cond_t cond_var;
    bool data_ready;
} SharedData;

void producer_thread(void* arg) {
    SharedData *shared = (SharedData*)arg;

    for (int i = 0; i < 10; i++) {
        // Produce data
        pthread_mutex_lock(&shared->mutex);

        while (shared->data_ready) {
            // Wait for consumer to consume data
            pthread_cond_wait(&shared->cond_var, &shared->mutex);
        }

        shared->data = i;
        shared->data_ready = true;
        printf("Produced: %d\n", i);

        // Signal consumer
        pthread_cond_signal(&shared->cond_var);
        pthread_mutex_unlock(&shared->mutex);

        usleep(100000);  // Simulate work
    }
}

void* consumer_thread(void* arg) {
    SharedData *shared = (SharedData*)arg;

    while (1) {
        pthread_mutex_lock(&shared->mutex);

        while (!shared->data_ready) {
            pthread_cond_wait(&shared->cond_var, &shared->mutex);
        }

        int data = shared->data;
        shared->data_ready = false;

        printf("Consumed: %d\n", data);

        // Signal producer
        pthread_cond_signal(&shared->cond_var);
        pthread_mutex_unlock(&shared->mutex);

        if (data == 9) break;  // End condition

        usleep(100000);  // Simulate processing
    }

    return NULL;
}
```

### Semaphores
```c
#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>

// Simple semaphore implementation using mutex and condition variable
typedef struct {
    int count;
    int max_count;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} SimpleSemaphore;

void semaphore_init(SimpleSemaphore *sem, int initial_count) {
    sem->count = initial_count;
    sem->max_count = initial_count;
    pthread_mutex_init(&sem->mutex, NULL);
    pthread_cond_init(&sem->cond, NULL);
}

void semaphore_wait(SimpleSemaphore *sem) {
    pthread_mutex_lock(&sem->mutex);
    while (sem->count == 0) {
        pthread_cond_wait(&sem->cond, &sem->mutex);
    }
    sem->count--;
    pthread_mutex_unlock(&sem->mutex);
}

void semaphore_signal(SimpleSemaphore *sem) {
    pthread_mutex_lock(&sem->mutex);
    sem->count++;
    pthread_cond_signal(&sem->cond);
    pthread_mutex_unlock(&sem->mutex);
}

void semaphore_destroy(SimpleSemaphore *sem) {
    pthread_mutex_destroy(&sem->mutex);
    pthread_cond_destroy(&sem->cond);
}

// Producer-consumer with semaphores
typedef struct {
    int buffer[10];
    int in, out;
    SimpleSemaphore empty;
    SimpleSemaphore full;
    pthread_mutex_t mutex;
} BoundedBuffer;

void buffer_init(BoundedBuffer *buf) {
    buf->in = buf->out = 0;
    semaphore_init(&buf->empty, 10);  // 10 empty slots
    semaphore_init(&buf->full, 0);    // 0 full slots
    pthread_mutex_init(&buf->mutex, NULL);
}

void buffer_put(BoundedBuffer *buf, int item) {
    semaphore_wait(&buf->empty);
    pthread_mutex_lock(&buf->mutex);

    buf->buffer[buf->in] = item;
    buf->in = (buf->in + 1) % 10;

    pthread_mutex_unlock(&buf->mutex);
    semaphore_signal(&buf->full);
}

int buffer_get(BoundedBuffer *buf) {
    semaphore_wait(&buf->full);
    pthread_mutex_lock(&buf->mutex);

    int item = buf->buffer[buf->out];
    buf->out = (buf->out + 1) % 10;

    pthread_mutex_unlock(&buf->mutex);
    semaphore_signal(&buf->empty);

    return item;
}
```

### Read-Write Locks
```c
#include <pthread.h>

typedef struct {
    pthread_mutex_t mutex;
    pthread_cond_t read_cond;
    pthread_cond_t write_cond;
    int readers;
    int writers;
    int waiting_writers;
} RWLock;

void rwlock_init(RWLock *lock) {
    pthread_mutex_init(&lock->mutex, NULL);
    pthread_cond_init(&lock->read_cond, NULL);
    pthread_cond_init(&lock->write_cond, NULL);
    lock->readers = 0;
    lock->writers = 0;
    lock->waiting_writers = 0;
}

void rwlock_read_lock(RWLock *lock) {
    pthread_mutex_lock(&lock->mutex);

    while (lock->writers > 0 || lock->waiting_writers > 0) {
        pthread_cond_wait(&lock->read_cond, &lock->mutex);
    }

    lock->readers++;
    pthread_mutex_unlock(&lock->mutex);
}

void rwlock_read_unlock(RWLock *lock) {
    pthread_mutex_lock(&lock->mutex);

    lock->readers--;
    if (lock->readers == 0 && lock->waiting_writers > 0) {
        pthread_cond_signal(&lock->write_cond);
    }

    pthread_mutex_unlock(&lock->mutex);
}

void rwlock_write_lock(RWLock *lock) {
    pthread_mutex_lock(&lock->mutex);

    lock->waiting_writers++;
    while (lock->readers > 0 || lock->writers > 0) {
        pthread_cond_wait(&lock->write_cond, &lock->mutex);
    }
    lock->waiting_writers--;
    lock->writers++;

    pthread_mutex_unlock(&lock->mutex);
}

void rwlock_write_unlock(RWLock *lock) {
    pthread_mutex_lock(&lock->mutex);

    lock->writers--;

    // Wake up waiting readers or writers
    if (lock->waiting_writers > 0) {
        pthread_cond_signal(&lock->write_cond);
    } else {
        pthread_cond_broadcast(&lock->read_cond);
    }

    pthread_mutex_unlock(&lock->mutex);
}
```

---

## 19.3 Concurrent Data Structures

### Thread-Safe Linked List
```c
#include <stdlib.h>
#include <pthread.h>

typedef struct Node {
    int data;
    struct Node* next;
    pthread_mutex_t mutex;
} Node;

typedef struct {
    Node* head;
    pthread_mutex_t mutex;
} ThreadSafeList;

void list_init(ThreadSafeList *list) {
    list->head = NULL;
    pthread_mutex_init(&list->mutex, NULL);
}

Node* node_create(int data) {
    Node *node = malloc(sizeof(Node));
    if (node) {
        node->data = data;
        node->next = NULL;
        pthread_mutex_init(&node->mutex, NULL);
    }
    return node;
}

void list_insert(ThreadSafeList *list, int data) {
    Node *new_node = node_create(data);
    if (!new_node) return;

    pthread_mutex_lock(&list->mutex);

    new_node->next = list->head;
    list->head = new_node;

    pthread_mutex_unlock(&list->mutex);
}

bool list_remove(ThreadSafeList *list, int data) {
    pthread_mutex_lock(&list->mutex);

    Node *current = list->head;
    Node *prev = NULL;

    while (current != NULL) {
        if (current->data == data) {
            if (prev == NULL) {
                list->head = current->next;
            } else {
                prev->next = current->next;
            }
            pthread_mutex_unlock(&list->mutex);
            pthread_mutex_destroy(&current->mutex);
            free(current);
            return true;
        }
        prev = current;
        current = current->next;
    }

    pthread_mutex_unlock(&list->mutex);
    return false;
}

void list_print(ThreadSafeList *list) {
    pthread_mutex_lock(&list->mutex);

    Node *current = list->head;
    printf("List: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");

    pthread_mutex_unlock(&list->mutex);
}

void list_destroy(ThreadSafeList *list) {
    pthread_mutex_lock(&list->mutex);

    Node *current = list->head;
    while (current != NULL) {
        Node *next = current->next;
        pthread_mutex_destroy(&current->mutex);
        free(current);
        current = next;
    }

    pthread_mutex_unlock(&list->mutex);
    pthread_mutex_destroy(&list->mutex);
}
```

### Concurrent Hash Table
```c
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define HASH_SIZE 16
#define MAX_KEY_LENGTH 64

typedef struct HashEntry {
    char key[MAX_KEY_LENGTH];
    int value;
    struct HashEntry* next;
} HashEntry;

typedef struct {
    HashEntry* entries[HASH_SIZE];
    pthread_mutex_t mutexes[HASH_SIZE];
} ConcurrentHashMap;

unsigned int hash_function(const char* key) {
    unsigned int hash = 5381;
    int c;
    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % HASH_SIZE;
}

void hashmap_init(ConcurrentHashMap *map) {
    for (int i = 0; i < HASH_SIZE; i++) {
        map->entries[i] = NULL;
        pthread_mutex_init(&map->mutexes[i], NULL);
    }
}

bool hashmap_put(ConcurrentHashMap *map, const char* key, int value) {
    unsigned int index = hash_function(key);
    pthread_mutex_lock(&map->mutexes[index]);

    // Check if key already exists
    HashEntry *current = map->entries[index];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            current->value = value;
            pthread_mutex_unlock(&map->mutexes[index]);
            return true;
        }
        current = current->next;
    }

    // Create new entry
    HashEntry *new_entry = malloc(sizeof(HashEntry));
    if (new_entry == NULL) {
        pthread_mutex_unlock(&map->mutexes[index]);
        return false;
    }

    strncpy(new_entry->key, key, MAX_KEY_LENGTH - 1);
    new_entry->key[MAX_KEY_LENGTH - 1] = '\0';
    new_entry->value = value;
    new_entry->next = map->entries[index];
    map->entries[index] = new_entry;

    pthread_mutex_unlock(&map->mutexes[index]);
    return true;
}

bool hashmap_get(ConcurrentHashMap *map, const char* key, int *value) {
    unsigned int index = hash_function(key);
    pthread_mutex_lock(&map->mutexes[index]);

    HashEntry *current = map->entries[index];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            *value = current->value;
            pthread_mutex_unlock(&map->mutexes[index]);
            return true;
        }
        current = current->next;
    }

    pthread_mutex_unlock(&map->mutexes[index]);
    return false;
}

void hashmap_destroy(ConcurrentHashMap *map) {
    for (int i = 0; i < HASH_SIZE; i++) {
        pthread_mutex_lock(&map->mutexes[i]);

        HashEntry *current = map->entries[i];
        while (current != NULL) {
            HashEntry *next = current->next;
            free(current);
            current = next;
        }

        pthread_mutex_unlock(&map->mutexes[i]);
        pthread_mutex_destroy(&map->mutexes[i]);
    }
}
```

---

## 19.4 Parallel Algorithms

### Parallel Summation
```c
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#define ARRAY_SIZE 1000000
#define NUM_THREADS 4

typedef struct {
    int *array;
    int start;
    int end;
    long long partial_sum;
} SumData;

void* partial_sum_worker(void* arg) {
    SumData *data = (SumData*)arg;
    data->partial_sum = 0;

    for (int i = data->start; i < data->end; i++) {
        data->partial_sum += data->array[i];
    }

    return NULL;
}

long long parallel_sum(int *array, int size) {
    pthread_t threads[NUM_THREADS];
    SumData thread_data[NUM_THREADS];
    int chunk_size = size / NUM_THREADS;

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_data[i].array = array;
        thread_data[i].start = i * chunk_size;
        thread_data[i].end = (i == NUM_THREADS - 1) ? size : (i + 1) * chunk_size;

        pthread_create(&threads[i], NULL, partial_sum_worker, &thread_data[i]);
    }

    // Wait for threads and combine results
    long long total_sum = 0;
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
        total_sum += thread_data[i].partial_sum;
    }

    return total_sum;
}
```

### Parallel Matrix Multiplication
```c
#define MATRIX_SIZE 1000

typedef struct {
    int **a, **b, **c;
    int start_row, end_row;
    int size;
} MatrixMulData;

void* matrix_multiply_worker(void* arg) {
    MatrixMulData *data = (MatrixMulData*)arg;

    for (int i = data->start_row; i < data->end_row; i++) {
        for (int j = 0; j < data->size; j++) {
            data->c[i][j] = 0;
            for (int k = 0; k < data->size; k++) {
                data->c[i][j] += data->a[i][k] * data->b[k][j];
            }
        }
    }

    return NULL;
}

void parallel_matrix_multiply(int **a, int **b, int **c, int size) {
    pthread_t threads[NUM_THREADS];
    MatrixMulData thread_data[NUM_THREADS];
    int rows_per_thread = size / NUM_THREADS;

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_data[i].a = a;
        thread_data[i].b = b;
        thread_data[i].c = c;
        thread_data[i].start_row = i * rows_per_thread;
        thread_data[i].end_row = (i == NUM_THREADS - 1) ? size : (i + 1) * rows_per_thread;
        thread_data[i].size = size;

        pthread_create(&threads[i], NULL, matrix_multiply_worker, &thread_data[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
}
```

### Parallel Merge Sort
```c
typedef struct {
    int *array;
    int left;
    int right;
} SortData;

void merge(int *array, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int *L = malloc(n1 * sizeof(int));
    int *R = malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) L[i] = array[left + i];
    for (int j = 0; j < n2; j++) R[j] = array[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            array[k] = L[i];
            i++;
        } else {
            array[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        array[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        array[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void merge_sort(int *array, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort(array, left, mid);
        merge_sort(array, mid + 1, right);
        merge(array, left, mid, right);
    }
}

void* parallel_merge_sort_worker(void* arg) {
    SortData *data = (SortData*)arg;
    merge_sort(data->array, data->left, data->right);
    return NULL;
}

void parallel_merge_sort(int *array, int size) {
    if (size < 1000) {  // Use sequential sort for small arrays
        merge_sort(array, 0, size - 1);
        return;
    }

    int mid = size / 2;
    pthread_t thread1, thread2;
    SortData data1 = {array, 0, mid - 1};
    SortData data2 = {array, mid, size - 1};

    pthread_create(&thread1, NULL, parallel_merge_sort_worker, &data1);
    pthread_create(&thread2, NULL, parallel_merge_sort_worker, &data2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    merge(array, 0, mid - 1, size - 1);
}
```

---

## 19.5 Thread Pools

### Simple Thread Pool Implementation
```c
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Task {
    void (*function)(void* arg);
    void* arg;
    struct Task* next;
} Task;

typedef struct {
    pthread_t *threads;
    Task *task_queue_head;
    Task *task_queue_tail;
    int thread_count;
    int queue_size;
    bool shutdown;

    pthread_mutex_t queue_mutex;
    pthread_cond_t queue_not_empty;
    pthread_cond_t queue_not_full;
} ThreadPool;

void* worker_thread(void* arg) {
    ThreadPool *pool = (ThreadPool*)arg;

    while (!pool->shutdown) {
        pthread_mutex_lock(&pool->queue_mutex);

        while (pool->task_queue_head == NULL && !pool->shutdown) {
            pthread_cond_wait(&pool->queue_not_empty, &pool->queue_mutex);
        }

        if (pool->shutdown) {
            pthread_mutex_unlock(&pool->queue_mutex);
            break;
        }

        Task *task = pool->task_queue_head;
        pool->task_queue_head = task->next;
        if (pool->task_queue_head == NULL) {
            pool->task_queue_tail = NULL;
        }
        pool->queue_size--;

        pthread_cond_signal(&pool->queue_not_full);
        pthread_mutex_unlock(&pool->queue_mutex);

        task->function(task->arg);
        free(task);
    }

    return NULL;
}

ThreadPool* thread_pool_create(int thread_count, int queue_size) {
    ThreadPool *pool = malloc(sizeof(ThreadPool));
    if (!pool) return NULL;

    pool->thread_count = thread_count;
    pool->queue_size = 0;
    pool->shutdown = false;
    pool->task_queue_head = NULL;
    pool->task_queue_tail = NULL;

    pthread_mutex_init(&pool->queue_mutex, NULL);
    pthread_cond_init(&pool->queue_not_empty, NULL);
    pthread_cond_init(&pool->queue_not_full, NULL);

    pool->threads = malloc(thread_count * sizeof(pthread_t));
    if (!pool->threads) {
        free(pool);
        return NULL;
    }

    for (int i = 0; i < thread_count; i++) {
        pthread_create(&pool->threads[i], NULL, worker_thread, pool);
    }

    return pool;
}

bool thread_pool_submit(ThreadPool *pool, void (*function)(void*), void* arg) {
    Task *new_task = malloc(sizeof(Task));
    if (!new_task) return false;

    new_task->function = function;
    new_task->arg = arg;
    new_task->next = NULL;

    pthread_mutex_lock(&pool->queue_mutex);

    if (pool->queue_size >= queue_size) {
        pthread_mutex_unlock(&pool->queue_mutex);
        free(new_task);
        return false;
    }

    if (pool->task_queue_tail == NULL) {
        pool->task_queue_head = pool->task_queue_tail = new_task;
    } else {
        pool->task_queue_tail->next = new_task;
        pool->task_queue_tail = new_task;
    }
    pool->queue_size++;

    pthread_cond_signal(&pool->queue_not_empty);
    pthread_mutex_unlock(&pool->queue_mutex);

    return true;
}

void thread_pool_destroy(ThreadPool *pool) {
    if (!pool) return;

    pthread_mutex_lock(&pool->queue_mutex);
    pool->shutdown = true;
    pthread_cond_broadcast(&pool->queue_not_empty);
    pthread_mutex_unlock(&pool->queue_mutex);

    for (int i = 0; i < pool->thread_count; i++) {
        pthread_join(pool->threads[i], NULL);
    }

    // Clean up remaining tasks
    while (pool->task_queue_head != NULL) {
        Task *task = pool->task_queue_head;
        pool->task_queue_head = task->next;
        free(task);
    }

    pthread_mutex_destroy(&pool->queue_mutex);
    pthread_cond_destroy(&pool->queue_not_empty);
    pthread_cond_destroy(&pool->queue_not_full);

    free(pool->threads);
    free(pool);
}
```

---

## 19.6 Performance Analysis and Optimization

### Measuring Parallel Performance
```c
#include <time.h>
#include <sys/time.h>

// High-resolution timer
double get_time() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec / 1000000.0;
}

// Performance measurement
void measure_performance(void (*sequential_func)(), void (*parallel_func)(),
                        const char *test_name) {
    printf("Testing %s:\n", test_name);

    // Measure sequential performance
    double start = get_time();
    sequential_func();
    double sequential_time = get_time() - start;
    printf("  Sequential time: %f seconds\n", sequential_time);

    // Measure parallel performance
    start = get_time();
    parallel_func();
    double parallel_time = get_time() - start;
    printf("  Parallel time: %f seconds\n", parallel_time);

    // Calculate speedup
    double speedup = sequential_time / parallel_time;
    printf("  Speedup: %fx\n", speedup);

    // Calculate efficiency (ideal speedup = number of threads)
    double efficiency = speedup / NUM_THREADS;
    printf("  Efficiency: %.1f%%\n\n", efficiency * 100);
}
```

### Common Parallel Programming Pitfalls
```c
#include <stdio.h>

// Race condition example (incorrect)
int shared_counter = 0;

void* bad_increment(void* arg) {
    for (int i = 0; i < 100000; i++) {
        shared_counter++;  // Race condition!
    }
    return NULL;
}

// Correct version with proper synchronization
void* good_increment(void* arg) {
    static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

    for (int i = 0; i < 100000; i++) {
        pthread_mutex_lock(&mutex);
        shared_counter++;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

// Deadlock example (incorrect)
typedef struct {
    pthread_mutex_t mutex1;
    pthread_mutex_t mutex2;
} DeadlockResources;

void* thread1_func(void* arg) {
    DeadlockResources *res = (DeadlockResources*)arg;

    pthread_mutex_lock(&res->mutex1);
    usleep(100);  // Increase chance of deadlock
    pthread_mutex_lock(&res->mutex2);

    // Critical section
    printf("Thread 1 in critical section\n");

    pthread_mutex_unlock(&res->mutex2);
    pthread_mutex_unlock(&res->mutex1);

    return NULL;
}

void* thread2_func(void* arg) {
    DeadlockResources *res = (DeadlockResources*)arg;

    pthread_mutex_lock(&res->mutex2);  // Different order!
    usleep(100);
    pthread_mutex_lock(&res->mutex1);

    // Critical section
    printf("Thread 2 in critical section\n");

    pthread_mutex_unlock(&res->mutex1);
    pthread_mutex_unlock(&res->mutex2);

    return NULL;
}

// Deadlock-free version (consistent lock ordering)
void* safe_thread2_func(void* arg) {
    DeadlockResources *res = (DeadlockResources*)arg;

    pthread_mutex_lock(&res->mutex1);  // Same order as thread1!
    pthread_mutex_lock(&res->mutex2);

    // Critical section
    printf("Thread 2 in critical section\n");

    pthread_mutex_unlock(&res->mutex2);
    pthread_mutex_unlock(&res->mutex1);

    return NULL;
}
```

---

## 🎯 Chapter Summary

### Key Concepts Covered
1. **Concurrency Fundamentals**: Understanding parallelism, threads, and synchronization
2. **Synchronization Primitives**: Mutexes, semaphores, condition variables
3. **Concurrent Data Structures**: Thread-safe implementations of common data structures
4. **Parallel Algorithms**: Parallel versions of fundamental algorithms
5. **Thread Pools**: Efficient task scheduling and execution
6. **Performance Analysis**: Measuring and optimizing parallel programs

### Skills Developed
- Designing and implementing thread-safe programs
- Understanding synchronization mechanisms and their trade-offs
- Building concurrent data structures
- Writing efficient parallel algorithms
- Debugging and optimizing parallel programs

### Applications
- Multi-threaded applications
- High-performance computing
- Real-time systems
- Network servers
- Parallel data processing

---

## 💻 Exercises

### Exercise 1: Parallel Image Processing
Create a parallel image processing library that applies filters to images using multiple threads.

### Exercise 2: Concurrent Web Server
Build a simple concurrent web server that handles multiple client connections simultaneously.

### Exercise 3: Parallel Sorting Comparison
Implement and compare different parallel sorting algorithms for various data sizes.

### Exercise 4: Producer-Consumer Pipeline
Create a multi-stage producer-consumer pipeline for data processing tasks.

### Exercise 5: Load Balancer
Implement a dynamic load balancer that distributes work among worker threads based on current load.

---

## 📚 Further Reading

- "The Art of Multiprocessor Programming" by Herlihy & Shavit
- "Programming with POSIX Threads" by David Butenhof
- "C++ Concurrency in Action" by Anthony Williams (concepts apply to C)
- Parallel computing research papers and online resources