#ifndef NEIGHBOR_HPP
#define NEIGHBOR_HPP

#include <unordered_map>
#include <cstdint>

#include <base/Vector.hpp>

namespace node
{
    struct Neighbor
    {
        float timestamp {};
        base::Vector position {};
    };

    using NeighborsMap = std::unordered_map<uint64_t, node::Neighbor>;
}

#endif // !NEIGHBOR_HPP
