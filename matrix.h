#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 * Matrix type. M rows and N columns of int entries. For the purpose of this
 * assignment, this matrix is actually stored in column-order form instead of
 * row-order.
 */
typedef struct {
    int m;
    int n;
    int **_entries;
    void *_block;
} matrix_t;

/*
 * Creates a new m x n integer matrix. Uses a single contiguous block of memory
 */
void matrix_init(matrix_t *matrix, int m, int n) {
    int i;
    int *block = malloc(sizeof(int) * m * n);
    if (block == NULL) {
        fprintf(stderr, "Insufficient memory!\n");
        exit(1);
    }

    int **entries = malloc(n * sizeof(int *));
    if (entries == NULL) {
        fprintf(stderr, "Insufficient memory!\n");
        exit(1);
    }
    for (i = 0; i < n; i++) {
        entries[i] = &block[i * m];
        printf("%d: %p\n", i, entries[i]);
    }

    matrix->m = m;
    matrix->n = n;
    matrix->_entries = entries;
    matrix->_block = block;
}

#define matrix_get(ptr, i, j) ((ptr)->_entries[j][i])
#define matrix_set(ptr, i, j, val) ((ptr)->_entries[j][i] = (val))

/*
 * Given a matrix, fill its entries in with random values
 */
void matrix_fill_random(matrix_t *matrix) {
    int i, j, m, n;
    m = matrix->m;
    n = matrix->n;
    srand(time(NULL));
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            matrix_set(matrix, i, j, rand());
}

/*
 * Print a matrix to stdout
 */
void matrix_print(matrix_t *matrix) {
    int i, j;
    for (i = 0; i < matrix->m; i++) {
        for (j = 0; j < matrix->n; j++)
            printf("%10d ", matrix_get(matrix, i, j));
        printf("\n");
    }
}

void matrix_free(matrix_t *matrix) {
    free(matrix->_entries);
    free(matrix->_block);
}

#endif
