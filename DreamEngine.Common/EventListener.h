#pragma once

#include <string>

class IEventListener
{

public:

    virtual ~IEventListener() = default;

};

template <typename ...arg>
class BaseEventListener : public IEventListener
{

public:

    virtual const std::string& GetEventName() const = 0;
    virtual void Call(arg... a) = 0;

};

template <class C, typename ...arg>
class EventListener : public BaseEventListener<arg...>
{

public:
	
    // Alias for template callback
    typedef void(C::* CallbackType)(arg...);

    // Constructor
    explicit EventListener(const std::string& name, C* listener, const CallbackType& callbackType)
        : eventName(name), listener(listener), calledFunction(callbackType) {}

    const std::string& GetEventName() const override { return eventName; }
    const C* GetListener() const { return listener; }

    // Call function
    void Call(arg... a) override
    {
        (listener->*calledFunction)(a...);
    }

private:
	
    std::string eventName;
    C* listener;
    CallbackType const calledFunction;

};