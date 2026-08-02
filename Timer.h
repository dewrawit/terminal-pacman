#pragma once
#include <cassert>

class Timer
{
    private:
    int m_maxDuration{};
    int m_timer{};

    public:
    Timer() = default;
    Timer(int maxSeconds) : m_maxDuration{ maxSeconds }, m_timer{ m_maxDuration } {}
    void reset()
    {
        m_timer = m_maxDuration;
    }
    void decrement()
    {
        if(m_timer > 0)
            --m_timer;
    }
    bool timeout()
    {
        return m_timer <= 0;
    }
};