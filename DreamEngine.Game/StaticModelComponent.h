#pragma once

#include "ActorComponentScene.h"
#include "ModelData.h"
#include "MeshObject.h"

class StaticModelComponent : public ActorComponentScene
{

public:

    StaticModelComponent(Game* game, Actor* actor, Transform* transform, ModelData* modelData);

protected:

    ModelData* modelData;

    std::vector<MeshObject*> meshObjects;

    void onDraw() override;
    void onDrawShadowMap() override;

};

