#include <core/Simulator.hpp>

int main(int, char* argv[])
{
    std::string conf_path = argv[1] ? argv[1] : "../bnet.conf";

    core::Simulator sim;
    sim.Init(conf_path);

    sim.Run();

    return 0;
}
