#include "pch.h"

#include "nlohmann/json.hpp"
#include <fstream>
#include <iostream>
#include <iomanip>

class JsonTest
{
    using json = nlohmann::json;
public: 
    void JsonTest::TestJsRead()
    {
        std::ifstream file("Person.json");
        json j;

        file >> j;

        std::string objectName;
        std::string name;
        int age = 0;

        if (j.find("Object name") != j.end())
        {
            objectName = j["Object name"];
        }

        if (j.find("Name") != j.end())
        {
            name = j["Name"];
        }

        if (j.find("Age") != j.end())
        {
            age = j["Age"].get<int>();
        }

        std::cout << j << "\n";
        std::cout << objectName << "\n";
        std::cout << name << "\n";
        std::cout << age;
    }

    void JsonTest::TestJsCreate(std::string objectName, std::string name, int age)
    {
        json j;
        j["Object name"] = objectName;
        j["Name"] = name;
        j["Age"] = age;

        std::ofstream file("Person.json");
        file << std::setw(4) << j << std::endl;
    }
};

TEST(JSonTest, CreateTest)
{
    JsonTest* jsonCreater = new JsonTest();
    jsonCreater->TestJsCreate("Person", "Alex", 25);
}

TEST(JSonTest, ReadTest)
{
    JsonTest* jsonReader = new JsonTest();
    jsonReader->TestJsRead();
}