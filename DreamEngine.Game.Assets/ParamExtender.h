#pragma once

#include <map>
#include "Param.h"

class ParamExtender
{

public:

    const std::map<std::string, BaseParam*>& GetParamMap() const;
    void AddParam(std::string name, BaseParam* param);

protected:

    std::map<std::string, BaseParam*> paramMap;


};

