#include <iostream>
#include <cassert>
#include "column_sorter.h"
#include "matrix.h"

/*
 * Returns k such that x = 2^k
 */
int log_base_2(unsigned long x) {
    assert(x != 0);

    int i = 0;
    for (; ; i++, x >>= 1)
        if (x & 1)
            break;
    return i;
}


ColumnSorter::ColumnSorter(long n)
    :left(Matrix()), right(Matrix()) {
    int k = log_base_2(n);
    r = 1 << (k / 2 + k % 2);
    s = 1 << k / 2;
    for (; r < 2 * (s-1) * (s-1); r <<= 1, s >>= 1);
    left.init(r, s);
    right.init(r, s);
}

std::ostream& operator<<(std::ostream& strm, const ColumnSorter& cs) {
    return strm << cs.left;
}

std::istream& operator>>(std::istream& strm, const ColumnSorter& cs) {
    return strm >> cs.left;
}
