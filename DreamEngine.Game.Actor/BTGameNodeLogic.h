#pragma once

#include "BTGameNode.h"

class BTGameNodeLogic : public BTGameNode
{

public:

    BTGameNodeLogic() = delete;
    BTGameNodeLogic(BTGameNodeWithChild* parentNode, BehaviorTreeGame* behaviorTree);

};

