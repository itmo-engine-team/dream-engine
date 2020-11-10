#include "AssetInfo.h"

AssetInfo::AssetInfo(const int id, const AssetType type) : id(id), type(type)
{

}

int AssetInfo::GetId() const
{
    return id;
}

AssetType AssetInfo::GetAssetType() const
{
    return type;
}
