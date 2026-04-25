#ifndef BEACON_HPP
#define BEACON_HPP

#include <cstdint>

#include <base/Vector.hpp>
#include <node/Neighbor.hpp>

namespace protocol
{
    struct Beacon
    {
        uint64_t senderId {};
        float timestamp {};
        base::Vector position {};
        bool mobile {};
        float battery {};
        node::NeighborsMap neighbors {};

        uint64_t size_in_bytes() const;
        uint64_t size_in_bits() const;
    };
}

#endif // !BEACON_HPP
