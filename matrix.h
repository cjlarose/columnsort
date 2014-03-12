class Matrix {
    public:
        Matrix(long m, long n);
        long& operator() (long i, long j) const;
        long rows() const;
        long columns() const;
    private:
        long* elements;
        long m;
        long n;
        void sort_column(long j);
        void sort_column_shift(long j, long shift);
        void transpose_column(Matrix& dest, long j);
        void reverse_transpose_column(Matrix& dest, long j);
};

std::ostream& operator<<(std::ostream &strm, const Matrix& matrix);
std::istream& operator>>(std::istream &in, const Matrix& matrix);
