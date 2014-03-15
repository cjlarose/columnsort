#ifndef _SEQ_COLUMN_SORTER_H_
#define _SEQ_COLUMN_SORTER_H_

#include "column_sorter.h"

class SeqColumnSorter: public ColumnSorter {
    public:
        SeqColumnSorter(unsigned long n);
        void sort();
};

#endif
