#pragma once

#include "Serializable.h"
#include "ParamType.h"

class BaseParam : public Serializable
{

public:

    BaseParam(ParamType type) : type(type) {}

    ParamType GetType() const
    {
        return type;
    }

private:

    ParamType type;

};

template<typename Type>
class Param : public BaseParam
{

public:

    Param(ParamType type, Type def) : BaseParam(type)
    {
        this->def = def;
        this->value = def;
    }

    void Set(Type value)
    {
        this->value = value;
    }

    Type Get() const
    {
        return value;
    }

    Json toJson() override
    {
        Json json = Serializable::toJson();

        json["value"] = value;
        json["def"] = def;

        return json;
    }

    void fromJson(Json json) override
    {
        initVariable(json, "value", &value);
        initVariable(json, "def", &def);
    }

protected:

    Type value;
    Type def;

};

