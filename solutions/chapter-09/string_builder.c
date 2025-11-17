#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *buffer;
    size_t length;
    size_t capacity;
} StringBuilder;

StringBuilder* create_string_builder(size_t initial_capacity) {
    StringBuilder *sb = (StringBuilder*)malloc(sizeof(StringBuilder));
    if (!sb) return NULL;

    sb->buffer = (char*)malloc(initial_capacity);
    if (!sb->buffer) {
        free(sb);
        return NULL;
    }

    sb->buffer[0] = '\0';
    sb->length = 0;
    sb->capacity = initial_capacity;

    return sb;
}

void free_string_builder(StringBuilder *sb) {
    if (sb) {
        free(sb->buffer);
        free(sb);
    }
}

int sb_append(StringBuilder *sb, const char *str) {
    if (!sb || !str) return 0;

    size_t str_len = strlen(str);
    size_t needed = sb->length + str_len + 1;

    // Resize if needed
    if (needed > sb->capacity) {
        size_t new_capacity = sb->capacity * 2;
        while (new_capacity < needed) {
            new_capacity *= 2;
        }

        char *new_buffer = (char*)realloc(sb->buffer, new_capacity);
        if (!new_buffer) return 0;

        sb->buffer = new_buffer;
        sb->capacity = new_capacity;
    }

    // Append string
    strcat(sb->buffer, str);
    sb->length += str_len;

    return 1;
}

int sb_append_char(StringBuilder *sb, char c) {
    char str[2] = {c, '\0'};
    return sb_append(sb, str);
}

int sb_append_int(StringBuilder *sb, int value) {
    char buffer[32];
    snprintf(buffer, sizeof(buffer), "%d", value);
    return sb_append(sb, buffer);
}

const char* sb_to_string(const StringBuilder *sb) {
    return sb ? sb->buffer : "";
}

size_t sb_length(const StringBuilder *sb) {
    return sb ? sb->length : 0;
}

void sb_clear(StringBuilder *sb) {
    if (sb) {
        sb->buffer[0] = '\0';
        sb->length = 0;
    }
}

void print_sb_info(const StringBuilder *sb) {
    if (sb) {
        printf("StringBuilder Info:\n");
        printf("  Length: %zu\n", sb->length);
        printf("  Capacity: %zu\n", sb->capacity);
        printf("  Utilization: %.1f%%\n", (float)sb->length * 100 / sb->capacity);
        printf("  Content: \"%s\"\n", sb->buffer);
    }
}

int main() {
    StringBuilder *sb;

    printf("String Builder Demo\n");
    printf("==================\n");

    sb = create_string_builder(16);
    if (!sb) {
        printf("Failed to create string builder\n");
        return 1;
    }

    printf("Initial state:\n");
    print_sb_info(sb);

    // Append various types
    sb_append(sb, "Hello");
    printf("\nAfter appending 'Hello':\n");
    print_sb_info(sb);

    sb_append(sb, ", ");
    sb_append(sb, "World");
    printf("\nAfter appending ', World':\n");
    print_sb_info(sb);

    sb_append_char(sb, '!');
    sb_append(sb, " ");
    sb_append_int(sb, 2024);
    sb_append(sb, " is the year.");

    printf("\nAfter building complete string:\n");
    print_sb_info(sb);

    printf("\nFinal string: \"%s\"\n", sb_to_string(sb));

    // Demonstrate clearing and reusing
    sb_clear(sb);
    printf("\nAfter clearing:\n");
    print_sb_info(sb);

    sb_append(sb, "C programming is fun!");
    printf("\nAfter new content:\n");
    print_sb_info(sb);

    free_string_builder(sb);
    printf("\nString builder freed successfully.\n");

    return 0;
}