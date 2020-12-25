#pragma once

#include "Actor.h"

class NavMesh;

class A_NavMesh : public Actor
{

public:

    A_NavMesh(ActorContext* context, Transform* transform);

private:

    NavMesh* navMesh;

};

