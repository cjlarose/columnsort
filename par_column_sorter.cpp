#include <iostream>
#include <thread>
#include <vector>
#include "par_column_sorter.h"
#include "matrix.h"
#include "barrier.h"

ParColumnSorter::ParColumnSorter(unsigned long n, int num_threads)
    :ColumnSorter(n), p((num_threads > s) ? s : num_threads), barrier(Barrier(p)) {
}

/*
 * Worker for a range of columns from start (inclusive) to end (exclusive)
 */
void ParColumnSorter::worker(int id, Barrier& barrier, Matrix& left,
    Matrix& right, long start, long end) {

    long j;
    for (j = start; j < end; ++j)
        left.sort_column(j);

    barrier.set_arrived(id);

    for (j = start; j < end; ++j)
        left.transpose_column(right, j);

    barrier.set_arrived(id);

    for (j = start; j < end; ++j)
        right.sort_column(j);

    barrier.set_arrived(id);

    for (j = start; j < end; ++j)
        right.reverse_transpose_column(left, j);

    barrier.set_arrived(id);

    for (j = start; j < end; ++j)
        left.sort_column(j);

    barrier.set_arrived(id);

    for (j = start; j < end; ++j)
        left.sort_column_shift(j);
}

/*
 * Performs column sort in parallel by assigning column ranges to threads.
 */
void ParColumnSorter::sort() {
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

        threads[i] = std::thread(&ParColumnSorter::worker, i, std::ref(barrier),
            std::ref(left), std::ref(right), j, j + num_cols);

        j += num_cols;
    }

    for (auto& t: threads)
        t.join();
}
