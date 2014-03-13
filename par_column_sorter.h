#ifndef _PAR_COLUMN_SORTER_H_
#define _PAR_COLUMN_SORTER_H_

#include "column_sorter.h"
#include "matrix.h"

/*
typedef struct {
    Matrix& left;
    Matrix& right;
    long start;
    long end;
} worker_message_t;
*/

class ParColumnSorter: public ColumnSorter {
    public:
        ParColumnSorter(long r, long s, int p);
        void sort();
    private:
        //static void worker(worker_message_t* msg);
        static void worker(Matrix& left, Matrix& right, long start, long end);
        int p;
};

#endif
