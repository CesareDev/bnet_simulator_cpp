#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <cstdint>

#include <core/Event.hpp>

namespace core
{
    class Channel
    {
        public:
            void Init();
            void Update(EventQueue& queue, base::Timepoint simulation_time);

        private:
            bool m_IdealChannel {};
            uint32_t m_BitRate {};
            uint32_t m_SpeedOfLight {};
            float m_CommRangeHighProb {};
            float m_CommRangeMax {};
            float m_DeliveryProbHigh {};
            float m_DeliveryProbLow {};
    };
}

#endif // !CHANNEL_HPP
