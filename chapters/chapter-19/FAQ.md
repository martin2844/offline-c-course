# Chapter 19: Parallel Computing and Concurrency - FAQ

## Parallel Computing Fundamentals

### Q: What's the difference between concurrency and parallelism?
A: **Concurrency** is dealing with multiple tasks at once, **parallelism** is doing multiple tasks at once. Concurrency is about structure, parallelism is about execution.

### Q: Why learn parallel programming in C?
A: Modern computers have multiple cores, and C gives you low-level control to maximize performance for computationally intensive tasks.

### Q: When should I use multiple threads?
A: Use threads when:
- Tasks can be done independently
- You have CPU-bound workloads
- You need responsive user interfaces
- You're doing parallel computations

### Q: What's a race condition?
A: When multiple threads access shared data without proper synchronization, leading to unpredictable results:
```c
int counter = 0;
void increment() {
    counter++;  // Not thread-safe! Can lose increments
}
```

### Q: What's Amdahl's Law?
A: The theoretical maximum speedup of parallel processing is limited by the sequential portion of the program: `Speedup = 1 / (S + P/N)` where S is sequential portion, P is parallel portion, N is number of processors.

## Threading Basics

### Q: What's the difference between processes and threads?
A: **Processes**: Independent memory spaces, heavier
**Threads**: Shared memory space, lighter, more efficient for data sharing

### Q: How do I create threads in C?
A: Use pthreads (POSIX threads):
```c
#include <pthread.h>

void* thread_function(void* arg) {
    // Thread code here
    return NULL;
}

int main() {
    pthread_t thread;
    pthread_create(&thread, NULL, thread_function, NULL);
    pthread_join(thread, NULL);
    return 0;
}
```

### Q: What does `pthread_join` do?
A: Waits for a thread to finish execution and collects its return value.

### Q: What happens if I don't join threads?
A: The thread becomes a "zombie thread" - its resources aren't released until the program exits.

### Q: How many threads should I use?
A: Usually one per CPU core for CPU-bound tasks, more for I/O-bound tasks. Start with `sysconf(_SC_NPROCESSORS_ONLN)` to get core count.

## Synchronization

### Q: What's a mutex?
A: A mutual exclusion lock that ensures only one thread can access a critical section at a time:
```c
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

pthread_mutex_lock(&mutex);
// Critical section code
pthread_mutex_unlock(&mutex);
```

### Q: What's a deadlock?
A: When two or more threads are waiting for each other to release resources, causing indefinite waiting.

### Q: How do I prevent deadlocks?
A:
- Always lock resources in the same order
- Use timeout mechanisms
- Minimize lock holding time
- Avoid nested locks when possible

### Q: What's a condition variable?
A: A synchronization primitive that allows threads to wait for specific conditions to become true:
```c
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

// Wait
pthread_cond_wait(&cond, &mutex);

// Signal
pthread_cond_signal(&cond);
```

### Q: What's a semaphore?
A: A synchronization object that controls access to resources through a counter:
```c
#include <semaphore.h>

sem_t semaphore;
sem_init(&semaphore, 0, 1);  // Initialize with count of 1

sem_wait(&semaphore);  // Wait
sem_post(&semaphore);  // Signal
```

## Thread Safety

### Q: What makes code thread-safe?
A: Code is thread-safe when it can be safely executed by multiple threads simultaneously without causing race conditions or data corruption.

### Q: What's the difference between thread-safe and reentrant?
A: **Thread-safe**: Can be called by multiple threads
**Reentrant**: Can be called multiple times simultaneously (even by the same thread)

### Q: Which C library functions are thread-safe?
A: Most modern C library functions are thread-safe, but check documentation. Functions like `strtok()` are notoriously not thread-safe.

### Q: How do I make global variables thread-safe?
A: Use mutexes, atomic operations, or thread-local storage:
```c
// Thread-local storage
__thread int local_var;

// Atomic operations
#include <stdatomic.h>
atomic_int counter = ATOMIC_VAR_INIT(0);
atomic_fetch_add(&counter, 1);
```

### Q: What's thread-local storage?
A: Variables that have separate instances for each thread:
```c
__thread int thread_id;  // Each thread gets its own copy
```

## Performance

### Q: Why is my parallel code slower than sequential?
A: Common causes:
- Too much synchronization overhead
- False sharing (cache line contention)
- Lock contention
- Too many threads for available cores
- Sequential bottleneck

### Q: What's false sharing?
A: When multiple threads access different variables that share the same cache line, causing unnecessary cache invalidation.

### Q: How do I measure parallel performance?
A: Use speedup and efficiency:
- **Speedup**: Sequential time / Parallel time
- **Efficiency**: Speedup / Number of threads

### Q: What's the overhead of creating threads?
A: Thread creation has overhead (~100 microseconds to 1 millisecond), so thread pools are better for short tasks.

### Q: When does parallelization not help?
A:
- Tasks are inherently sequential
- Overhead exceeds parallel benefits
- Memory bandwidth is bottleneck
- Synchronization costs are high

## Common Problems

### Q: Why does my program crash randomly?
A: Likely race conditions or memory corruption from improper synchronization.

### Q: Why does my program hang?
A: Probably deadlock - check for circular wait conditions.

### Q: Why are my results inconsistent?
A: Race conditions causing non-deterministic behavior.

### Q: Why do I get segmentation faults?
A: Could be use-after-free in multithreaded code or accessing freed memory from another thread.

### Q: How do I debug multithreaded programs?
A:
- Use thread sanitizers: `-fsanitize=thread`
- Use GDB with thread commands
- Add debug prints with thread IDs
- Use static analysis tools

## Advanced Concepts

### Q: What's a thread pool?
A: A collection of worker threads that execute tasks from a queue, reducing thread creation overhead:
```c
ThreadPool *pool = thread_pool_create(4, 100);  // 4 threads, 100 task queue
thread_pool_submit(pool, task_function, arg);
```

### Q: What's lock-free programming?
A: Programming without locks using atomic operations, often more complex but can eliminate lock contention.

### Q: What's a read-write lock?
A: Allows multiple readers or one exclusive writer, useful for read-heavy data structures:
```c
pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;

pthread_rwlock_rdlock(&rwlock);   // Read lock
pthread_rwlock_wrlock(&rwlock);   // Write lock
```

### Q: What's memory ordering?
A: Rules for how memory operations become visible to other threads, crucial for lock-free programming.

### Q: What are atomic operations?
A: Operations that complete indivisibly, preventing race conditions without locks:
```c
#include <stdatomic.h>
atomic_int counter = ATOMIC_VAR_INIT(0);
int old = atomic_fetch_add(&counter, 1);
```

## Data Structures

### Q: What makes a data structure thread-safe?
A: Proper synchronization of all modifications and reads, ensuring consistent state.

### Q: How do I implement a thread-safe queue?
A: Use mutexes and condition variables, or lock-free algorithms with atomic operations.

### Q: What's the difference between blocking and non-blocking queues?
A: **Blocking**: Thread waits if queue is empty/full
**Non-blocking**: Returns immediately, may fail if operation can't complete

### Q: How do I handle memory management in concurrent code?
A:
- Use reference counting
- Careful ownership transfer
- Avoid sharing complex data structures when possible
- Use memory pools

### Q: What's the safest way to share data between threads?
A: Avoid sharing when possible. If necessary:
- Use immutable data
- Use proper synchronization
- Consider message passing instead

## Tools and Debugging

### Q: How do I compile with thread sanitizers?
A:
```bash
gcc -fsanitize=thread -pthread -g program.c -o program
```

### Q: What tools help with thread debugging?
A:
- **ThreadSanitizer**: Detects data races
- **Helgrind** (Valgrind): Thread error detector
- **GDB**: Thread debugging with `info threads`, `thread N`, `bt`
- **Static analyzers**: Find potential issues at compile time

### Q: How do I use GDB with threads?
A:
- `info threads`: List all threads
- `thread N`: Switch to thread N
- `bt`: Show stack trace for current thread
- `thread apply all bt`: Show stack traces for all threads

### Q: What's `-pthread` compiler flag?
A: Links with pthread library and defines necessary macros. Always use it when compiling with pthreads.

### Q: How do I detect data races?
A: Use ThreadSanitizer:
```bash
gcc -fsanitize=thread program.c -o program
./program
```

## Best Practices

### Q: Should I use global variables in multithreaded programs?
A: Avoid them when possible. If necessary, protect with proper synchronization.

### Q: How many locks is too many?
A: Too many locks can cause complexity and deadlocks. Try to minimize lock count and scope.

### Q: Should I use recursive locks?
A: Avoid if possible. They can mask design issues and make code harder to reason about.

### Q: How do I handle errors in multithreaded code?
A:
- Check return values from pthread functions
- Have consistent error handling strategy
- Consider cleanup handlers
- Use RAII-style patterns when possible

### Q: What's the best way to test multithreaded code?
A:
- Run many iterations
- Vary thread counts
- Use ThreadSanitizer
- Stress test with high contention
- Test on different hardware

## Architecture Patterns

### Q: What's the Producer-Consumer pattern?
A: One or more threads produce data that other threads consume, typically using a queue for communication.

### Q: What's the MapReduce pattern?
A: Parallel processing where data is mapped (processed independently) and then reduced (combined).

### Q: What's thread-per-connection architecture?
A: Creating a new thread for each client connection, common in network servers.

### Q: What's the Reactor pattern?
A: Event-driven architecture where a single thread monitors multiple I/O sources and dispatches work to worker threads.

### Q: When should I use processes vs threads?
A: **Processes**: For isolation, security, different programs
**Threads**: For shared data, lower overhead, same program

## Modern Extensions

### Q: What's C11 thread support?
A: C11 introduced standard thread support with `<threads.h>`, but not all compilers support it well yet.

### Q: Should I use C11 threads or pthreads?
A: Use pthreads for better portability and tool support currently. C11 threads may become standard in the future.

### Q: What's OpenMP?
A: Pragmas-based parallel programming extension, good for data parallelism:
```c
#pragma omp parallel for
for (int i = 0; i < N; i++) {
    // Parallel loop
}
```

### Q: When should I use OpenMP vs pthreads?
A: **OpenMP**: Easier for data parallelism, loops
**Pthreads**: Better for complex synchronization, task parallelism

### Q: What's SIMD?
A: Single Instruction Multiple Data - using CPU vector instructions to process multiple data elements simultaneously.

---

## 💡 Pro Tips

### Design Principles
1. **Minimize shared state** - reduces synchronization needs
2. **Use coarse-grained locking first** - optimize later if needed
3. **Avoid nested locks** - prevents deadlocks
4. **Lock for minimum time** - reduces contention
5. **Design for thread safety from start** - retrofitting is hard

### Performance Optimization
1. **Profile before optimizing** - measure actual bottlenecks
2. **Consider memory locality** - reduce false sharing
3. **Use thread pools** - avoid creation overhead
4. **Batch small operations** - reduce synchronization
5. **Choose appropriate granularity** - balance parallelism and overhead

### Debugging Strategy
1. **Use thread sanitizers** - catch data races automatically
2. **Add logging with thread IDs** - understand execution flow
3. **Reproduce with deterministic input** - isolate issues
4. **Test with varying thread counts** - stress test synchronization
5. **Use appropriate tools** - GDB, Valgrind, sanitizers

### Common Pitfalls to Avoid
1. **Assuming operations are atomic** - most aren't
2. **Forgetting to join threads** - resource leaks
3. **Using wrong lock order** - deadlocks
4. **Ignoring return values** - missed error conditions
5. **Over-synchronizing** - performance bottlenecks