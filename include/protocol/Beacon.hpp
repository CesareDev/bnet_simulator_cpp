#ifndef BEACON_HPP
#define BEACON_HPP

#include <base/Vector.hpp>

#include <cstdint>
#include <vector>

namespace protocol
{
    struct BeaconBuoyRepresentation
    {
        uint64_t buoyId {};
        float timestamp {};
        base::Vector position {};
    };

    struct Beacon
    {
        uint64_t senderId {};
        float timestamp {};
        base::Vector position {};
        bool mobile {};
        float battery {};
        std::vector<BeaconBuoyRepresentation> neighbors {};

        uint64_t size_in_bytes() const;
        uint64_t size_in_bits() const;
    };
}

#endif // !BEACON_HPP
