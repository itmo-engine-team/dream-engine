#include "BTAssetInfo.h"

BTAssetInfo::BTAssetInfo() : AssetInfo(AssetType::BT)
{

}

BTAssetInfo::BTAssetInfo(BTAssetInfo& assetInfo) : AssetInfo(assetInfo)
{

}

BTAssetInfo::~BTAssetInfo()
{

}

Json BTAssetInfo::toJson()
{
    Json json = AssetInfo::toJson();

    return json;
}

void BTAssetInfo::fromJson(Json json)
{
    AssetInfo::fromJson(json);
}
