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
    #pragma omp parallel for collapse(2) schedule(static) shared(A, B, result) default(none)
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            result[i][j] = A[i][j] - B[i][j];
        }
    }
}

int main() {
    int A[ROWS][COLS], B[ROWS][COLS], result[ROWS][COLS];
    double start_time, end_time;
    double run_times[RUNS];
    
    // Seed for random number generation
    srand(time(0));
    
    // Initialize matrices
    initializeMatrix(A);
    initializeMatrix(B);
    
    // Set the number of threads
    int num_threads = 4;  // You can change this value to experiment with different thread counts
    omp_set_num_threads(num_threads);
    
    double total_time = 0.0;
    
    // Use a critical section to print results in order
    #pragma omp parallel for private(start_time, end_time) shared(run_times, A, B, result) schedule(static)
    for (int run = 0; run < RUNS; run++) {
        start_time = omp_get_wtime(); // More accurate timing for parallel code
        
        subtractMatrices(A, B, result);
        
        end_time = omp_get_wtime();
        run_times[run] = end_time - start_time;
        
        #pragma omp critical
        {
            printf("Run %d executed in %f seconds.\n", run + 1, run_times[run]);
        }
    }
    
    // Calculate average time (sequential part)
    for (int i = 0; i < RUNS; i++) {
        total_time += run_times[i];
    }
    
    double average_time = total_time / RUNS;
    printf("Average execution time over %d runs with %d threads: %f seconds.\n", 
           RUNS, num_threads, average_time);
    
    return 0;
}