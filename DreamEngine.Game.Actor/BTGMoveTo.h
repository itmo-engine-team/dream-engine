#pragma once

#include "BTGameNodeLogic.h"

class BTGMoveTo : public BTGameNodeLogic
{
    BTGMoveTo() = delete;
    BTGMoveTo(BTGameNodeRoot* parentNode, BehaviorTreeGame* behaviorTree);
    BTGMoveTo(BTGameNodeComposite* parentNode, BehaviorTreeGame* behaviorTree);

    bool Run() override;
};

