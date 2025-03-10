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
