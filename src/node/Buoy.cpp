#include <logging/Logger.hpp>
#include <node/Buoy.hpp>
#include <base/Random.hpp>

namespace node
{
    void Buoy::Init()
    {
        m_Scheduler.Init();
    }

    void Buoy::Setup(base::Vector position, base::Vector velocity, bool is_mobile)
    {
        m_Id = base::GetRandomUint64();
        m_Position = position;
        m_Velocity = velocity;
        m_State = BuoyState::SLEEPING;
        m_Battery = 100.f;
        m_IsMobile = is_mobile;
    }

    void Buoy::HandleEvent(const core::Event& event, core::EventQueue& queue, float simulation_time)
    {
        switch (event.Type)
        {
            case core::EventType::SCHEDULER_CHECK:
                handleSchedulerCheck(event, simulation_time);
                break;
            case core::EventType::CHANNEL_SENSE:
                handleChannelSense(event, simulation_time);
                break;
            case core::EventType::DIFS_COMPLETION:
                handleDifsCompletion(event, simulation_time);
                break;
            case core::EventType::BACKOFF_COMPLETION:
                handleBackoffCompletion(event, simulation_time);
                break;
            case core::EventType::TRANSMISSION_START:
                handleTransmissionStart(event, simulation_time);
                break;
            case core::EventType::RECEPTION:
                handleReception(event, simulation_time);
                break;
            case core::EventType::NEIGHBOR_CLEANUP:
                handleNeighborCleanup(event, simulation_time);
                break;
            case core::EventType::BUOY_MOVEMENT:
                handlBuoyMovement(event, simulation_time);
                break;
            default:
                LOG_ERROR("Unrecognized event");
                break;
        }
    }

    void Buoy::handleSchedulerCheck(const core::Event &event, float simulation_time)
    {
        bool should_send = m_Scheduler.ShouldSend(m_Battery, m_Velocity, m_Neighbors, simulation_time);
    }

    void Buoy::handleChannelSense(const core::Event& event, float simulation_time)
    {
    }

    void Buoy::handleDifsCompletion(const core::Event& event, float simulation_time)
    {
    }

    void Buoy::handleBackoffCompletion(const core::Event& event, float simulation_time)
    {
    }

    void Buoy::handleTransmissionStart(const core::Event& event, float simulation_time)
    {
    }

    void Buoy::handleReception(const core::Event& event, float simulation_time)
    {
    }

    void Buoy::handleNeighborCleanup(const core::Event& event, float simulation_time)
    {
    }

    void Buoy::handlBuoyMovement(const core::Event& event, float simulation_time)
    {
    }
}
