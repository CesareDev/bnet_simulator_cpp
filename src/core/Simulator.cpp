#include <core/Simulator.hpp>
#include <base/Time.hpp>
#include <base/ConfigLoader.hpp>
#include <logging/Logger.hpp>

#include <iostream>

namespace core
{
    void Simulator::Init(const std::string& config_path)
    {
        static std::string method_name = "Simulator::Init";

        base::ConfigLoader& config_loader = base::ConfigLoader::Instance();
        config_loader.Load(config_path);

        m_Channel.Init(config_path);
        m_Buoys.resize(size_t(std::stoull(config_loader.Get("BUOYS_COUNT"))));
        m_Duration = base::DurationSeconds(std::stoi(config_loader.Get("SIM_DURATION")));
        m_MobilePercentage = float(std::stof(config_loader.Get("MOBILE_BUOY_PERC")));
    }

    void Simulator::Run()
    {
        base::Timepoint start_simulation = base::GetTimepoint();

        while (m_SimulationTime - start_simulation < m_Duration)
        {
            update();
        }
    }

    void Simulator::update()
    {
        Event event = m_EventQueue.top();
        m_EventQueue.pop();

        m_SimulationTime = event.Timepoint;

        switch (event.TargetType)
        {
            case EventTargetType::BUOY:
                for (node::Buoy& buoy : m_Buoys)
                {
                    // Update every single buoy
                }
                break;
            case EventTargetType::CHANNEL:
                // Update the channel
                break;
            case EventTargetType::SIMULATOR:
                // Update the simulator
                break;
            default:
                break;
        }
    }
}
