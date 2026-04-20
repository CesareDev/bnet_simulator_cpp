#include <core/Simulator.hpp>

#ifndef CONF_PATH
#define CONF_PATH "../bnet.ini"
#endif // !CONF_PATH

int main(int, char* argv[])
{
    core::Simulator sim;
    sim.Init(CONF_PATH);

    sim.Run();

    return 0;
}
