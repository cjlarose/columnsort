#include <iostream>
#include <fstream>
#include "columnsort.h"
#include "matrix.h"

/*
 * seq-sort 128 foobar 0 1
 * par-sort 128 4 foobar 0 1
 */
int parse_args(int argc, char **argv, unsigned long *num_items,
    long *num_threads, char **filename, bool *print_time, bool *print_output) {

    if (num_threads == NULL && argc < 5) {
        std::cerr << "Usage: " << argv[0] << " n filename print_time print_output" << std::endl;
        return 0;
    } else if (num_threads != NULL && argc < 6) {
        std::cerr << "Usage: par-sort n num_threads filename print_time print_output" << std::endl;
        return 0;
    }

    // with an unsigned long, we can accept arguments up to 2^31
    unsigned long n = atol(argv[1]);

    if (n <= 0 || !power_of_two(n)) {
        std::cerr << "n must be a power of 2 greater than or equal to 1" << std::endl;
        return 0;
    }

    *num_items = n;

    int i = 2;
    if (num_threads != NULL)
        *num_threads = atol(argv[i++]);

    *filename = argv[i++];
    *print_time = atoi(argv[i++]) == 1;
    *print_output = atoi(argv[i++]) == 1;
    return 1;
}


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
