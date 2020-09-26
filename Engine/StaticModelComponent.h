#pragma once

#include "SceneComponent.h"
#include "ModelData.h"
#include "MeshObject.h"

class StaticModelComponent : public SceneComponent
{

public:

    StaticModelComponent(Engine* engine, Actor* actor, Transform* transform, ModelData* modelData);

protected:

    ModelData* modelData;

    std::vector<MeshObject*> meshObjects;

    void onDraw() override;

};

