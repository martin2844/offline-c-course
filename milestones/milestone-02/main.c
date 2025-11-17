#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"

// Function prototypes
void display_main_menu(void);
void add_contact_menu(ContactManager *cm);
void view_contacts_menu(ContactManager *cm);
void search_contacts_menu(ContactManager *cm);
void edit_contact_menu(ContactManager *cm);
void delete_contact_menu(ContactManager *cm);
void display_statistics(ContactManager *cm);
void save_and_exit(ContactManager *cm);
int load_database(ContactManager *cm, const char *filename);
int save_database(ContactManager *cm, const char *filename);

int main() {
    ContactManager cm;

    printf("=== Contact Manager v1.0 ===\n");
    printf("==========================\n");

    // Initialize contact manager
    if (!init_contact_manager(&cm)) {
        printf("Error: Failed to initialize contact manager.\n");
        return 1;
    }

    // Load existing database
    if (!load_database(&cm, "contacts.dat")) {
        printf("Starting with empty contact database.\n");
    } else {
        printf("Loaded %d contacts from database.\n", cm.count);
    }

    int choice;
    do {
        display_main_menu();

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }
        while (getchar() != '\n'); // Clear input buffer

        switch (choice) {
            case 0:
                save_and_exit(&cm);
                break;
            case 1:
                add_contact_menu(&cm);
                break;
            case 2:
                view_contacts_menu(&cm);
                break;
            case 3:
                search_contacts_menu(&cm);
                break;
            case 4:
                edit_contact_menu(&cm);
                break;
            case 5:
                delete_contact_menu(&cm);
                break;
            case 6:
                display_statistics(&cm);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

        if (choice != 0) {
            printf("\nPress Enter to continue...");
            getchar();
        }

    } while (choice != 0);

    // Cleanup
    free_contact_manager(&cm);
    return 0;
}

void display_main_menu(void) {
    printf("\n=== Main Menu ===\n");
    printf("1. Add New Contact\n");
    printf("2. View All Contacts\n");
    printf("3. Search Contacts\n");
    printf("4. Edit Contact\n");
    printf("5. Delete Contact\n");
    printf("6. View Statistics\n");
    printf("0. Save and Exit\n");
    printf("Choice: ");
}

void add_contact_menu(ContactManager *cm) {
    printf("\n=== Add New Contact ===\n");

    Contact new_contact;
    input_contact(&new_contact);

    int result = add_contact(cm, &new_contact);

    if (result > 0) {
        printf("\nContact added successfully with ID: %d\n", result);
    } else if (result == -1) {
        printf("\nError: Phone number already exists.\n");
    } else {
        printf("\nError: Failed to add contact.\n");
    }
}

void view_contacts_menu(ContactManager *cm) {
    printf("\n=== Contact List ===\n");

    if (cm->count == 0) {
        printf("No contacts found.\n");
        return;
    }

    display_contact_list(cm, 0, cm->count - 1);

    // Option to view detailed contact
    int id;
    printf("\nEnter contact ID to view details (0 to cancel): ");
    if (scanf("%d", &id) == 1 && id > 0) {
        while (getchar() != '\n'); // Clear input buffer

        Contact *contact = find_contact_by_id(cm, id);
        if (contact) {
            display_contact(contact);
        } else {
            printf("Contact with ID %d not found.\n", id);
        }
    }
    while (getchar() != '\n'); // Clear input buffer
}

void search_contacts_menu(ContactManager *cm) {
    printf("\n=== Search Contacts ===\n");
    printf("1. Search by Name\n");
    printf("2. Search by Phone\n");
    printf("3. Search by Email\n");
    printf("4. Search by Company\n");
    printf("Choice: ");

    int choice;
    if (scanf("%d", &choice) != 1) {
        printf("Invalid input.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n'); // Clear input buffer

    char search_term[100];
    int found_count = 0;

    switch (choice) {
        case 1:
            printf("Enter name to search: ");
            fgets(search_term, sizeof(search_term), stdin);
            search_term[strcspn(search_term, "\n")] = '\0';

            printf("\nSearch Results:\n");
            for (int i = 0; i < cm->count; i++) {
                char full_name[100];
                snprintf(full_name, sizeof(full_name), "%s %s",
                         cm->contacts[i].first_name, cm->contacts[i].last_name);

                if (strstr(full_name, search_term) != NULL) {
                    if (found_count == 0) print_contact_header();
                    print_contact_row(&cm->contacts[i], i);
                    found_count++;
                }
            }
            break;

        case 2:
            printf("Enter phone number to search: ");
            fgets(search_term, sizeof(search_term), stdin);
            search_term[strcspn(search_term, "\n")] = '\0';

            printf("\nSearch Results:\n");
            for (int i = 0; i < cm->count; i++) {
                if (strstr(cm->contacts[i].phone, search_term) != NULL) {
                    if (found_count == 0) print_contact_header();
                    print_contact_row(&cm->contacts[i], i);
                    found_count++;
                }
            }
            break;

        case 3:
            printf("Enter email to search: ");
            fgets(search_term, sizeof(search_term), stdin);
            search_term[strcspn(search_term, "\n")] = '\0';

            printf("\nSearch Results:\n");
            for (int i = 0; i < cm->count; i++) {
                if (strstr(cm->contacts[i].email, search_term) != NULL) {
                    if (found_count == 0) print_contact_header();
                    print_contact_row(&cm->contacts[i], i);
                    found_count++;
                }
            }
            break;

        case 4:
            printf("Enter company to search: ");
            fgets(search_term, sizeof(search_term), stdin);
            search_term[strcspn(search_term, "\n")] = '\0';

            printf("\nSearch Results:\n");
            for (int i = 0; i < cm->count; i++) {
                if (strstr(cm->contacts[i].company, search_term) != NULL) {
                    if (found_count == 0) print_contact_header();
                    print_contact_row(&cm->contacts[i], i);
                    found_count++;
                }
            }
            break;

        default:
            printf("Invalid choice.\n");
            return;
    }

    if (found_count == 0) {
        printf("No contacts found matching your search.\n");
    } else {
        printf("\nFound %d contact(s).\n", found_count);
    }
}

void edit_contact_menu(ContactManager *cm) {
    printf("\n=== Edit Contact ===\n");

    if (cm->count == 0) {
        printf("No contacts available to edit.\n");
        return;
    }

    int id;
    printf("Enter contact ID to edit: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid input.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n'); // Clear input buffer

    Contact *contact = find_contact_by_id(cm, id);
    if (!contact) {
        printf("Contact with ID %d not found.\n", id);
        return;
    }

    printf("\nCurrent Contact Details:\n");
    display_contact(contact);

    printf("\nEnter new details (press Enter to keep current value):\n");

    Contact updated_contact = *contact;
    char buffer[200];
    int field;

    do {
        printf("\nSelect field to edit:\n");
        printf("1. First Name\n");
        printf("2. Last Name\n");
        printf("3. Phone\n");
        printf("4. Email\n");
        printf("5. Company\n");
        printf("6. Address\n");
        printf("7. Group\n");
        printf("8. Notes\n");
        printf("0. Save and Exit\n");
        printf("Choice: ");

        if (scanf("%d", &field) != 1) {
            printf("Invalid input.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n'); // Clear input buffer

        switch (field) {
            case 1:
                printf("Current First Name: %s\n", contact->first_name);
                printf("Enter new First Name: ");
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = '\0';
                if (strlen(buffer) > 0) {
                    strcpy(updated_contact.first_name, buffer);
                }
                break;

            case 2:
                printf("Current Last Name: %s\n", contact->last_name);
                printf("Enter new Last Name: ");
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = '\0';
                if (strlen(buffer) > 0) {
                    strcpy(updated_contact.last_name, buffer);
                }
                break;

            case 3:
                printf("Current Phone: %s\n", contact->phone);
                do {
                    printf("Enter new Phone: ");
                    fgets(buffer, sizeof(buffer), stdin);
                    buffer[strcspn(buffer, "\n")] = '\0';
                    if (strlen(buffer) > 0) {
                        format_phone_number(buffer);
                        if (!is_valid_phone(buffer)) {
                            printf("Invalid phone number. Please try again.\n");
                        } else if (is_duplicate_phone(cm, buffer, id)) {
                            printf("Phone number already exists.\n");
                        } else {
                            strcpy(updated_contact.phone, buffer);
                            break;
                        }
                    } else {
                        break; // Keep current value
                    }
                } while (1);
                break;

            case 4:
                printf("Current Email: %s\n", contact->email);
                printf("Enter new Email: ");
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = '\0';
                if (strlen(buffer) > 0) {
                    strcpy(updated_contact.email, buffer);
                }
                break;

            case 5:
                printf("Current Company: %s\n", contact->company);
                printf("Enter new Company: ");
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = '\0';
                if (strlen(buffer) > 0) {
                    strcpy(updated_contact.company, buffer);
                }
                break;

            case 6:
                printf("Current Address: %s\n", contact->address);
                printf("Enter new Address: ");
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = '\0';
                if (strlen(buffer) > 0) {
                    strcpy(updated_contact.address, buffer);
                }
                break;

            case 7:
                printf("Current Group: %s\n", get_group_name(contact->group));
                printf("Enter new Group (Personal/Business/Other): ");
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = '\0';
                if (strlen(buffer) > 0) {
                    strcpy(updated_contact.group, buffer);
                }
                break;

            case 8:
                printf("Current Notes: %s\n", contact->notes);
                printf("Enter new Notes: ");
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = '\0';
                if (strlen(buffer) > 0) {
                    strcpy(updated_contact.notes, buffer);
                }
                break;

            case 0:
                // Save changes
                if (update_contact(cm, id, &updated_contact)) {
                    printf("\nContact updated successfully!\n");
                } else {
                    printf("\nFailed to update contact.\n");
                }
                return;

            default:
                printf("Invalid choice.\n");
        }
    } while (field != 0);
}

void delete_contact_menu(ContactManager *cm) {
    printf("\n=== Delete Contact ===\n");

    if (cm->count == 0) {
        printf("No contacts available to delete.\n");
        return;
    }

    int id;
    printf("Enter contact ID to delete: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid input.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n'); // Clear input buffer

    Contact *contact = find_contact_by_id(cm, id);
    if (!contact) {
        printf("Contact with ID %d not found.\n", id);
        return;
    }

    printf("\nContact to delete:\n");
    display_contact(contact);

    printf("\nAre you sure you want to delete this contact? (y/N): ");
    char confirmation[10];
    fgets(confirmation, sizeof(confirmation), stdin);

    if (confirmation[0] == 'y' || confirmation[0] == 'Y') {
        if (delete_contact(cm, id)) {
            printf("Contact deleted successfully.\n");
        } else {
            printf("Failed to delete contact.\n");
        }
    } else {
        printf("Deletion cancelled.\n");
    }
}

void display_statistics(ContactManager *cm) {
    printf("\n=== Contact Statistics ===\n");

    char summary[200];
    generate_contact_summary(cm, summary, sizeof(summary));
    printf("Summary: %s\n", summary);

    if (cm->count > 0) {
        // Calculate statistics
        int personal = 0, business = 0, other = 0;
        time_t now = time(NULL);
        int recent_contacts = 0;

        for (int i = 0; i < cm->count; i++) {
            if (strcasecmp(cm->contacts[i].group, "personal") == 0) {
                personal++;
            } else if (strcasecmp(cm->contacts[i].group, "business") == 0) {
                business++;
            } else {
                other++;
            }

            double days_diff = difftime(now, cm->contacts[i].created) / (24 * 60 * 60);
            if (days_diff <= 30) {
                recent_contacts++;
            }
        }

        printf("\nBreakdown by Group:\n");
        printf("  Personal: %d (%.1f%%)\n", personal,
               (float)personal * 100 / cm->count);
        printf("  Business: %d (%.1f%%)\n", business,
               (float)business * 100 / cm->count);
        printf("  Other: %d (%.1f%%)\n", other,
               (float)other * 100 / cm->count);

        printf("\nRecent Activity:\n");
        printf("  Contacts added in last 30 days: %d\n", recent_contacts);
        printf("  Database capacity used: %d/%d (%.1f%%)\n",
               cm->count, cm->capacity,
               (float)cm->count * 100 / cm->capacity);
    }
}

int save_database(ContactManager *cm, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (!file) return 0;

    // Write header
    fwrite(&cm->count, sizeof(int), 1, file);
    fwrite(&cm->next_id, sizeof(int), 1, file);

    // Write contacts
    fwrite(cm->contacts, sizeof(Contact), cm->count, file);

    fclose(file);
    return 1;
}

int load_database(ContactManager *cm, const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) return 0;

    int count, next_id;

    // Read header
    if (fread(&count, sizeof(int), 1, file) != 1) {
        fclose(file);
        return 0;
    }
    if (fread(&next_id, sizeof(int), 1, file) != 1) {
        fclose(file);
        return 0;
    }

    // Resize if needed
    if (count > cm->capacity) {
        if (!resize_contacts(cm, count + 10)) {
            fclose(file);
            return 0;
        }
    }

    // Read contacts
    if (fread(cm->contacts, sizeof(Contact), count, file) != count) {
        fclose(file);
        return 0;
    }

    fclose(file);

    cm->count = count;
    cm->next_id = next_id;

    return 1;
}

void save_and_exit(ContactManager *cm) {
    if (save_database(cm, "contacts.dat")) {
        printf("Saved %d contacts to database.\n", cm->count);
    } else {
        printf("Warning: Failed to save database.\n");
    }

    printf("Goodbye!\n");
}