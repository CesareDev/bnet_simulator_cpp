#include <base/Time.hpp>

#include <chrono>

namespace base
{
    Timestamp GetTimestamp()
    {
        auto now = std::chrono::steady_clock::now().time_since_epoch();
        return std::chrono::duration_cast<std::chrono::nanoseconds>(now).count();
    }
}
