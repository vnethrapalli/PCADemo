#include "utils/serial.h"

/* maximum dimensions currently set to 16 */

int main() {
    int i, j, n = 3;
    double (*A)[MAXDIM] = malloc(sizeof(*A)*MAXDIM);
    double (*B)[MAXDIM] = malloc(sizeof(*B)*MAXDIM);
    double (*C)[MAXDIM] = malloc(sizeof(*C)*MAXDIM);

    /* initialize with some dummy values */
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            A[i][j] = i*n + j;
            B[i][j] = 1;
        }
    }
    matmul_serial(A, B, C, n, n, n);

    printf("A = \n");
    print_matrix(A, n, n);
    printf("\nB = \n");
    print_matrix(B, n, n);
    printf("\nC = AB = \n");
    print_matrix(C, n, n);

    free(A);
    free(B);
    free(C);
    
    return 0;
}