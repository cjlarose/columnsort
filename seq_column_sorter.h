#ifndef _SEQ_COLUMN_SORTER_H_
#define _SEQ_COLUMN_SORTER_H_

#include "column_sorter.h"

class SeqColumnSorter: public ColumnSorter {
    public:
        SeqColumnSorter(long r, long s);
        void sort();
};

#endif
