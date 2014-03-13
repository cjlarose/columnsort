#include <iostream>
#include <thread>
#include "par_column_sorter.h"
#include "matrix.h"

ParColumnSorter::ParColumnSorter(long r, long s, int p)
    :ColumnSorter(r, s), p(p) {
    if (p > s)
        p = s;
}

/*
void ParColumnSorter::worker(worker_message_t* message) {
    for (long j = message->start; j < message->end; ++j)
        message->left.sort_column(j);
}
*/
void ParColumnSorter::worker(Matrix& left, Matrix& right, long start, 
    long end) {
    for (long j = start; j < end; ++j)
        left.sort_column(j);
}

void ParColumnSorter::sort() {
    /*
    worker_message_t message = {left, right, 0, s};
    std::thread sorter(worker, &message);
    */
    std::thread sorter(&ParColumnSorter::worker, std::ref(left), std::ref(right), 0, s);

    sorter.join();
}
