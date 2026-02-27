#ifndef BUOY_HPP
#define BUOY_HPP

#include <base/Types.hpp>
#include <base/Vector.hpp>
#include <core/Channel.hpp>
#include <protocol/Scheduler.hpp>

namespace node
{
    enum class BuoyState
    {
        SLEEPING,
        RECEIVING,
        WAITING_DIFS,
        BACKOFF
    };

    class Buoy
    {
        public:
            Buoy(core::Channel& channel, base::Vector position, base::Vector velocity, bool is_mobile);

        private:
            core::Channel* m_Channel {};
            base::UUID m_Id {};
            base::Vector m_Position {};
            base::Vector m_Velocity {};
            protocol::Scheduler m_Scheduler {};
            BuoyState m_State {};
            float m_Battery {};
            bool m_IsMobile {};
    };
}

#endif // !BUOY_HPP
