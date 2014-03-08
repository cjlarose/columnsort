#ifndef _COLUMNSORT_H_
#define _COLUMNSORT_H_

#include "quicksort.h"

void sort_row(matrix_t *matrix, int i) {
    quicksort(matrix->entries[i], 0, matrix->n - 1);
}

#endif
