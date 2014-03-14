#include <iostream>
#include <thread>
#include "par_column_sorter.h"
#include "matrix.h"

ParColumnSorter::ParColumnSorter(long n, int p)
    :ColumnSorter(n), p(p) {
    if (p > s)
        p = s;
}

void ParColumnSorter::worker(Matrix& left, Matrix& right, long start, 
    long end) {
    for (long j = start; j < end; ++j)
        left.sort_column(j);
}

void ParColumnSorter::sort() {
    std::thread sorter(&ParColumnSorter::worker, std::ref(left), std::ref(right), 0, s);

    sorter.join();
}
