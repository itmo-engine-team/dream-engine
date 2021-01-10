#pragma once

#include "Actor.h"

class NavMesh;
class ModelData;
class ACS_StaticModel;

class A_NavMesh : public Actor
{

public:

    A_NavMesh(ActorContext* context);

    NavMesh* GetNavMesh() const;

private:

    NavMesh* navMesh;
    ACS_StaticModel* staticModelComponent;

    void onUpdate() override;

};

