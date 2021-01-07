#pragma once

#include "BTGameNode.h"

class BTGameNodeWithChild : public BTGameNode
{

public:

    BTGameNodeWithChild() = delete;
    BTGameNodeWithChild(BehaviorTreeGame* behaviorTree) : BTGameNode(behaviorTree){};
    BTGameNodeWithChild(BTGameNodeWithChild* parentNode, BehaviorTreeGame* behaviorTree) : BTGameNode(parentNode, behaviorTree){};

    virtual void AddChildNode(BTGameNode* childNod) = 0;
};

