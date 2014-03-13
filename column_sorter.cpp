#include <iostream>
#include "column_sorter.h"
#include "matrix.h"

ColumnSorter::ColumnSorter(long r, long s)
    :left(Matrix(r, s)), right(Matrix(r, s)), r(r), s(s) {
}

std::ostream& operator<<(std::ostream& strm, const ColumnSorter& cs) {
    return strm << cs.left;
}

std::istream& operator>>(std::istream& strm, const ColumnSorter& cs) {
    return strm >> cs.left;
}
