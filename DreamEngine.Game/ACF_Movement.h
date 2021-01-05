#pragma once

#include "ActorComponentFixed.h"

class PathFinding;

class ACF_Movement : public ActorComponentFixed
{

public:

    ACF_Movement() = delete;
    ACF_Movement(ActorContext* context, Actor* actor);

private:

    PathFinding* pathFindingInst;

};

