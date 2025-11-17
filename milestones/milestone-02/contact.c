#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"

// Initialize contact manager
int init_contact_manager(ContactManager *cm) {
    if (!cm) return 0;

    cm->contacts = (Contact*)malloc(INITIAL_CAPACITY * sizeof(Contact));
    if (!cm->contacts) {
        return 0;
    }

    cm->count = 0;
    cm->capacity = INITIAL_CAPACITY;
    cm->next_id = 1;

    return 1;
}

// Free contact manager memory
void free_contact_manager(ContactManager *cm) {
    if (cm && cm->contacts) {
        free(cm->contacts);
        cm->contacts = NULL;
        cm->count = 0;
        cm->capacity = 0;
        cm->next_id = 0;
    }
}

// Resize contact array
int resize_contacts(ContactManager *cm, int new_capacity) {
    if (!cm || new_capacity <= cm->capacity) return 0;

    Contact *new_contacts = (Contact*)realloc(cm->contacts, new_capacity * sizeof(Contact));
    if (!new_contacts) return 0;

    cm->contacts = new_contacts;
    cm->capacity = new_capacity;
    return 1;
}

// Add new contact
int add_contact(ContactManager *cm, const Contact *contact) {
    if (!cm || !contact || cm->count >= MAX_CONTACTS) {
        return 0;
    }

    // Resize if needed
    if (cm->count >= cm->capacity) {
        if (!resize_contacts(cm, cm->capacity * 2)) {
            return 0;
        }
    }

    // Check for duplicate phone
    if (is_duplicate_phone(cm, contact->phone, -1)) {
        return -1; // Duplicate phone number
    }

    // Add contact
    Contact new_contact = *contact;
    new_contact.id = cm->next_id++;
    new_contact.created = time(NULL);
    new_contact.modified = time(NULL);

    cm->contacts[cm->count] = new_contact;
    cm->count++;

    return new_contact.id;
}

// Update existing contact
int update_contact(ContactManager *cm, int id, const Contact *contact) {
    if (!cm || !contact) return 0;

    for (int i = 0; i < cm->count; i++) {
        if (cm->contacts[i].id == id) {
            // Check for duplicate phone (excluding current contact)
            if (is_duplicate_phone(cm, contact->phone, id)) {
                return -1; // Duplicate phone number
            }

            // Update contact (preserve ID and creation time)
            time_t created = cm->contacts[i].created;
            cm->contacts[i] = *contact;
            cm->contacts[i].id = id;
            cm->contacts[i].created = created;
            cm->contacts[i].modified = time(NULL);
            return 1;
        }
    }

    return 0; // Contact not found
}

// Delete contact
int delete_contact(ContactManager *cm, int id) {
    if (!cm) return 0;

    for (int i = 0; i < cm->count; i++) {
        if (cm->contacts[i].id == id) {
            // Shift remaining contacts
            for (int j = i; j < cm->count - 1; j++) {
                cm->contacts[j] = cm->contacts[j + 1];
            }
            cm->count--;
            return 1;
        }
    }

    return 0; // Contact not found
}

// Find contact by ID
Contact* find_contact_by_id(ContactManager *cm, int id) {
    if (!cm) return NULL;

    for (int i = 0; i < cm->count; i++) {
        if (cm->contacts[i].id == id) {
            return &cm->contacts[i];
        }
    }

    return NULL;
}

// Find contact by phone
Contact* find_contact_by_phone(ContactManager *cm, const char *phone) {
    if (!cm || !phone) return NULL;

    for (int i = 0; i < cm->count; i++) {
        if (strcmp(cm->contacts[i].phone, phone) == 0) {
            return &cm->contacts[i];
        }
    }

    return NULL;
}

// Display single contact
void display_contact(const Contact *contact) {
    if (!contact) return;

    printf("\n=== Contact Details ===\n");
    printf("ID: %d\n", contact->id);
    printf("Name: %s %s\n", contact->first_name, contact->last_name);
    printf("Phone: %s\n", contact->phone);
    printf("Email: %s\n", contact->email);
    printf("Company: %s\n", contact->company);
    printf("Address: %s\n", contact->address);
    printf("Group: %s\n", get_group_name(contact->group));

    if (strlen(contact->notes) > 0) {
        printf("Notes: %s\n", contact->notes);
    }

    char created_str[30], modified_str[30];
    strftime(created_str, sizeof(created_str), "%Y-%m-%d %H:%M", localtime(&contact->created));
    strftime(modified_str, sizeof(modified_str), "%Y-%m-%d %H:%M", localtime(&contact->modified));

    printf("Created: %s\n", created_str);
    printf("Modified: %s\n", modified_str);
}

// Display contact list with table format
void display_contact_list(const ContactManager *cm, int start, int end) {
    if (!cm || cm->count == 0) {
        printf("No contacts to display.\n");
        return;
    }

    if (start < 0) start = 0;
    if (end >= cm->count) end = cm->count - 1;
    if (start > end) return;

    print_contact_header();

    for (int i = start; i <= end; i++) {
        print_contact_row(&cm->contacts[i], i);
    }
}

// Print table header
void print_contact_header(void) {
    printf("\n%-5s %-20s %-15s %-25s %-15s %-10s\n",
           "ID", "Name", "Phone", "Email", "Company", "Group");
    printf("%-5s %-20s %-15s %-25s %-15s %-10s\n",
           "---", "----", "-----", "-----", "-------", "-----");
}

// Print contact row
void print_contact_row(const Contact *contact, int index) {
    char full_name[40];
    snprintf(full_name, sizeof(full_name), "%s %s",
             contact->first_name, contact->last_name);

    // Truncate long fields
    char email_display[26] = {0};
    strncpy(email_display, contact->email, 25);

    char company_display[16] = {0};
    strncpy(company_display, contact->company, 15);

    printf("%-5d %-20s %-15s %-25s %-15s %-10s\n",
           contact->id,
           full_name,
           contact->phone,
           email_display,
           company_display,
           get_group_name(contact->group));
}

// Input contact from user
void input_contact(Contact *contact) {
    char buffer[MAX_STRING_LENGTH];

    printf("Enter First Name: ");
    fgets(contact->first_name, sizeof(contact->first_name), stdin);
    contact->first_name[strcspn(contact->first_name, "\n")] = '\0';

    printf("Enter Last Name: ");
    fgets(contact->last_name, sizeof(contact->last_name), stdin);
    contact->last_name[strcspn(contact->last_name, "\n")] = '\0';

    do {
        printf("Enter Phone Number: ");
        fgets(contact->phone, sizeof(contact->phone), stdin);
        contact->phone[strcspn(contact->phone, "\n")] = '\0';
        format_phone_number(contact->phone);

        if (!is_valid_phone(contact->phone)) {
            printf("Invalid phone number. Please use format like: 555-123-4567\n");
        }
    } while (!is_valid_phone(contact->phone));

    printf("Enter Email: ");
    fgets(contact->email, sizeof(contact->email), stdin);
    contact->email[strcspn(contact->email, "\n")] = '\0';

    printf("Enter Company: ");
    fgets(contact->company, sizeof(contact->company), stdin);
    contact->company[strcspn(contact->company, "\n")] = '\0';

    printf("Enter Address: ");
    fgets(contact->address, sizeof(contact->address), stdin);
    contact->address[strcspn(contact->address, "\n")] = '\0';

    printf("Enter Group (Personal/Business/Other): ");
    fgets(contact->group, sizeof(contact->group), stdin);
    contact->group[strcspn(contact->group, "\n")] = '\0';

    printf("Enter Notes (optional): ");
    fgets(contact->notes, sizeof(contact->notes), stdin);
    contact->notes[strcspn(contact->notes, "\n")] = '\0';
}

// Validate phone number
int is_valid_phone(const char *phone) {
    int digit_count = 0;

    for (int i = 0; phone[i] != '\0'; i++) {
        if (isdigit(phone[i])) {
            digit_count++;
        } else if (phone[i] != '-' && phone[i] != '(' && phone[i] != ')' && phone[i] != ' ') {
            return 0; // Invalid character
        }
    }

    return digit_count >= 10; // At least 10 digits
}

// Validate email
int is_valid_email(const char *email) {
    int at_count = 0;
    int dot_count = 0;

    for (int i = 0; email[i] != '\0'; i++) {
        if (email[i] == '@') at_count++;
        if (email[i] == '.') dot_count++;
    }

    return at_count == 1 && dot_count >= 1;
}

// Check for duplicate phone number
int is_duplicate_phone(ContactManager *cm, const char *phone, int exclude_id) {
    if (!cm || !phone) return 0;

    for (int i = 0; i < cm->count; i++) {
        if (cm->contacts[i].id != exclude_id &&
            strcmp(cm->contacts[i].phone, phone) == 0) {
            return 1;
        }
    }

    return 0;
}

// Get group display name
const char* get_group_name(const char *group) {
    if (strlen(group) == 0) return "Unassigned";
    if (strcasecmp(group, "personal") == 0) return "Personal";
    if (strcasecmp(group, "business") == 0) return "Business";
    if (strcasecmp(group, "other") == 0) return "Other";
    return group;
}

// Format phone number
void format_phone_number(char *phone) {
    char formatted[20] = {0};
    int j = 0;
    int digit_count = 0;

    for (int i = 0; phone[i] != '\0' && j < 19; i++) {
        if (isdigit(phone[i])) {
            digit_count++;
            formatted[j++] = phone[i];

            // Add formatting
            if (digit_count == 3 && j < 19) {
                formatted[j++] = '-';
            } else if (digit_count == 6 && j < 19) {
                formatted[j++] = '-';
            }
        }
    }

    strcpy(phone, formatted);
}

// Generate contact summary
void generate_contact_summary(const ContactManager *cm, char *summary, int max_len) {
    if (!cm || !summary) return;

    if (cm->count == 0) {
        snprintf(summary, max_len, "No contacts in database");
        return;
    }

    int personal = 0, business = 0, other = 0;
    time_t now = time(NULL);
    int recent_contacts = 0;

    for (int i = 0; i < cm->count; i++) {
        // Count by group
        if (strcasecmp(cm->contacts[i].group, "personal") == 0) {
            personal++;
        } else if (strcasecmp(cm->contacts[i].group, "business") == 0) {
            business++;
        } else {
            other++;
        }

        // Count recent contacts (created in last 30 days)
        double days_diff = difftime(now, cm->contacts[i].created) / (24 * 60 * 60);
        if (days_diff <= 30) {
            recent_contacts++;
        }
    }

    snprintf(summary, max_len,
             "Total: %d | Personal: %d | Business: %d | Other: %d | Recent: %d",
             cm->count, personal, business, other, recent_contacts);
}