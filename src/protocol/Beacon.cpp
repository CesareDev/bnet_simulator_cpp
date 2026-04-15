#include <protocol/Beacon.hpp>

namespace protocol
{
    uint64_t Beacon::size_in_bytes() const
    {
        return 37 + 28 * neighbors.size();
    }

    uint64_t Beacon::size_in_bits() const
    {
        return size_in_bytes() * 8;
    }
}
