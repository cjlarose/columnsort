#include "par_column_sorter.h"
#include "matrix.h"

ParColumnSorter::ParColumnSorter(long r, long s, int p)
    :ColumnSorter(r, s), p(p) {
}

void ParColumnSorter::sort() {
}
