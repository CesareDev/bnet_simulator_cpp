#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>

#if defined(_MSC_VER)
    #define METHOD_NAME __FUNCSIG__
#else
    #define METHOD_NAME __PRETTY_FUNCTION__
#endif

namespace logging
{
    void DEBUG(const std::string& method_name, const char* message, ...);
    void INFO(const std::string& method_name, const char* message, ...);
    void ERROR(const std::string& method_name, const char* message, ...);
    void FATAL(const std::string& method_name, const char* message, ...);
}

#endif // !LOGGER_HPP
