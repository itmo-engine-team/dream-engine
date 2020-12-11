#include "AssetInfo.h"

AssetInfo::AssetInfo(const AssetType type) : type(type)
{

}

AssetInfo::AssetInfo(AssetInfo& assetInfo)
{
    type = assetInfo.type;
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

    return json;
}

void AssetInfo::fromJson(Json json)
{
    initVariable(json, "id", &id);
    initVariable(json, "type", &id);
}

void AssetInfo::setId(unsigned int id)
{
    this->id = id;
}

AssetType AssetInfo::GetAssetType() const
{
    return type;
}
