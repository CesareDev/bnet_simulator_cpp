#ifndef CONFIGLOADER_HPP
#define CONFIGLOADER_HPP

#include <string>
#include <unordered_map>

namespace base
{
    class ConfigLoader
    {
        public:
            static ConfigLoader& Instance();
            
            void Load(const std::string& config_path = "");
            std::string Get(const std::string& config);

        private:
            ConfigLoader();
            std::unordered_map<std::string, std::string> m_ConfigMap;
    };
}

#endif // !CONFIGLOADER_HPP
