#pragma once

#include "BTGameNodeLogic.h"
#include "SimpleMath.h"

class ACF_Movement;

using namespace DirectX::SimpleMath;

class BTGMoveTo : public BTGameNodeLogic
{

public:

    BTGMoveTo() = delete;
    BTGMoveTo(BTGameNodeWithChild* parentNode, BehaviorTreeGame* behaviorTree);

    bool Run() override;

    Vector3 GetTargetLocation() const;
    void SetTargetPosition(Vector3 targetLocation);

    float GetReachRadius() const;
    void SetReachRadius(float reachRadius);

private:

    Vector3 target = {0, 0, 0};
    ACF_Movement* movementComponent;
    float reachRadius = 0;
};

