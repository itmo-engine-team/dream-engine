#pragma once

#include <string>

class IEvent
{
public:
    virtual  ~IEvent() {}
};

template <typename ...arg>
class BaseEvent : public IEvent
{
public:
    virtual const std::string& GetName() const = 0;
    virtual void Call(arg... a) = 0;
};

template <class C, typename ...arg>
class Event : public BaseEvent<arg...>
{
public:
	
    // Alias for template callback
    typedef void(C::* CallbackType)(arg...);

    // Constructor
    explicit Event(const std::string& name, C& nameClass, const CallbackType& callbackType) : eventName(name), className(nameClass), calledFunction(callbackType) {}

    // Get event name
    const std::string& GetName() const override { return eventName; }

    // Call function
    void Call(arg... a) override
    {
        (className.*calledFunction)(a...);
    }

private:
	
    std::string eventName;
    C& className;
    CallbackType const calledFunction;
};