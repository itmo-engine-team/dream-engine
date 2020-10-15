#include "pch.h"

#include "../Engine/EventDispatcher/EventDispatcher.h"
//#include "../Engine/EventDispatcher/EventDispatcher.cpp"

class EventDispatcherTestClass : public ::testing::Test
{
public:

    EventDispatcher* eventDispatcher = nullptr;

    EventDispatcherTestClass() = default;
    ~EventDispatcherTestClass() = default;

    void SetUp() override
    {
        eventDispatcher = new EventDispatcher();
    }

    void TearDown() override
    {
        delete eventDispatcher;
        eventDispatcher = nullptr;
    }

};

class EventListenerTestClass
{

public:

    bool Switcher = false;
    int Value = 0;

    EventListenerTestClass() = default;
    ~EventListenerTestClass() = default;

    void Switch()
    {
        Switcher = !Switcher;
    }

    void SetValue(const int value)
    {
        Value = value;
    }

};

TEST(EventDispatcherTest, DeleteTest)
{
    auto* eventDispatcher = new EventDispatcher();

    auto* listener1 = new EventListenerTestClass();
    eventDispatcher->BindEvent(new EventListener<EventListenerTestClass, int>(
        "SetIntEvent", listener1, &EventListenerTestClass::SetValue));

    auto* listener2 = new EventListenerTestClass();
    eventDispatcher->BindEvent(new EventListener<EventListenerTestClass>(
        "SwitchEvent", listener2, &EventListenerTestClass::Switch));

    auto* listener3 = new EventListenerTestClass();
    eventDispatcher->BindEvent(new EventListener<EventListenerTestClass>(
        "SwitchEvent", listener3, &EventListenerTestClass::Switch));

    delete eventDispatcher;
}

TEST_F(EventDispatcherTestClass, BindTest) {
    auto* listener = new EventListenerTestClass();
    ASSERT_EQ(listener->Switcher, false);

    eventDispatcher->BindEvent(new EventListener<EventListenerTestClass>(
            "SwitchEvent", listener, &EventListenerTestClass::Switch));

    eventDispatcher->CallEvent("SwitchEvent");
    ASSERT_EQ(listener->Switcher, true);
}

TEST_F(EventDispatcherTestClass, CallWithArgTest) {
    auto* listener = new EventListenerTestClass();

    eventDispatcher->BindEvent(new EventListener<EventListenerTestClass, int>(
        "SetIntEvent", listener, &EventListenerTestClass::SetValue));

    eventDispatcher->CallEvent("SetIntEvent", 5);

    ASSERT_EQ(listener->Value, 5);
}

TEST_F(EventDispatcherTestClass, CallNotExistEventTest) {
    eventDispatcher->CallEvent("NotExistEvent", 5);
}

TEST_F(EventDispatcherTestClass, UnbindFirstListenerTest) {
    // Test listener 1
    auto* listener1 = new EventListenerTestClass();
    ASSERT_EQ(listener1->Switcher, false);

    eventDispatcher->BindEvent(new EventListener<EventListenerTestClass>(
        "SwitchEvent", listener1, &EventListenerTestClass::Switch));

    // Test listener 2
    auto* listener2 = new EventListenerTestClass();
    ASSERT_EQ(listener2->Switcher, false);

    eventDispatcher->BindEvent(new EventListener<EventListenerTestClass>(
        "SwitchEvent", listener2, &EventListenerTestClass::Switch));

    // Test listener 3
    auto* listener3 = new EventListenerTestClass();
    ASSERT_EQ(listener3->Switcher, false);

    eventDispatcher->BindEvent(new EventListener<EventListenerTestClass>(
        "SwitchEvent", listener3, &EventListenerTestClass::Switch));

    // Unbind listener 1 (first listener)
    eventDispatcher->UnbindListener<EventListenerTestClass>("SwitchEvent", listener1);

    eventDispatcher->CallEvent("SwitchEvent");

    ASSERT_EQ(listener1->Switcher, false);
    ASSERT_EQ(listener2->Switcher, true);
    ASSERT_EQ(listener3->Switcher, true);

    ASSERT_EQ(eventDispatcher->GetListenerCount("SwitchEvent"), 2);
}

TEST_F(EventDispatcherTestClass, UnbindMiddleListenerTest) {
    // Test listener 1
    auto* listener1 = new EventListenerTestClass();
    ASSERT_EQ(listener1->Switcher, false);

    eventDispatcher->BindEvent(new EventListener<EventListenerTestClass>(
        "SwitchEvent", listener1, &EventListenerTestClass::Switch));

    // Test listener 2
    auto* listener2 = new EventListenerTestClass();
    ASSERT_EQ(listener2->Switcher, false);

    eventDispatcher->BindEvent(new EventListener<EventListenerTestClass>(
        "SwitchEvent", listener2, &EventListenerTestClass::Switch));

    // Test listener 3
    auto* listener3 = new EventListenerTestClass();
    ASSERT_EQ(listener3->Switcher, false);

    eventDispatcher->BindEvent(new EventListener<EventListenerTestClass>(
        "SwitchEvent", listener3, &EventListenerTestClass::Switch));

    // Unbind listener 2 (middle listener)
    eventDispatcher->UnbindListener<EventListenerTestClass>("SwitchEvent", listener2);

    eventDispatcher->CallEvent("SwitchEvent");

    ASSERT_EQ(listener1->Switcher, true);
    ASSERT_EQ(listener2->Switcher, false);
    ASSERT_EQ(listener3->Switcher, true);

    ASSERT_EQ(eventDispatcher->GetListenerCount("SwitchEvent"), 2);
}

TEST_F(EventDispatcherTestClass, UnbindLastListenerTest) {
    // Test listener 1
    auto* listener1 = new EventListenerTestClass();
    ASSERT_EQ(listener1->Switcher, false);

    eventDispatcher->BindEvent(new EventListener<EventListenerTestClass>(
        "SwitchEvent", listener1, &EventListenerTestClass::Switch));

    // Test listener 2
    auto* listener2 = new EventListenerTestClass();
    ASSERT_EQ(listener2->Switcher, false);

    eventDispatcher->BindEvent(new EventListener<EventListenerTestClass>(
        "SwitchEvent", listener2, &EventListenerTestClass::Switch));

    // Test listener 3
    auto* listener3 = new EventListenerTestClass();
    ASSERT_EQ(listener3->Switcher, false);

    eventDispatcher->BindEvent(new EventListener<EventListenerTestClass>(
        "SwitchEvent", listener3, &EventListenerTestClass::Switch));

    // Unbind listener 3 (last listener)
    eventDispatcher->UnbindListener<EventListenerTestClass>("SwitchEvent", listener3);

    eventDispatcher->CallEvent("SwitchEvent");

    ASSERT_EQ(listener1->Switcher, true);
    ASSERT_EQ(listener2->Switcher, true);
    ASSERT_EQ(listener3->Switcher, false);

    ASSERT_EQ(eventDispatcher->GetListenerCount("SwitchEvent"), 2);
}

TEST_F(EventDispatcherTestClass, UnbindNotExistListenerTest) {
    // Test listener 1
    auto* listener1 = new EventListenerTestClass();
    ASSERT_EQ(listener1->Switcher, false);

    eventDispatcher->BindEvent(new EventListener<EventListenerTestClass>(
        "SwitchEvent", listener1, &EventListenerTestClass::Switch));

    // Test listener 2
    auto* listener2 = new EventListenerTestClass();
    ASSERT_EQ(listener2->Switcher, false);

    eventDispatcher->BindEvent(new EventListener<EventListenerTestClass>(
        "SwitchEvent", listener2, &EventListenerTestClass::Switch));

    // Test listener 3
    auto* listener3 = new EventListenerTestClass();
    ASSERT_EQ(listener3->Switcher, false);

    eventDispatcher->BindEvent(new EventListener<EventListenerTestClass>(
        "SwitchEvent", listener3, &EventListenerTestClass::Switch));

    // Unbind not exist listener
    auto* notExistListener = new EventListenerTestClass();
    eventDispatcher->UnbindListener<EventListenerTestClass>("SwitchEvent", notExistListener);

    eventDispatcher->CallEvent("SwitchEvent");

    ASSERT_EQ(listener1->Switcher, true);
    ASSERT_EQ(listener2->Switcher, true);
    ASSERT_EQ(listener3->Switcher, true);

    ASSERT_EQ(eventDispatcher->GetListenerCount("SwitchEvent"), 3);
}

TEST_F(EventDispatcherTestClass, UnbindNotExistEventTest) {
    // Unbind not exist listener from not exist event
    auto* notExistListener = new EventListenerTestClass();
    eventDispatcher->UnbindListener<EventListenerTestClass>("NotExistEvent", notExistListener);
}

TEST_F(EventDispatcherTestClass, UnbindAllTest) {
    // Test listener 1
    auto* listener1 = new EventListenerTestClass();
    ASSERT_EQ(listener1->Switcher, false);

    eventDispatcher->BindEvent(new EventListener<EventListenerTestClass>(
        "SwitchEvent", listener1, &EventListenerTestClass::Switch));

    // Test listener 2
    auto* listener2 = new EventListenerTestClass();
    ASSERT_EQ(listener2->Switcher, false);

    eventDispatcher->BindEvent(new EventListener<EventListenerTestClass>(
        "SwitchEvent", listener2, &EventListenerTestClass::Switch));

    // Test listener 3
    auto* listener3 = new EventListenerTestClass();
    ASSERT_EQ(listener3->Switcher, false);

    eventDispatcher->BindEvent(new EventListener<EventListenerTestClass>(
        "SwitchEvent", listener3, &EventListenerTestClass::Switch));

    // Unbind all
    eventDispatcher->UnbindAllListeners("SwitchEvent");

    eventDispatcher->CallEvent("SwitchEvent");

    ASSERT_EQ(listener1->Switcher, false);
    ASSERT_EQ(listener2->Switcher, false);
    ASSERT_EQ(listener3->Switcher, false);

    ASSERT_EQ(eventDispatcher->GetListenerCount("SwitchEvent"), 0);
}

TEST_F(EventDispatcherTestClass, UnbindAllNotExistEventTest) {
    // Unbind all
    eventDispatcher->UnbindAllListeners("NotExistEvent");
    ASSERT_EQ(eventDispatcher->GetListenerCount("NotExistEvent"), 0);
}