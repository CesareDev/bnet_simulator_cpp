#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include <vector>
#include <core/Channel.hpp>
#include <core/Event.hpp>
#include <node/Buoy.hpp>

namespace core
{
    class Simulator
    {
        public:
            void Init();
            void Run();

        private:
            void update();

        private:
            Channel m_Channel {};
            std::vector<node::Buoy> m_Buoys {};
            base::DurationSeconds m_Duration {};
            base::Timepoint m_SimulationTime {};
            EventQueue m_EventQueue {};
    };
}

#endif // !SIMULATOR_HPP
