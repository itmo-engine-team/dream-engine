#pragma once

#include "nlohmann/json.hpp"

using Json = nlohmann::json;

class AssetService;

class Serializable
{

protected:

    friend AssetService;

    virtual Json toJson()
    {
        return {};
    }

    virtual void fromJson(Json json) = 0;

    template <typename type>
    void initVariable(Json json, std::string varName, type* var)
    {
        if (json.contains(varName))
            *var = json[varName].get<type>();
        else
            log(varName + " not found in json file");
    }

    void log(std::string message);

};