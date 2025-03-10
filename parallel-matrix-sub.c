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

int main() {
    int A[ROWS][COLS], B[ROWS][COLS], result[ROWS][COLS];
    srand(time(0));  // Seed for random number generation

    // Initialize matrices
    initializeMatrix(A);
    initializeMatrix(B);

    // Set the number of threads (this can also be controlled via OMP_NUM_THREADS environment variable)
    int num_threads = 4;  // You can change this value to experiment with different thread counts
    omp_set_num_threads(num_threads);

    double total_time = 0.0;
    for (int run = 0; run < RUNS; run++) {
        clock_t start = clock();
        subtractMatrices(A, B, result);
        clock_t end = clock();
        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        total_time += time_taken;
        printf("Run %d executed in %f seconds.\n", run + 1, time_taken);
    }

    double average_time = total_time / RUNS;
    printf("Average execution time over %d runs: %f seconds.\n", RUNS, average_time);

    return 0;
}
