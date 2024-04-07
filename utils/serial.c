#include <stdio.h>
#include <math.h>
#include <time.h>
#include "serial.h"


/*
computes matrix multiplication X = AB
A (dim1 x dim2); B (dim2 x dim3)
*/
void matmul_serial(double (*A)[MAXDIM], double (*B)[MAXDIM], double (*X)[MAXDIM], int dim1, int dim2, int dim3) {
    // initialize variables
    int i, j, k;

    double start_time, tot_time, avg_time, val;

    // printf("output format: average runtime {runtime} seconds when using {num_threads} threads\n");
    for (int i = 0; i < dim1; i++)
        for (int k = 0; k < dim2; k++)
            for (int j = 0; j < dim3; j++)
                X[i][j] = X[i][j] + A[i][k]*B[k][j];
}

void print_matrix(double (*A)[MAXDIM], int rows, int cols) {
    int i, j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++)
            printf("%.6f ", A[i][j]);
        printf("\n");
    }
}
