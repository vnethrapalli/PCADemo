#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXDIM 16

void matmul_serial(double (*A)[MAXDIM], double (*B)[MAXDIM], double (*X)[MAXDIM], int dim1, int dim2, int dim3);
void print_matrix(double (*A)[MAXDIM], int m, int n);
void gramschmidt_qr_serial(double (*A)[MAXDIM], int n, double (*Q)[MAXDIM], double (*R)[MAXDIM]);