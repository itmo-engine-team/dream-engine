#pragma once

#include <functional>
#include <string>

class IEvent
{
public:
	
    virtual const std::string& getName() const = 0;
    virtual  ~IEvent() {}
};


template <class Class, typename ...arg>
class Event : public IEvent
{
public:
	
    //Alias for template callback
    typedef std::function<void(Class&, arg...)> CallbackType;

    //Constructor
    explicit Event(const std::string& name, const CallbackType& cb) : EventName(name), CalledFunction(cb) {}

    //Get event name
    const std::string& getName() const override { return this->EventName; }

    //Call function
    void Call(Class& t, arg... a)
    {
        this->CalledFunction(t, a...);
    }

private:
	
    //Event Name
    std::string EventName;

    CallbackType const CalledFunction;
};