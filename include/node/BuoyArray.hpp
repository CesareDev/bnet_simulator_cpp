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

        private:
            std::vector<node::Buoy> m_Buoys;
    };
}

#endif // !BUOYARRAY_HPP
