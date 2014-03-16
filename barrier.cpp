#include <cmath>
#include <iostream>
#include <mutex>
#include "barrier.h"

Barrier::Barrier(int p)
    :p(p) {
    arrive = std::vector<int>(p, -1);
    num_stages = (int) ceil(log2((double) p));
    #if DEBUG
    std::cout << "num_stages = " << num_stages << "\n";
    #endif
}

std::ostream& operator<<(std::ostream& strm, const Barrier& barrier) {
    strm << "arrive: ";
    for (int i: barrier.arrive)
        strm << i << " ";
    strm << "\n";
    return strm;
}


/*
Thread i:
for j = 1 to ceiling(log(P)) {
    <await arrive[i] == 0>
    arrive[i] = j
    lookAt = (i + 2^(j-1)) % p
    <await arrive[lookAt] == j>
    arrive[lookAt] = 0
}
*/
void Barrier::set_arrived(int i) {
    for (int j = 0; j < num_stages; ++j) {
        while (arrive[i] != -1);
        arrive[i] = j;
        int look_at = (i + (1 << j)) % p;
        while (arrive[look_at] != j);
        arrive[look_at] = -1;
    }
}
