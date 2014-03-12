#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "matrix.h"
#include "columnsort.h"

int main(int argc, char **argv) {
    unsigned long n;
    long r, s;
    parse_args(argc, argv, &n, NULL);

    get_matrix_size(n, &r, &s);

    printf("n = %lu, r = %ld, s = %ld\n", n, r, s);

    matrix_t matrix, matrix_2;
    matrix_init(&matrix, r, s);
    matrix_init(&matrix_2, r, s);

    matrix_fill_random(&matrix);
    matrix_print(&matrix);

    long j;

    printf("SORT\n");
    for (j = 0; j < matrix.n; j++)
        sort_column(&matrix, j);

    matrix_print(&matrix);

    printf("TRANSPOSE\n");
    for (j = 0; j < matrix.n; j++)
        transpose_column(&matrix, &matrix_2, j);

    matrix_print(&matrix_2);

    printf("SORT\n");
    for (j = 0; j < matrix.n; j++)
        sort_column(&matrix_2, j);

    matrix_print(&matrix_2);

    printf("REVERSE TRANSPOSE\n");
    for (j = 0; j < matrix.n; j++)
        reverse_transpose_column(&matrix_2, &matrix, j);

    matrix_print(&matrix);

    printf("SORT\n");
    for (j = 0; j < matrix.n; j++)
        sort_column(&matrix, j);

    matrix_print(&matrix);

    printf("SHIFT SORT\n");
    for (j = 0; j < matrix.n; j++)
        sort_column_shift(&matrix, j, matrix.m / 2);

    matrix_print(&matrix);

    matrix_free(&matrix);
    matrix_free(&matrix_2);
    return 0;
}
