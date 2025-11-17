# Chapters 11-13: Advanced Data Structures, Algorithms, System Programming - FAQ

## Advanced Data Structures (Chapter 11)

### Q: When should I use a linked list vs an array?
A:
- **Array**: Random access needed, fixed size known, memory compact
- **Linked list**: Frequent insertions/deletions, size changes, no random access needed

### Q: What's the time complexity of linked list operations?
A:
- Access head: O(1)
- Access tail (with tail pointer): O(1)
- Access middle element: O(n)
- Insert at head: O(1)
- Insert at tail (with tail pointer): O(1)
- Insert at middle: O(n)

### Q: Why use doubly linked lists vs singly linked lists?
A:
- **Singly**: Simpler, less memory, forward traversal only
- **Doubly**: Can traverse both directions, more complex, uses more memory

### Q: What's the difference between stack and queue?
A:
- **Stack**: LIFO (Last In, First Out) - like plates
- **Queue**: FIFO (First In, First Out) - like checkout line

### Q: When should I use a stack?
A:
- Function call stack simulation
- Expression evaluation
- Undo/redo functionality
- Depth-first search

### Q: When should I use a queue?
A:
- Task scheduling
- Breadth-first search
- Message passing
- Buffering between processes

### Q: What's the difference between BST and array for searching?
A:
- **Array (sorted)**: O(log n) with binary search, fast access
- **BST**: O(log n) average, O(n) worst case, dynamic insertion/deletion

### Q: Why might a binary search tree become unbalanced?
A:
- Inserting sorted data
- Not rebalancing after insertions/deletions
- Worst-case becomes linked list: O(n)

### Q: What are the advantages of hash tables?
A:
- O(1) average case for insert, delete, search
- Fast for large datasets
- Flexible key types

### Q: What are hash table collision resolution strategies?
A:
- **Chaining**: Linked lists at each hash bucket
- **Open addressing**: Linear probing, quadratic probing
- **Robin Hood hashing**: Minimize maximum probe length

### Q: When do hash tables perform poorly?
A:
- Many collisions (poor hash function)
- High load factor
- Non-random key distribution
- Poorly implemented collision resolution

### Q: Should I implement my own data structures?
A:
- For learning: Absolutely!
- For production: Usually use well-tested libraries
- Custom implementation may be needed for specific requirements

### Q: What's the difference between a deque and a queue?
A: Deque (double-ended queue) allows insertion/deletion from both ends. Queue only allows insertion at rear, deletion from front.

## Algorithms and Problem Solving (Chapter 12)

### Q: What is Big O notation and why does it matter?
A: Big O describes how algorithm runtime grows with input size. Matters because it predicts performance on large datasets.

### Q: Is O(n²) always bad?
A: Not necessarily. For small n or when O(n²) is optimal for the problem, it's fine. But for large datasets, consider alternatives.

### Q: When is binary search better than linear search?
A: When data is sorted and random access is available. O(log n) vs O(n) for large datasets.

### Q: What's the difference between bubble sort and quicksort?
A:
- **Bubble sort**: O(n²), simple, stable, good for small/nearly sorted data
- **Quicksort**: O(n log n) average, O(n²) worst case, faster for large random data

### Q: What are sorting stability requirements?
A: Stable sort maintains relative order of equal elements. Important when sorting by multiple criteria.

### Q: Which sorting algorithms are stable?
A:
- Stable: Bubble sort, insertion sort, merge sort, Timsort
- Unstable: Quicksort, heap sort, selection sort

### Q: What is recursion and when should I use it?
A: Function calls itself. Use for:
- Divide and conquer algorithms
- Tree/graph traversals
- Problems with natural recursive structure
- When recursive solution is much clearer than iterative

### Q: What are the downsides of recursion?
A:
- Stack overflow for deep recursion
- Can be slower than iterative solutions
- Harder to debug
- May use more memory

### Q: When should I use recursion vs iteration?
A:
- Use recursion when problem naturally recursive and depth is bounded
- Use iteration for performance-critical code or large input sizes
- Consider hybrid approaches for best of both

### Q: What is memoization?
A: Caching results of expensive function calls to avoid recomputation:
```c
int memo[100];
int fibonacci(int n) {
    if (n <= 1) return n;
    if (memo[n] != 0) return memo[n];
    return memo[n] = fibonacci(n-1) + fibonacci(n-2);
}
```

### Q: What's dynamic programming?
A: Solving complex problems by breaking into simpler subproblems and storing results.

### Q: What's the difference between memoization and dynamic programming?
A:
- **Memoization**: Top-down recursion with caching
- **Dynamic programming**: Bottom-up iteration with table

### Q: What are two pointers technique?
A: Using two pointers to solve problems efficiently:
```c
// Example: Find pair with given sum in sorted array
int left = 0, right = n-1;
while (left < right) {
    int sum = arr[left] + arr[right];
    if (sum == target) return true;
    else if (sum < target) left++;
    else right--;
}
```

### Q: When should I use sliding window technique?
A: For problems involving subarrays/contiguous subsequences with sliding properties.

### Q: What is greedy algorithm?
A: Makes locally optimal choice at each step, hoping to find global optimum.

### Q: When do greedy algorithms fail?
A:
- When local optimum doesn't lead to global optimum
- Problems requiring global optimization
- When future choices affect current decisions

## System Programming (Chapter 13)

### Q: What's the difference between a process and a thread?
A:
- **Process**: Independent program with own memory space
- **Thread**: Lightweight execution unit within process, shares memory

### Q: What's the difference between `fork()` and `exec()`?
A:
- `fork()`: Creates child process (duplicate of parent)
- `exec()`: Replaces current process image with new program

### Q: How do I create a child process?
A: Use `fork()`:
```c
pid_t pid = fork();
if (pid == 0) {
    // Child process
    execlp("ls", "ls", NULL);
} else if (pid > 0) {
    // Parent process
    wait(NULL);
}
```

### Q: What are zombie processes?
A: Child processes that have terminated but parent hasn't called `wait()` or `waitpid()`.

### Q: What are orphan processes?
A: Child processes whose parent has terminated. Adopted by init process.

### Q: What is IPC (Inter-Process Communication)?
A: Methods for processes to exchange data: pipes, shared memory, message queues, sockets.

### Q: When should I use pipes vs shared memory?
A:
- **Pipes**: Simple communication, related processes, streaming data
- **Shared memory**: High performance, large data, complex data structures

### Q: What's the difference between named and unnamed pipes?
A:
- **Unnamed pipes**: Related processes, temporary
- **Named pipes**: Unrelated processes, persistent filesystem entry

### Q: What are file descriptors?
A: Small integers that OS uses to refer to open files/connections (0=stdin, 1=stdout, 2=stderr).

### Q: What's the difference between file descriptors and FILE pointers?
A:
- **File descriptor**: Low-level OS handle (`int`)
- **FILE pointer**: C standard library wrapper (`FILE*`)

### Q: How do I implement a simple server?
A:
1. Create socket
2. Bind to address/port
3. Listen for connections
4. Accept connections
5. Handle client requests

### Q: What are the different socket types?
A:
- `SOCK_STREAM`: TCP (reliable, ordered)
- `SOCK_DGRAM`: UDP (unreliable, unordered)
- `SOCK_RAW`: Raw IP packets

### Q: What's the difference between TCP and UDP?
A:
- **TCP**: Reliable, ordered, connection-oriented, slower
- **UDP**: Unreliable, unordered, connectionless, faster

### Q: What are signals in Unix?
A: Software interrupts that notify processes of events: SIGINT, SIGTERM, SIGKILL, etc.

### Q: How do I handle signals?
A:
```c
void signal_handler(int signum) {
    // Handle signal
}
signal(SIGINT, signal_handler);
```

### Q: What is multithreading?
A: Multiple threads of execution within same process, sharing memory space.

### Q: How do I create threads?
A:
```c
pthread_t thread_id;
pthread_create(&thread_id, NULL, thread_function, arg);
pthread_join(thread_id, NULL);
```

### Q: What are the challenges of multithreading?
A:
- Race conditions
- Deadlocks
- Synchronization
- Debugging complexity
- Performance overhead

### Q: What is thread synchronization?
A: Mechanisms to coordinate thread access to shared resources: mutexes, semaphores, condition variables.

### Q: What's the difference between mutex and semaphore?
A:
- **Mutex**: Binary (locked/unlocked), mutual exclusion
- **Semaphore**: Counting, can allow multiple threads

### Q: What is a deadlock?
A: Two or more threads waiting for each other to release resources, causing indefinite wait.

### Q: How do I prevent deadlocks?
A:
- Lock resources in consistent order
- Use timeouts
- Avoid nested locks
- Design lock-free algorithms when possible

## Common Mistakes

### Q: Why does my linked list have memory leaks?
A:
- Not freeing nodes when deleting list
- Forgetting to free node data
- Double freeing memory

### Q: Why does my binary search not work?
A:
- Array not sorted
- Off-by-one errors in bounds
- Integer overflow in middle calculation

### Q: Why does my sort algorithm give wrong results?
A:
- Incorrect comparison logic
- Not handling equal elements properly
- Stability issues if required

### Q: Why does my fork() code not work as expected?
A:
- Not checking return value
- Race conditions with parent/child
- Not waiting for child processes
- Uninitialized variables in child

### Q: Why does my multithreaded code crash randomly?
A:
- Race conditions
- Unprotected shared data
- Deadlocks
- Invalid memory access

## Best Practices

### Q: How should I structure data structures?
A:
- Clear API with initialization/cleanup functions
- Consistent naming conventions
- Good error handling
- Memory management
- Documentation

### Q: How should I implement algorithms?
A:
- Handle edge cases
- Document complexity
- Provide clear interfaces
- Include test cases
- Optimize only when necessary

### Q: How should I handle system programming errors?
A:
- Check return values of all system calls
- Use `perror()` for error messages
- Clean up resources before exit
- Provide meaningful error messages

### Q: How should I handle concurrency?
A:
- Minimize shared state
- Use appropriate synchronization
- Keep critical sections short
- Test thoroughly
- Consider thread safety in design

---

## 💡 Pro Tips

### Data Structures
1. **Choose the right data structure** for the problem
2. **Consider memory overhead** of complex structures
3. **Implement clear interfaces** for data structure operations
4. **Test edge cases**: empty structures, single elements
5. **Document time/space complexity** of operations

### Algorithms
1. **Profile before optimizing** - measure first
2. **Consider trade-offs**: time vs space vs simplicity
3. **Test with edge cases**: empty input, large input, duplicate values
4. **Use appropriate data structures** - algorithm depends on structure
5. **Understand Big O** - predict performance on large inputs

### System Programming
1. **Always check return values** of system calls
2. **Handle signals properly** - reestablish handlers
3. **Clean up resources** - close files, free memory, join threads
4. **Use appropriate IPC mechanism** for the problem
5. **Be careful with security** - validate all inputs
6. **Test on different platforms** - portability considerations

### Concurrency
1. **Minimize shared mutable state**
2. **Use thread-safe libraries** when available
3. **Keep critical sections small**
4. **Test thoroughly** with stress tests
5. **Consider lock-free alternatives** when possible