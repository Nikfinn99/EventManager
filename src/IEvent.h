#pragma once

#include <Arduino.h>

class IEvent
{
  private:
    unsigned long start;
    int delay;
    bool active;

  public:
    IEvent(int delay) : start(0), delay(delay), active(false) {}

    inline void enable()
    {
        setEnabled(true);
    }

    inline IEvent& disable()
    {
        setEnabled(false);
        return *this;
    }

    inline IEvent& abort()
    {
        setEnabled(false);
        return *this;
    }

    inline IEvent& setEnabled(bool enabled)
    {
        active = enabled;
        return *this;
    }

    inline IEvent& schedule(int delay)
    {
        if (!active)
        {
            start = millis();
            delay = delay;
            setEnabled(true);
        }
        return *this;
    }

    inline IEvent& schedule()
    {
        if (!active)
        {
            start = millis();
            setEnabled(true);
        }
        return *this;
    }

    inline IEvent& reschedule()
    {
        start = millis();
        setEnabled(true);
        return *this;
    }

    inline bool isEnabled()
    {
        return active;
    }

    inline int getDelay()
    {
        return delay;
    }

    IEvent& update()
    {
        if (active)
        {
            if (millis() >= start + delay)
            {
                trigger();
                setEnabled(false);
            }
        }
        return *this;
    }

    virtual void trigger() = 0;
};
