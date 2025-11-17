#include <stdio.h>

int main() {
    int score;

    printf("Grade Calculator\n");
    printf("================\n");
    printf("Enter a score (0-100): ");
    scanf("%d", &score);

    printf("\nScore: %d - ", score);

    if (score < 0 || score > 100) {
        printf("Invalid score! Please enter a value between 0 and 100.\n");
    } else if (score >= 90) {
        printf("Grade: A - Excellent work!\n");
    } else if (score >= 80) {
        printf("Grade: B - Good job!\n");
    } else if (score >= 70) {
        printf("Grade: C - Satisfactory.\n");
    } else if (score >= 60) {
        printf("Grade: D - Needs improvement.\n");
    } else if (score >= 0) {
        printf("Grade: F - Please see the instructor.\n");
    }

    // Additional feedback using switch
    printf("\nPerformance Level: ");
    if (score >= 70) {
        printf("Passing\n");
    } else {
        printf("Needs Attention\n");
    }

    return 0;
}