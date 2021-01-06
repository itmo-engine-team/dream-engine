#pragma once

#include "BTGameNodeComposite.h"

class BTGameNodeSelector : public BTGameNodeComposite
{

public:

    BTGameNodeSelector() = delete;
    BTGameNodeSelector(BTGameNodeComposite* parentNode, BehaviorTreeGame* behaviorTree);
    BTGameNodeSelector(BTGameNodeRoot* parentNode, BehaviorTreeGame* behaviorTree);

    bool Run() override;

};

