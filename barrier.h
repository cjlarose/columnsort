#ifndef _BARRIER_H_
#define _BARRIER_H_

#include <vector>

class Barrier {
    public:
        Barrier(int p);
        void set_arrived(int i);
    private:
        int num_stages;
        std::vector<int> arrive;
};

#endif
