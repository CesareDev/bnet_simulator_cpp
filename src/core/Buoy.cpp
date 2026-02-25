#include "base/UUID.hpp"
#include <buoy/Buoy.hpp>

namespace buoy
{
    Buoy::Buoy(core::Channel& channel, base::Vector position, base::Vector velocity, bool is_mobile) :
        m_Channel(&channel),
        m_Id(base::GetUUID()),
        m_Position(position),
        m_Velocity(velocity),
        m_State(BuoyState::SLEEPING),
        m_Battery(100.f),
        m_IsMobile(is_mobile)
    {}
}
