#include <cmath>
#include <iostream>
#include "barrier.h"

Barrier::Barrier(int p) {
    arrive = std::vector<int>(p, 0);
    num_stages = (int) ceil(log2((double) p));
    #if DEBUG
    std::cout << "num_stages = " << num_stages << "\n";
    #endif
}

/*
Thread i:
for j = 1 to ceiling(log(P)) {
    <await arrive[i] == 0>
    arrive[i] = j
    lookAt = (i + 2j-1) % p
    <await arrive[lookAt] == j>
    arrive[lookAt] = 0
}
*/
void Barrier::set_arrived(int i) {
    #if DEBUG
    std::cout << "Thread " << i << " has arrived at the barrier\n";
    #endif
}
