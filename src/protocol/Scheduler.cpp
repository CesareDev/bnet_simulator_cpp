#include <cmath>

#include <base/ConfigLoader.hpp>
#include <base/Random.hpp>
#include <base/Vector.hpp>
#include <logging/Logger.hpp>
#include <protocol/Scheduler.hpp>

#define BEACON_MIN_INTERVAL "BEACON_MIN_INTERVAL"
#define BEACON_MAX_INTERVAL "BEACON_MAX_INTERVAL"
#define BEACON_STATIC_INTERVAL "BEACON_STATIC_INTERVAL"
#define NEIGHBORS_THRESHOLD "NEIGHBORS_THRESHOLD"
#define CONTACT_THRESHOLD "CONTACT_THRESHOLD"
#define DEFAULT_BUOY_VELOCITY "DEFAULT_BUOY_VELOCITY"
#define SCHEDULER_MODE "SCHEDULER_MODE"

namespace protocol
{
    void Scheduler::Init()
    {
        base::ConfigLoader& c = base::ConfigLoader::Instance();
        try
        {
            m_MinInterval = std::stof(c.Get(BEACON_MIN_INTERVAL));
            m_MaxInterval = std::stof(c.Get(BEACON_MAX_INTERVAL));
            m_StaticInterval = std::stof(c.Get(BEACON_STATIC_INTERVAL));
            m_NeighborThreshold = std::stoi(c.Get(NEIGHBORS_THRESHOLD));
            m_ContactThreshold = std::stof(c.Get(CONTACT_THRESHOLD));
            m_DefaultVelocty = std::stof(c.Get(DEFAULT_BUOY_VELOCITY));
            std::string mode = c.Get(SCHEDULER_MODE);
            if (mode == "Static")
                m_Mode = SchedulerMode::Static;
            if (mode == "ADAB")
                m_Mode = SchedulerMode::ADAB;
            if (mode == "ACAB")
                m_Mode = SchedulerMode::ACAB;
            LOG_INFO("Configuration loaded");
        }
        catch(const std::exception& e)
        {
            LOG_ERROR("Exeption: " << e.what());
            LOG_ERROR("Fallback to the default configuration");
            m_MinInterval = 1.0;
            m_MaxInterval = 5.0;
            m_StaticInterval = 0.25;
            m_NeighborThreshold = 15;
            m_ContactThreshold = 20.f;
            m_DefaultVelocty = 15.f;
            m_Mode = SchedulerMode::Static;
        }

        m_NextSendTime = 
            m_Mode == SchedulerMode::Static ?
            base::GetRandomFloat() * m_StaticInterval : base::GetRandomFloat() * m_MaxInterval;
    }

    bool Scheduler::ShouldSend(float battery, base::Vector velocity, const node::NeighborsMap& neighbors, float sim_time)
    {
        switch (m_Mode)
        {
            case SchedulerMode::Static:
                return shouldSendStatic(sim_time);
                break;
            case SchedulerMode::ADAB:
                return shouldSendADAB(neighbors, sim_time);
                break;
            case SchedulerMode::ACAB:
                return shouldSendACAB(battery, velocity, neighbors, sim_time);
                break;
            default:
                LOG_ERROR("Unrecognized mode");
                return false;
                break;
        }
    }

    float Scheduler::GetNextCheckInterval()
    {
        if (m_Mode == SchedulerMode::Static)
            return m_StaticInterval;
        else
            return m_NextSendTime;
    }

    bool Scheduler::shouldSendStatic(float sim_time)
    {
        float time_since_last = sim_time - m_LastSendTime;
        if (time_since_last > m_StaticInterval)
        {
            m_LastSendTime = sim_time;
            return true;
        }
        return false;
    }

    bool Scheduler::shouldSendADAB(const node::NeighborsMap& neighbors, float sim_time)
    {
        float density_score = std::min(1.f, (float)neighbors.size() / (float)m_NeighborThreshold);
        float fq = density_score * density_score;
        float bi = m_MinInterval + fq * (m_MaxInterval - m_MinInterval);
        float jitter = base::GetRandomFloat() - 0.5f;
        float bi_final = bi * (1.f + jitter);
        float interval = std::max(m_MinInterval, std::min(bi_final, m_MaxInterval));

        float time_since_last = sim_time - m_LastSendTime;
        if (time_since_last > m_NextSendTime)
        {
            m_LastSendTime = sim_time;
            m_NextSendTime = interval;
            return true;
        }
        return false;
    }

    bool Scheduler::shouldSendACAB(float battery, base::Vector velocity, const node::NeighborsMap& neighbors, float sim_time)
    {
        float density_score = std::min(1.f, (float)neighbors.size() / (float)m_NeighborThreshold);

        float contact_score {};
        if (!neighbors.empty())
        {
            float last_contact {};
            for (const auto& item : neighbors)
            {
                if (item.second.timestamp > last_contact)
                    last_contact = item.second.timestamp;
            }
            float delta = sim_time - last_contact;
            contact_score = std::max(0.f, 1.f - (delta / m_ContactThreshold));
        }

        float speed = std::hypot(velocity.x, velocity.y);
        float mobility_score = std::min(1.f, speed / m_DefaultVelocty);

        float w_density = 0.4;
        float w_contact = 0.3;
        float w_mobility = 0.3;

        float combined =
            w_density * density_score + 
            w_contact * contact_score + 
            w_mobility * (1.f - mobility_score);

        float fq = combined * combined;
        float bi = m_MinInterval + fq * (m_MaxInterval - m_MinInterval);
        float jitter = base::GetRandomFloat() - 0.5f;
        float bi_final = bi * (1.f + jitter);
        float interval = std::max(m_MinInterval, std::min(bi_final, m_MaxInterval));

        float time_since_last = sim_time - m_LastSendTime;
        if (time_since_last > m_NextSendTime)
        {
            m_LastSendTime = sim_time;
            m_NextSendTime = interval;
            return true;
        }
        return false;
    }
}
