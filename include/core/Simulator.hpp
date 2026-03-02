#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include <string>

#include <core/Channel.hpp>
#include <core/Event.hpp>
#include <node/BuoyArray.hpp>

namespace core
{
    class Simulator
    {
        public:
            void Init(const std::string& config_path);
            void Run();

        private:
            void update();

        private:
            Channel m_Channel {};
            node::BuoyArray m_Buoys {};
            base::DurationSeconds m_Duration {};
            float m_MobilePercentage {};
            base::Timepoint m_SimulationTime {};
            EventQueue m_EventQueue {};
    };
}

#endif // !SIMULATOR_HPP
