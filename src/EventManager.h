#pragma once

#include <map>
#include <string>
#include "IEvent.h"
#include "EventGPIO.h"
#include <SerialStream.h>

class EventManager
{
  private:
    typedef std::map<std::string, std::vector<IEvent *>> MapEvents;

    MapEvents m_all_events;

  public:
    EventManager() {}

    inline EventManager& attachEvent(std::string on, IEvent *event)
    {
        m_all_events[on].push_back(event); // add event to vector. if onaction has not been set before it will be created.
        return *this;
    }

    inline EventManager& clearEvents(std::string on){
        m_all_events[on].clear();// clear all events from this onaction
        return *this;
    }

    EventManager& triggerEvent(std::string on)
    {
        MapEvents::iterator it = m_all_events.find(on);
        if (it != m_all_events.end()) // only if onaction was already found in eventlist
        {
            for (IEvent *event : it->second) // loop through all events stored for this onaction
            {
                event->schedule(); // reschedule event
            }
        }
        return *this;
    }

    EventManager& abortEvent(std::string on){
        MapEvents::iterator it = m_all_events.find(on);
        if (it != m_all_events.end()) // only if onaction was already found in eventlist
        {
            for (IEvent *event : it->second) // loop through all events stored for this onaction
            {
                event->abort(); // abort event
            }
        }
        return *this;
    }

    EventManager& loop()
    {
        for (const auto &vec : m_all_events)
        {
            for (IEvent *event : vec.second)
            {
                event->update();
            }
        }
        return *this;
    }
};
