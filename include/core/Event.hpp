#ifndef EVENT_HPP
#define EVENT_HPP

#include <base/Types.hpp>

namespace core
{
    enum class EventType
    {
        SCHEDULER_CHECK,
        CHANNEL_SENSE,
        DIFS_COMPLETION,
        BACKOFF_COMPLETION,
        TRANSMISSION_START,
        TRANSMISSION_END,
        RECEPTION,
        NEIGHBOR_CLEANUP,
        BUOY_MOVEMENT,
        CHANNEL_UPDATE,
        BUOY_ARRAY_UPDATE,
        AVG_NEIGHBORS_CALCULATION
    };

    class Event
    {
        public:
            Event(base::Timestamp timestamp, EventType type);

        private:
            base::Timestamp m_Timestamp;
            EventType m_Type;
    };
}

#endif // !EVENT_HPP
