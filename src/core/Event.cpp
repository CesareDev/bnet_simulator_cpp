#include <core/Event.hpp>

namespace core
{
    Event::Event(base::Timestamp timestamp, EventType type) :
        m_Timestamp(timestamp), m_Type(type)
    {}
}
