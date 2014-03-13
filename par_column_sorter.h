#ifndef _PAR_COLUMN_SORTER_H_
#define _PAR_COLUMN_SORTER_H_

#include "column_sorter.h"

class ParColumnSorter: public ColumnSorter {
    public:
        ParColumnSorter(long r, long s);
        void sort();
};

#endif
