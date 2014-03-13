#include <iostream>
#include "par_column_sorter.h"
#include "matrix.h"

ParColumnSorter::ParColumnSorter(long r, long s, int p)
    :ColumnSorter(r, s), p(p) {
    if (p > s)
        p = s;
}

void ParColumnSorter::sort() {
}
