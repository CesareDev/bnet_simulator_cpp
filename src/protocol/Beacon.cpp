#include <protocol/Beacon.hpp>

namespace protocol
{
    uint64_t Beacon::size_in_bytes()
    {
        return 37 + 28 * neighbors.size();
    }

    uint64_t Beacon::size_in_bits()
    {
        return size_in_bytes() * 8;
    }
}
