#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int **data;
    int rows;
    int cols;
} Matrix;

Matrix* create_matrix(int rows, int cols) {
    Matrix *matrix = (Matrix*)malloc(sizeof(Matrix));
    if (!matrix) return NULL;

    matrix->data = (int**)malloc(rows * sizeof(int*));
    if (!matrix->data) {
        free(matrix);
        return NULL;
    }

    for (int i = 0; i < rows; i++) {
        matrix->data[i] = (int*)malloc(cols * sizeof(int));
        if (!matrix->data[i]) {
            // Cleanup on failure
            for (int j = 0; j < i; j++) {
                free(matrix->data[j]);
            }
            free(matrix->data);
            free(matrix);
            return NULL;
        }
    }

    matrix->rows = rows;
    matrix->cols = cols;

    // Initialize with zeros
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix->data[i][j] = 0;
        }
    }

    return matrix;
}

void free_matrix(Matrix *matrix) {
    if (matrix) {
        for (int i = 0; i < matrix->rows; i++) {
            free(matrix->data[i]);
        }
        free(matrix->data);
        free(matrix);
    }
}

void set_element(Matrix *matrix, int row, int col, int value) {
    if (matrix && row >= 0 && row < matrix->rows && col >= 0 && col < matrix->cols) {
        matrix->data[row][col] = value;
    }
}

int get_element(Matrix *matrix, int row, int col) {
    if (matrix && row >= 0 && row < matrix->rows && col >= 0 && col < matrix->cols) {
        return matrix->data[row][col];
    }
    return 0; // Default return for invalid access
}

void print_matrix(Matrix *matrix) {
    if (!matrix) return;

    printf("Matrix (%d x %d):\n", matrix->rows, matrix->cols);
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            printf("%4d ", matrix->data[i][j]);
        }
        printf("\n");
    }
}

Matrix* add_matrices(Matrix *a, Matrix *b) {
    if (!a || !b || a->rows != b->rows || a->cols != b->cols) {
        return NULL;
    }

    Matrix *result = create_matrix(a->rows, a->cols);
    if (!result) return NULL;

    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < a->cols; j++) {
            result->data[i][j] = a->data[i][j] + b->data[i][j];
        }
    }

    return result;
}

int main() {
    Matrix *matrix1, *matrix2, *sum;

    printf("Dynamic Matrix Demo\n");
    printf("==================\n");

    // Create first matrix (3x3)
    matrix1 = create_matrix(3, 3);
    if (!matrix1) {
        printf("Failed to create matrix1\n");
        return 1;
    }

    // Fill first matrix
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            set_element(matrix1, i, j, (i + 1) * (j + 1));
        }
    }

    // Create second matrix (3x3)
    matrix2 = create_matrix(3, 3);
    if (!matrix2) {
        printf("Failed to create matrix2\n");
        free_matrix(matrix1);
        return 1;
    }

    // Fill second matrix
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            set_element(matrix2, i, j, (i + j) * 2);
        }
    }

    printf("Matrix 1:\n");
    print_matrix(matrix1);

    printf("\nMatrix 2:\n");
    print_matrix(matrix2);

    // Add matrices
    sum = add_matrices(matrix1, matrix2);
    if (sum) {
        printf("\nSum of matrices:\n");
        print_matrix(sum);
    }

    // Cleanup
    free_matrix(matrix1);
    free_matrix(matrix2);
    free_matrix(sum);

    printf("\nAll matrices freed successfully.\n");

    return 0;
}