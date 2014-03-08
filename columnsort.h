#ifndef _COLUMNSORT_H_
#define _COLUMNSORT_H_

#include "quicksort.h"

void sort_row(matrix_t *matrix, int i) {
    quicksort(matrix->entries[i], 0, matrix->n - 1);
}

void transpose_row(matrix_t *src, matrix_t *dest, int i) {
    int m, n, j, start_col;
    m = src->m; n = src->n;
    start_col = i * (n / m);
    for (j = 0; j < n; j++)
        dest->entries[j % m][start_col + j / m] = src->entries[i][j];
}

#endif
