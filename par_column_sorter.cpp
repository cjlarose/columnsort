#include <iostream>
#include <thread>
#include <vector>
#include "par_column_sorter.h"
#include "matrix.h"

ParColumnSorter::ParColumnSorter(unsigned long n, int p)
    :ColumnSorter(n), p(p) {
}

/*
 * Worker for a range of columns from start (inclusive) to end (exclusive)
 */
void ParColumnSorter::worker(Matrix& left, Matrix& right, long start, 
    long end) {
    for (long j = start; j < end; ++j)
        left.sort_column(j);
}

/*
 * Performs column sort in parallel by assigning column ranges to threads.
 */
void ParColumnSorter::sort() {
    if (p > s)
        p = s;
    std::vector<std::thread> threads(p);

    int columns_per_thread = s / p;
    long j = 0;
    for (long i = 0; i < p; ++i) {
        int num_cols = columns_per_thread;
        if (i < s % p)
            num_cols++;

        #if DEBUG
        std::cout << "Thread i = " << i << " on cols " << j << " thru "
            << j + num_cols << "\n";
        #endif

        threads[i] = std::thread(&ParColumnSorter::worker, std::ref(left),
            std::ref(right), j, j + num_cols);

        j += num_cols;
    }

    for (auto& t: threads)
        t.join();
}
