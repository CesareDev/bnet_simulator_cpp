#include <node/BuoyArray.hpp>
#include <logging/Logger.hpp>
#include <base/Random.hpp>
#include <base/ConfigLoader.hpp>

#define BUOYS_COUNT "BUOYS_COUNT"
#define MOBILE_BUOY_PERC "MOBILE_BUOY_PERC"
#define WORLD_WIDTH "WORLD_WIDTH"
#define WORLD_HEIGHT "WORLD_HEIGHT"
#define DEFAULT_BUOY_VELOCITY "DEFAULT_BUOY_VELOCITY"

namespace node
{
    void BuoyArray::Init()
    {
        float world_width {};
        float world_height {};
        float default_velocity {};

        base::ConfigLoader& c = base::ConfigLoader::Instance();
        try
        {
            m_Buoys.resize(std::stoull(c.Get(BUOYS_COUNT)));
            m_MobilePercentage = std::stof(c.Get(MOBILE_BUOY_PERC));
            world_width = std::stof(c.Get(WORLD_WIDTH));
            world_height = std::stof(c.Get(WORLD_HEIGHT));
            default_velocity = std::stof(c.Get(DEFAULT_BUOY_VELOCITY));
            LOG_INFO("Configuration loaded");
        }
        catch (const std::exception& e)
        {
            LOG_ERROR("Exception: " << e.what());
            LOG_ERROR("Fallback to the default configuration");
            m_Buoys.resize(50);
            m_MobilePercentage = 0.2f;
            world_width = 600.f;
            world_height = 600.f;
        }
        
        size_t counter {};
        for (auto& buoy : m_Buoys)
        {
            buoy.Init();

            base::Vector position
            {
                base::GetRandomFloat() * world_width,
                base::GetRandomFloat() * world_height
            };

            if (counter < m_Buoys.size() * m_MobilePercentage)
            {
                base::Vector velocity
                {
                    base::GetRandomFloat() * default_velocity,
                    base::GetRandomFloat() * default_velocity
                };
                buoy.Setup(position, velocity, true);
            }
            else
            {
                buoy.Setup(position, { 0.f,0.f }, false);
            }

            ++counter;
        }
    }

    void BuoyArray::HandleEvent(const core::Event& event, core::EventQueue& queue, float simulation_time)
    {
    }
}
