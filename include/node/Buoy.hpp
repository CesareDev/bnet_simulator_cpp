#ifndef BUOY_HPP
#define BUOY_HPP

#include <base/Vector.hpp>
#include <protocol/Scheduler.hpp>
#include <core/Event.hpp>

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
            void HandleEvent(const core::Event& event, core::EventQueue& queue, float simulation_time);

        private:
            void handleSchedulerCheck(const core::Event& event, float simulation_time);
            void handleChannelSense(const core::Event& event, float simulation_time);
            void handleDifsCompletion(const core::Event& event, float simulation_time);
            void handleBackoffCompletion(const core::Event& event, float simulation_time);
            void handleTransmissionStart(const core::Event& event, float simulation_time);
            void handleReception(const core::Event& event, float simulation_time);
            void handleNeighborCleanup(const core::Event& event, float simulation_time);
            void handlBuoyMovement(const core::Event& event, float simulation_time);

        private:
            uint64_t m_Id {};
            base::Vector m_Position {};
            base::Vector m_Velocity {};
            BuoyState m_State {};
            node::NeighborsMap m_Neighbors {};
            protocol::Scheduler m_Scheduler {};
            float m_Battery {};
            bool m_IsMobile {};

            float m_Difstime {};
            float m_SlotTime {};
            uint32_t m_ContentionWindow {};

            float m_NeighborTimeout {};
            float m_WorldWidth {};
            float m_WorldHeight {};
            float m_SpeedOfLight {};
            float m_CommRangeMax {};

            float m_BackoffTime {};
            float m_BackoffRemaining {};
            float m_NextTryTime {};
            bool m_WantToSend {};
            float m_SchedulerDecisionTime {};
    };
}

#endif // !BUOY_HPP
