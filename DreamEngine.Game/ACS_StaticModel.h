#pragma once

#include "ActorComponentScene.h"
#include "ModelData.h"
#include "MeshObject.h"

class ACS_StaticModel : public ActorComponentScene
{

public:

    ACS_StaticModel(ActorContext* context, Actor* actor, Transform* transform, ModelData* modelData);

protected:

    ModelData* modelData;

    std::vector<MeshObject*> meshObjects;

    void onDraw() override;
    void onDrawShadowMap() override;

};

class ACS_Creator_StaticModel : public ACS_Creator
{

public:

    ActorComponentScene* Create(Actor* actor, ActorComponentSceneInfo* actorInfo) override
    {
        return new ACS_StaticModel(actor->GetContext(), actor,
            new Transform(actorInfo->GetTransformInfo()->GetPosition()), new ModelData());
    }

};