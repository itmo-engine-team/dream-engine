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

void ParamExtender::UpdateParam(std::string name, const BaseParam* paramCopy)
{
    auto iter = paramMap.find(name);
    if (iter == paramMap.end())
        return;

    iter->second->Update(paramCopy);
    onParamUpdate(name, iter->second);
}

void ParamExtender::onParamUpdate(std::string name, BaseParam* param)
{

}
