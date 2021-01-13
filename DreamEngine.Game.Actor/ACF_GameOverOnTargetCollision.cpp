#include "ACF_GameOverOnTargetCollision.h"
#include "GameAssetManager.h"

ACF_GameOverOnTargetCollision::ACF_GameOverOnTargetCollision(Actor* actor)
    : ACF_OnTargetCollision(actor)
{

}

void ACF_GameOverOnTargetCollision::onTargetCollision(Actor* targetActor)
{
    actor->GetContext()->GetGameAssetManager()->GameOver(false);
}
