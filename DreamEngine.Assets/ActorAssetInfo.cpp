#include "ActorAssetInfo.h"

ActorAssetInfo::ActorAssetInfo() : AssetInfo(AssetType::Actor)
{

}

ActorAssetInfo::ActorAssetInfo(ActorAssetInfo& assetInfo) : AssetInfo(assetInfo)
{

}

Json ActorAssetInfo::toJson()
{
    Json json = AssetInfo::toJson();

    return json;
}

void ActorAssetInfo::fromJson(Json json)
{
    AssetInfo::fromJson(json);
}
