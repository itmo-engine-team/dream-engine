#include "pch.h"

#include "EventDispatcher/EventDispatcher.h"

class TestClass
{
public:
    void testFunc()
    {
        std::cout << "test";
    }
};

TEST(JobSysTest, Main) {
   // JobSystemTest();
    TestClass* testClass = new TestClass();
    EventDispatcher* test = new EventDispatcher();
    test->BindEvent(new Event<TestClass>("test", *testClass, &TestClass::testFunc));
    test->CallEvent("test");
    EXPECT_EQ(1, 1);
    EXPECT_TRUE(true);
}