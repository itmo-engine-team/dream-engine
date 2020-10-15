#pragma once

#include <map>
#include <vector>

#include "EventListener.h"

class EventDispatcher
{

public:

    // Constructor 
    EventDispatcher() = default;
    ~EventDispatcher();

    // Register event
    template <class C, typename ...arg>
    void BindEvent(EventListener<C, arg...>* listener);

    template <class C, typename ...arg>
    void UnbindListener(const std::string& eventName, const C* listenerToUnbind);

    void UnbindAllListeners(const std::string& eventName);

    template <typename ...arg>
    void CallEvent(const std::string& eventName, arg ... a);

    unsigned int GetEventCount() const;

    unsigned int GetListenerCount(const std::string& eventName) const;

protected:
	
    std::map<std::string, std::vector<IEventListener*>> eventList;

};
