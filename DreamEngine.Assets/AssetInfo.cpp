#include "AssetInfo.h"

AssetInfo::AssetInfo(const AssetType type) : type(type)
{

}

AssetInfo::AssetInfo(AssetInfo& assetInfo)
{
    type = assetInfo.type;
}

AssetInfo::~AssetInfo()
{
}

unsigned int AssetInfo::GetId() const
{
    return id;
}


void AssetInfo::setId(unsigned int id)
{
    this->id = id;
}

AssetType AssetInfo::GetAssetType() const
{
    return type;
}
