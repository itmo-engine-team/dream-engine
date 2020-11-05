#pragma once

#include "nlohmann/json.hpp"
#include <fstream>

class JsonReader
{
    using json = nlohmann::json;

public:
    void TestJsRead();
};