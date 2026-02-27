#include <base/Random.hpp>

#include <random>
#include <algorithm>

static thread_local std::mt19937_64 engine(std::random_device{}());

namespace base
{
    void Seed()
    {
        std::random_device rd;
        std::seed_seq seq
        {
            rd(), rd(), rd(), rd(),
            rd(), rd(), rd(), rd(),
        };
        engine.seed(seq);
    }

    void Seed(uint64_t seed)
    {
        engine.seed(seed);
    }

    void Shuffle(std::vector<node::Buoy>& buoys)
    {
        std::shuffle(buoys.begin(), buoys.end(), engine);
    }

    float RandomValue()
    {
        static thread_local std::uniform_real_distribution<double> dist(0.0, 1.0);
        return dist(engine);
    }
}
