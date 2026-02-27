#include <fstream>
#include <base/ConfigLoader.hpp>
#include <logging/Logger.hpp>

namespace base
{
    ConfigLoader& ConfigLoader::Instance()
    {
        static ConfigLoader loader;
        return loader;
    }

    void ConfigLoader::Load(const std::string& config_path)
    {
        static std::string method_name = "ConfigLoader::Load";
        if (config_path.size() == 0)
        {
            // Default configuration
        }
        else
        {
            std::ifstream file(config_path);

            if (!file)
            {
                logging::ERROR(method_name, "Error opening the configuration file: " + config_path);
                return;
            }

            std::string line;

            while (std::getline(file, line))
            {
                // Trim trailing whitespaces
                line.erase(0, line.find_first_not_of(" \t"));

                // Skip empty lines or the comments 
                if (line.empty() || line[0] == '#')
                {
                    continue;
                }

                auto pos = line.find('=');

                if (pos == std::string::npos)
                {
                    logging::ERROR(method_name, "Invalid configuration: " + line);
                    continue;
                }

                if (pos != std::string::npos)
                {
                    auto key = line.substr(0, pos);
                    auto value = line.substr(pos + 1);

                    // Trim whitespaces from the key and the value
                    key.erase(key.find_last_not_of(" \t") + 1);
                    value.erase(0, value.find_first_not_of(" \t"));
                    value.erase(value.find_last_not_of(" \t") + 1);

                    m_ConfigMap[key] = value;
                }
            }
        }
    }

    std::string ConfigLoader::Get(const std::string& config)
    {
        static std::string method_name = "ConfigLoader::Get";
        if (m_ConfigMap.find(config) == m_ConfigMap.end())
        {
            logging::ERROR(method_name, "Configuration " + config + " not found");
            return "";
        }
        return m_ConfigMap[config];
    }

    ConfigLoader::ConfigLoader()
    {
    }
}
