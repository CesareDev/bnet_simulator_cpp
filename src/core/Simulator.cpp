#include <core/Simulator.hpp>
#include <base/ConfigLoader.hpp>
#include <logging/Logger.hpp>

#define SIM_DURATION "SIM_DURATION"
#define MOBILE_BUOY_PERC "MOBILE_BUOY_PERC"

namespace core
{
    void Simulator::Init()
    {
        base::ConfigLoader& config_loader = base::ConfigLoader::Instance();

        m_Channel.Init();
        m_Buoys.Init();

        try
        {
            m_Duration = std::stof(config_loader.Get(SIM_DURATION));
            m_MobilePercentage = std::stof(config_loader.Get(MOBILE_BUOY_PERC));
            LOG_INFO("Configuration loaded");
        }
        catch (const std::exception& e)
        {
            LOG_ERROR("Exception: " << e.what());
            LOG_ERROR("Fallback to the default configuration");
            m_Duration = 600.f;
            m_MobilePercentage = 0.1f;
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
