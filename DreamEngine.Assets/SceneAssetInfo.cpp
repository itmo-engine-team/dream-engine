#include "SceneAssetInfo.h"

SceneAssetInfo::SceneAssetInfo() : AssetInfo(AssetType::Scene)
{

}

SceneAssetInfo::SceneAssetInfo(SceneAssetInfo& assetInfo) : AssetInfo(assetInfo)
{

}

Json SceneAssetInfo::toJson()
{
    Json json = AssetInfo::toJson();

    return json;
}

void SceneAssetInfo::fromJson(Json json)
{
    AssetInfo::fromJson(json);
}
