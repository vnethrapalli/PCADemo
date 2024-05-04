#include "utils/serial.h"
#include <math.h>

#define MAXDATAPOINTS 128
#define MAXFEATURES 128

int main() {
    double (*X)[MAXFEATURES] = malloc(sizeof(*X)*MAXDATAPOINTS);
    double (*X_std)[MAXFEATURES] = malloc(sizeof(*X_std)*MAXDATAPOINTS);
    double (*cov)[MAXFEATURES] = malloc(sizeof(*cov)*MAXDATAPOINTS);
    double (*X_proj)[MAXFEATURES] = malloc(sizeof(*cov)*MAXDATAPOINTS);

    double (*Q)[MAXFEATURES] = malloc(sizeof(*Q)*MAXDATAPOINTS);
    double (*evals)[MAXFEATURES] = malloc(sizeof(*evals)*MAXDATAPOINTS);
    double (*evects)[MAXFEATURES] = malloc(sizeof(*evects)*MAXDATAPOINTS);
    double (*proj)[MAXFEATURES] = malloc(sizeof(*proj)*MAXDATAPOINTS);

    FILE* fp;
    char* line = NULL;
    double x, y, sm, svar, next_sm, next_svar, tot;
    int rows, cols, i, j, k, temp, min_eval_idx, num_components = 1;
    double* means = malloc(MAXFEATURES * sizeof(double));
    int* sorted_idxs_desc = malloc(MAXFEATURES * sizeof(int));
    size_t len = 0;
    

    /* read in first line to get dimensions of the data */
    fp = fopen("data/ellipse.txt", "r");
    getline(&line, &len, fp);
    sscanf(line, "%d,%d", &rows, &cols);
    i = 0;
    while ((getline(&line, &len, fp)) != -1) {
        sscanf(line, "%lf,%lf", &x, &y);
        X[i][0] = x;
        X[i][1] = y;
        i++;
    }
    fclose(fp);

    /* normalize each column of the data */
    for (i = 0; i < cols; i++) {
        sm = 0;
        svar = 0;
        for (j = 0; j < rows; j++) {
            next_sm = sm + (X[j][i] - sm) / (j + 1);
            next_svar = j <= 1 ? 0 : (1 - 1.0 / j) * svar + (j + 1) * (next_sm - sm) * (next_sm - sm);
            sm = next_sm;
            svar = next_svar;
        }
        means[i] = sm;

        /* transform each column of data */
        for (j = 0; j < rows; j++) 
            X_std[j][i] = (X[j][i] - sm) / sqrt(svar);
    }

    // printf("standardized data\n");
    // print_matrix(X_std, rows, cols);

    /* compute covariance matrix */
    for (i = 0; i < cols; i++) {
        for (j = i; j < cols; j++) {
            tot = 0;
            for (k = 0; k < rows; k++) {
                tot += X_std[k][i] * X_std[k][j];
            }
            tot /= rows;
            cov[i][j] = tot;
            cov[j][i] = tot;
        }
    }
    
    // printf("covariance matrix\n");
    // print_matrix(cov, cols, cols);

    /* get eigen values and eigen vectors from covariance matrix */
    eigs_qr(cov, cols, Q, evals, evects);

    printf("eigenvalues (on diagonal):\n");
    print_matrix(evals, cols, cols);
    printf("\neigenvectors (columns):\n");
    print_matrix(evects, cols, cols);

    /* picking k biggest principal components to construct projection matrix */
    for (i = 0; i < cols; i++)
        sorted_idxs_desc[i] = i;

    /* selection sort is used here for simplicity, but more efficient sorts could be used */
    for (i = cols-1; i > 0; i--) {
        min_eval_idx = i;
        for (j = i - 1; j >= 0; j--) {
            if (evals[j][j] < evals[min_eval_idx][min_eval_idx]) {
                min_eval_idx = j;
            }
            temp = sorted_idxs_desc[i];
            sorted_idxs_desc[i] = min_eval_idx;
            sorted_idxs_desc[min_eval_idx] = temp;
        }
    }


    /* write down principal components in order to file for use in python plotter (transposed) */
    fp = fopen("data/components.txt", "w");
    for (i = 0; i < cols; i++) {
        for (j = 0; j < cols; j++) {
            if (j != cols - 1)
                fprintf(fp, "%lf,", evects[j][sorted_idxs_desc[i]]);
            else
                fprintf(fp, "%lf\n", evects[j][sorted_idxs_desc[i]]);
        }   
    }
    fclose(fp);

    /* construct projection matrix from the desired number of principal components and eigenvectors */
    num_components = 1;
    for (i = 0; i < num_components; i++)
        for (j = 0; j < cols; j++)
            proj[j][i] = evects[j][sorted_idxs_desc[i]];

    // printf("\nprojection matrix:\n");
    // print_matrix(proj, cols, num_components);

    /* project standardized data onto the specified principal components */
    matmul_serial(X_std, proj, X_proj, rows, cols, num_components);

    // printf("\nprojected data:\n");
    // print_matrix(X_proj, rows, num_components);

    /* write projected data to file for use in python plotter */
    fp = fopen("data/xproj.txt", "w");
    for (i = 0; i < rows; i++) {
        for (j = 0; j < num_components; j++) {
            if (j != num_components - 1)
                fprintf(fp, "%lf,", X_proj[i][j]);
            else
                fprintf(fp, "%lf\n", X_proj[i][j]);
        }   
    }
    fclose(fp);

    free(X);
    free(cov);
    free(means);
    free(X_std);
    free(Q);
    free(evals);
    free(evects);
    free(sorted_idxs_desc);
    free(proj);
}
