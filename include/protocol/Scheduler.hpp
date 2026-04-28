#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

#include <cstdint>

#include <base/Vector.hpp>
#include <node/Neighbor.hpp>

namespace protocol
{
    enum class SchedulerMode
    {
        Static,
        ADAB,
        ACAB,
    };

    class Scheduler
    {
        public:
            void Init();
            bool ShouldSend(float battery, base::Vector velocity, const node::NeighborsMap& neighbors, float sim_time);
            float GetNextCheckInterval();

        private:
            bool shouldSendStatic(float sim_time);
            bool shouldSendADAB(const node::NeighborsMap& neighbors, float sim_time);
            bool shouldSendACAB(float battery, base::Vector velocity, const node::NeighborsMap& neighbors, float sim_time);

        private:
            float m_MinInterval {};
            float m_MaxInterval {};
            float m_StaticInterval {};
            uint8_t m_NeighborThreshold {};
            float m_ContactThreshold {};
            float m_DefaultVelocty {};
            SchedulerMode m_Mode {};

            float m_LastSendTime {};
            float m_NextSendTime {};

    };
}

#endif // !SCHEDULER_HPP
