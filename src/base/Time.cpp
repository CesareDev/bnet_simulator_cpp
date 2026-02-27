#include <base/Time.hpp>

#include <chrono>

namespace base
{
    Timepoint GetTimepoint()
    {
        return std::chrono::steady_clock::now();
    }
}
