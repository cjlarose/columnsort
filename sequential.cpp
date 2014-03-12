#include <iostream>
#include "columnsort.h"

int main(int argc, char * argv[]) {
    unsigned long n;
    long r, s;
    if (!parse_args(argc, argv, &n, NULL))
        return 1;

    get_matrix_size(n, &r, &s);

    std::cout << "n = " << n << ", r = " << r << ", s = " << s << std::endl;
    return 0;
}
