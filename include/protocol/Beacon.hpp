#ifndef BEACON_HPP
#define BEACON_HPP

#include <base/Types.hpp>

#include <vector>

namespace protocol
{
    struct BeaconBuoyRepresentation
    {
        base::UUID buoyId {};
        float battery {};
        base::Position position {};
    };

    struct Beacon
    {
        base::UUID senderId {};
        bool mobile {};
        base::Position position {};
        float battery {};
        std::vector<BeaconBuoyRepresentation> neighbors {};
        base::Timestamp timestamp {};
    };
}

#endif // !BEACON_HPP
