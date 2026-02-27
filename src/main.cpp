#include <core/Simulator.hpp>

int main(int, char* argv[])
{
    std::string conf_path = argv[1] ? argv[1] : "";

    core::Simulator sim;
    sim.Init(conf_path);

    return 0;
}
