#ifndef CONTACT_H
#define CONTACT_H

#include <time.h>

#define INITIAL_CAPACITY 10
#define MAX_CONTACTS 10000
#define MAX_STRING_LENGTH 200

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
Contact* find_contact_by_phone(ContactManager *cm, const char *phone);
void display_contact(const Contact *contact);
void display_contact_list(const ContactManager *cm, int start, int end);

// Input/output functions
void input_contact(Contact *contact);
void edit_contact_menu(ContactManager *cm, int id);
void print_contact_header(void);
void print_contact_row(const Contact *contact, int index);

// Validation functions
int is_valid_phone(const char *phone);
int is_valid_email(const char *email);
int is_duplicate_phone(ContactManager *cm, const char *phone, int exclude_id);

// Utility functions
const char* get_group_name(const char *group);
void format_phone_number(char *phone);
void generate_contact_summary(const ContactManager *cm, char *summary, int max_len);

#endif