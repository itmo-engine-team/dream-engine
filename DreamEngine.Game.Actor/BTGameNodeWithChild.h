#pragma once

#include "BTGameNode.h"

class BTGameNodeWithChild : public BTGameNode
{

public:

    BTGameNodeWithChild() = delete;

    virtual void AddChildNode(BTGameNode* childNod) = 0;

protected:

    BTGameNodeWithChild(BehaviorTreeGame* behaviorTree) : BTGameNode(behaviorTree) {};
    BTGameNodeWithChild(BTGameNodeWithChild* parentNode, BehaviorTreeGame* behaviorTree) : BTGameNode(parentNode, behaviorTree) {};
};

