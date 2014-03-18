#ifndef _BARRIER_H_
#define _BARRIER_H_

#include <condition_variable>
#include <mutex>
#include <vector>

class Barrier {
    public:
        Barrier(const Barrier& other) :p(other.p) {}
        Barrier(int p);
        void set_arrived(int i);
        friend std::ostream& operator<<(std::ostream& strm,
            const Barrier& barrier);
    private:
        int p;
        int num_stages;
        std::vector<int> arrive;
        std::vector<std::condition_variable> arrive_cond;
        std::mutex lock;
};

std::ostream& operator<<(std::ostream& strm, const Barrier& barrier);

#endif
