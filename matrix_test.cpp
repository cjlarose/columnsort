#include <iostream>
#include "Matrix.h"

int main() {
    Matrix m(2, 2);
    m(0, 0) = 1;
    m(0, 1) = 2;
    m(1, 0) = 3;
    m(1, 1) = 3;
    std::cout << m << std::endl;
    return 0;
}
