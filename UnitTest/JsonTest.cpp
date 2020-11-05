#include "pch.h"

#include "JsonCreater.h"
#include "JsonReader.h"

TEST(JsonTest, CreateTest)
{
    JsonCreater* jsonCreater = new JsonCreater();
    jsonCreater->TestJsCreate("Person", "Alex", 25);
}

TEST(JsonTest, ReadTest)
{
    JsonReader* jsonReader = new JsonReader();
    jsonReader->TestJsRead();
}