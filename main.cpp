#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <sys/time.h>
#include "seq_column_sorter.h"
#include "par_column_sorter.h"

/*
 * Determines if an integer is a power of two.
 * Classic bithack from http://graphics.stanford.edu/~seander/bithacks.html
 */
int power_of_two(long x) {
    return (x != 0) && ((x & (x - 1)) == 0);
}

/*
 * seq-sort 128 foobar 0 1
 * par-sort 128 4 foobar 0 1
 */
int parse_args(int argc, char **argv, unsigned long *num_items,
    int *num_threads, char **filename, bool *print_time, bool *print_output) {

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

int main(int argc, char* argv[]) {
    unsigned long n;
    bool print_time, print_output;
    char *filename;

    #if SEQUENTIAL

    if (!parse_args(argc, argv, &n, NULL, &filename, &print_time,
        &print_output))
        return 1;
    SeqColumnSorter cs(n);

    #else

    int p;
    if (!parse_args(argc, argv, &n, &p, &filename, &print_time,
        &print_output))
        return 1;
    ParColumnSorter cs(n, p);

    #endif

    std::ifstream input_file;
    input_file.open(filename);
    if (input_file.fail()) {
        std::cerr << "Unable to open file " << filename << std::endl;
        return 1;
    }
    input_file >> cs;
    input_file.close();

    struct timeval start, stop;
    gettimeofday(&start, NULL);
    cs.sort();
    gettimeofday(&stop, NULL);

    if (print_time) {
        double elapsed = (double) (stop.tv_sec - start.tv_sec)
            + (double) (stop.tv_usec - start.tv_usec) / 1000000.0;
        std::cout << std::setprecision(3) << std::fixed << elapsed << "\n";
    }

    if (print_output)
        std::cout << cs;

    return 0;
}
