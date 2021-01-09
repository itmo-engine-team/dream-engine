#include "ACF_AI.h"

#include "BTAssetInfo.h"

ACF_AI::ACF_AI(Actor* actor) : ActorComponentFixed(actor)
{
    btAssetParam = new ParamAsset(AssetType::BT);
    AddParam("BT Asset", btAssetParam);
}

BehaviorTreeGame* ACF_AI::GetBehaviorTree()
{
    return behaviorTree;
}

void ACF_AI::onInit()
{
    if (btAssetParam->IsDefault()) return;

    BTAssetInfo* assetInfo = dynamic_cast<BTAssetInfo*>(actor->GetContext()->GetAssetManager()->GetAssetByType(btAssetParam->GetAssetType(), btAssetParam->Get()));
    behaviorTree = new BehaviorTreeGame(actor, assetInfo->GetBTEditor());
}
