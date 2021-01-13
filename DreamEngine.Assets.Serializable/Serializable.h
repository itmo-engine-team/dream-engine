#pragma once

#include "JsonUtils.h"

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
    static void initVariable(Json json, std::string varName, type* var, bool canNotExist = false)
    {
        if (json.contains(varName))
        {
            *var = json[varName].get<type>();
            return;
        }

        if (!canNotExist)
            log(varName + " not found in json file\n" + json.dump());
    }

    template <typename type>
    static Json arrayToJson(type args...)
    {
        Json json = Json::array();

        for (type var : args)
        {
            json.push_back(json);
        }

        return json;
    }

    template <typename type>
    static type tryGet(Json json, std::string varName, type def)
    {
        return json.contains(varName) ? json[varName].get<type>() : def;
    }

    static void log(std::string message);

};