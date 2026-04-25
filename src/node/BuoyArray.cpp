#include <node/BuoyArray.hpp>
#include <base/ConfigLoader.hpp>
#include <logging/Logger.hpp>

#define BUOYS_COUNT "BUOYS_COUNT"

namespace node
{
    void BuoyArray::Init()
    {
        base::ConfigLoader& c = base::ConfigLoader::Instance();
        try
        {
            m_Buoys.resize(std::stoull(c.Get(BUOYS_COUNT)));
            LOG_INFO("Configuration loaded");
        }
        catch (const std::exception& e)
        {
            LOG_ERROR("Exception: " << e.what());
            LOG_ERROR("Fallback to the default configuration");
            m_Buoys.resize(50);
        }
    }

    void BuoyArray::HandleEvent(const core::Event& event, core::EventQueue& queue, float simulation_time)
    {
    }
}
