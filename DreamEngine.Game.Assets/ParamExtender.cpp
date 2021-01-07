#include "ParamExtender.h"

const std::map<std::string, BaseParam*>& ParamExtender::GetParamMap() const
{
    return paramMap;
}

void ParamExtender::AddParam(std::string name, BaseParam* param)
{
    paramMap[name] = param;
}

void ParamExtender::CopyParams(const std::map<std::string, BaseParam*>& paramMapToCopy)
{
    for (auto iter : paramMapToCopy)
    {
        if (paramMap.find(iter.first) == paramMap.end())
            paramMap[iter.first] = iter.second->Copy();
    }
}
