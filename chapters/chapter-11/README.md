# Chapter 11: Advanced Data Structures

## Learning Objectives
By the end of this chapter, you will be able to:
- Implement linked lists (singly, doubly, circular)
- Create and use stacks and queues
- Build binary search trees and understand tree operations
- Implement basic hash tables with collision resolution
- Represent and traverse graphs
- Choose appropriate data structures for different problems

## Introduction to Advanced Data Structures

While C provides basic arrays and structures, many real-world problems require more sophisticated data structures. This chapter introduces you to fundamental data structures that form the backbone of efficient algorithms and complex applications.

### From Arrays to Advanced Structures

Throughout this course, you've worked with arrays - C's most fundamental data structure. Arrays are powerful but have limitations:
- **Fixed size**: Arrays can't grow or shrink dynamically
- **Inefficient insertions**: Inserting in the middle requires shifting elements
- **Memory waste**: Arrays may allocate more memory than needed
- **Sequential access**: Finding specific values often requires linear search

Advanced data structures address these limitations by providing:
- **Dynamic sizing**: Grow and shrink as needed
- **Efficient operations**: Optimized for specific types of access
- **Memory efficiency**: Use only the memory you need
- **Specialized access patterns**: Fast search, insertion, or deletion based on use case

### Why Advanced Data Structures Matter

1. **Efficiency**: Different structures offer different performance trade-offs
   - Arrays: O(1) access, O(n) search/insertion/deletion
   - Linked lists: O(n) access/search, O(1) insertion/deletion at ends
   - Trees: O(log n) average for most operations
   - Hash tables: O(1) average for search/insertion/deletion

2. **Scalability**: Some structures handle growing data better than arrays
   - Dynamic memory allocation allows handling unknown data sizes
   - Efficient algorithms maintain performance as data grows
   - Memory usage scales with actual needs

3. **Flexibility**: Complex problems often need specialized organization
   - Hierarchical data (trees)
   - Priority-based access (heaps)
   - Key-value pairs (hash tables)
   - Graph relationships (graphs)

4. **Problem Solving**: Many algorithms are built around specific data structures
   - Sorting algorithms often use specific tree structures
   - Search algorithms depend on data organization
   - Caching systems use hash tables
   - Scheduling uses priority queues

### Understanding Memory Layout

Before diving into specific structures, it's crucial to understand how they differ from arrays in memory:

**Arrays (Contiguous Memory):**
```
[100][200][300][400]  // All elements adjacent in memory
```
- Pros: Cache-friendly, O(1) random access
- Cons: Fixed size, expensive insertions/deletions

**Linked Lists (Scattered Memory):**
```
[100] -> [300] -> [200] -> [400]  // Elements scattered, linked by pointers
```
- Pros: Dynamic size, efficient insertions/deletions
- Cons: Pointer overhead, poor cache locality

**Trees (Hierarchical Memory):**
```
    [200]
    /   \
[100]   [300]
          /
       [400]
```
- Pros: Logarithmic operations, sorted data
- Cons: More complex, pointer overhead

### Performance Analysis Framework

When evaluating data structures, we use **Big O notation** to describe performance:

- **O(1)**: Constant time - operation time doesn't depend on data size
- **O(log n)**: Logarithmic time - time increases slowly with data size
- **O(n)**: Linear time - time increases proportionally with data size
- **O(n log n)**: Linearithmic time - common for efficient sorting
- **O(n²)**: Quadratic time - time increases quadratically with data size

**Space Complexity**: Memory usage relative to data size
- **O(1)**: Constant extra space
- **O(n)**: Linear extra space
- **O(n²)**: Quadratic extra space

### Trade-offs and Design Decisions

No single data structure is best for all problems. Consider:

1. **Access Patterns**: How will you access the data most often?
   - Random access → Arrays
   - Sequential access → Linked lists
   - Key-based access → Hash tables
   - Range queries → Trees

2. **Data Dynamics**: How often will data change?
   - Static data → Arrays
   - Frequent insertions/deletions → Linked lists or trees
   - Mixed operations → Balanced trees

3. **Memory Constraints**: How much memory can you use?
   - Minimal overhead → Arrays
   - Flexibility needed → Dynamic structures
   - Cache performance critical → Arrays

4. **Implementation Complexity**: How complex can your solution be?
   - Simple requirements → Basic structures
   - Performance critical → Optimized structures
   - Maintainability important → Well-documented standard structures

This understanding will guide your choice of data structures throughout your programming career.

## Linked Lists

### What are Linked Lists?
A linked list is a linear collection of data elements whose order is not given by their physical placement in memory. Instead, each element points to the next.

### Singly Linked List Implementation

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Node structure for singly linked list
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// List structure to track head and size
typedef struct {
    Node* head;
    int size;
} LinkedList;

// Function prototypes
LinkedList* create_list();
void free_list(LinkedList* list);
void insert_front(LinkedList* list, int data);
void insert_back(LinkedList* list, int data);
void insert_at(LinkedList* list, int data, int position);
void delete_front(LinkedList* list);
void delete_back(LinkedList* list);
void delete_at(LinkedList* list, int position);
void delete_value(LinkedList* list, int value);
int find(LinkedList* list, int value);
void print_list(LinkedList* list);
int is_empty(LinkedList* list);

// Create a new empty list
LinkedList* create_list() {
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    if (list == NULL) {
        return NULL;
    }
    list->head = NULL;
    list->size = 0;
    return list;
}

// Free all nodes and the list
void free_list(LinkedList* list) {
    if (list == NULL) return;

    Node* current = list->head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}

// Insert at the front of the list
void insert_front(LinkedList* list, int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    new_node->data = data;
    new_node->next = list->head;
    list->head = new_node;
    list->size++;
}

// Insert at the back of the list
void insert_back(LinkedList* list, int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    new_node->data = data;
    new_node->next = NULL;

    if (list->head == NULL) {
        list->head = new_node;
    } else {
        Node* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
    list->size++;
}

// Insert at a specific position (0-indexed)
void insert_at(LinkedList* list, int data, int position) {
    if (position < 0 || position > list->size) {
        printf("Invalid position!\n");
        return;
    }

    if (position == 0) {
        insert_front(list, data);
        return;
    }

    if (position == list->size) {
        insert_back(list, data);
        return;
    }

    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    new_node->data = data;

    Node* current = list->head;
    for (int i = 0; i < position - 1; i++) {
        current = current->next;
    }

    new_node->next = current->next;
    current->next = new_node;
    list->size++;
}

// Delete from the front
void delete_front(LinkedList* list) {
    if (is_empty(list)) {
        printf("List is empty!\n");
        return;
    }

    Node* temp = list->head;
    list->head = list->head->next;
    free(temp);
    list->size--;
}

// Delete from the back
void delete_back(LinkedList* list) {
    if (is_empty(list)) {
        printf("List is empty!\n");
        return;
    }

    if (list->head->next == NULL) {
        delete_front(list);
        return;
    }

    Node* current = list->head;
    while (current->next->next != NULL) {
        current = current->next;
    }

    free(current->next);
    current->next = NULL;
    list->size--;
}

// Delete at a specific position
void delete_at(LinkedList* list, int position) {
    if (position < 0 || position >= list->size) {
        printf("Invalid position!\n");
        return;
    }

    if (position == 0) {
        delete_front(list);
        return;
    }

    Node* current = list->head;
    for (int i = 0; i < position - 1; i++) {
        current = current->next;
    }

    Node* temp = current->next;
    current->next = temp->next;
    free(temp);
    list->size--;
}

// Delete first occurrence of a value
void delete_value(LinkedList* list, int value) {
    if (is_empty(list)) {
        printf("List is empty!\n");
        return;
    }

    if (list->head->data == value) {
        delete_front(list);
        return;
    }

    Node* current = list->head;
    while (current->next != NULL && current->next->data != value) {
        current = current->next;
    }

    if (current->next == NULL) {
        printf("Value not found!\n");
        return;
    }

    Node* temp = current->next;
    current->next = temp->next;
    free(temp);
    list->size--;
}

// Find position of a value (return -1 if not found)
int find(LinkedList* list, int value) {
    Node* current = list->head;
    int position = 0;

    while (current != NULL) {
        if (current->data == value) {
            return position;
        }
        current = current->next;
        position++;
    }

    return -1; // Not found
}

// Print the list
void print_list(LinkedList* list) {
    if (is_empty(list)) {
        printf("List: [empty]\n");
        return;
    }

    printf("List: [");
    Node* current = list->head;
    while (current != NULL) {
        printf("%d", current->data);
        if (current->next != NULL) {
            printf(" -> ");
        }
        current = current->next;
    }
    printf("] (size: %d)\n", list->size);
}

// Check if list is empty
int is_empty(LinkedList* list) {
    return list->head == NULL;
}

int main() {
    LinkedList* list = create_list();

    printf("Linked List Demo\n");
    printf("================\n");

    // Insert elements
    printf("\n1. Inserting elements:\n");
    insert_back(list, 10);
    insert_back(list, 20);
    insert_back(list, 30);
    print_list(list);

    printf("\n2. Inserting at front:\n");
    insert_front(list, 5);
    print_list(list);

    printf("\n3. Inserting at position 2:\n");
    insert_at(list, 15, 2);
    print_list(list);

    // Search
    printf("\n4. Searching for elements:\n");
    int search_value = 20;
    int position = find(list, search_value);
    if (position != -1) {
        printf("Found %d at position %d\n", search_value, position);
    } else {
        printf("%d not found\n", search_value);
    }

    // Delete operations
    printf("\n5. Deleting operations:\n");
    printf("Deleting front: ");
    delete_front(list);
    print_list(list);

    printf("Deleting back: ");
    delete_back(list);
    print_list(list);

    printf("Deleting value 15: ");
    delete_value(list, 15);
    print_list(list);

    // Final list
    printf("\nFinal list:\n");
    print_list(list);

    // Clean up
    free_list(list);
    printf("\nList freed successfully.\n");

    return 0;
}
```

### Doubly Linked List

```c
#include <stdio.h>
#include <stdlib.h>

// Node for doubly linked list
typedef struct DNode {
    int data;
    struct DNode* prev;
    struct DNode* next;
} DNode;

typedef struct {
    DNode* head;
    DNode* tail;
    int size;
} DoublyLinkedList;

// Basic operations
DoublyLinkedList* create_dlist();
void free_dlist(DoublyLinkedList* list);
void insert_front_dlist(DoublyLinkedList* list, int data);
void insert_back_dlist(DoublyLinkedList* list, int data);
void delete_front_dlist(DoublyLinkedList* list);
void delete_back_dlist(DoublyLinkedList* list);
void print_dlist_forward(DoublyLinkedList* list);
void print_dlist_backward(DoublyLinkedList* list);

DoublyLinkedList* create_dlist() {
    DoublyLinkedList* list = (DoublyLinkedList*)malloc(sizeof(DoublyLinkedList));
    if (list == NULL) return NULL;

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

void free_dlist(DoublyLinkedList* list) {
    if (list == NULL) return;

    DNode* current = list->head;
    while (current != NULL) {
        DNode* temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}

void insert_front_dlist(DoublyLinkedList* list, int data) {
    DNode* new_node = (DNode*)malloc(sizeof(DNode));
    if (new_node == NULL) return;

    new_node->data = data;
    new_node->prev = NULL;
    new_node->next = list->head;

    if (list->head != NULL) {
        list->head->prev = new_node;
    } else {
        list->tail = new_node;
    }

    list->head = new_node;
    list->size++;
}

void insert_back_dlist(DoublyLinkedList* list, int data) {
    DNode* new_node = (DNode*)malloc(sizeof(DNode));
    if (new_node == NULL) return;

    new_node->data = data;
    new_node->next = NULL;
    new_node->prev = list->tail;

    if (list->tail != NULL) {
        list->tail->next = new_node;
    } else {
        list->head = new_node;
    }

    list->tail = new_node;
    list->size++;
}

void delete_front_dlist(DoublyLinkedList* list) {
    if (list->head == NULL) return;

    DNode* temp = list->head;
    list->head = list->head->next;

    if (list->head != NULL) {
        list->head->prev = NULL;
    } else {
        list->tail = NULL;
    }

    free(temp);
    list->size--;
}

void delete_back_dlist(DoublyLinkedList* list) {
    if (list->tail == NULL) return;

    DNode* temp = list->tail;
    list->tail = list->tail->prev;

    if (list->tail != NULL) {
        list->tail->next = NULL;
    } else {
        list->head = NULL;
    }

    free(temp);
    list->size--;
}

void print_dlist_forward(DoublyLinkedList* list) {
    printf("Forward: [");
    DNode* current = list->head;
    while (current != NULL) {
        printf("%d", current->data);
        if (current->next != NULL) printf(" <-> ");
        current = current->next;
    }
    printf("]\n");
}

void print_dlist_backward(DoublyLinkedList* list) {
    printf("Backward: [");
    DNode* current = list->tail;
    while (current != NULL) {
        printf("%d", current->data);
        if (current->prev != NULL) printf(" <-> ");
        current = current->prev;
    }
    printf("]\n");
}

// Demo
int main() {
    DoublyLinkedList* dlist = create_dlist();

    printf("Doubly Linked List Demo\n");
    printf("======================\n");

    insert_back_dlist(dlist, 10);
    insert_back_dlist(dlist, 20);
    insert_back_dlist(dlist, 30);
    insert_front_dlist(dlist, 5);

    print_dlist_forward(dlist);
    print_dlist_backward(dlist);

    delete_front_dlist(dlist);
    delete_back_dlist(dlist);

    printf("\nAfter deletions:\n");
    print_dlist_forward(dlist);

    free_dlist(dlist);
    return 0;
}
```

## Stacks

### Stack Implementation Using Linked List

```c
#include <stdio.h>
#include <stdlib.h>

// Stack using linked list
typedef struct StackNode {
    int data;
    struct StackNode* next;
} StackNode;

typedef struct {
    StackNode* top;
    int size;
} Stack;

Stack* create_stack();
void free_stack(Stack* stack);
void push(Stack* stack, int data);
int pop(Stack* stack);
int peek(Stack* stack);
int is_empty(Stack* stack);
int get_size(Stack* stack);

Stack* create_stack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (stack == NULL) return NULL;

    stack->top = NULL;
    stack->size = 0;
    return stack;
}

void free_stack(Stack* stack) {
    if (stack == NULL) return;

    while (!is_empty(stack)) {
        pop(stack);
    }
    free(stack);
}

void push(Stack* stack, int data) {
    StackNode* new_node = (StackNode*)malloc(sizeof(StackNode));
    if (new_node == NULL) {
        printf("Stack overflow!\n");
        return;
    }

    new_node->data = data;
    new_node->next = stack->top;
    stack->top = new_node;
    stack->size++;
}

int pop(Stack* stack) {
    if (is_empty(stack)) {
        printf("Stack underflow!\n");
        return -1;
    }

    StackNode* temp = stack->top;
    int data = temp->data;
    stack->top = temp->next;
    free(temp);
    stack->size--;
    return data;
}

int peek(Stack* stack) {
    if (is_empty(stack)) {
        printf("Stack is empty!\n");
        return -1;
    }

    return stack->top->data;
}

int is_empty(Stack* stack) {
    return stack->top == NULL;
}

int get_size(Stack* stack) {
    return stack->size;
}

// Print stack
void print_stack(Stack* stack) {
    if (is_empty(stack)) {
        printf("Stack: [empty]\n");
        return;
    }

    printf("Stack (top -> bottom): [");
    StackNode* current = stack->top;
    while (current != NULL) {
        printf("%d", current->data);
        if (current->next != NULL) {
            printf(", ");
        }
        current = current->next;
    }
    printf("]\n");
}

// Stack applications
void reverse_string_using_stack(const char* str) {
    Stack* stack = create_stack();

    // Push each character
    for (int i = 0; str[i] != '\0'; i++) {
        push(stack, str[i]);
    }

    printf("Original: %s\n", str);
    printf("Reversed: ");

    // Pop to reverse
    while (!is_empty(stack)) {
        printf("%c", pop(stack));
    }
    printf("\n");

    free_stack(stack);
}

int is_palindrome(const char* str) {
    Stack* stack = create_stack();
    int length = 0;

    // Find length and push first half
    while (str[length] != '\0') {
        push(stack, str[length]);
        length++;
    }

    // Check palindrome
    for (int i = 0; i < length; i++) {
        if (str[i] != pop(stack)) {
            free_stack(stack);
            return 0; // Not palindrome
        }
    }

    free_stack(stack);
    return 1; // Is palindrome
}

int main() {
    Stack* stack = create_stack();

    printf("Stack Demo\n");
    printf("==========\n");

    // Basic stack operations
    printf("\n1. Pushing elements:\n");
    push(stack, 10);
    push(stack, 20);
    push(stack, 30);
    push(stack, 40);
    print_stack(stack);

    printf("\n2. Top element (peek): %d\n", peek(stack));
    printf("Stack size: %d\n", get_size(stack));

    printf("\n3. Popping elements:\n");
    while (!is_empty(stack)) {
        printf("Popped: %d\n", pop(stack));
        print_stack(stack);
    }

    // Stack applications
    printf("\n4. String reversal:\n");
    reverse_string_using_stack("Hello, World!");

    printf("\n5. Palindrome check:\n");
    char str1[] = "racecar";
    char str2[] = "hello";

    printf("\"%s\" is %s\n", str1, is_palindrome(str1) ? "palindrome" : "not palindrome");
    printf("\"%s\" is %s\n", str2, is_palindrome(str2) ? "palindrome" : "not palindrome");

    free_stack(stack);
    return 0;
}
```

## Queues

### Queue Implementation Using Linked List

```c
#include <stdio.h>
#include <stdlib.h>

// Queue using linked list
typedef struct QueueNode {
    int data;
    struct QueueNode* next;
} QueueNode;

typedef struct {
    QueueNode* front;
    QueueNode* rear;
    int size;
} Queue;

Queue* create_queue();
void free_queue(Queue* queue);
void enqueue(Queue* queue, int data);
int dequeue(Queue* queue);
int peek_queue(Queue* queue);
int is_queue_empty(Queue* queue);
int get_queue_size(Queue* queue);
void print_queue(Queue* queue);

Queue* create_queue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if (queue == NULL) return NULL;

    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
    return queue;
}

void free_queue(Queue* queue) {
    if (queue == NULL) return;

    while (!is_queue_empty(queue)) {
        dequeue(queue);
    }
    free(queue);
}

void enqueue(Queue* queue, int data) {
    QueueNode* new_node = (QueueNode*)malloc(sizeof(QueueNode));
    if (new_node == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    new_node->data = data;
    new_node->next = NULL;

    if (is_queue_empty(queue)) {
        queue->front = new_node;
        queue->rear = new_node;
    } else {
        queue->rear->next = new_node;
        queue->rear = new_node;
    }
    queue->size++;
}

int dequeue(Queue* queue) {
    if (is_queue_empty(queue)) {
        printf("Queue is empty!\n");
        return -1;
    }

    QueueNode* temp = queue->front;
    int data = temp->data;
    queue->front = queue->front->next;

    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    free(temp);
    queue->size--;
    return data;
}

int peek_queue(Queue* queue) {
    if (is_queue_empty(queue)) {
        printf("Queue is empty!\n");
        return -1;
    }

    return queue->front->data;
}

int is_queue_empty(Queue* queue) {
    return queue->front == NULL;
}

int get_queue_size(Queue* queue) {
    return queue->size;
}

void print_queue(Queue* queue) {
    if (is_queue_empty(queue)) {
        printf("Queue: [empty]\n");
        return;
    }

    printf("Queue (front -> rear): [");
    QueueNode* current = queue->front;
    while (current != NULL) {
        printf("%d", current->data);
        if (current->next != NULL) {
            printf(", ");
        }
        current = current->next;
    }
    printf("]\n");
}

// Queue application: Josephus problem
void josephus_problem(int n, int k) {
    Queue* queue = create_queue();

    // Initialize queue with people numbered 1 to n
    for (int i = 1; i <= n; i++) {
        enqueue(queue, i);
    }

    printf("Josephus Problem (n=%d, k=%d):\n", n, k);
    printf("Elimination order: ");

    while (!is_queue_empty(queue)) {
        // Move k-1 people from front to back
        for (int i = 1; i < k; i++) {
            enqueue(queue, dequeue(queue));
        }

        // Eliminate kth person
        int eliminated = dequeue(queue);
        printf("%d", eliminated);

        if (!is_queue_empty(queue)) {
            printf(", ");
        }
    }
    printf("\n");

    free_queue(queue);
}

int main() {
    Queue* queue = create_queue();

    printf("Queue Demo\n");
    printf("==========\n");

    // Basic queue operations
    printf("\n1. Enqueueing elements:\n");
    enqueue(queue, 10);
    enqueue(queue, 20);
    enqueue(queue, 30);
    enqueue(queue, 40);
    print_queue(queue);

    printf("\n2. Front element (peek): %d\n", peek_queue(queue));
    printf("Queue size: %d\n", get_queue_size(queue));

    printf("\n3. Dequeueing elements:\n");
    while (!is_queue_empty(queue)) {
        printf("Dequeued: %d\n", dequeue(queue));
        print_queue(queue);
    }

    // Queue application
    printf("\n4. Josephus Problem:\n");
    josephus_problem(7, 3); // 7 people, eliminate every 3rd

    free_queue(queue);
    return 0;
}
```

## Binary Search Trees

### BST Implementation

```c
#include <stdio.h>
#include <stdlib.h>

// Binary Search Tree node
typedef struct BSTNode {
    int data;
    struct BSTNode* left;
    struct BSTNode* right;
} BSTNode;

BSTNode* create_bst_node(int data);
BSTNode* insert_bst(BSTNode* root, int data);
BSTNode* search_bst(BSTNode* root, int data);
BSTNode* find_min(BSTNode* root);
BSTNode* find_max(BSTNode* root);
BSTNode* delete_bst(BSTNode* root, int data);
void inorder_traversal(BSTNode* root);
void preorder_traversal(BSTNode* root);
void postorder_traversal(BSTNode* root);
int get_height(BSTNode* root);
void free_bst(BSTNode* root);
void print_tree(BSTNode* root, int space);

BSTNode* create_bst_node(int data) {
    BSTNode* new_node = (BSTNode*)malloc(sizeof(BSTNode));
    if (new_node == NULL) return NULL;

    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

BSTNode* insert_bst(BSTNode* root, int data) {
    if (root == NULL) {
        return create_bst_node(data);
    }

    if (data < root->data) {
        root->left = insert_bst(root->left, data);
    } else if (data > root->data) {
        root->right = insert_bst(root->right, data);
    }
    // If equal, don't insert (no duplicates)

    return root;
}

BSTNode* search_bst(BSTNode* root, int data) {
    if (root == NULL || root->data == data) {
        return root;
    }

    if (data < root->data) {
        return search_bst(root->left, data);
    } else {
        return search_bst(root->right, data);
    }
}

BSTNode* find_min(BSTNode* root) {
    if (root == NULL) return NULL;

    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

BSTNode* find_max(BSTNode* root) {
    if (root == NULL) return NULL;

    while (root->right != NULL) {
        root = root->right;
    }
    return root;
}

BSTNode* delete_bst(BSTNode* root, int data) {
    if (root == NULL) return root;

    if (data < root->data) {
        root->left = delete_bst(root->left, data);
    } else if (data > root->data) {
        root->right = delete_bst(root->right, data);
    } else {
        // Node found
        // Case 1: No children
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }

        // Case 2: One child
        if (root->left == NULL) {
            BSTNode* temp = root->right;
            free(root);
            return temp;
        }
        if (root->right == NULL) {
            BSTNode* temp = root->left;
            free(root);
            return temp;
        }

        // Case 3: Two children
        // Find inorder successor (minimum in right subtree)
        BSTNode* temp = find_min(root->right);
        root->data = temp->data;
        root->right = delete_bst(root->right, temp->data);
    }

    return root;
}

void inorder_traversal(BSTNode* root) {
    if (root != NULL) {
        inorder_traversal(root->left);
        printf("%d ", root->data);
        inorder_traversal(root->right);
    }
}

void preorder_traversal(BSTNode* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder_traversal(root->left);
        preorder_traversal(root->right);
    }
}

void postorder_traversal(BSTNode* root) {
    if (root != NULL) {
        postorder_traversal(root->left);
        postorder_traversal(root->right);
        printf("%d ", root->data);
    }
}

int get_height(BSTNode* root) {
    if (root == NULL) return -1;

    int left_height = get_height(root->left);
    int right_height = get_height(root->right);

    return (left_height > right_height ? left_height : right_height) + 1;
}

void free_bst(BSTNode* root) {
    if (root != NULL) {
        free_bst(root->left);
        free_bst(root->right);
        free(root);
    }
}

void print_tree(BSTNode* root, int space) {
    const int INDENT = 4;

    if (root == NULL) return;

    space += INDENT;

    print_tree(root->right, space);

    printf("\n");
    for (int i = INDENT; i < space; i++) {
        printf(" ");
    }
    printf("%d\n", root->data);

    print_tree(root->left, space);
}

int main() {
    BSTNode* root = NULL;

    printf("Binary Search Tree Demo\n");
    printf("=======================\n");

    // Insert elements
    int elements[] = {50, 30, 70, 20, 40, 60, 80, 25, 35};
    int n = sizeof(elements) / sizeof(elements[0]);

    printf("\n1. Inserting elements: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", elements[i]);
        root = insert_bst(root, elements[i]);
    }
    printf("\n");

    // Print tree structure
    printf("\n2. Tree structure:\n");
    print_tree(root, 0);

    // Traversals
    printf("\n3. Tree traversals:\n");
    printf("Inorder: ");
    inorder_traversal(root);
    printf("\n");

    printf("Preorder: ");
    preorder_traversal(root);
    printf("\n");

    printf("Postorder: ");
    postorder_traversal(root);
    printf("\n");

    // Search
    printf("\n4. Search operations:\n");
    int search_values[] = {40, 55};
    for (int i = 0; i < 2; i++) {
        BSTNode* result = search_bst(root, search_values[i]);
        if (result != NULL) {
            printf("Found %d in the tree\n", search_values[i]);
        } else {
            printf("%d not found in the tree\n", search_values[i]);
        }
    }

    // Find min and max
    BSTNode* min_node = find_min(root);
    BSTNode* max_node = find_max(root);
    printf("\n5. Min value: %d\n", min_node ? min_node->data : -1);
    printf("Max value: %d\n", max_node ? max_node->data : -1);

    // Tree height
    printf("Tree height: %d\n", get_height(root));

    // Delete operations
    printf("\n6. Delete operations:\n");

    // Delete leaf node (20)
    printf("Deleting 20 (leaf node):\n");
    root = delete_bst(root, 20);
    print_tree(root, 0);

    // Delete node with one child (80)
    printf("\nDeleting 80 (one child):\n");
    root = delete_bst(root, 80);
    print_tree(root, 0);

    // Delete node with two children (50)
    printf("\nDeleting 50 (two children - root):\n");
    root = delete_bst(root, 50);
    print_tree(root, 0);

    // Final inorder traversal
    printf("\n7. Final inorder traversal: ");
    inorder_traversal(root);
    printf("\n");

    free_bst(root);
    return 0;
}
```

## Hash Tables

### Simple Hash Table Implementation

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10
#define MAX_NAME_LENGTH 50

typedef struct KeyValue {
    char key[MAX_NAME_LENGTH];
    int value;
    struct KeyValue* next; // For chaining
} KeyValue;

typedef struct {
    KeyValue* buckets[TABLE_SIZE];
    int size;
} HashTable;

// Hash function (simple modulo)
unsigned int hash(const char* key) {
    unsigned int hash_value = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        hash_value = (hash_value * 31 + key[i]) % TABLE_SIZE;
    }
    return hash_value;
}

HashTable* create_hash_table() {
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    if (table == NULL) return NULL;

    for (int i = 0; i < TABLE_SIZE; i++) {
        table->buckets[i] = NULL;
    }
    table->size = 0;

    return table;
}

KeyValue* create_key_value(const char* key, int value) {
    KeyValue* kv = (KeyValue*)malloc(sizeof(KeyValue));
    if (kv == NULL) return NULL;

    strncpy(kv->key, key, MAX_NAME_LENGTH - 1);
    kv->key[MAX_NAME_LENGTH - 1] = '\0';
    kv->value = value;
    kv->next = NULL;

    return kv;
}

void insert_hash(HashTable* table, const char* key, int value) {
    unsigned int index = hash(key);

    // Check if key already exists
    KeyValue* current = table->buckets[index];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            current->value = value; // Update existing key
            return;
        }
        current = current->next;
    }

    // Insert new key-value pair at the beginning of the chain
    KeyValue* new_kv = create_key_value(key, value);
    if (new_kv == NULL) return;

    new_kv->next = table->buckets[index];
    table->buckets[index] = new_kv;
    table->size++;
}

int search_hash(HashTable* table, const char* key) {
    unsigned int index = hash(key);

    KeyValue* current = table->buckets[index];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current->value;
        }
        current = current->next;
    }

    return -1; // Not found
}

int delete_hash(HashTable* table, const char* key) {
    unsigned int index = hash(key);

    KeyValue* current = table->buckets[index];
    KeyValue* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            if (prev == NULL) {
                // Delete first node in chain
                table->buckets[index] = current->next;
            } else {
                prev->next = current->next;
            }

            free(current);
            table->size--;
            return 1; // Success
        }
        prev = current;
        current = current->next;
    }

    return 0; // Key not found
}

void print_hash_table(HashTable* table) {
    printf("Hash Table Contents:\n");
    printf("====================\n");

    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("Bucket %d: ", i);

        if (table->buckets[i] == NULL) {
            printf("[empty]\n");
        } else {
            KeyValue* current = table->buckets[i];
            while (current != NULL) {
                printf("(%s: %d)", current->key, current->value);
                if (current->next != NULL) {
                    printf(" -> ");
                }
                current = current->next;
            }
            printf("\n");
        }
    }
    printf("Total elements: %d\n", table->size);
}

void free_hash_table(HashTable* table) {
    if (table == NULL) return;

    for (int i = 0; i < TABLE_SIZE; i++) {
        KeyValue* current = table->buckets[i];
        while (current != NULL) {
            KeyValue* temp = current;
            current = current->next;
            free(temp);
        }
    }

    free(table);
}

int main() {
    HashTable* table = create_hash_table();

    printf("Hash Table Demo\n");
    printf("===============\n");

    // Insert key-value pairs
    printf("\n1. Inserting key-value pairs:\n");
    insert_hash(table, "apple", 5);
    insert_hash(table, "banana", 3);
    insert_hash(table, "orange", 8);
    insert_hash(table, "grape", 2);
    insert_hash(table, "mango", 7);
    insert_hash(table, "pear", 4);

    print_hash_table(table);

    // Search operations
    printf("\n2. Search operations:\n");
    char* search_keys[] = {"apple", "grape", "coconut"};
    for (int i = 0; i < 3; i++) {
        int value = search_hash(table, search_keys[i]);
        if (value != -1) {
            printf("Found '%s': %d\n", search_keys[i], value);
        } else {
            printf("'%s' not found\n", search_keys[i]);
        }
    }

    // Update operation
    printf("\n3. Updating 'apple' to 10:\n");
    insert_hash(table, "apple", 10);
    printf("Search 'apple': %d\n", search_hash(table, "apple"));

    // Delete operations
    printf("\n4. Delete operations:\n");
    printf("Deleting 'orange': %s\n",
           delete_hash(table, "orange") ? "Success" : "Failed");
    printf("Deleting 'coconut': %s\n",
           delete_hash(table, "coconut") ? "Success" : "Failed");

    print_hash_table(table);

    // Demonstrate collision handling
    printf("\n5. Demonstrating collision handling:\n");

    // These keys should hash to different values, but let's force a collision
    // by inserting many items to show chaining
    for (int i = 0; i < 15; i++) {
        char key[20];
        sprintf(key, "key%d", i);
        insert_hash(table, key, i * 10);
    }

    print_hash_table(table);

    free_hash_table(table);
    return 0;
}
```

## Choosing the Right Data Structure

### Decision Guide

```c
#include <stdio.h>

void print_usage_guide() {
    printf("Data Structure Selection Guide\n");
    printf("==============================\n\n");

    printf("ARRAY (Built-in):\n");
    printf("  Use when: Fixed size, random access needed\n");
    printf("  Operations: O(1) access, O(n) search/insert/delete\n");
    printf("  Memory: Contiguous, efficient cache usage\n\n");

    printf("LINKED LIST:\n");
    printf("  Use when: Dynamic size, frequent insertions/deletions\n");
    printf("  Operations: O(n) access/search, O(1) insert/delete at known position\n");
    printf("  Memory: Non-contiguous, pointer overhead\n\n");

    printf("STACK:\n");
    printf("  Use when: LIFO (Last In, First Out) behavior needed\n");
    printf("  Operations: O(1) push/pop/peek\n");
    printf("  Applications: Function calls, undo systems, expression evaluation\n\n");

    printf("QUEUE:\n");
    printf("  Use when: FIFO (First In, First Out) behavior needed\n");
    printf("  Operations: O(1) enqueue/dequeue/peek\n");
    printf("  Applications: Task scheduling, breadth-first search, buffers\n\n");

    printf("BINARY SEARCH TREE:\n");
    printf("  Use when: Ordered data, fast search/insert/delete needed\n");
    printf("  Operations: O(log n) average, O(n) worst case\n");
    printf("  Applications: Dictionaries, symbol tables, range queries\n\n");

    printf("HASH TABLE:\n");
    printf("  Use when: Fast key-value lookup needed\n");
    printf("  Operations: O(1) average case for search/insert/delete\n");
    printf("  Applications: Caches, dictionaries, symbol tables\n\n");

    printf("PERFORMANCE COMPARISON:\n");
    printf("Structure    | Access | Search | Insert | Delete | Memory\n");
    printf("-------------|--------|--------|--------|--------|--------\n");
    printf("Array        |  O(1)  |  O(n)  |  O(n)  |  O(n)  |  Low   \n");
    printf("Linked List  |  O(n)  |  O(n)  |  O(1)  |  O(1)  |  High  \n");
    printf("Stack        |  O(1)  |  O(n)  |  O(1)  |  O(1)  |  Low   \n");
    printf("Queue        |  O(1)  |  O(n)  |  O(1)  |  O(1)  |  Low   \n");
    printf("BST          |  O(n)  | O(log n)|O(log n)|O(log n)| Medium \n");
    printf("Hash Table   |  O(1)  |  O(1)  |  O(1)  |  O(1)  |  High  \n");
}

int main() {
    print_usage_guide();
    return 0;
}
```

## Best Practices

### Memory Management
1. **Always free allocated memory** - Each malloc should have a corresponding free
2. **Check for allocation failures** - malloc can return NULL
3. **Free data structures recursively** - Trees and lists need careful cleanup
4. **Avoid memory leaks** - Use tools like valgrind to detect leaks

### Performance Considerations
1. **Choose the right structure** for your specific use case
2. **Consider cache locality** - Arrays are often faster than linked lists
3. **Profile before optimizing** - Measure actual performance
4. **Understand algorithmic complexity** - Big O notation matters

### Error Handling
1. **Validate input parameters** - Check for NULL pointers
2. **Handle edge cases** - Empty structures, single elements
3. **Use consistent error codes** - Return meaningful values
4. **Document error conditions** - Explain what can go wrong

## Exercises

### Exercise 11.1: Linked List Operations
Implement a function to reverse a linked list in-place.

### Exercise 11.2: Stack Application
Use a stack to check if parentheses are balanced in an expression.

### Exercise 11.3: Queue Application
Implement a circular queue using an array.

### Exercise 11.4: BST Operations
Add functions to find the k-th smallest element in a BST.

### Exercise 11.5: Hash Table Enhancement
Implement rehashing to automatically resize the hash table.

## Challenge Problems

### Challenge 11.1: Priority Queue
Implement a priority queue using a heap data structure.

### Challenge 11.2: LRU Cache
Design and implement an LRU (Least Recently Used) cache.

### Challenge 11.3: Trie Implementation
Create a trie (prefix tree) for efficient string searching.

## Quick Reference

### Common Data Structure Operations
```c
// Linked List
Node* create_node(data);
void insert_front(list, data);
void insert_back(list, data);
int delete_node(list, data);

// Stack
void push(stack, data);
int pop(stack);
int peek(stack);

// Queue
void enqueue(queue, data);
int dequeue(queue);
int peek_queue(queue);

// BST
BSTNode* insert_bst(root, data);
BSTNode* search_bst(root, data);
BSTNode* delete_bst(root, data);
void inorder_traversal(root);

// Hash Table
unsigned int hash(key);
void insert_hash(table, key, value);
int search_hash(table, key);
```

## Next Steps
Once you're comfortable with:
- Implementing basic data structures
- Understanding time and space complexity
- Choosing appropriate structures for problems

You're ready for **Chapter 12: Algorithms and Problem Solving**!