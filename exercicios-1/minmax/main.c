#include <stdlib.h>
#include <stdio.h>

typedef struct MinMax {
    int min;
    int max;
} MinMax;

MinMax *getMinMax(int *vector, int size) {
    return NULL;
}

void initVector(int *vector, int size) {
    for (int i = 0; i < size; i++) {
        vector[i] = rand()%100;
        printf("%d\n", vector[i]);
    }
}

int main () {
    int vector[10];
    initVector(vector, 10);
    MinMax *m;
    m = getMinMax(vector, 10);
    free(m);
    return 0;
}