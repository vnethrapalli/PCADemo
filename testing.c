#include "utils/serial.h"

/* maximum dimensions currently set to 16 */

int main() {
    int i, j, n = 3;
    double (*A)[MAXDIM] = malloc(sizeof(*A)*MAXDIM);
    double (*B)[MAXDIM] = malloc(sizeof(*B)*MAXDIM);
    double (*C)[MAXDIM] = malloc(sizeof(*C)*MAXDIM);
    double (*Q)[MAXDIM] = malloc(sizeof(*Q)*MAXDIM);
    double (*R)[MAXDIM] = malloc(sizeof(*R)*MAXDIM);
    double (*QR)[MAXDIM] = malloc(sizeof(*QR)*MAXDIM);

    srand(123123);

    /* initialize with some dummy values */
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            A[i][j] = rand() % 5;
            B[i][j] = 1;
        }
    }
    matmul_serial(A, B, C, n, n, n);

    printf("testing matrix multiplication\n");
    printf("A = \n");
    print_matrix(A, n, n);
    printf("\nB = \n");
    print_matrix(B, n, n);
    printf("\nC = AB = \n");
    print_matrix(C, n, n);

    printf("\n\ntesting QR factorization with regular Gram-Schmidt\n");
    gramschmidt_qr_serial(A, n, Q, R);
    matmul_serial(Q, R, QR, n, n, n);
    printf("A = \n");
    print_matrix(A, n, n);
    printf("\nQ = \n");
    print_matrix(Q, n, n);
    printf("\nR = \n");
    print_matrix(R, n, n);
    printf("\nQR = \n");
    print_matrix(QR, n, n);

    free(A);
    free(B);
    free(C);
    free(Q);
    free(R);
    free(QR);
    
    return 0;
}