#ifndef _COLUMNSORT_H_
#define _COLUMNSORT_H_

#include "quicksort.h"
#include "matrix.h"

void sort_column(matrix_t *matrix, int j) {
    quicksort(matrix->_entries[j], 0, matrix->m - 1);
}

void transpose_column(matrix_t *src, matrix_t *dest, int j) {
    int m, n, i, start_row;
    m = src->m; n = src->n;
    start_row = j * (m / n);
    for (i = 0; i < m; i++)
        matrix_set(dest, start_row + i / n, i % n,
            matrix_get(src, i, j));
}

void reverse_transpose_column(matrix_t *src, matrix_t *dest, int j) {
    int m, n, i;
    m = src->m; n = src->n;
    for (i = 0; i < m; i++)
        matrix_set(dest, ((n * i) + j) % m, i / (m/n), matrix_get(src, i, j));
}

#endif
