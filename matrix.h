class Matrix {
    public:
        Matrix(long m, long n);
        long& operator() (long i, long j) const;
        long rows() const;
        long columns() const;
    private:
        friend std::ostream& operator<<(std::ostream&, const Matrix&);
        long* elements;
        long m;
        long n;
};

std::ostream& operator<<(std::ostream &strm, const Matrix& matrix);
std::istream& operator>>(std::istream &in, const Matrix& matrix);
