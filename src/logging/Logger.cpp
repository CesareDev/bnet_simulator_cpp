#include <logging/Logger.hpp>

#include <ctime>
#include <cstdarg>
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
    void DEBUG(const std::string& method_name, const char* message, ...)
    {
        va_list args;
        va_start(args, message);

        // Print prefix
        printf("%s [DEBUG] [%s] ", get_day_and_time().c_str(), method_name.c_str());

        // Print user message
        vprintf(message, args);

        printf("\n");

        va_end(args);
    }

    void INFO(const std::string& method_name, const char* message, ...)
    {
        va_list args;
        va_start(args, message);

        // Print prefix
        printf("%s [INFO] [%s] ", get_day_and_time().c_str(), method_name.c_str());

        // Print user message
        vprintf(message, args);

        printf("\n");

        va_end(args);
    }

    void ERROR(const std::string& method_name, const char* message, ...)
    {
        va_list args;
        va_start(args, message);

        // Print prefix
        printf("%s [ERROR] [%s] ", get_day_and_time().c_str(), method_name.c_str());

        // Print user message
        vprintf(message, args);

        printf("\n");

        va_end(args);
    }

    void FATAL(const std::string& method_name, const char* message, ...)
    {
        va_list args;
        va_start(args, message);

        // Print prefix
        printf("%s [FATAL] [%s] ", get_day_and_time().c_str(), method_name.c_str());

        // Print user message
        vprintf(message, args);

        printf("\n");

        va_end(args);
    }
}
