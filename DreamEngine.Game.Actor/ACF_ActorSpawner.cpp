#include "ACF_ActorSpawner.h"
#include "ParamFloat.h"
#include "ParamAsset.h"
#include "DeltaTimeHandler.h"
#include <random>
#include "GameAssetManager.h"
#include "Transform.h"

ACF_ActorSpawner::ACF_ActorSpawner(Actor* actor) : ActorComponentFixed(actor)
{
    spawnAsset = new ParamAsset(AssetType::Actor);
    AddParam("Spawn Actor", spawnAsset);
    timeToStart = new ParamFloat();
    AddParam("Time to Start", timeToStart);
    timeToSpawn = new ParamFloat();
    AddParam("Time to Spawn", timeToSpawn);
    randomDistribution = new ParamFloat();
    AddParam("Random Distribution", randomDistribution);
}

void ACF_ActorSpawner::onInit()
{
    currentTimeToSpawn = timeToStart->Get();
}

void ACF_ActorSpawner::onUpdate()
{
    if (currentTimeToSpawn < 0)
    {
        actor->GetContext()->GetGameAssetManager()->CreateActorByAsset(
            actor->GetContext(), spawnAsset->Get(), actor->GetTransform()->GetWorldPosition());

        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist10(1, 10);

        float random = dist10(rng) / 10 * randomDistribution->Get();

        currentTimeToSpawn = timeToSpawn->Get() + random;
        return;
    }

    currentTimeToSpawn -= actor->GetContext()->GetDeltaTimeHandler()->GetDeltaTime();
}
