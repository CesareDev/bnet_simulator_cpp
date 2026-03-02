#include <base/UUID.hpp>
#include <random>

static thread_local std::mt19937_64 engine(std::random_device{}());

namespace base
{
    UUID GetRandomUUID()
    {
        static thread_local std::uniform_int_distribution<uint64_t> dist(0, UINT64_MAX);
        return dist(engine);
    }
}
