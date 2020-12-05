#include "AssetInfo.h"

AssetInfo::AssetInfo(const AssetType type) : type(type)
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
