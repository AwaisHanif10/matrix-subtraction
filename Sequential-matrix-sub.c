#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 500
#define COLS 500

// Function to initialize a matrix with random numbers
void initializeMatrix(int matrix[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            matrix[i][j] = rand() % 100;  // Random numbers from 0 to 99
        }
    }
}

// Function to subtract two matrices
void subtractMatrices(int A[ROWS][COLS], int B[ROWS][COLS], int result[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            result[i][j] = A[i][j] - B[i][j];
        }
    }
}

int main() {
    int A[ROWS][COLS], B[ROWS][COLS], result[ROWS][COLS];
    srand(time(0));  // Seed for random number generation

    // Initialize matrices
    initializeMatrix(A);
    initializeMatrix(B);

    // Measure execution time for a single run
    clock_t start = clock();
    subtractMatrices(A, B, result);
    clock_t end = clock();

    // Calculate and print execution time
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Matrix subtraction executed in %f seconds.\n", time_taken);

    return 0;
}
