#pragma once

#include "BTGameNodeComposite.h"

class BTGameNodeSequence : public BTGameNodeComposite
{

public:

    BTGameNodeSequence() = delete;
    BTGameNodeSequence(BTGameNodeWithChild* parentNode, BehaviorTreeGame* behaviorTree);

    bool Run() override;
};

