#ifndef _COLUMN_SORTER_H_
#define _COLUMN_SORTER_H_

#include "matrix.h"

class ColumnSorter {
    public:
        ColumnSorter(long m, long n);
        void sort();
        friend std::ostream& operator<<(std::ostream& strm, const ColumnSorter& cs);
        friend std::istream& operator>>(std::istream& strm, const ColumnSorter& cs);
    private:
        const long r, s;
        Matrix left;
        Matrix right;
};

std::ostream& operator<<(std::ostream& strm, const ColumnSorter& cs);
std::istream& operator>>(std::istream& strm, const ColumnSorter& cs);

#endif
