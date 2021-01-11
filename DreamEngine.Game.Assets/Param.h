#pragma once

#include "Serializable.h"
#include "ParamType.h"

class BaseParam : public Serializable
{

public:

    BaseParam(ParamType type) : type(type) {}
    BaseParam(BaseParam& param)
    {
        this->type = param.type;
        this->isDefault = param.isDefault;
    }

    ParamType GetType() const
    {
        return type;
    }

    bool IsDefault() const
    {
        return isDefault;
    }
    
    virtual BaseParam* Copy() = 0;
    virtual void Update(const BaseParam* paramCopy) = 0;

    Json toJson() override = 0;
    void fromJson(Json json) override = 0;

protected:

    bool isDefault = true;

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

    Param(Param& param) : BaseParam(param)
    {
        this->value = param.value;
        this->def = param.def;
    }

    virtual void Set(Type value)
    {
        this->value = value;
        isDefault = false;
    }

    virtual void SetDef()
    {
        value = def;
        isDefault = true;
    }

    Type Get() const
    {
        return value;
    }

    void Update(const BaseParam* paramCopy) override
    {
        if (paramCopy->IsDefault())
        {
            this->SetDef();
        }
        else
        {
            UpdateValue(paramCopy);
        }
    }

protected:

    Type value;
    Type def;

    virtual void UpdateValue(const BaseParam* paramCopy) = 0;

};

