#pragma once

#include <map>
#include <vector>
#include "Event.h"

class EventDispatcher
{
public:

    // Constructor 
    EventDispatcher() {}
    ~EventDispatcher()
    {
        for (auto mapEvent : eventList)
        {
            for (auto e : mapEvent.second)
                delete e;
        }
    }

    // Register event
    void BindEvent(IEvent* event)
    {
        if (event)
            eventList[event->GetName()].push_back(event);
    }


    template <class Class, typename ...arg>
    void CallEvent(const std::string& eventName, arg... a)
    {
        auto eventIterator = eventList.find(eventName);

        // Check EventIterator valid
        if (eventIterator == eventList.end())  return;

        for (auto* ie : eventIterator->second)
        {
            if (Event<Class, arg...>* event = dynamic_cast<Event<Class, arg...>*>(ie))
            {
                Class classTemplate;
                event->Call(classTemplate, a...);
            }
            else
            {
                printf("Dynamic cast failed");
            }
        }
    }

private:
	
    std::map<std::string, std::vector<IEvent*>> eventList;
};