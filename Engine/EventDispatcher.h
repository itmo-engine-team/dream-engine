#pragma once

#include <map>
#include <vector>
#include "Event.h"

class EventDispatcher
{
public:

    //Constructor 
    EventDispatcher() {}
    ~EventDispatcher()
    {
        for (auto mapEvent : EventList)
        {
            for (auto e : mapEvent.second)
                delete e;
        }
    }

    //Register event
    void BindEvent(IEvent* event)
    {
        if (event)
            EventList[event->getName()].push_back(event);
    }


    template <class Class, typename ...arg>
    void CallEvent(const std::string& eventName, arg... a)
    {
        auto EventIterator = EventList.find(eventName);

        //Check EventIterator valid
        if (EventIterator == EventList.end())  return;

        for (auto* ie : EventIterator->second)
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
	
    std::map<std::string, std::vector<IEvent*>> EventList;
};