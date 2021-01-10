#pragma once

#include "BTGameNodeLogic.h"

class Actor;

class BTGTargetNear : public BTGameNodeLogic
{

public:

    BTGTargetNear() = delete;
    BTGTargetNear(BTGameNodeWithChild* parentNode, BehaviorTreeGame* behaviorTree);

    bool Run() override;

private:

    Actor* targetActor = nullptr;
    float fieldOfView = 1;

    bool checkTargetNear();
};

