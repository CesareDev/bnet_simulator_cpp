#include <core/Simulator.hpp>
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
            m_Duration = std::stof(s_duration);
            logging::INFO(METHOD_NAME, "Simulation duration setted to: %d", m_Duration); 
        }
        catch (const std::exception& e)
        {
            logging::ERROR(METHOD_NAME, "Exception: %s", e.what());
            m_Duration = 600.f;
            logging::INFO(METHOD_NAME, "Simulation duration fallback to: %d", m_Duration); 
        }

        std::string s_mob_perc = config_loader.Get(MOBILE_BUOY_PERC);
        try
        {
            m_MobilePercentage = float(std::stof(s_mob_perc));
            logging::INFO(METHOD_NAME, "Mobile percentage setted to: %f", m_MobilePercentage); 
        }
        catch (const std::exception& e)
        {
            logging::ERROR(METHOD_NAME, "Exception: %s", e.what());
            m_MobilePercentage = 0.1f;
            logging::INFO(METHOD_NAME, "Mobile percentage fallback to: %f", m_MobilePercentage); 
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
                m_Buoys.HandleEvent(event, m_EventQueue, m_SimulationTime);
                break;
            case EventTargetType::CHANNEL:
                m_Channel.HandleEvent(event, m_EventQueue, m_SimulationTime);
                break;
            case EventTargetType::SIMULATOR:
                handleEvent(event);
                break;
            default:
                break;
        }
    }

    void Simulator::handleEvent(const Event& event)
    {
    }
}
