#include <base/UUID.hpp>
#include <node/Buoy.hpp>

namespace node
{
    void Buoy::Init()
    {
        m_Scheduler.Init();
    }

    void Buoy::Setup(base::Vector position, base::Vector velocity, bool is_mobile)
    {
        m_Id = base::GetRandomUUID();
        m_Position = position;
        m_Velocity = velocity;
        m_State = BuoyState::SLEEPING;
        m_Battery = 100.f;
        m_IsMobile = is_mobile;
    }
}
