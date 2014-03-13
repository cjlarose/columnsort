#include <iostream>
#include "column_sorter.h"
#include "matrix.h"

/*
 * Sets r and s to the dimensions of a matrix for sorting n integers satisfying
 * the following constraints: r % s == 0, r >= 2(s-1)^2, and r - s is minimal.
 */
ColumnSorter::ColumnSorter(long r, long s)
    :left(Matrix(r, s)), right(Matrix(r, s)), r{r}, s{s} {
}

std::ostream& operator<<(std::ostream& strm, const ColumnSorter& cs) {
    return strm << cs.left;
}

std::istream& operator>>(std::istream& strm, const ColumnSorter& cs) {
    return strm >> cs.left;
}

void ColumnSorter::sort() {
    std::cout << "r = " << r << ", s = " << s << std::endl;
    std::cout << "SORT\n";
    long j;
    for (j = 0; j < s; j++)
        left.sort_column(j);

    std::cout << left;

    std::cout << "TRANSPOSE\n";
    for (j = 0; j < s; j++)
        left.transpose_column(right, j);

    std::cout << right;

    std::cout << "SORT\n";
    for (j = 0; j < s; j++)
        right.sort_column(j);

    std::cout << right;

    std::cout << "REVERSE TRANSPOSE\n";
    for (j = 0; j < s; j++)
        right.reverse_transpose_column(left, j);

    std::cout << left;

    std::cout << "SORT\n";
    for (j = 0; j < s; j++)
        left.sort_column(j);

    std::cout << left;

    std::cout << "SHIFT SORT\n";
    for (j = 0; j < s; j++)
        left.sort_column_shift(j, r / 2);
}
