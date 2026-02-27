#include <base/UUID.hpp>
#include <random>

namespace base
{
    UUID GetRandomUUID()
    {
        static std::random_device dev;
        static std::mt19937 rng(dev());

        std::uniform_int_distribution<int> dist(0, 15);

        const char *v = "0123456789abcdef";

        UUID res;
        res.reserve(32);

        for (uint8_t i {}; i < 32; ++i)
        {
            res.push_back(v[dist(rng)]);
        }

        return res;
    }
}
