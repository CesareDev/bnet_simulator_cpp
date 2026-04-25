#include <base/ConfigLoader.hpp>
#include <core/Simulator.hpp>

#ifndef CONF_PATH
#define CONF_PATH "../bnet.ini"
#endif // !CONF_PATH

int main()
{
    base::ConfigLoader& c = base::ConfigLoader::Instance();
    c.Load(CONF_PATH);

    core::Simulator sim;
    sim.Init();

    sim.Run();

    return 0;
}
