#include <iostream>
#include <iomanip>
#include "matrix.h"

Matrix::Matrix(long m, long n)
    :elements{new long[m * n]}, m{m}, n{n}
{
}

long& Matrix::operator()(long i, long j) const
{
    return elements[n*j + i];
}

long Matrix::rows() const
{
    return m;
}

long Matrix::columns() const
{
    return n;
}

std::ostream& operator<<(std::ostream &strm, const Matrix& matrix)
{
    for (int i = 0; i < matrix.rows(); ++i) {
        for (int j = 0; j < matrix.columns(); ++j)
            strm << std::setw(11) << matrix(i, j);
        strm << "\n";
    }

    return strm;
}

std::istream& operator>>(std::istream &in, const Matrix& matrix)
{
    for (int i = 0; i < matrix.rows(); ++i)
        for (int j = 0; j < matrix.columns(); ++j)
            in >> matrix(i, j);
    return in;
}
