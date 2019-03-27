#pragma once

#include "IEvent.h"

class EventGPIO : public IEvent
{
  private:
    uint8_t pin;
    uint8_t level;

  public:
    EventGPIO(int delay, uint8_t pin, bool level) : IEvent(delay)
    {
        this->pin = pin;
        this->level = level;
        pinMode(pin, OUTPUT);
    }

    virtual void trigger()
    {
        digitalWrite(pin, level);
    }
};
