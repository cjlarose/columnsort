#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <iostream>

class Matrix {
    public:
        void init(long m, long n);
        ~Matrix();
        long& operator() (long i, long j) const;
        long rows() const;
        long columns() const;
        void sort_column(long j);
        void sort_column_shift(long j);
        void transpose_column(Matrix& dest, long j);
        void reverse_transpose_column(Matrix& dest, long j);
    private:
        void sort_column_shift(long j, long shift);
        long& at(long i, long j) const;
        long** cols;
        long* elements;
        long m;
        long n;
};

std::ostream& operator<<(std::ostream &strm, const Matrix& matrix);
std::istream& operator>>(std::istream &in, const Matrix& matrix);

#endif
