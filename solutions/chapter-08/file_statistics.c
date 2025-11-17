#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct {
    int lines;
    int words;
    int characters;
    int bytes;
} FileStats;

void count_file_stats(const char *filename, FileStats *stats) {
    FILE *file;
    char ch;
    int in_word = 0;

    // Initialize stats
    stats->lines = 0;
    stats->words = 0;
    stats->characters = 0;
    stats->bytes = 0;

    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return;
    }

    while ((ch = fgetc(file)) != EOF) {
        stats->bytes++;
        stats->characters++;

        if (ch == '\n') {
            stats->lines++;
        }

        if (isspace(ch)) {
            in_word = 0;
        } else if (!in_word) {
            in_word = 1;
            stats->words++;
        }
    }

    // Handle case where file doesn't end with newline
    if (stats->characters > 0 && ch != '\n') {
        stats->lines++;
    }

    fclose(file);
}

int main() {
    char filename[256];
    FileStats stats;

    printf("File Statistics Counter\n");
    printf("=======================\n");
    printf("Enter filename: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = '\0';

    count_file_stats(filename, &stats);

    printf("\nStatistics for %s:\n", filename);
    printf("Lines: %d\n", stats.lines);
    printf("Words: %d\n", stats.words);
    printf("Characters: %d\n", stats.characters);
    printf("Bytes: %d\n", stats.bytes);

    return 0;
}