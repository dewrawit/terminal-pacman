#pragma once
#include <cassert>
#include <string_view>
#include <string>

class Timer
{
    public:
    enum TimerTypes { stalemate, chase, scatter, scared, maxTimerTypes };

    private:
    std::string m_name{};
    int m_maxDuration{};
    int m_timer{};
    bool m_activated { false };
    TimerTypes m_type {};

    using SV = std::string_view;

    public:
    Timer() = default;
    Timer(SV name, int maxSeconds, TimerTypes type) 
        : m_name{ name }
        , m_maxDuration{ maxSeconds }
        , m_timer{ m_maxDuration }
        , m_type{ type } 
        { }
    
    const std::string& getName() const { return m_name; }
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
    bool isRunning() const
    {
        return m_activated;
    }
    bool isPaused() const
    {
        return !isRunning();
    }
    void activateAndReset()
    {
        m_activated = true;
        m_timer = m_maxDuration;
    }
    void deactivateAndReset()
    {
        m_activated = false;
        m_timer = m_maxDuration;
    }
    void pause()
    {
        m_activated = false;
    }
    void resume()
    {
        m_activated = true;
    }
    TimerTypes getType() const
    {
        return m_type;
    }
};