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

/*
 * Sets r and s to the dimensions of a matrix for sorting n integers satisfying
 * the following constraints: r % s == 0, r >= 2(s-1)^2, and r - s is minimal.
 */
ColumnSorter::ColumnSorter(unsigned long n) {
    int k = log_base_2(n);
    r = 1 << (k / 2 + k % 2);
    s = 1 << k / 2;
    for (; r < 2 * (s-1) * (s-1); r <<= 1, s >>= 1);

    std::cout << "n = " << n << ", r = " << r << ", s = " << s << std::endl;

    left = new Matrix(r, s);
    right = new Matrix(r, s);
}

std::ostream& operator<<(std::ostream& strm, const ColumnSorter& cs) {
    return strm << *cs.left;
}

std::istream& operator>>(std::istream& strm, const ColumnSorter& cs) {
    return strm >> *cs.left;
}
