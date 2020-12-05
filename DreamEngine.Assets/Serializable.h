#pragma once

#include "nlohmann/json.hpp"

using Json = nlohmann::json;

class AssetService;

class Serializable
{

protected:

    friend AssetService;

    virtual Json ToJson()
    {
        return {};
    }

    virtual void FromJson(Json json) = 0;
};