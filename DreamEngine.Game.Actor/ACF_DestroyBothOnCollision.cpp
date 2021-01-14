#include "ACF_DestroyBothOnCollision.h"
#include "GameAssetManager.h"

ACF_DestroyBothOnCollision::ACF_DestroyBothOnCollision(Actor* actor)
    : ACF_DestroyTargetOnCollision(actor)
{

}

void ACF_DestroyBothOnCollision::onTargetCollision(Actor* targetActor)
{
    ACF_DestroyTargetOnCollision::onTargetCollision(targetActor);

    actor->GetContext()->GetGameAssetManager()->DeleteActor(actor);
}
