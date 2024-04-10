#include "utils/serial.h"

/* maximum dimensions currently set to 16 */

int main() {
    int i, j, n = 3, r;
    double (*A)[MAXDIM] = malloc(sizeof(*A)*MAXDIM);
    double (*A_sym)[MAXDIM] = malloc(sizeof(*A_sym)*MAXDIM);
    double (*B)[MAXDIM] = malloc(sizeof(*B)*MAXDIM);
    double (*C)[MAXDIM] = malloc(sizeof(*C)*MAXDIM);
    double (*Q)[MAXDIM] = malloc(sizeof(*Q)*MAXDIM);
    double (*R)[MAXDIM] = malloc(sizeof(*R)*MAXDIM);
    double (*QR)[MAXDIM] = malloc(sizeof(*QR)*MAXDIM);
    double (*V)[MAXDIM] = malloc(sizeof(*V)*MAXDIM);
    double (*eVects)[MAXDIM] = malloc(sizeof(*eVects)*MAXDIM);
    double (*eVals)[MAXDIM] = malloc(sizeof(*eVals)*MAXDIM);

    srand(1123);

    /* initialize with some dummy values */
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            A[i][j] = rand() % 5;
            B[i][j] = 1;
        }
    }
    // matmul_serial(A, B, C, n, n, n);

    // printf("testing matrix multiplication\n");
    // printf("A = \n");
    // print_matrix(A, n, n);
    // printf("\nB = \n");
    // print_matrix(B, n, n);
    // printf("\nC = AB = \n");
    // print_matrix(C, n, n);

    // printf("\n\ntesting QR factorization with regular Gram-Schmidt\n");
    // gramschmidt_qr_serial(A, n, Q, R);
    // matmul_serial(Q, R, QR, n, n, n);
    // printf("A = \n");
    // print_matrix(A, n, n);
    // printf("\nQ = \n");
    // print_matrix(Q, n, n);
    // printf("\nR = \n");
    // print_matrix(R, n, n);
    // printf("\nQR = \n");
    // print_matrix(QR, n, n);

    // printf("\n\ntesting infinity norm\n");
    // printf("A = \n");
    // print_matrix(A, n, n);
    // printf("\ninfinity norm: %.6f\n", infinity_norm(A, n));

    printf("\n\ntesting finding eigenvalues and eigenvectors for symmetric matrix\n");
    printf("A_sym = \n");
    for (i = 0; i < n; i++) {
        for (j = i; j < n; j++) {
            r = rand();
            A_sym[i][j] = 1 + (r % 5);
            A_sym[j][i] = 1 + (r % 5);
        }
    }
    print_matrix(A_sym, n, n);
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            Q[i][j] = 0;
            R[i][j] = 0;
        }
    }
    eigs_qr(A_sym, n, Q, R, V);
    printf("\neigenvalues:\n");
    print_matrix(R, n, n);
    printf("\neigenvectors:\n");
    print_matrix(V, n, n);

    free(A);
    free(A_sym);
    free(B);
    free(C);
    free(Q);
    free(V);
    free(R);
    free(QR);
    free(eVects);
    free(eVals);
    
    return 0;
}