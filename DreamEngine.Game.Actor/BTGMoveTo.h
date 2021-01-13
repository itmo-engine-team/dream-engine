#pragma once

#include "BTGameNodeLogic.h"
#include "SimpleMath.h"

class Actor;
class ACF_Movement;
class ACF_TargetTag;

using namespace DirectX::SimpleMath;

class BTGMoveTo : public BTGameNodeLogic
{

public:

    BTGMoveTo() = delete;
    BTGMoveTo(BTGameNodeWithChild* parentNode, BehaviorTreeGame* behaviorTree);

    bool Run() override;

    Vector3 GetTargetLocation() const;
    void SetTargetLocation(Vector3 targetLocation);

private:

    Vector3 targetLocation = {0, 0, 0};
    ACF_TargetTag* targetTagComponent = nullptr;
    ACF_Movement* movementComponent;
};

