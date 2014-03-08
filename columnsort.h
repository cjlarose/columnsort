#ifndef _COLUMNSORT_H_
#define _COLUMNSORT_H_

#include "quicksort.h"
#include "matrix.h"

// Classic bithack from http://graphics.stanford.edu/~seander/bithacks.html
int power_of_two(int x) {
    return (x != 0) && ((x & (x - 1)) == 0);
}

// Returns k such that x = 2^k
int log_base_2(unsigned int x) {
    assert(x != 0);

    int i = 0;
    for (; ; i++, x >>= 1)
        if (x & 1)
            break;
    return i;
}

int parse_args(int argc, char **argv, unsigned int *dest) {

    if (argc < 2) {
        fprintf(stderr, "Usage: seq-sum n\n");
        return 0;
    }

    // with an unsigned int, we can accept arguments up to 2^31
    unsigned int n = atol(argv[1]);

    if (n <= 0 || !power_of_two(n)) {
        fprintf(stderr, "n must be a power of 2 greater than or equal to 1\n");
        return 0;
    }

    *dest = n;
    return 1;
}

void get_matrix_size(unsigned int n, int *r, int *s) {
    int k = log_base_2(n);
    *r = 1 << (k / 2 + k % 2);
    *s = 1 << k / 2;
}

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
    } else
        quicksort(matrix->_entries[j] - shift, 0, matrix->m - 1);
}

#endif
