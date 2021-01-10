#pragma once

#include "Param.h"

class ParamExtender
{

public:

    const std::unordered_map<std::string, BaseParam*>& GetParamMap() const;
    void AddParam(std::string name, BaseParam* param);
    void CopyParams(const std::unordered_map<std::string, BaseParam*>& paramMapToCopy);
    void UpdateParam(std::string name, const BaseParam* paramCopy);

protected:

    std::unordered_map<std::string, BaseParam*> paramMap;

    virtual void onParamUpdate(std::string name, BaseParam* param);

};

