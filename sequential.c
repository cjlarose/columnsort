#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "matrix.h"
#include "columnsort.h"

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

int main(int argc, char **argv) {
    unsigned int n;
    int k, success, r, s;
    success = parse_args(argc, argv, &n);
    if (!success)
        return 1;

    k = log_base_2(n);
    r = 1 << (k / 2 + k % 2);
    s = 1 << k / 2;

    printf("n = %u, k = %d,\n r = %d, s = %d\n", n, k, r, s);

    matrix_t matrix, matrix_2;
    matrix_init(&matrix, r, s);
    matrix_init(&matrix_2, r, s);

    matrix_fill_random(&matrix);
    matrix_print(&matrix);

    int j;
    printf("SORT\n");
    for (j = 0; j < matrix.n; j++)
        sort_column(&matrix, j);

    matrix_print(&matrix);

    printf("TRANSPOSE\n");
    for (j = 0; j < matrix.n; j++)
        transpose_column(&matrix, &matrix_2, j);

    matrix_print(&matrix_2);

    matrix_free(&matrix);
    matrix_free(&matrix_2);
    return 0;
}
