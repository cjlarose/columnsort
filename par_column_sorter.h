#ifndef _PAR_COLUMN_SORTER_H_
#define _PAR_COLUMN_SORTER_H_

#include "column_sorter.h"
#include "matrix.h"

class ParColumnSorter: public ColumnSorter {
    public:
        ParColumnSorter(unsigned long n, int p);
        void sort();
    private:
        static void worker(Matrix& left, Matrix& right, long start, long end);
        int p;
};

#endif
