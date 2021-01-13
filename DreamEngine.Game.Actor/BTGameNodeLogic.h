#pragma once

#include "BTGameNode.h"

class BTGameNodeLogic : public BTGameNode
{

protected:

    BTGameNodeLogic() = delete;
    BTGameNodeLogic(BTGameNodeWithChild* parentNode, BehaviorTreeGame* behaviorTree);
};

