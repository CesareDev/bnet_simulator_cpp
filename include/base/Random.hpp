#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <vector>
#include <node/Buoy.hpp>

namespace base
{
    void Seed();
    void Seed(uint64_t seed);
    void Shuffle(std::vector<node::Buoy>& buoys);
    float GetRandomFloat();
    uint64_t GetRandomUint64();
    int32_t GetRandomInt32Range(int32_t min, int32_t max);
}

#endif // !RANDOM_HPP
