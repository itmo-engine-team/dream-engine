#pragma once

#include "BTGameNode.h"

class BTGameNodeLogic : public BTGameNode
{

public:

    BTGameNodeLogic() = delete;
    BTGameNodeLogic(BTGameNodeRoot* parentNode, BehaviorTreeGame* behaviorTree);
    BTGameNodeLogic(BTGameNodeComposite* parentNode, BehaviorTreeGame* behaviorTree);

};

