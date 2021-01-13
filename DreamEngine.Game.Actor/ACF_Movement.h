#pragma once

#include "ActorComponentFixed.h"

#include "PathFinding.h"

class ParamFloat;

class ACF_Movement : public ActorComponentFixed
{

public:

    ACF_Movement() = delete;
    ACF_Movement(Actor* actor);

    bool MoveTo(Vector3 targetLocation);

    float GetSpeed();

    bool GetCanMoveByDiagonal();
    void SetCanMoveByDiagonal(bool canMoveByDiagonal);

private:

    PathFinding* pathFindingInst;
    std::vector<NavMeshPolygon*> path;
    ParamFloat* actorSpeed;
    bool moveByDiagonal = false;
    int polygonCount = 0;

    bool pathIsValid();
    void changeLocation();
};

class ACF_Creator_Movement : public ACF_Creator
{

public:

    ActorComponentFixed* Create(Actor* actor, ActorComponentFixedInfo* actorInfo) override
    {
        return new ACF_Movement(actor);
    }

};