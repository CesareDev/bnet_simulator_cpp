#ifndef TYPES_HPP
#define TYPES_HPP

#include <chrono>

namespace base
{
    using UUID = uint64_t;
    using Timepoint = std::chrono::steady_clock::time_point;
    using DurationSeconds = std::chrono::seconds;
    using DurationMinutes = std::chrono::minutes;
    using DurationHours = std::chrono::hours;
}

#endif // !TYPES_HPP
