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
            logging::ERROR(METHOD_NAME, e.what()); 
        }

        std::string s_bit_rate = config_loader.Get(BIT_RATE);
        try
        {
            m_BitRate = uint32_t(std::stoul(s_bit_rate));
            logging::INFO(METHOD_NAME, "Bit rate setted to: %d", m_BitRate);
        }
        catch (const std::exception& e)
        {
            logging::ERROR(METHOD_NAME, e.what()); 
        }

        std::string s_speed_of_light = config_loader.Get(SPEED_OF_LIGHT);
        try
        {
            m_SpeedOfLight = uint32_t(std::stoul(s_speed_of_light));
            logging::INFO(METHOD_NAME, "Speed of light setted to: %d", m_SpeedOfLight);
        }
        catch (const std::exception& e)
        {
            logging::ERROR(METHOD_NAME, e.what()); 
        }

        std::string s_comm_range_high_prob = config_loader.Get(COMM_RANGE_HIGH_PROB);
        try
        {
            m_CommRangeHighProb = float(std::stof(s_comm_range_high_prob));
            logging::INFO(METHOD_NAME, "Communication range with high probability setted to: %f", m_CommRangeHighProb);
        }
        catch (const std::exception& e)
        {
            logging::ERROR(METHOD_NAME, e.what()); 
        }

        std::string s_comm_range_max = config_loader.Get(COMM_RANGE_MAX);
        try
        {
            m_CommRangeMax = float(std::stof(s_comm_range_max));
            logging::INFO(METHOD_NAME, "Max communication range setted to: %f", m_CommRangeMax);
        }
        catch (const std::exception& e)
        {
            logging::ERROR(METHOD_NAME, e.what()); 
        }

        std::string s_delivery_prob_high = config_loader.Get(DELIVERY_PROB_HIGH);
        try
        {
            m_DeliveryProbHigh = float(std::stof(s_delivery_prob_high));
            logging::INFO(METHOD_NAME, "High delivery probability setted to: %f", m_DeliveryProbHigh);
        }
        catch (const std::exception& e)
        {
            logging::ERROR(METHOD_NAME, e.what()); 
        }

        std::string s_delivery_prob_low = config_loader.Get(DELIVERY_PROB_LOW);
        try
        {
            m_DeliveryProbLow = float(std::stof(s_delivery_prob_low));
            logging::INFO(METHOD_NAME, "Low delivery probability setted to: %f", m_DeliveryProbLow);
        }
        catch (const std::exception& e)
        {
            logging::ERROR(METHOD_NAME, e.what()); 
        }
    }

    void Channel::Update(EventQueue& queue, base::Timepoint SIMULATION_TIME)
    {
    }
}
