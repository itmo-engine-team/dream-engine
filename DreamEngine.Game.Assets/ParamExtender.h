#pragma once

#include <map>
#include "Param.h"

class ParamExtender
{

public:

    const std::map<std::string, BaseParam*>& GetParamMap() const;
    void AddParam(std::string name, BaseParam* param);
    void CopyParams(const std::map<std::string, BaseParam*>& paramMapToCopy);
    void UpdateParam(std::string name, const BaseParam* paramCopy);

protected:

    std::map<std::string, BaseParam*> paramMap;

    virtual void onParamUpdate(std::string name, BaseParam* param);

};

