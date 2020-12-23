#pragma once

#include "ActorComponentScene.h"
#include "ModelData.h"
#include "MeshObject.h"

class ACS_StaticModel : public ActorComponentScene
{

public:

    ACS_StaticModel(ActorContext context, Actor* actor, Transform* transform, ModelData* modelData);

protected:

    ModelData* modelData;

    std::vector<MeshObject*> meshObjects;

    void onDraw() override;
    void onDrawShadowMap() override;

};

