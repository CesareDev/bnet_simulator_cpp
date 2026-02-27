#include <core/Simulator.hpp>
#include <base/Time.hpp>

namespace core
{
    void Simulator::Init()
    {
        // From configuration file, load:
        // - Number of buoys and ratio
        // - Duration
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
