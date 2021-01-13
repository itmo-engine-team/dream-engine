#pragma once
#include "BTGameNodeLogic.h"
class BTGReturnTrue : public BTGameNodeLogic
{

public:

    BTGReturnTrue() = delete;
    BTGReturnTrue(BTGameNodeWithChild* parentNode, BehaviorTreeGame* behaviorTree);

    bool Run() override;
};

