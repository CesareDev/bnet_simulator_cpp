#include <core/Channel.hpp>
#include <base/ConfigLoader.hpp>

namespace core
{
    void Channel::Init(const std::string& config_path)
    {
        static std::string method_name = "Simulator::Init";

        base::ConfigLoader& config_loader = base::ConfigLoader::Instance();
        config_loader.Load(config_path);
    }
}
