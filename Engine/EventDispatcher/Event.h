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
    typedef void(Class::* CallbackType)(arg...);

    // Constructor
    explicit Event(const std::string& name, C& cl, const CallbackType& cb) : EventName(name), Class(cl), CalledFunction(cb) {}

    // Get event name
    const std::string& GetName() const override { return this->eventName; }

    // Call function
    void Call(arg... a)
    {
        this->calledFunction(a...);
    }

private:
	
    std::string EventName;
    C& Class;
    CallbackType const CalledFunction;
};