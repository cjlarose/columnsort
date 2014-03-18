#include <cmath>
#include <iostream>
#include "barrier.h"

Barrier::Barrier(int p)
    :p(p) {
    arrive = std::vector<int>(p, -1);
    num_stages = (int) ceil(log2((double) p));
    #if DEBUG
    std::cout << "num_stages = " << num_stages << "\n";
    #endif
    arrive_cond = std::vector<std::condition_variable>(p);
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
        std::unique_lock<std::mutex> l(lock);
        arrive_cond[i].wait(l, [&, this]{return arrive[i] == -1; });
        arrive[i] = j;
        l.unlock();


        int look_at = (i + (1 << j)) % p;
        std::unique_lock<std::mutex> l2(lock);
        arrive_cond[look_at].wait(l2, [&, this]{return arrive[look_at] == j; });
        arrive[look_at] = -1;
        l2.unlock();


        arrive_cond[i].notify_all();
        arrive_cond[look_at].notify_all();
    }
}
