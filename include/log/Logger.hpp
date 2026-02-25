#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>

namespace logging
{
    void DEBUG(const std::string& method_name, const std::string& message);
    void INFO(const std::string& method_name, const std::string& message);
    void ERROR(const std::string& method_name, const std::string& message);
    void FATAL(const std::string& method_name, const std::string& message);
}

#endif // !LOGGER_HPP
