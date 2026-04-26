#include <iostream>

#include <base/ConfigLoader.hpp>
#include <core/Simulator.hpp>

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Wrong numbers of argumets" << std::endl;
        std::cout << "  USAGE: " << argv[0] << " <conf_file>" << std::endl;
        return 1;
    }

    std::string conf_path = argv[1];

    base::ConfigLoader& c = base::ConfigLoader::Instance();
    c.Load(conf_path);

    core::Simulator sim;
    sim.Init();

    sim.Run();

    return 0;
}
