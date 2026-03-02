#include <node/BuoyArray.hpp>
#include <base/ConfigLoader.hpp>
#include <logging/Logger.hpp>

namespace node
{

    void BuoyArray::Init()
    {
        base::ConfigLoader& c = base::ConfigLoader::Instance();
        std::string s_count = c.Get("BUOYS_COUNT");
        uint64_t count {};
        try
        {
            count = std::stoull(s_count);
            m_Buoys.resize(count);
        }
        catch (const std::exception& e)
        {
            logging::ERROR(METHOD_NAME, e.what()); 
        }
    }
}
