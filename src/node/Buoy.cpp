#include <logging/Logger.hpp>
#include <node/Buoy.hpp>
#include <base/Random.hpp>
#include <base/ConfigLoader.hpp>

#define DIFS_TIME "DIFS_TIME"
#define SLOT_TIME "SLOT_TIME"
#define CW "CW"
#define NEIGHBOR_TIMEOUT "NEIGHBOR_TIMEOUT"
#define WORLD_WIDTH "WORLD_WIDTH"
#define WORLD_HEIGHT "WORLD_HEIGHT"
#define SPEED_OF_LIGHT "SPEED_OF_LIGHT"
#define COMM_RANGE_MAX "COMM_RANGE_MAX"

namespace node
{
    void Buoy::Init()
    {
        base::ConfigLoader& c = base::ConfigLoader::Instance();
        m_Scheduler.Init();
        m_Id = base::GetRandomUint64();
        m_State = BuoyState::SLEEPING;
        m_Battery = 100.f;
        
        try
        {
            m_DifsTime = std::stof(c.Get(DIFS_TIME));
            m_SlotTime = std::stof(c.Get(SLOT_TIME));
            m_ContentionWindow = std::stoi(c.Get(CW));
            m_NeighborTimeout = std::stof(c.Get(NEIGHBOR_TIMEOUT));
            m_WorldWidth = std::stof(c.Get(WORLD_WIDTH));
            m_WorldHeight = std::stof(c.Get(WORLD_HEIGHT));
            m_SpeedOfLight = std::stof(c.Get(SPEED_OF_LIGHT));
            m_CommRangeMax = std::stof(c.Get(COMM_RANGE_MAX));
            LOG_INFO("Configuration loaded");
        }
        catch (const std::exception& e)
        {
            LOG_ERROR("Exeption: " << e.what());
            LOG_ERROR("Fallback to the default configuration");
            m_DifsTime = 2.0e-05;
            m_SlotTime = 5.0e-05;
            m_ContentionWindow = 16;
            m_NeighborTimeout = 15.0;
            m_WorldWidth = 600.0;
            m_WorldHeight = 600.0;
            m_SpeedOfLight = 300000000.0;
            m_CommRangeMax = 120.0;
        }
    }

    void Buoy::Setup(base::Vector position, base::Vector velocity, bool is_mobile)
    {
        m_Position = position;
        m_Velocity = velocity;
        m_IsMobile = is_mobile;
    }

    void Buoy::HandleEvent(const core::Event& event, core::EventQueue& queue, core::Channel& channel, float simulation_time)
    {
        switch (event.Type)
        {
            case core::EventType::SCHEDULER_CHECK:
                handleSchedulerCheck(event, queue, channel, simulation_time);
                break;
            case core::EventType::CHANNEL_SENSE:
                handleChannelSense(event, queue, channel, simulation_time);
                break;
            case core::EventType::DIFS_COMPLETION:
                handleDifsCompletion(event, queue, channel, simulation_time);
                break;
            case core::EventType::BACKOFF_COMPLETION:
                handleBackoffCompletion(event, queue, channel, simulation_time);
                break;
            case core::EventType::TRANSMISSION_START:
                handleTransmissionStart(event, queue, channel, simulation_time);
                break;
            case core::EventType::RECEPTION:
                handleReception(event, queue, channel, simulation_time);
                break;
            case core::EventType::NEIGHBOR_CLEANUP:
                handleNeighborCleanup(event, queue, channel, simulation_time);
                break;
            case core::EventType::BUOY_MOVEMENT:
                handlBuoyMovement(event, queue, channel, simulation_time);
                break;
            default:
                LOG_ERROR("Unrecognized event");
                break;
        }
    }

    void Buoy::handleSchedulerCheck(const core::Event& event, core::EventQueue& queue, core::Channel& channel, float simulation_time)
    {
        bool should_send = m_Scheduler.ShouldSend(m_Battery, m_Velocity, m_Neighbors, simulation_time);
        if (should_send)
        {
            m_WantToSend = true;
            m_SchedulerDecisionTime = simulation_time;

            core::Event ev;
            ev.Timepoint = simulation_time;
            ev.TargetType = core::EventTargetType::BUOY;
            ev.TargetUUID = m_Id;
            ev.Type = core::EventType::CHANNEL_SENSE;
            queue.push(ev);
        }
        float next_check_interval = m_Scheduler.GetNextCheckInterval();

        core::Event ev;
        ev.Timepoint = simulation_time + next_check_interval;
        ev.TargetType = core::EventTargetType::BUOY;
        ev.TargetUUID = m_Id;
        ev.Type = core::EventType::SCHEDULER_CHECK;
        queue.push(ev);
    }

    void Buoy::handleChannelSense(const core::Event& event, core::EventQueue& queue, core::Channel& channel, float simulation_time)
    {
        if (m_WantToSend)
        {
            if (channel.IsBusy(m_Position, simulation_time))
            {
                core::Event ev;
                ev.Timepoint = simulation_time + 0.01f;
                ev.TargetType = core::EventTargetType::BUOY;
                ev.TargetUUID = m_Id;
                ev.Type = core::EventType::CHANNEL_SENSE;
                queue.push(ev);
            }
            else
            {
                m_State = BuoyState::WAITING_DIFS;
                core::Event ev;
                ev.Timepoint = simulation_time + m_DifsTime;
                ev.TargetType = core::EventTargetType::BUOY;
                ev.TargetUUID = m_Id;
                ev.Type = core::EventType::DIFS_COMPLETION;
                queue.push(ev);
            }
        }
    }

    void Buoy::handleDifsCompletion(const core::Event& event, core::EventQueue& queue, core::Channel& channel, float simulation_time)
    {
        if (!m_WantToSend || m_State != BuoyState::WAITING_DIFS)
            return;

        if (channel.IsBusy(m_Position, simulation_time))
        {
            m_State = BuoyState::RECEIVING;
            core::Event ev;
            ev.Timepoint = simulation_time;
            ev.TargetType = core::EventTargetType::BUOY;
            ev.TargetUUID = m_Id;
            ev.Type = core::EventType::CHANNEL_SENSE;
            queue.push(ev);
        }
        else
        {
            if (m_BackoffRemaining <= 0)
            {
                int32_t backoff_slot = base::GetRandomInt32Range(0, m_ContentionWindow - 1);
                float backoff_time = backoff_slot * m_SlotTime;
                m_BackoffTime = backoff_time;
                m_BackoffRemaining = backoff_time;
            }
            m_State = BuoyState::BACKOFF;
            m_BackoffStartedTime = simulation_time;
            core::Event ev;
            ev.Timepoint = simulation_time  + m_BackoffRemaining;
            ev.TargetType = core::EventTargetType::BUOY;
            ev.TargetUUID = m_Id;
            ev.Type = core::EventType::BACKOFF_COMPLETION;
            queue.push(ev);
        }
    }

    void Buoy::handleBackoffCompletion(const core::Event& event, core::EventQueue& queue, core::Channel& channel, float simulation_time)
    {
        if (!m_WantToSend || m_State != BuoyState::BACKOFF)
            return;

        if (channel.IsBusy(m_Position, simulation_time))
        {
            float elapsed = simulation_time - m_BackoffStartedTime;
            m_BackoffRemaining = std::max(0.f, m_BackoffRemaining - elapsed);
            m_State = BuoyState::RECEIVING;
            core::Event ev;
            ev.Timepoint = simulation_time + 0.01f;
            ev.TargetType = core::EventTargetType::BUOY;
            ev.TargetUUID = m_Id;
            ev.Type = core::EventType::CHANNEL_SENSE;
        }
        else
        {
            m_BackoffRemaining = 0.f;
            m_BackoffStartedTime = 0.f;
            core::Event ev;
            ev.Timepoint = simulation_time;
            ev.TargetType = core::EventTargetType::BUOY;
            ev.TargetUUID = m_Id;
            ev.Type = core::EventType::TRANSMISSION_START;
        }
    }

    void Buoy::handleTransmissionStart(const core::Event& event, core::EventQueue& queue, core::Channel& channel, float simulation_time)
    {
    }

    void Buoy::handleReception(const core::Event& event, core::EventQueue& queue, core::Channel& channel, float simulation_time)
    {
    }

    void Buoy::handleNeighborCleanup(const core::Event& event, core::EventQueue& queue, core::Channel& channel, float simulation_time)
    {
    }

    void Buoy::handlBuoyMovement(const core::Event& event, core::EventQueue& queue, core::Channel& channel, float simulation_time)
    {
    }
}
