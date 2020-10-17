#pragma once

#include <map>
#include <vector>

#include "ErrorLogger.h"
#include "EventListener.h"

class EventDispatcher
{

public:

    // Constructor 
    EventDispatcher() = default;
    ~EventDispatcher();
	
    template <class C, typename ... arg>
    void BindEvent(EventListener<C, arg...>* listener)
    {
        if (!listener) return;

        eventList[listener->GetEventName()].push_back(listener);
    }

    template <class C, typename ... arg>
    void UnbindListener(const std::string& eventName, const C* listenerToUnbind)
    {
        auto eventIterator = eventList.find(eventName);

        // Check EventIterator valid
        if (eventIterator == eventList.end()) return;

        auto listenerIterator = eventIterator->second.begin();
        while (listenerIterator < eventIterator->second.end())
        {
            auto* eventListener = dynamic_cast<EventListener<C, arg...>*>(*listenerIterator);
            if (!eventListener || eventListener->GetListener() != listenerToUnbind)
            {
                ++listenerIterator;
                continue;
            }

            listenerIterator = eventIterator->second.erase(listenerIterator);
            delete eventListener;
        }
    }

    template <typename ... arg>
    void CallEvent(const std::string& eventName, arg ... a)
    {
        auto listenerIterator = eventList.find(eventName);

        // Check EventIterator valid
        if (listenerIterator == eventList.end()) return;

        for (auto* ie : listenerIterator->second)
        {
            if (auto* listener = dynamic_cast<BaseEventListener<arg...>*>(ie))
            {
                listener->Call(a...);
            }
            else
            {
                const std::string message = "Can't call listener for event " + eventName;
                ErrorLogger::Log(Error, "Can't call listener for event ");
            }
        }
    }

    void UnbindAllListeners(const std::string& eventName);

    unsigned int GetEventCount() const;

    unsigned int GetListenerCount(const std::string& eventName) const;

protected:
	
    std::map<std::string, std::vector<IEventListener*>> eventList;

};
