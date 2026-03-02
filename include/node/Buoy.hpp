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
            void Init();
            void Setup(base::Vector position, base::Vector velocity, bool is_mobile);

        private:
            base::UUID m_Id {};
            base::Vector m_Position {};
            base::Vector m_Velocity {};
            BuoyState m_State {};
            protocol::Scheduler m_Scheduler {};
            float m_Battery {};
            bool m_IsMobile {};
    };
}

#endif // !BUOY_HPP
