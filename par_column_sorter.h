#ifndef _PAR_COLUMN_SORTER_H_
#define _PAR_COLUMN_SORTER_H_

#include "column_sorter.h"
#include "matrix.h"
#include "barrier.h"

class ParColumnSorter: public ColumnSorter {
    public:
        ParColumnSorter(unsigned long n, int p);
        void sort();
    private:
        static void worker(int id, Barrier& barrier, Matrix& left,
            Matrix& right, long start, long end);
        const int p;
        Barrier barrier;
};

#endif
