#include <stdlib.h>
#include <time.h>

/*
 * Matrix type. M rows and N columns of int entries.
 */
typedef struct {
    int m;
    int n;
    int **entries;
    void *_block;
} matrix_t;

/*
 * Creates a new m x n integer matrix. Uses a single contiguous block of memory
 */
void matrix_init(matrix_t *matrix, int m, int n) {
    int i;
    int *block = malloc(sizeof(int) * m * n);

    int **entries = malloc(m * sizeof(int *));
    for (i = 0; i < m; i++) {
        entries[i] = &block[i * n];
        printf("%d: %p\n", i, entries[i]);
    }

    matrix->m = m;
    matrix->n = n;
    matrix->entries = entries;
    matrix->_block = block;
}

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
            matrix->entries[i][j] = rand();
}

/*
 * Print a matrix to stdout
 */
void matrix_print(matrix_t *matrix) {
    int i, j;
    for (i = 0; i < matrix->m; i++) {
        for (j = 0; j < matrix->n; j++)
            printf("%10d ", matrix->entries[i][j]);
        printf("\n");
    }
}

void matrix_free(matrix_t *matrix) {
    free(matrix->entries);
    free(matrix->_block);
}
