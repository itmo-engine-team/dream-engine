#pragma once

#include "nlohmann/json.hpp"
#include <fstream>
#include <iomanip>

class JsonCreater
{
    using json = nlohmann::json;

public:
    void TestJsCreate(std::string objectName, std::string name, int age);
    

};
