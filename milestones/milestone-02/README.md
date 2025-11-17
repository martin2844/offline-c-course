# Milestone 2: Contact Manager

**🎯 Apply Chapters 1-7: Structures, Arrays, Strings, Pointers, and Advanced Programming**

## Project Overview

Create a comprehensive contact management system that demonstrates all the concepts you've learned so far:
- Structures for organizing contact data
- Dynamic memory allocation for flexible storage
- String manipulation for names and search
- File I/O for data persistence
- Advanced data structures and algorithms

## Learning Objectives

After completing this project, you will have:
- ✅ Built a complete data management application
- ✅ Applied advanced structure design principles
- ✅ Implemented dynamic memory management
- ✅ Created efficient search and sorting algorithms
- ✅ Added file persistence for data storage
- ✅ Practiced professional software development

## Project Requirements

### Core Features
1. **Contact Management**: Add, edit, delete, and view contacts
2. **Advanced Search**: Search by name, phone, email, or company
3. **Sorting**: Sort contacts by various criteria
4. **Data Persistence**: Save and load contacts from files
5. **Memory Management**: Efficient dynamic memory allocation

### Advanced Features
1. **Contact Groups**: Organize contacts into groups
2. **Import/Export**: CSV file support
3. **Search History**: Track recent searches
4. **Backup/Restore**: Multiple database files

### Technical Requirements
- **Modular Design**: Separate files for different functionalities
- **Memory Safety**: Proper allocation and deallocation
- **Error Handling**: Robust error checking and recovery
- **User Interface**: Clean, intuitive command-line interface
- **Performance**: Efficient algorithms for large datasets

## Implementation Guide

### Step 1: Project Structure
Create these files:
```
contact_manager/
├── main.c              # Main program and menu
├── contact.h           # Contact structure and function prototypes
├── contact.c           # Contact management functions
├── file_ops.h          # File operation prototypes
├── file_ops.c          # File I/O functions
├── search.h            # Search function prototypes
├── search.c            # Search and sorting functions
├── utils.h             # Utility function prototypes
├── utils.c             # Input validation and helper functions
├── data/               # Directory for contact files
└── Makefile            # Build configuration
```

### Step 2: Contact Structure Design
```c
// Enhanced contact structure
typedef struct {
    int id;
    char first_name[50];
    char last_name[50];
    char phone[20];
    char email[100];
    char company[100];
    char address[200];
    char group[30];
    char notes[500];
    time_t created;
    time_t modified;
} Contact;

typedef struct {
    Contact *contacts;  // Dynamic array of contacts
    int count;          // Number of contacts
    int capacity;       // Allocated capacity
    int next_id;        // Next available ID
} ContactManager;
```

### Step 3: Core Functionality Modules

#### Contact Management (contact.c)
```c
// Core contact operations
int init_contact_manager(ContactManager *cm);
int add_contact(ContactManager *cm, const Contact *contact);
int update_contact(ContactManager *cm, int id, const Contact *contact);
int delete_contact(ContactManager *cm, int id);
Contact* find_contact_by_id(ContactManager *cm, int id);
void free_contact_manager(ContactManager *cm);
```

#### Search and Sort (search.c)
```c
// Search operations
Contact** search_by_name(ContactManager *cm, const char *name, int *count);
Contact** search_by_phone(ContactManager *cm, const char *phone, int *count);
Contact** search_by_company(ContactManager *cm, const char *company, int *count);

// Sorting operations
void sort_contacts_by_name(ContactManager *cm);
void sort_contacts_by_company(ContactManager *cm);
void sort_contacts_by_created_date(ContactManager *cm);
```

#### File Operations (file_ops.c)
```c
// File persistence
int save_contacts(ContactManager *cm, const char *filename);
int load_contacts(ContactManager *cm, const char *filename);
int export_to_csv(ContactManager *cm, const char *filename);
int import_from_csv(ContactManager *cm, const char *filename);
int backup_database(ContactManager *cm, const char *backup_name);
```

### Step 4: Main Menu Structure
```
Contact Manager Main Menu
=========================
1. Add New Contact
2. View All Contacts
3. Search Contacts
4. Edit Contact
5. Delete Contact
6. Sort Contacts
7. Contact Groups
8. File Operations
9. Settings
0. Exit

Enter your choice:
```

## Detailed Implementation

### Contact Header (contact.h)
```c
#ifndef CONTACT_H
#define CONTACT_H

#include <time.h>

#define INITIAL_CAPACITY 10
#define MAX_CONTACTS 10000

// Contact structure
typedef struct {
    int id;
    char first_name[50];
    char last_name[50];
    char phone[20];
    char email[100];
    char company[100];
    char address[200];
    char group[30];
    char notes[500];
    time_t created;
    time_t modified;
} Contact;

// Contact manager structure
typedef struct {
    Contact *contacts;
    int count;
    int capacity;
    int next_id;
} ContactManager;

// Contact management functions
int init_contact_manager(ContactManager *cm);
void free_contact_manager(ContactManager *cm);
int add_contact(ContactManager *cm, const Contact *contact);
int update_contact(ContactManager *cm, int id, const Contact *contact);
int delete_contact(ContactManager *cm, int id);
Contact* find_contact_by_id(ContactManager *cm, int id);
void display_contact(const Contact *contact);
void display_contact_list(const ContactManager *cm, int start, int end);

// Input/output functions
void input_contact(Contact *contact);
void edit_contact_menu(ContactManager *cm, int id);

#endif
```

### Search Module (search.h)
```c
#ifndef SEARCH_H
#define SEARCH_H

#include "contact.h"

// Search results structure
typedef struct {
    Contact **contacts;
    int count;
    int capacity;
} SearchResult;

// Search functions
SearchResult* search_contacts(ContactManager *cm, const char *query, int search_type);
SearchResult* search_by_name(ContactManager *cm, const char *name);
SearchResult* search_by_phone(ContactManager *cm, const char *phone);
SearchResult* search_by_email(ContactManager *cm, const char *email);
SearchResult* search_by_company(ContactManager *cm, const char *company);
SearchResult* search_by_group(ContactManager *cm, const char *group);

// Sorting functions
void sort_contacts_by_name(ContactManager *cm);
void sort_contacts_by_company(ContactManager *cm);
void sort_contacts_by_created_date(ContactManager *cm);

// Search result management
SearchResult* create_search_result(void);
void free_search_result(SearchResult *sr);
void add_search_result(SearchResult *sr, Contact *contact);

// Search type constants
#define SEARCH_NAME 1
#define SEARCH_PHONE 2
#define SEARCH_EMAIL 3
#define SEARCH_COMPANY 4
#define SEARCH_GROUP 5

#endif
```

### File Operations (file_ops.h)
```c
#ifndef FILE_OPS_H
#define FILE_OPS_H

#include "contact.h"

// File operation functions
int save_contacts(ContactManager *cm, const char *filename);
int load_contacts(ContactManager *cm, const char *filename);
int export_to_csv(ContactManager *cm, const char *filename);
int import_from_csv(ContactManager *cm, const char *filename);
int backup_database(ContactManager *cm, const char *backup_name);
int restore_database(ContactManager *cm, const char *backup_name);

// File format constants
#define CONTACT_FILE "contacts.dat"
#define BACKUP_DIR "backups/"
#define CSV_EXPORT "contacts_export.csv"

#endif
```

## Development Phases

### Phase 1: Basic Contact Management
1. **Set up project structure**
2. **Implement Contact structure**
3. **Create basic add/edit/delete functions**
4. **Build simple user interface**
5. **Add input validation**

### Phase 2: Search and Sorting
1. **Implement search algorithms**
2. **Add sorting functionality**
3. **Create advanced search interface**
4. **Add pagination for large lists**

### Phase 3: File Operations
1. **Implement binary file format**
2. **Add save/load functionality**
3. **Create CSV import/export**
4. **Add backup/restore features**

### Phase 4: Advanced Features
1. **Add contact groups**
2. **Implement search history**
3. **Add data validation**
4. **Create configuration system**

### Phase 5: Polish and Optimization
1. **Optimize memory usage**
2. **Add comprehensive error handling**
3. **Improve user interface**
4. **Add help system**

## Key Algorithms and Concepts

### Dynamic Array Implementation
```c
int resize_contact_array(ContactManager *cm, int new_capacity) {
    Contact *new_contacts = realloc(cm->contacts,
                                   new_capacity * sizeof(Contact));
    if (new_contacts == NULL) {
        return 0; // Failed to allocate
    }

    cm->contacts = new_contacts;
    cm->capacity = new_capacity;
    return 1; // Success
}
```

### Efficient Search Algorithm
```c
// Binary search for sorted contact lists
Contact* binary_search_contact(ContactManager *cm, const char *name) {
    int left = 0, right = cm->count - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = strcasecmp(cm->contacts[mid].first_name, name);

        if (cmp == 0) {
            return &cm->contacts[mid];
        } else if (cmp < 0) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return NULL; // Not found
}
```

### File Format Design
```c
// Binary file format for contacts
typedef struct {
    int magic_number;      // File format identifier
    int version;          // File version
    int contact_count;    // Number of contacts
    int next_id;          // Next available ID
    time_t last_modified; // Last modification time
} FileHeader;
```

## Error Handling Strategy

### Return Code Conventions
```c
#define SUCCESS 0
#define ERROR_MEMORY -1
#define ERROR_FILE_NOT_FOUND -2
#define ERROR_INVALID_INPUT -3
#define ERROR_CONTACT_NOT_FOUND -4
#define ERROR_DUPLICATE_CONTACT -5
```

### Error Handling Pattern
```c
int add_contact_safe(ContactManager *cm, const Contact *contact) {
    // Validate input
    if (!cm || !contact) {
        return ERROR_INVALID_INPUT;
    }

    // Check for duplicates
    if (find_contact_by_phone(cm, contact->phone) != NULL) {
        return ERROR_DUPLICATE_CONTACT;
    }

    // Ensure capacity
    if (cm->count >= cm->capacity) {
        if (!resize_contact_array(cm, cm->capacity * 2)) {
            return ERROR_MEMORY;
        }
    }

    // Add contact
    return add_contact(cm, contact);
}
```

## Testing Your Contact Manager

### Test Cases
1. **Basic Operations**
   - Add valid contacts
   - Handle duplicate prevention
   - Test edit and delete operations

2. **Search Functionality**
   - Search by different fields
   - Test partial matches
   - Verify sort accuracy

3. **File Operations**
   - Save and load data
   - Test import/export
   - Verify backup/restore

4. **Error Handling**
   - Invalid input handling
   - Memory allocation failures
   - File access errors

### Sample Test Plan
```c
void run_unit_tests() {
    ContactManager cm;

    printf("Running Contact Manager Tests...\n");

    // Test initialization
    assert(init_contact_manager(&cm) == SUCCESS);
    assert(cm.count == 0);
    assert(cm.capacity >= INITIAL_CAPACITY);

    // Test contact addition
    Contact test_contact = {0};
    strcpy(test_contact.first_name, "John");
    strcpy(test_contact.last_name, "Doe");
    strcpy(test_contact.phone, "555-1234");

    assert(add_contact(&cm, &test_contact) == SUCCESS);
    assert(cm.count == 1);

    // Test search
    Contact *found = search_by_phone(&cm, "555-1234");
    assert(found != NULL);
    assert(strcmp(found->first_name, "John") == 0);

    // Test cleanup
    free_contact_manager(&cm);

    printf("All tests passed!\n");
}
```

## Performance Considerations

### Memory Management
- **Resize strategy**: Double capacity when needed
- **Memory pools**: Reallocate large blocks
- **Garbage collection**: Clean up deleted contacts

### Search Optimization
- **Indexing**: Create indexes for frequent searches
- **Caching**: Cache recent search results
- **Lazy loading**: Load data as needed

### File I/O Optimization
- **Buffering**: Use file buffers for large files
- **Compression**: Compress large data files
- **Incremental saves**: Save only changed contacts

## User Interface Design

### Menu System
```c
void display_main_menu() {
    printf("\n=== Contact Manager ===\n");
    printf("1. Add New Contact\n");
    printf("2. View All Contacts\n");
    printf("3. Search Contacts\n");
    printf("4. Edit Contact\n");
    printf("5. Delete Contact\n");
    printf("6. Sort Contacts\n");
    printf("7. Contact Groups\n");
    printf("8. File Operations\n");
    printf("9. Statistics\n");
    printf("0. Exit\n");
    printf("Choice: ");
}
```

### Input Validation
```c
int get_valid_phone(char *phone, int max_length) {
    while (1) {
        if (fgets(phone, max_length, stdin) == NULL) {
            return 0;
        }

        // Remove newline
        phone[strcspn(phone, "\n")] = '\0';

        // Validate phone format
        if (is_valid_phone(phone)) {
            return 1;
        }

        printf("Invalid phone format. Try again: ");
    }
}
```

## Bonus Features

### Advanced Search
- **Fuzzy search**: Allow typos in searches
- **Regular expressions**: Pattern matching
- **Filter combinations**: Multiple criteria

### Data Visualization
- **Contact statistics**: Display graphs and charts
- **Group distribution**: Visual contact organization
- **Activity tracking**: Contact interaction history

### Integration Features
- **Email integration**: Send emails from contacts
- **Calendar integration**: Birthdays and events
- **Import from other formats**: vCard, Outlook

## Evaluation Criteria

### Functionality (40%)
- All required features implemented
- Data integrity maintained
- Search and sorting accuracy
- File operations reliability

### Code Quality (30%)
- Modular design and organization
- Proper memory management
- Error handling robustness
- Code documentation

### User Experience (20%)
- Intuitive interface design
- Clear error messages
- Consistent behavior
- Performance optimization

### Advanced Features (10%)
- Additional functionality
- Innovative solutions
- Performance optimization
- Exception handling

## Submission Checklist

- [ ] All basic contact management features
- [ ] Advanced search and sorting
- [ ] File persistence and backup
- [ ] Comprehensive error handling
- [ ] Memory leak-free code
- [ ] User documentation
- [ ] Test coverage
- [ ] Performance optimization

## Next Steps

After completing this contact manager:
1. **Review and optimize** your code
2. **Add extra features** if you're interested
3. **Move to Chapter 8** to learn about File I/O in depth
4. **Start planning** the final DevTools project

## Troubleshooting

### Common Issues
- **Memory leaks**: Use tools like valgrind to detect
- **File corruption**: Implement file validation
- **Search performance**: Add indexing for large datasets
- **UI responsiveness**: Add progress indicators for long operations

### Debugging Tips
- **Use assert statements** for debugging
- **Log file operations** for troubleshooting
- **Test with edge cases** (empty data, large datasets)
- **Memory debugging** with specialized tools

---

**🎯 Ready to build your first complete data management application?**

This contact manager will demonstrate your mastery of C programming concepts and create a practical tool you can actually use!

Good luck, and happy coding! 🚀