#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include <core/Channel.hpp>
#include <core/Event.hpp>
#include <node/BuoyArray.hpp>

namespace core
{
    class Simulator
    {
        public:
            void Init();
            void Run();

        private:
            void update();
            void handleEvent(const Event& event);

        private:
            Channel m_Channel {};
            node::BuoyArray m_Buoys {};
            float m_Duration {};
            float m_MobilePercentage {};
            float m_SimulationTime {};
            EventQueue m_EventQueue {};
    };
}

#endif // !SIMULATOR_HPP
