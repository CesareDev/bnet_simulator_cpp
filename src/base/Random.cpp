#include <random>
#include <algorithm>

#include <base/Random.hpp>

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

    float GetRandomFloat()
    {
        static thread_local std::uniform_real_distribution<double> dist(0.0, 1.0);
        return dist(engine);
    }

    uint64_t GetRandomUint64()
    {
        static thread_local std::uniform_int_distribution<uint64_t> dist(0, UINT64_MAX);
        return dist(engine);
    }

    int32_t GetRandomInt32Range(int32_t min, int32_t max)
    {
        static thread_local std::uniform_int_distribution<int32_t> dist(min, max);
        return dist(engine);
    }
}
