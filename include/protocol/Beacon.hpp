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
        base::Timestamp timestamp {};
        base::Vector position {};
    };

    struct Beacon
    {
        base::UUID senderId {};
        base::Timestamp timestamp {};
        base::Vector position {};
        bool mobile {};
        float battery {};
        std::vector<BeaconBuoyRepresentation> neighbors {};
    };
}

#endif // !BEACON_HPP
