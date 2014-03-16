#ifndef _BARRIER_H_
#define _BARRIER_H_

#include <vector>

class Barrier {
    public:
        Barrier(int p);
        void set_arrived(int i);
        friend std::ostream& operator<<(std::ostream& strm,
            const Barrier& barrier);
    private:
        int p;
        int num_stages;
        std::vector<int> arrive;
};

std::ostream& operator<<(std::ostream& strm, const Barrier& barrier);

#endif
