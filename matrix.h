#include <stdlib.h>
#include <time.h>

typedef struct {
    int m;
    int n;
    int **entries;
} matrix_t;

void matrix_init(matrix_t *matrix, int m, int n, int **entries) {
    matrix->m = m;
    matrix->n = n;
    matrix->entries = entries;
}

matrix_t *matrix_new(int m, int n) {
    int i;
    matrix_t *matrix = malloc(sizeof(matrix_t));
    int *block = malloc(sizeof(int) * m * n);

    int **entries = malloc(m * sizeof(int *));
    for (i = 0; i < m; i++) {
        entries[i] = &block[i * n];
        printf("%d: %p\n", i, entries[i]);
    }
    matrix_init(matrix, m, n, entries);
    return matrix;
}

void matrix_fill_random(matrix_t *matrix) {
    int i, j, m, n;
    m = matrix->m;
    n = matrix->n;
    srand(time(NULL));
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            matrix->entries[i][j] = rand();
}

void matrix_print(matrix_t *matrix) {
    int i, j;
    for (i = 0; i < matrix->m; i++) {
        for (j = 0; j < matrix->n; j++)
            printf("%10d ", matrix->entries[i][j]);
        printf("\n");
    }
}
