#include <iostream>
#include <iomanip>
#include <cassert>
#include "quicksort.h"
#include "matrix.h"

Matrix::Matrix(long m, long n)
    :elements(new long[m * n]), m(m), n(n)
{
}

long& Matrix::operator()(long i, long j) const {
    return at(i, j);
}

long& Matrix::at(long i, long j) const {
    assert(i < m);
    assert(j < n);
    return elements[m*j + i];
}

long Matrix::rows() const {
    return m;
}

long Matrix::columns() const {
    return n;
}

std::ostream& operator<<(std::ostream &strm, const Matrix& matrix) {
    for (int i = 0; i < matrix.rows(); ++i) {
        for (int j = 0; j < matrix.columns(); ++j)
            strm << std::setw(11) << matrix(i, j);
        strm << "\n";
    }

    return strm;
}

std::istream& operator>>(std::istream &in, const Matrix& matrix) {
    for (int j = 0; j < matrix.columns(); ++j)
        for (int i = 0; i < matrix.rows(); ++i)
            in >> matrix(i, j);
    return in;
}

/*
 * Sorting a column j in our column-order matrix is actually just
 * sorting the ith row.
 */
void Matrix::sort_column(long j) {
    quicksort(&elements[j*m], 0, m - 1);
}

void Matrix::transpose_column(Matrix& dest, long j) {
    long start_row = j * (m / n);
    for (long i = 0; i < m; ++i)
        dest(start_row + i / n, i % n) = at(i, j);
}

void Matrix::reverse_transpose_column(Matrix& dest, long j) {
    for (long i = 0; i < m; i++)
        dest( ((n * i) + j) % m, i / (m/n) ) = at(i, j);
}

/*
 * Instead of actually moving elements around and then sorting by column,
 * We can just sort with an offset, which is facilitated by the fact that
 * our matrix is stored in column-order form. Sorting the 0th column here
 * actually means to sort the first m - (n / 2) elements, then sorting the
 * last n / 2 elements.
 */
void Matrix::sort_column_shift(long j, long shift) {
    if (j == 0) {
        quicksort(&elements[0], 0, m - shift - 1);
        quicksort(&elements[n*m - 1], m - shift, m - 1);
    } else
        quicksort(&elements[j*m] - shift, 0, m - 1);
}
