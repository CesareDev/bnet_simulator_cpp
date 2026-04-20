#ifndef LOGGER_HPP
#define LOGGER_HPP

#if defined(_MSC_VER)
    #define METHOD_NAME __FUNCSIG__
#else
    #define METHOD_NAME __PRETTY_FUNCTION__
#endif

#include <iostream>

#define LOG_DEBUG(msg) std::cout << "[DEBUG] [" << __DATE__ ", " << __TIME__ "] " << "[" << METHOD_NAME << "] { " << msg << " }" << std::endl
#define LOG_INFO(msg) std::cout << "[INFO] [" << __DATE__ ", " << __TIME__ "] " << "[" << METHOD_NAME << "] { " << msg << " }" << std::endl
#define LOG_ERROR(msg) std::cerr << "[ERROR] [" << __DATE__ ", " << __TIME__ "] " << "[" << METHOD_NAME << "] { " << msg << " }" << std::endl
#define LOG_FATAL(msg) std::cerr << "[FATAL] [" << __DATE__ ", " << __TIME__ "] " << "[" << METHOD_NAME << "] { " << msg << " }" << std::endl

#endif // !LOGGER_HPP
