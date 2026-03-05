#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <cstdint>
#include <unordered_map>

#include <core/Event.hpp>
#include <protocol/Beacon.hpp>

namespace core
{
    struct Trasmission
    {
        protocol::Beacon beacon {};
        float simulation_time {};
        float end_time {};
        uint32_t receivers_count {};
        uint32_t successful_receivers {};
    };

    class Channel
    {
        public:
            void Init();
            void HandleEvent(const core::Event& event, EventQueue& queue, float simulation_time);
            bool Broadcast(const protocol::Beacon& beacon, float simulation_time);
            bool IsBusy(base::Vector position, float simulation_time);

        private:
            void update(float simulation_time);

        private:
            bool m_IdealChannel {};
            uint32_t m_BitRate {};
            uint32_t m_SpeedOfLight {};
            float m_CommRangeHighProb {};
            float m_CommRangeMax {};
            float m_DeliveryProbHigh {};
            float m_DeliveryProbLow {};

            std::unordered_map<base::UUID, Trasmission> m_ActiveTransmission {};
            std::unordered_map<base::UUID, Trasmission> m_CollidedBeacon {};
    };
}

#endif // !CHANNEL_HPP
