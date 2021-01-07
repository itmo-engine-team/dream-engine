#include "ParamExtender.h"

const std::map<std::string, BaseParam*>& ParamExtender::GetParamMap() const
{
    return paramMap;
}

void ParamExtender::AddParam(std::string name, BaseParam* param)
{
    paramMap[name] = param;
}
