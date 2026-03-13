#include <node/Buoy.hpp>
#include <base/Random.hpp>

namespace node
{
    void Buoy::Init()
    {
        m_Scheduler.Init();
    }

    void Buoy::Setup(base::Vector position, base::Vector velocity, bool is_mobile)
    {
        m_Id = base::GetRandomUint64();
        m_Position = position;
        m_Velocity = velocity;
        m_State = BuoyState::SLEEPING;
        m_Battery = 100.f;
        m_IsMobile = is_mobile;
    }

    void Buoy::HandleEvent(const core::Event& event, core::EventQueue& queue, float simulation_time)
    {
    }
}
