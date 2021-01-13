#pragma once

#include "BTGameNodeComposite.h"

class BTGameNodeSelector : public BTGameNodeComposite
{

public:

    BTGameNodeSelector() = delete;
    BTGameNodeSelector(BTGameNodeWithChild* parentNode, BehaviorTreeGame* behaviorTree);

    bool Run() override;

};

