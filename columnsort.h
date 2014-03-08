#ifndef _COLUMNSORT_H_
#define _COLUMNSORT_H_

#include "quicksort.h"

void sort_column(matrix_t *matrix, int i) {
    //quicksort(matrix->entries[i], 0, matrix->n - 1);
}

void transpose_column(matrix_t *src, matrix_t *dest, int j) {
    int m, n, i, start_row;
    m = src->m; n = src->n;
    start_row = j * (m / n);
    for (i = 0; i < m; i++)
        matrix_set(dest, start_row + i / n, i % n,
            matrix_get(src, i, j));
}

#endif
