#ifndef _COLUMNSORT_H_
#define _COLUMNSORT_H_

#include "quicksort.h"
#include "matrix.h"

/*
 * Sorting a column j in our column-order matrix is actually just
 * sorting the ith row. This is theorhetically better for cache
 * utilization
 */
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

/*
 * Instead of actually moving elements around and then sorting by column,
 * We can just sort with an offset, which is facilitated by the fact that
 * our matrix is stored in column-order form. Sorting the 0th column here
 * actually means to sort the first m - (n / 2) elements, then sorting the
 * last n / 2 elements.
 */
void sort_column_shift(matrix_t *matrix, int j, int shift) {
    if (j == 0) {
        quicksort(matrix->_entries[0], 0, matrix->m - shift - 1);
        quicksort(matrix->_entries[matrix->n - 1], matrix->m - shift, matrix->m - 1);
        /*
        int i = 0;
        for (; i < matrix->m - shift; i++)
            matrix_set(matrix, i, 0, 0xDEADBEEF);
        for (i = matrix->m - shift; i < matrix->m; i++)
            matrix_set(matrix, i, matrix->n - 1, 0xDEADBEEF);
        */
    } else {
        quicksort(matrix->_entries[j] - shift, 0, matrix->m - 1);
        /*
        int i;
        for (i = -shift; i < matrix->m - shift; i++)
            matrix_set(matrix, i, j, j);
        */
    }
}

#endif
