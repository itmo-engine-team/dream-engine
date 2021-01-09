#pragma once

#include "Actor.h"

class NavMesh;
class ModelData;

class A_NavMesh : public Actor
{

public:

    A_NavMesh(ActorContext* context);

    NavMesh* GetNavMesh() const;

private:

    NavMesh* navMesh;

    void onUpdate() override;

};

