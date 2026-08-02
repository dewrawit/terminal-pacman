#pragma once
#include <cassert>

class Timer
{
    private:
    int m_maxDuration{};
    int m_timer{};
    bool m_activated { false };

    public:
    Timer() = default;
    Timer(int maxSeconds) : m_maxDuration{ maxSeconds }, m_timer{ m_maxDuration } {}
    
    void decrement()
    {
        assert(m_activated && "Timer is not activated.");
        if(m_timer > 0)
            --m_timer;
    }
    bool timeout() const
    {
        return m_timer <= 0;
    }
    bool isActivated() const
    {
        return m_activated;
    }
    bool isDeactivated() const
    {
        return !isActivated();
    }
    bool activateAndReset()
    {
        m_activated = true;
        m_timer = m_maxDuration;
    }
    void deactivateAndReset()
    {
        m_activated = false;
        m_timer = m_maxDuration;
    }
};