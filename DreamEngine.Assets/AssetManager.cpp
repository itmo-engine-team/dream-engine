#include "AssetManager.h"

AssetManager::AssetManager()
{
    for (auto assetType : ALL_ASSET_TYPES)
    {
        assetLastIdMap[assetType] = 0;
    }

    // TODO init AssetInfo
}

AssetManager::~AssetManager()
{

}
