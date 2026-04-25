#include <core/Channel.hpp>
#include <base/ConfigLoader.hpp>
#include <logging/Logger.hpp>

#define IDEAL_CHANNEL "IDEAL_CHANNEL"
#define BIT_RATE "BIT_RATE"
#define SPEED_OF_LIGHT "SPEED_OF_LIGHT"
#define COMM_RANGE_HIGH_PROB "COMM_RANGE_HIGH_PROB"
#define COMM_RANGE_MAX "COMM_RANGE_MAX"
#define DELIVERY_PROB_HIGH "DELIVERY_PROB_HIGH"
#define DELIVERY_PROB_LOW "DELIVERY_PROB_LOW"

namespace core
{
    void Channel::Init()
    {
        base::ConfigLoader& config_loader = base::ConfigLoader::Instance();

        try
        {
            m_IdealChannel = std::stoi(config_loader.Get(IDEAL_CHANNEL));
            m_BitRate = std::stoul(config_loader.Get(BIT_RATE));
            m_SpeedOfLight = std::stoul(config_loader.Get(SPEED_OF_LIGHT));
            m_CommRangeHighProb = std::stof(config_loader.Get(COMM_RANGE_HIGH_PROB));
            m_CommRangeMax = std::stof(config_loader.Get(COMM_RANGE_MAX));
            m_DeliveryProbHigh = std::stof(config_loader.Get(DELIVERY_PROB_HIGH));
            m_DeliveryProbLow = std::stof(config_loader.Get(DELIVERY_PROB_LOW));
            LOG_INFO("Configuration loaded");
        }
        catch (const std::exception& e)
        {
            LOG_ERROR("Exception: " << e.what());
            LOG_ERROR("Fallback to the default configuration");
            m_IdealChannel = true;
            m_BitRate = 1000000;
            m_SpeedOfLight = 300000000;
            m_CommRangeHighProb = 70.f;
            m_CommRangeMax = 120.f;
            m_DeliveryProbHigh = 0.9f;
            m_DeliveryProbLow = 0.15f;
        }
    }

    void Channel::update(float simulation_time)
    {
        float max_delay = m_CommRangeMax / m_SpeedOfLight;
        float grace_period = max_delay + 1e-6;
        std::vector<uint64_t> expired_beacon {};

        for (auto& item : m_ActiveTransmission)
        {
            if (item.second.end_time + grace_period < simulation_time)
            {
                expired_beacon.push_back(item.first);
            }

            if (m_IdealChannel)
            {
                // ToDo: Count actually received
            }
        }
        
        for (uint64_t beacon_id : expired_beacon)
        {
            m_ActiveTransmission.erase(beacon_id);
        }
    }

    void Channel::HandleEvent(const core::Event& event, EventQueue& queue, float simulation_time)
    {
        if (event.Type == EventType::CHANNEL_UPDATE)
        {
            update(simulation_time);
        }
    }

    bool Channel::Broadcast(const protocol::Beacon& beacon, float simulation_time)
    {
        // ToDo: count sent

        float transmission_time = (float)beacon.size_in_bits() / (float)m_BitRate;
        float new_end_time = transmission_time + simulation_time;
    }

    bool Channel::IsBusy(base::Vector position, float simulation_time)
    {
    }
}
