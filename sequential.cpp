#include <iostream>
#include <fstream>
#include "columnsort.h"
#include "matrix.h"

int main(int argc, char * argv[]) {
    unsigned long n;
    long r, s;
    bool print_time, print_output;
    char *filename;
    if (!parse_args(argc, argv, &n, NULL, &filename, &print_time,
        &print_output))
        return 1;

    get_matrix_size(n, &r, &s);

    std::cout << "n = " << n << ", r = " << r << ", s = " << s << std::endl;

    Matrix m(r, s);

    std::ifstream input_file;
    input_file.open(filename);
    input_file >> m;
    input_file.close();

    std::cout << m;

    return 0;
}
