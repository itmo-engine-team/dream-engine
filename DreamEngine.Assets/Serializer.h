#pragma once

#include <filesystem>
#include <fstream>

#include "nlohmann/json.hpp"

using json = nlohmann::json;

class Serializer
{

public:

    virtual json ToJson() = 0;
    virtual Serializer* FromJson(std::filesystem::path pathToConfig) = 0;
};