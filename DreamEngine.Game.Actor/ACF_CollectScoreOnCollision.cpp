#include "ACF_CollectScoreOnCollision.h"

#include "GameAssetManager.h"
#include "ParamInt.h"

ACF_CollectScoreOnCollision::ACF_CollectScoreOnCollision(Actor* actor)
    : ACF_DestroyTargetOnCollision(actor)
{
    scoreOnCollectParam = new ParamInt();
    AddParam("Score On Collect", scoreOnCollectParam);
}

void ACF_CollectScoreOnCollision::onTargetCollision(Actor* targetActor)
{
    ACF_DestroyTargetOnCollision::onTargetCollision(targetActor);

    actor->GetContext()->GetGameAssetManager()->AddScore(scoreOnCollectParam->Get());
}
