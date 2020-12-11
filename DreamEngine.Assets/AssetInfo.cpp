#include "AssetInfo.h"

AssetInfo::AssetInfo(const AssetType type) : type(type)
{

}

AssetInfo::AssetInfo(AssetInfo& assetInfo)
{
    type = assetInfo.type;
}

AssetNode* AssetInfo::GetAssetNode() const
{
    return node;
}

void AssetInfo::SetAssetNode(AssetNode* node)
{
    this->node = node;
}

unsigned int AssetInfo::GetId() const
{
    return id;
}


Json AssetInfo::toJson()
{
    Json json = Serializable::toJson();

    json["id"] = id;
    json["type"] = type;
    json["name"] = name;

    return json;
}

void AssetInfo::fromJson(Json json)
{
    Serializable::fromJson(json);

    initVariable(json, "id", &id);
    initVariable(json, "type", &type);
    initVariable(json, "name", &name);
}

void AssetInfo::setId(unsigned int id)
{
    this->id = id;
}

AssetType AssetInfo::GetAssetType() const
{
    return type;
}

const std::string& AssetInfo::GetName() const
{
    return name;
}

void AssetInfo::SetName(std::string& name)
{
    this->name = name;
}
