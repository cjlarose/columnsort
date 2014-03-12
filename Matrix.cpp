#include <iostream>
#include "Matrix.h"

Matrix::Matrix(long m, long n)
    :elements{new long[m * n]}, m{m}, n{n}
{
}

long& Matrix::operator()(long i, long j)
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
    return strm << "Matrix(" << matrix.rows() << " x " << matrix.columns() << ")";
}
