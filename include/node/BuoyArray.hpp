#ifndef BUOYARRAY_HPP
#define BUOYARRAY_HPP

#include <vector>
#include <node/Buoy.hpp>

namespace node
{
    class BuoyArray
    {
        public:
            void Init();
            void HandleEvent(const core::Event& event, core::EventQueue& queue, float simulation_time);

        private:
            std::vector<node::Buoy> m_Buoys;
    };
}

#endif // !BUOYARRAY_HPP
