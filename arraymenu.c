#include <stdio.h>
#include <stdlib.h>

// ANSI color codes
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

// Function declarations
void array1DMenu();
void array1D(int op);
void array2DMenu();
void array2D(int op);
int **createMatrix(int row, int col);
void displayMatrix(int **a, int row, int col);
void displayArray(int *a, int size, char name[]);
void addMatrix(int **a, int **b, int **r, int row, int col);
void subtractMatrix(int **a, int **b, int **r, int row, int col);
void multiplyMatrix(int **a, int **b, int **r, int row1, int col1, int row2, int col2);\

// Adds two matrices
void addMatrix(int **a, int **b, int **r, int row, int col) {
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            r[i][j] = a[i][j] + b[i][j];
}

// Subtracts second matrix from the first
void subtractMatrix(int **a, int **b, int **r, int row, int col) {
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            r[i][j] = a[i][j] - b[i][j];
}

// Multiplies two matrices
void multiplyMatrix(int **a, int **b, int **r, int row1, int col1, int row2, int col2) {
    for (int i = 0; i < row1; i++)
        for (int j = 0; j < col2; j++) {
            r[i][j] = 0;
            for (int k = 0; k < col1; k++)
                r[i][j] += a[i][k] * b[k][j];
        }
}

int main() {
    int choice;
    while (1) {
        
        printf(YELLOW "1. Work with 1D Arrays\n" RESET);
        printf(YELLOW "2. Work with 2D Arrays\n" RESET);
        printf(RED "3. Exit\n" RESET);
        printf(GREEN "Enter your choice: " RESET);
        scanf("%d", &choice);

        switch (choice) {
            case 1: array1DMenu(); break;
            case 2: array2DMenu(); break;
            case 3: printf(RED "\nExiting... Have a great day!\n" RESET); return 0;
            default: printf(RED "Invalid choice! Try again.\n" RESET);
        }
    }
}

// ---------- 1D ARRAY FUNCTIONS ---------- //
void array1DMenu() {
    int choice;
    
    printf(YELLOW "1. Addition\n" RESET);
    printf(YELLOW "2. Subtraction\n" RESET);
    printf(YELLOW "3. Multiplication\n" RESET);
    printf(GREEN "Enter your choice: " RESET);
    scanf("%d", &choice);

    if (choice >= 1 && choice <= 3)
        array1D(choice);
    else
        printf(RED "Invalid choice.\n" RESET);
}

void array1D(int op) {
    int size;
    printf(GREEN "\nEnter size of 1D arrays: " RESET);
    scanf("%d", &size);

    int *a = malloc(size * sizeof(int));
    int *b = malloc(size * sizeof(int));
    int *result = malloc(size * sizeof(int));

    printf(BLUE "Enter elements of Array A:\n" RESET);
    for (int i = 0; i < size; i++) {
        printf("A[%d]: ", i);
        scanf("%d", &a[i]);
    }

    printf(BLUE "Enter elements of Array B:\n" RESET);
    for (int i = 0; i < size; i++) {
        printf("B[%d]: ", i);
        scanf("%d", &b[i]);
    }

    // Show input arrays
    printf(GREEN "\nYou entered:\n" RESET);
    displayArray(a, size, "A");
    displayArray(b, size, "B");

    // Operation
    for (int i = 0; i < size; i++) {
        if (op == 1) result[i] = a[i] + b[i];
        else if (op == 2) result[i] = a[i] - b[i];
        else if (op == 3) result[i] = a[i] * b[i];
    }

    printf(YELLOW "\nResultant Array:\n" RESET);
    displayArray(result, size, "Result");

    free(a); free(b); free(result);
}

void displayArray(int *a, int size, char name[]) {
    printf(CYAN "+--------+--------+\n");
    printf("| Index  | Value  |\n");
    printf("+--------+--------+\n" RESET);
    for (int i = 0; i < size; i++)
        printf("| %5d  | %6d |\n", i, a[i]);
    printf(CYAN "+--------+--------+\n" RESET);
}

// ---------- 2D MATRIX FUNCTIONS ---------- //
void array2DMenu() {
    int choice;
    printf(CYAN "\n╔═════════════════════════════════╗\n");
    printf("║         2D Matrix Operations    ║\n");
    printf("╚═════════════════════════════════╝\n" RESET);
    printf(YELLOW "1. Addition\n" RESET);
    printf(YELLOW "2. Subtraction\n" RESET);
    printf(YELLOW "3. Multiplication\n" RESET);
    printf(GREEN "Enter your choice: " RESET);
    scanf("%d", &choice);

    if (choice >= 1 && choice <= 3)
        array2D(choice);
    else
        printf(RED "Invalid choice.\n" RESET);
}

void array2D(int op) {
    int row1, col1, row2, col2;
    printf(GREEN "\nEnter dimensions of Matrix A (rows cols): " RESET);
    scanf("%d %d", &row1, &col1);
    printf(GREEN "Enter dimensions of Matrix B (rows cols): " RESET);
    scanf("%d %d", &row2, &col2);

    int **a = createMatrix(row1, col1);
    int **b = createMatrix(row2, col2);
    int **result;

    // Input matrix A
    printf(BLUE "Enter elements of Matrix A:\n" RESET);
    for (int i = 0; i < row1; i++)
        for (int j = 0; j < col1; j++) {
            printf("A[%d][%d]: ", i, j);
            scanf("%d", &a[i][j]);
        }

    // Input matrix B
    printf(BLUE "Enter elements of Matrix B:\n" RESET);
    for (int i = 0; i < row2; i++)
        for (int j = 0; j < col2; j++) {
            printf("B[%d][%d]: ", i, j);
            scanf("%d", &b[i][j]);
        }

    printf(GREEN "\nYou entered Matrix A:\n" RESET);
    displayMatrix(a, row1, col1);
    printf(GREEN "You entered Matrix B:\n" RESET);
    displayMatrix(b, row2, col2);

    if ((op == 1 || op == 2) && (row1 != row2 || col1 != col2)) {
        printf(RED "Operation not possible. Dimension mismatch.\n" RESET);
    } else if (op == 3 && col1 != row2) {
        printf(RED "Multiplication not possible. Column of A != row of B.\n" RESET);
    } else {
        result = createMatrix((op == 3 ? row1 : row1), (op == 3 ? col2 : col1));

        if (op == 1)
            addMatrix(a, b, result, row1, col1);
        else if (op == 2)
            subtractMatrix(a, b, result, row1, col1);
        else if (op == 3)
            multiplyMatrix(a, b, result, row1, col1, row2, col2);

        printf(YELLOW "\nResultant Matrix:\n" RESET);
        displayMatrix(result, (op == 3 ? row1 : row1), (op == 3 ? col2 : col1));

        for (int i = 0; i < ((op == 3 ? row1 : row1)); i++) free(result[i]);
        free(result);
    }

    for (int i = 0; i < row1; i++) free(a[i]);
    for (int i = 0; i < row2; i++) free(b[i]);
    free(a); free(b);
}

// ---------- UTILITY FUNCTIONS ---------- //
int **createMatrix(int row, int col) {
    int **mat = malloc(row * sizeof(int *));
    for (int i = 0; i < row; i++)
        mat[i] = malloc(col * sizeof(int));
    return mat;
}

void displayMatrix(int **a, int row, int col) {
    // Print top border
    printf(CYAN "+");
    for (int j = 0; j < col; j++) printf("--------+");
    printf("\n" RESET);

    // Print row by row
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++)
            printf("| %6d ", a[i][j]);
        printf("|\n");

        // Print separator after each row
        printf(CYAN "+");
        for (int j = 0; j < col; j++) printf("--------+");
        printf("\n" RESET);
    }
}