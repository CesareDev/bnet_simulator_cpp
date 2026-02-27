#include <logging/Logger.hpp>

#include <ctime>
#include <iostream>

static std::string get_day_and_time()
{
    time_t timestamp;
    time(&timestamp);
    std::string time = ctime(&timestamp);
    time.pop_back();
    return time;
}

namespace logging
{
    void DEBUG(const std::string& method_name, const std::string& message)
    {
        std::cout << get_day_and_time() << " [DEBUG] [" << method_name << "], " << message << std::endl;
    }

    void INFO(const std::string& method_name, const std::string& message)
    {
        std::cout << get_day_and_time() << " [INFO]  [" << method_name << "], " << message << std::endl;
    }

    void ERROR(const std::string& method_name, const std::string& message)
    {
        std::cout << get_day_and_time() << " [ERROR] [" << method_name << "], " << message << std::endl;
    }

    void FATAL(const std::string& method_name, const std::string& message)
    {
        std::cout << get_day_and_time() << " [FATAL] [" << method_name << "], " << message << std::endl;
    }
}
