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
            logging::INFO(METHOD_NAME, "Buoy count setted to: %d", m_Buoys.size());
        }
        catch (const std::exception& e)
        {
            logging::ERROR(METHOD_NAME, "Exception: %s", e.what());
            m_Buoys.resize(50);
            logging::INFO(METHOD_NAME, "Buoy count fallback to: %d", m_Buoys.size());
        }
    }

    void BuoyArray::HandleEvent(const core::Event& event, core::EventQueue& queue, float simulation_time)
    {
    }
}
