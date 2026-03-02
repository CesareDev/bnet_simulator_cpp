#ifndef BEACON_HPP
#define BEACON_HPP

#include <base/Types.hpp>
#include <base/Vector.hpp>

#include <vector>

namespace protocol
{
    struct BeaconBuoyRepresentation
    {
        base::UUID buoyId {};
        base::Timepoint timestamp {};
        base::Vector position {};
    };

    struct Beacon
    {
        base::UUID senderId {};
        base::Timepoint timestamp {};
        base::Vector position {};
        bool mobile {};
        float battery {};
        std::vector<BeaconBuoyRepresentation> neighbors {};

        uint64_t size_in_bytes();
        uint64_t size_in_bits();
    };
}

#endif // !BEACON_HPP
