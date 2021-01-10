#pragma once
#include "BTGameNodeLogic.h"
class BTGReturnFalse : public BTGameNodeLogic
{

public:

    BTGReturnFalse() = delete;
    BTGReturnFalse(BTGameNodeWithChild* parentNode, BehaviorTreeGame* behaviorTree);

    bool Run() override;
};

