class Matrix {
    public:
        Matrix(long m, long n);
        long& operator() (long i, long j);
        long rows() const;
        long columns() const;
    private:
        long* elements;
        long m;
        long n;
};

std::ostream& operator<<(std::ostream &strm, const Matrix& matrix);
