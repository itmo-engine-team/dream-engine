#pragma once

#include "BTGameNodeLogic.h"

class Actor;
class ACF_TargetTag;

class BTGTargetNear : public BTGameNodeLogic
{

public:

    BTGTargetNear() = delete;
    BTGTargetNear(BTGameNodeWithChild* parentNode, BehaviorTreeGame* behaviorTree);

    bool Run() override;

private:

    ACF_TargetTag* targetTagAC;

    bool checkTargetNear();
};

