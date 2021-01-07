#pragma once

#include "ActorComponentFixed.h"

#include "PathFinding.h"

class ACF_Movement : public ActorComponentFixed
{

public:

    ACF_Movement() = delete;
    ACF_Movement(ActorContext* context, Actor* actor);

    bool MoveTo(Vector3 targetLocation);

    float GetSpeed();
    void SetSpeed(float newSpeed);
    bool GetCanMoveByDiagonal();
    void SetCanMoveByDiagonal(bool canMoveByDiagonal);

private:

    PathFinding* pathFindingInst;
    std::vector<NavMeshPolygon*> path;
    float actorSpeed = 0.01f;
    bool moveByDiagonal = false;

    bool pathIsValid();
    void changeLocation();
};

