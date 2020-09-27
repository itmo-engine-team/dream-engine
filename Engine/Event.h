#pragma once

#include <functional>
#include <string>

class IEvent
{
public:
	
    virtual const std::string& GetName() const = 0;
    virtual  ~IEvent() {}
};


template <class Class, typename ...arg>
class Event : public IEvent
{
public:
	
    // Alias for template callback
    typedef std::function<void(Class&, arg...)> CallbackType;

    // Constructor
    explicit Event(const std::string& name, const CallbackType& cb) : eventName(name), calledFunction(cb) {}

    // Get event name
    const std::string& GetName() const override { return this->eventName; }

    // Call function
    void Call(Class& t, arg... a)
    {
        this->calledFunction(t, a...);
    }

private:
	
    // Event Name
    std::string eventName;

    CallbackType const calledFunction;
};