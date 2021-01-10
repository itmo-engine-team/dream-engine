#include "ParamExtender.h"

const std::unordered_map<std::string, BaseParam*>& ParamExtender::GetParamMap() const
{
    return paramMap;
}

void ParamExtender::AddParam(std::string name, BaseParam* param)
{
    paramMap[name] = param;
}

void ParamExtender::CopyParams(const std::unordered_map<std::string, BaseParam*>& paramMapToCopy)
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

Json ParamExtender::toJson()
{
    Json json = Serializable::toJson();

    for (auto paramIter : paramMap)
    {
        json[paramIter.first] = paramIter.second->toJson();
    }

    return json;
}

void ParamExtender::fromJson(Json json)
{
    for (auto paramJsonItem : json.items())
    {
        paramJsonItem.key()
    }
}

void ParamExtender::onParamUpdate(std::string name, BaseParam* param)
{

}
