#include <iostream>
#include <cassert>
#include <cstdlib>

/*
 * Determines if an integer is a power of two.
 * Classic bithack from http://graphics.stanford.edu/~seander/bithacks.html
 */
int power_of_two(long x) {
    return (x != 0) && ((x & (x - 1)) == 0);
}

/*
 * Returns k such that x = 2^k
 */
int log_base_2(unsigned long x) {
    assert(x != 0);

    int i = 0;
    for (; ; i++, x >>= 1)
        if (x & 1)
            break;
    return i;
}

/*
 * seq-sort 128 foobar 0 1
 * par-sort 128 4 foobar 0 1
 */
int parse_args(int argc, char **argv, unsigned long *num_items,
    long *num_threads, char **filename, bool *print_time, bool *print_output) {

    if (num_threads == NULL && argc < 5) {
        std::cerr << "Usage: seq-sort n filename print_time print_output" << std::endl;
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

/*
 * Sets r and s to the dimensions of a matrix for sorting n integers satisfying
 * the following constraints: r % s == 0, r >= 2(s-1)^2, and r - s is minimal.
 */
void get_matrix_size(unsigned long n, long *r, long *s) {
    int k = log_base_2(n);
    *r = 1 << (k / 2 + k % 2);
    *s = 1 << k / 2;
    for (; *r < 2 * (*s-1) * (*s-1); *r <<= 1, *s >>= 1);
}
