#include <core/Simulator.hpp>
#include <base/Time.hpp>
#include <base/ConfigLoader.hpp>
#include <logging/Logger.hpp>

#define SIM_DURATION "SIM_DURATION"
#define MOBILE_BUOY_PERC "MOBILE_BUOY_PERC"

namespace core
{
    void Simulator::Init(const std::string& config_path)
    {
        base::ConfigLoader& config_loader = base::ConfigLoader::Instance();
        config_loader.Load(config_path);

        m_Channel.Init();
        m_Buoys.Init();

        std::string s_duration = config_loader.Get(SIM_DURATION);
        try
        {
            m_Duration = base::DurationSeconds(std::stoi(s_duration));
            logging::INFO(METHOD_NAME, "Simulation duration setted to: %d", m_Duration); 
        }
        catch (const std::exception& e)
        {
            logging::ERROR(METHOD_NAME, e.what()); 
        }

        std::string s_mob_perc = config_loader.Get(MOBILE_BUOY_PERC);
        try
        {
            m_MobilePercentage = float(std::stof(s_mob_perc));
            logging::INFO(METHOD_NAME, "Mobile percentage setted to: %f", m_MobilePercentage); 
        }
        catch (const std::exception& e)
        {
            logging::ERROR(METHOD_NAME, e.what()); 
        }
    }

    void Simulator::Run()
    {
        // base::Timepoint start_simulation = base::GetTimepoint();

        // while (m_SimulationTime - start_simulation < m_Duration)
        // {
        //     update();
        // }
    }

    void Simulator::update()
    {
        Event event = m_EventQueue.top();
        m_EventQueue.pop();

        m_SimulationTime = event.Timepoint;

        switch (event.TargetType)
        {
            case EventTargetType::BUOY:
                // Update the buoy array
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
