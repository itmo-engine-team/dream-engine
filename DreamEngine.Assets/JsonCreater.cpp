#include "JsonCreater.h"

void JsonCreater::TestJsCreate(std::string objectName, std::string name, int age)
{
    json j;
    j["Object name"] = objectName;
    j["Name"] = name;
    j["Age"] = age;

    std::ofstream file("Person.json");
    file << std::setw(4) << j << std::endl;
}
