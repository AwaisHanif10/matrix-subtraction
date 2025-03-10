#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define ROWS 500
#define COLS 500
#define RUNS 10

// Function to initialize a matrix with random numbers
// (kept sequential due to rand() being not thread-safe)
void initializeMatrix(int matrix[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            matrix[i][j] = rand() % 100;  // Random numbers from 0 to 99
        }
    }
}

// Function to subtract two matrices using OpenMP parallelization
void subtractMatrices(int A[ROWS][COLS], int B[ROWS][COLS], int result[ROWS][COLS]) {
    // Parallelizing the matrix subtraction using OpenMP
    #pragma omp parallel for collapse(2) shared(A, B, result) default(none)
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            result[i][j] = A[i][j] - B[i][j];
        }
    }
}
