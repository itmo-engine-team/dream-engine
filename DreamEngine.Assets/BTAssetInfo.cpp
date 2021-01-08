#include "BTAssetInfo.h"

BTAssetInfo::BTAssetInfo() : AssetInfo(AssetType::BT)
{
    behaviorTree = new BehaviorTreeEditor();
}

BTAssetInfo::BTAssetInfo(BTAssetInfo& assetInfo) : AssetInfo(assetInfo)
{
    behaviorTree = assetInfo.behaviorTree;
}

BTAssetInfo::~BTAssetInfo()
{

}

BehaviorTreeEditor* BTAssetInfo::GetBTEditor()
{
    return behaviorTree;
}

Json BTAssetInfo::toJson()
{
    Json json = AssetInfo::toJson();

    json["BT"] = behaviorTree->toJson();

    return json;
}

void BTAssetInfo::fromJson(Json json)
{
    AssetInfo::fromJson(json);

    behaviorTree->fromJson(json["BT"]);
}
