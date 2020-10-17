#include "pch.h"
#include "EventDispatcher.h"

EventDispatcher::~EventDispatcher()
{
    for (auto event : eventList)
    {
        for (auto e : event.second)
            delete e;
        event.second.clear();
    }
    eventList.clear();
}

void EventDispatcher::UnbindAllListeners(const std::string& eventName)
{
    auto eventIterator = eventList.find(eventName);

    // Check EventIterator valid
    if (eventIterator == eventList.end()) return;

    while (!eventIterator->second.empty())
    {
        auto listenerIterator = eventIterator->second.begin();
        auto* listener = *listenerIterator;

        eventIterator->second.erase(listenerIterator);
        delete listener;
    }
    eventList.erase(eventIterator);
}

unsigned EventDispatcher::GetEventCount() const
{
    return eventList.size();
}

unsigned EventDispatcher::GetListenerCount(const std::string& eventName) const
{
    const auto eventIterator = eventList.find(eventName);
    return eventIterator != eventList.end() ? eventIterator->second.size() : 0;
}


