#include <stdio.h>
#include <stdlib.h>

// Classic bithack from http://graphics.stanford.edu/~seander/bithacks.html
int power_of_two(int x) {
    return (x != 0) && ((x & (x - 1)) == 0);
}

// Returns k such that x = 2^k
int log_base_2(unsigned int x) {
    if (x == 0)
        return 0;

    int i = 0;
    for (; ; i++, x >>= 1)
        if (x & 1)
            break;
    return i;
}

int parse_args(int argc, char **argv, unsigned int *dest) {

    if (argc < 2) {
        fprintf(stderr, "Usage: seq-sum n\n");
        return 0;
    }

    // with an unsigned int, we can accept arguments up to 2^31
    unsigned int n = atol(argv[1]);

    if (n <= 0 || !power_of_two(n)) {
        fprintf(stderr, "n must be a power of 2 greater than 0\n");
        return 0;
    }

    *dest = n;
    return 1;
}


int main(int argc, char **argv) {
    unsigned int n;
    int k, success;
    success = parse_args(argc, argv, &n);
    if (!success)
        return 1;

    k = log_base_2(n);

    printf("n = %u, k = %d\n", n, k);
    return 0;
}
