#include <node/BuoyArray.hpp>
#include <base/ConfigLoader.hpp>
#include <logging/Logger.hpp>

namespace node
{

    void BuoyArray::Init()
    {
        base::ConfigLoader& c = base::ConfigLoader::Instance();
        std::string s_count = c.Get("BUOYS_COUNT");
        try
        {
            m_Buoys.resize(std::stoull(s_count));
            LOG_INFO("Buoy count setted to: " << m_Buoys.size());
        }
        catch (const std::exception& e)
        {
            LOG_ERROR("Exception: " << e.what());
            m_Buoys.resize(50);
            LOG_INFO("Buoy count fallback to: " << m_Buoys.size());
        }
    }

    void BuoyArray::HandleEvent(const core::Event& event, core::EventQueue& queue, float simulation_time)
    {
    }
}
