#ifndef EVENT_HPP
#define EVENT_HPP

#include <queue>
#include <base/Types.hpp>

namespace core
{
    enum class EventType
    {
        SCHEDULER_CHECK, // Buoy
        CHANNEL_SENSE, // Buoy
        DIFS_COMPLETION, // Buoy
        BACKOFF_COMPLETION, // Buoy
        TRANSMISSION_START, // Buoy
        TRANSMISSION_END, // Buoy
        RECEPTION, // Buoy
        NEIGHBOR_CLEANUP, // Buoy
        CHANNEL_UPDATE, // Channel
        BUOY_MOVEMENT, // Simulator
        BUOY_ARRAY_UPDATE, // Simulator
    };

    enum class EventTargetType
    {
        BUOY,
        CHANNEL,
        SIMULATOR,
    };

    struct Event
    {
        base::Timepoint Timepoint {};
        base::UUID TargetUUID {};
        EventType Type {};
        EventTargetType TargetType {};
    };

    struct EventPriority
    {
        bool operator()(const Event& l, const Event& r) const
        { 
            return l.Timepoint > r.Timepoint;
        }
    };

    using EventQueue = std::priority_queue<core::Event, std::vector<Event>, EventPriority>;
}

#endif // !EVENT_HPP
