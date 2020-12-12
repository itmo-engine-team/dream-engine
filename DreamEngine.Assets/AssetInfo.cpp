#include "AssetInfo.h"

#include "AssetInfoFactory.h"

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
    json["type"] = AssetInfoFactory::GetAssetTypeStringName(type);
    json["name"] = name;

    return json;
}

void AssetInfo::fromJson(Json json)
{
    std::string stringType;
    initVariable(json, "type", &stringType);
    type = AssetInfoFactory::GetAssetTypeByString(stringType);

    initVariable(json, "id", &id);
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
