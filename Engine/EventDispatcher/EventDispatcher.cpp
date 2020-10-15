#include "EventDispatcher.h"

#include "ErrorLogger/ErrorLogger.h"

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

template <class C, typename ... arg>
void EventDispatcher::BindEvent(EventListener<C, arg...>* listener)
{
    if (!listener) return;

    eventList[listener->GetEventName()].push_back(listener);
}

template <class C, typename ... arg>
void EventDispatcher::UnbindListener(const std::string& eventName, const C* listenerToUnbind)
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
void EventDispatcher::CallEvent(const std::string& eventName, arg ... a)
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
            //const std::string message = "Can't call listener for event " + eventName;
            ErrorLogger::Log(Error, "Can't call listener for event ");
        }
    }
}


