#include "ACF_Movement.h"

#include "PathFinding.h"

ACF_Movement::ACF_Movement(ActorContext* context, Actor* actor) : ActorComponentFixed(context, actor)
{
    pathFindingInst = new PathFinding();
}