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

        std::string s_ideal_channel = config_loader.Get(IDEAL_CHANNEL);
        try
        {
            m_IdealChannel = uint32_t(std::stoi(s_ideal_channel));
            logging::INFO(METHOD_NAME, "Ideal channel setted to: %d", m_IdealChannel);
        }
        catch (const std::exception& e)
        {
            logging::ERROR(METHOD_NAME, "Exception: %s", e.what());
            m_IdealChannel = true;
            logging::INFO(METHOD_NAME, "Ideal channel fallback to: %d", m_IdealChannel);
        }

        std::string s_bit_rate = config_loader.Get(BIT_RATE);
        try
        {
            m_BitRate = uint32_t(std::stoul(s_bit_rate));
            logging::INFO(METHOD_NAME, "Bit rate setted to: %d", m_BitRate);
        }
        catch (const std::exception& e)
        {
            logging::ERROR(METHOD_NAME, "Exception: %s", e.what());
            m_BitRate = 1000000;
            logging::INFO(METHOD_NAME, "Bit rate fallback to: %d", m_BitRate);
        }

        std::string s_speed_of_light = config_loader.Get(SPEED_OF_LIGHT);
        try
        {
            m_SpeedOfLight = uint32_t(std::stoul(s_speed_of_light));
            logging::INFO(METHOD_NAME, "Speed of light setted to: %d", m_SpeedOfLight);
        }
        catch (const std::exception& e)
        {
            logging::ERROR(METHOD_NAME, "Exception: %s", e.what());
            m_SpeedOfLight = 300000000;
            logging::INFO(METHOD_NAME, "Speed of light fallback to: %d", m_SpeedOfLight);
        }

        std::string s_comm_range_high_prob = config_loader.Get(COMM_RANGE_HIGH_PROB);
        try
        {
            m_CommRangeHighProb = float(std::stof(s_comm_range_high_prob));
            logging::INFO(METHOD_NAME, "Communication range with high probability setted to: %f", m_CommRangeHighProb);
        }
        catch (const std::exception& e)
        {
            logging::ERROR(METHOD_NAME, "Exception: %s", e.what());
            m_CommRangeHighProb = 70.f;
            logging::INFO(METHOD_NAME, "Communication range with high probability fallback to: %f", m_CommRangeHighProb);
        }

        std::string s_comm_range_max = config_loader.Get(COMM_RANGE_MAX);
        try
        {
            m_CommRangeMax = float(std::stof(s_comm_range_max));
            logging::INFO(METHOD_NAME, "Max communication range setted to: %f", m_CommRangeMax);
        }
        catch (const std::exception& e)
        {
            logging::ERROR(METHOD_NAME, "Exception: %s", e.what());
            m_CommRangeMax = 120.f;
            logging::INFO(METHOD_NAME, "Max communication range fallback to: %f", m_CommRangeMax);
        }

        std::string s_delivery_prob_high = config_loader.Get(DELIVERY_PROB_HIGH);
        try
        {
            m_DeliveryProbHigh = float(std::stof(s_delivery_prob_high));
            logging::INFO(METHOD_NAME, "High delivery probability setted to: %f", m_DeliveryProbHigh);
        }
        catch (const std::exception& e)
        {
            logging::ERROR(METHOD_NAME, "Exception: %s", e.what());
            m_DeliveryProbHigh = 0.9f;
            logging::INFO(METHOD_NAME, "High delivery probability fallback to: %f", m_DeliveryProbHigh);
        }

        std::string s_delivery_prob_low = config_loader.Get(DELIVERY_PROB_LOW);
        try
        {
            m_DeliveryProbLow = float(std::stof(s_delivery_prob_low));
            logging::INFO(METHOD_NAME, "Low delivery probability setted to: %f", m_DeliveryProbLow);
        }
        catch (const std::exception& e)
        {
            logging::ERROR(METHOD_NAME, "Exception: %s", e.what());
            m_DeliveryProbLow = 0.15f;
            logging::INFO(METHOD_NAME, "Low delivery probability fallback to: %f", m_DeliveryProbLow);
        }
    }

    void Channel::update(float simulation_time)
    {
        float max_delay = m_CommRangeMax / m_SpeedOfLight;
        float grace_period = max_delay + 1e-6;
        std::vector<base::UUID> expired_indeces {};

        for (auto& item : m_ActiveTransmission)
        {
            if (item.second.end_time + grace_period < simulation_time)
            {
                expired_indeces.push_back(item.first);
            }

            if (m_IdealChannel)
            {
            }
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
    }

    bool Channel::IsBusy(base::Vector position, float simulation_time)
    {
    }
}
