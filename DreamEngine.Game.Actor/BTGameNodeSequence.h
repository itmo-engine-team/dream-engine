#pragma once

#include "BTGameNodeComposite.h"

class BTGameNodeSequence : public BTGameNodeComposite
{

public:

    BTGameNodeSequence() = delete;
    BTGameNodeSequence(BTGameNodeRoot* parentNode, BehaviorTreeGame* behaviorTree);
    BTGameNodeSequence(BTGameNodeComposite* parentNode, BehaviorTreeGame* behaviorTree);

    bool Run() override;
};

