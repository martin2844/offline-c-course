// Chapter 11: Advanced Data Structures - Linked List Operations
// Solution to Exercise 11.1: Implement a function to reverse a linked list in-place

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    int size;
} LinkedList;

// Function prototypes
LinkedList* create_list();
void free_list(LinkedList* list);
void insert_front(LinkedList* list, int data);
void insert_back(LinkedList* list, int data);
void print_list(LinkedList* list);
Node* reverse_list(Node* head);
void reverse_list_iterative(Node** head_ref);
Node* reverse_list_recursive(Node* head);
Node* reverse_list_in_groups(Node* head, int k);
void delete_middle_node(Node* node);

// Create a new empty list
LinkedList* create_list() {
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    if (list == NULL) return NULL;

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
    if (new_node == NULL) return;

    new_node->data = data;
    new_node->next = list->head;
    list->head = new_node;
    list->size++;
}

// Insert at the back of the list
void insert_back(LinkedList* list, int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) return;

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

// Print the list
void print_list(LinkedList* list) {
    if (list == NULL || list->head == NULL) {
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

// SOLUTION: Iterative approach to reverse a linked list
Node* reverse_list(Node* head) {
    Node* prev = NULL;
    Node* current = head;
    Node* next = NULL;

    while (current != NULL) {
        next = current->next;    // Store next node
        current->next = prev;   // Reverse current node's pointer
        prev = current;         // Move pointers one position ahead
        current = next;
    }

    return prev;  // prev is the new head
}

// SOLUTION: In-place reversal using double pointer
void reverse_list_iterative(Node** head_ref) {
    Node* prev = NULL;
    Node* current = *head_ref;
    Node* next = NULL;

    while (current != NULL) {
        next = current->next;    // Store next
        current->next = prev;    // Reverse
        prev = current;          // Move prev
        current = next;          // Move current
    }

    *head_ref = prev;  // Update head
}

// SOLUTION: Recursive approach to reverse a linked list
Node* reverse_list_recursive(Node* head) {
    // Base case: if list is empty or has only one node
    if (head == NULL || head->next == NULL) {
        return head;
    }

    // Reverse the rest of the list
    Node* rest = reverse_list_recursive(head->next);

    // Put the first node at the end of the reversed list
    head->next->next = head;
    head->next = NULL;

    return rest;  // rest is the new head
}

// CHALLENGE: Reverse list in groups of size k
Node* reverse_list_in_groups(Node* head, int k) {
    if (head == NULL || k <= 1) {
        return head;
    }

    Node* current = head;
    Node* prev = NULL;
    Node* next = NULL;
    int count = 0;

    // Reverse first k nodes
    while (current != NULL && count < k) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
        count++;
    }

    // If there are more nodes, recursively reverse the rest
    if (next != NULL) {
        head->next = reverse_list_in_groups(next, k);
    }

    return prev;  // prev is the new head of this group
}

// CHALLENGE: Delete middle node (given access only to that node)
void delete_middle_node(Node* node) {
    if (node == NULL || node->next == NULL) {
        return;  // Cannot delete last node or NULL
    }

    Node* temp = node->next;
    node->data = temp->data;
    node->next = temp->next;
    free(temp);
}

int main() {
    printf("Linked List Operations Demo\n");
    printf("=============================\n");

    LinkedList* list = create_list();

    // Insert some elements
    printf("1. Creating original list:\n");
    insert_back(list, 10);
    insert_back(list, 20);
    insert_back(list, 30);
    insert_back(list, 40);
    insert_back(list, 50);
    print_list(list);

    // Test iterative reverse
    printf("\n2. Reversing list (iterative):\n");
    list->head = reverse_list(list->head);
    print_list(list);

    // Test recursive reverse
    printf("\n3. Reversing back (recursive):\n");
    list->head = reverse_list_recursive(list->head);
    print_list(list);

    // Test group reversal
    printf("\n4. Reversing in groups of 2:\n");
    list->head = reverse_list_in_groups(list->head, 2);
    print_list(list);

    // Test deleting middle node
    printf("\n5. Deleting middle node (30):\n");
    Node* current = list->head;
    // Find node with value 30
    while (current != NULL && current->data != 30) {
        current = current->next;
    }
    if (current != NULL) {
        delete_middle_node(current);
    }
    print_list(list);

    free_list(list);

    printf("\nLinked list operations completed successfully!\n");
    return 0;
}