#include "utils/serial.h"

#define MAXDATAPOINTS 128
#define MAXFEATURES 2

int main() {
    double (*X)[MAXFEATURES] = malloc(sizeof(*X)*MAXDATAPOINTS);

    // load csv data into X
    FILE* fp;
    char* line = NULL, *x, *y;
    size_t len = 0;
    

    fp = fopen("data/ellipse.txt", "r");
    while ((getline(&line, &len, fp)) != -1) {
        sscanf(line, "%s,%s", x, y);
    }
    fclose(fp);

    free(X);
}
