#include "serial.h"

/*
computes matrix multiplication X = AB
A (dim1 x dim2); B (dim2 x dim3)
*/
void matmul_serial(double (*A)[MAXDIM], double (*B)[MAXDIM], double (*X)[MAXDIM], int dim1, int dim2, int dim3) {
    // initialize variables
    int i, j, k;
    for (int i = 0; i < dim1; i++)
        for (int k = 0; k < dim2; k++)
            for (int j = 0; j < dim3; j++)
                X[i][j] += A[i][k] * B[k][j];
}

void matsub_serial(double (*A)[MAXDIM], double (*B)[MAXDIM], double (*X)[MAXDIM], int m, int n) {
    int i, j;
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            X[i][j] = A[i][j] - B[i][j];
}


void print_matrix(double (*A)[MAXDIM], int rows, int cols) {
    int i, j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++)
            printf("%.6f ", A[i][j]);
        printf("\n");
    }
}

void gramschmidt_qr_serial(double (*A)[MAXDIM], int n, double (*Q)[MAXDIM], double (*R)[MAXDIM]) {
    int i, j, k;
    double magn, dot;

    /* i controls the column being worked on */
    for (i = 0; i < n; i++) {
        /* initialize column i to that of matrix A */
        for(k = 0; k < n; k++)
            Q[k][i] = A[k][i];

        /* j controls the previous column being accounted for */
        for (j = 0; j < i; j++) {
            /* dot product between new column i and completed column j */
            dot = 0;
            for (k = 0; k < n; k++) {
                dot += Q[k][j] * A[k][i];
            }
            R[j][i] = dot;

            /* subtract (current column i dotted with old column j) times column j */
            for (k = 0; k < n; k++) {
                Q[k][i] -= dot * Q[k][j];
            }
        }

        /* normalize current column */
        magn = 0;
        for (k = 0; k < n; k++)
            magn += Q[k][i] * Q[k][i];
        magn = sqrt(magn);
        for (k = 0; k < n; k++) 
            Q[k][i] /= magn;
        R[i][i] = magn;
    }
}


/* https://www.cs.cornell.edu/~bindel/class/cs6210-f12/notes/lec26.pdf */
/* https://faculty.washington.edu/trogdon/105A/html/Lecture24.html */
/* https://math.stackexchange.com/questions/3947108/how-to-get-eigenvectors-using-qr-algorithm */
void eigs_qr(double (*A)[MAXDIM], int n, double (*Q)[MAXDIM], double (*R)[MAXDIM], double (*V)[MAXDIM]) {
    int i, j, evnum, it = 0, max_iter = 100;
    double rowsum, val, norm = -1, infinity_norm = 10000000; // big number
    double tolerance = 1e-8;
    double (*A_temp)[MAXDIM] = malloc(sizeof(*A_temp)*MAXDIM);
    double (*QQ)[MAXDIM] = malloc(sizeof(*QQ)*MAXDIM);

    matrix_copy(A, A_temp, n, n);

    /* initialize QQ to identity matrix */
    for (i = 0; i < n; i++)
        QQ[i][i] = 1;

    while (infinity_norm >= tolerance && it <= max_iter) {
        gramschmidt_qr_serial(A_temp, n, Q, R);

        // printf("\nQQ = \n");
        // print_matrix(QQ, n, n);
        // printf("\nQ = \n");
        // print_matrix(Q, n, n);

        /* use A_temp as storage to accumulate product of Qs */
        /* zero out A_temp and reuse its space for next calculation */
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                A_temp[i][j] = 0;
        matmul_serial(QQ, Q, A_temp, n, n, n);
        matrix_copy(A_temp, QQ, n, n);

        // printf("\nQQ = \n");
        // print_matrix(QQ, n, n);

        // printf("\n------------------------\n");

        /* zero out A_temp and reuse its space for next calculation */
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                A_temp[i][j] = 0;
        matmul_serial(R, Q, A_temp, n, n, n);

        /* compute infinity norm of A - diag(A) */
        // for (i = 0; i < n; i++) {
        //     rowsum = 0;
        //     for (j = 0; j < n; j++) {
        //         if (i != j)
        //             rowsum += abs(A[i][j]);
        //     }

        //     if (rowsum > norm)
        //         norm = rowsum;
        // }
        // infinity_norm = norm;
        // norm = -1;
        it += 1;
    }

    printf("\neigs in %d iterations\n", it);

    // V has columns being the eigen vectors
    /* initialize V to identity matrix */
    for (i = 0; i < n; i++)
        V[i][i] = 1;
    for (evnum = 1; evnum < n; evnum++) {
        /*
        solve (r_ii I - R(1:i-1, 1:i-1)) v_i(1:i-1) = R(1:i-1, i)
        next element of v_i is 1, followed by 0s
        */
        for (i = evnum - 1; i >= 0; i--) {
            val = R[i][i+1];
            for (j = i+1; j < evnum; j++) {
                val -= R[i][j] * QQ[j][i];
            }

            V[i][evnum] = val / (R[evnum][evnum] - R[i][i]);
        }
    }   

    /* eigen vectors are in QQ * V (put in V, using A_temp as auxiliary space) */
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            A_temp[i][j] = 0;
    matmul_serial(QQ, V, A_temp, n, n, n);
    matrix_copy(A_temp, V, n, n);

    free(A_temp); 
    free(QQ);   
}

void matrix_copy(double (*A)[MAXDIM], double (*B)[MAXDIM], int m, int n) {
    int i, j;
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            B[i][j] = A[i][j];
}


/* maximum rowsum of matrix A */
double infinity_norm(double (*A)[MAXDIM], int n) {
    double rowsum, norm = -1;
    int i, j;
    
    for (i = 0; i < n; i++) {
        rowsum = 0;
        for (j = 0; j < n; j++) 
            rowsum += abs(A[i][j]);

        if (rowsum > norm)
            norm = rowsum;
    }

    return norm;
}
