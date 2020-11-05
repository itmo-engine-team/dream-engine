#include "JsonReader.h"

#include <iostream>

void JsonReader::TestJsRead()
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
